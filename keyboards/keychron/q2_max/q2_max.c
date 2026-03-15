/* Copyright 2024 ~ 2025 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "keychron.h"
#include "debounce/keychron_debounce.h"
#include "timer.h"

extern uint8_t debounce_type;
extern uint8_t debounce_time;

#ifndef DEBOUNCE_SHOW
#define DEBOUNCE_SHOW 2000
#endif /* DEBOUNCE_SHOW */

static uint16_t show_debounce_timer = 0;
static bool show_debounce_algo = false;
static bool show_debounce_time_ind = false;

#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_kb(uint8_t index, bool active) {
    if (index == 0) {
        default_layer_set(1UL << (active ? 2 : 0));
    }
    dip_switch_update_user(index, active);

    return true;
}
#endif

bool process_record_keychron_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case DB_CYCL:
            case 0x5C10: /* VIA legacy CUSTOM(16) fallback */
                debounce_type++;
                if (debounce_type >= DEBOUNCE_MAX) {
                    debounce_type = 0;
                }
                debounce_set(debounce_type, debounce_time, true);
                debounce_save();
                show_debounce_algo = true;
                show_debounce_time_ind = false;
                show_debounce_timer = timer_read();
                return false;
            case DB_SHOW:
            case 0x5C11: /* VIA legacy CUSTOM(17) fallback */
                show_debounce_algo = true;
                show_debounce_time_ind = true;
                show_debounce_timer = timer_read();
                return false;
            case DB_INC:
            case 0x5C12: /* VIA legacy CUSTOM(18) fallback */
                if (debounce_time <= 250) {
                    debounce_time += 5;
                    debounce_set(debounce_type, debounce_time, true);
                    debounce_save();
                }
                show_debounce_algo = false;
                show_debounce_time_ind = true;
                show_debounce_timer = timer_read();
                return false;
            case DB_DEC:
            case 0x5C13: // VIA legacy CUSTOM(19) fallback
                if (debounce_time >= 5) {
                    debounce_time -= 5;
                    debounce_set(debounce_type, debounce_time, true);
                    debounce_save();
                }
                show_debounce_algo = false;
                show_debounce_time_ind = true;
                show_debounce_timer = timer_read();
                return false;
        }
    }
    return true;
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_user(void) {
    if (show_debounce_algo || show_debounce_time_ind) {
        if (timer_elapsed(show_debounce_timer) > DEBOUNCE_SHOW) {
            show_debounce_algo = false;
            show_debounce_time_ind = false;
        } else {
            rgb_matrix_set_color_all(0, 0, 0);
            if (show_debounce_algo) {
                uint8_t led_index = debounce_type + MATRIX_COLS;
                if (led_index <= MATRIX_COLS * 2) {
                    rgb_matrix_set_color(led_index, 0, 0, 255); // Blue
                }
            }
            if (show_debounce_time_ind) {
                uint8_t step = debounce_time / 5;
                if (step > 0) {
                    uint8_t last_full = step / 2;
                    for (uint8_t i = 1; i <= last_full; i++) {
                        if (i <= 10) rgb_matrix_set_color(i, 0, 255, 0); // Green
                    }
                    if (step % 2 != 0) {
                        uint8_t half_led = last_full + 1;
                        if (half_led <= 10) rgb_matrix_set_color(half_led, 255, 0, 0); // Red
                    }
                }
            }
            return false;
        }
    }
    return true;
}
#endif

void keyboard_post_init_kb(void) {
    keychron_common_init();
    keyboard_post_init_user();
}

#ifdef LK_WIRELESS_ENABLE
bool lpm_is_kb_idle(void) {
    return !backlight_indicator_is_active();
}
#endif
