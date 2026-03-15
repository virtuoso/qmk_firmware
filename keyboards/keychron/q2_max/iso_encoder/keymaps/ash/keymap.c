/* Copyright 2023 ~ 2025 @ Keychron (https://www.keychron.com)
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

#include QMK_KEYBOARD_H
#include "keychron_common.h"

#define KC_MS_BTN1 QK_MOUSE_BUTTON_1
#define KC_MS_BTN2 QK_MOUSE_BUTTON_2
#define KC_MS_UP QK_MOUSE_CURSOR_UP
#define KC_MS_DOWN QK_MOUSE_CURSOR_DOWN
#define KC_MS_LEFT QK_MOUSE_CURSOR_LEFT
#define KC_MS_RIGHT QK_MOUSE_CURSOR_RIGHT
#define KC_MS_WH_UP QK_MOUSE_WHEEL_UP
#define KC_MS_WH_DOWN QK_MOUSE_WHEEL_DOWN
#define KC_MS_WH_LEFT QK_MOUSE_WHEEL_LEFT
#define KC_MS_WH_RIGHT QK_MOUSE_WHEEL_RIGHT
#define MAGIC_TOGGLE_NKRO QK_MAGIC_TOGGLE_NKRO


enum layers {
    MAC_BASE,
    WIN_BASE,
    MAC_FN1,
    WIN_FN1,
    _FN2,
};

#define FN1_MAC MO(MAC_FN1)
#define FN1_WIN MO(WIN_FN1)
#define FN2 MO(_FN2)

enum custom_keycodes {
    ASH_APPSW = SAFE_RANGE, /* Cmd+Tab */
    ASH_TERM,               /* Ctrl+4 then Cmd+1 for my vscode */
    ASH_HLS,                /* Cmd+D then Cmd+G, "highlight search" in vscode */
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case ASH_APPSW:
                tap_code16(LGUI(KC_TAB));
                return false;
            case ASH_TERM:
                tap_code16(LCTL(KC_4));
                tap_code16(LGUI(KC_1));
                return false;
            case ASH_HLS:
                tap_code16(LGUI(KC_H));
                tap_code16(LGUI(KC_U));
                return false;
        }
    }
    return true;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_iso_68(
        MT(MOD_LCTL,KC_ESC), KC_1       , KC_2      , KC_3      , KC_4  , KC_5  , KC_6              , KC_7      , KC_8      , KC_9      , KC_0      , KC_MINS   , KC_EQL            , KC_BSPC   , ASH_APPSW,
        KC_TAB             , KC_Q       , KC_W      , KC_E      , KC_R  , KC_T  , KC_Y              , KC_U      , KC_I      , KC_O      , KC_P      , KC_LBRC   , KC_RBRC           , KC_DEL    ,
        KC_LALT            , KC_A       , KC_S      , KC_D      , KC_F  , KC_G  , KC_H              , KC_J      , KC_K      , KC_L      , KC_SCLN   , KC_QUOT   , KC_NUHS           , KC_ENT    , KC_HOME,
        KC_LSFT            , KC_GRV     , KC_Z      , KC_X      , KC_C  , KC_V  , KC_B              , KC_N      , KC_M      , KC_COMM   , KC_DOT    , KC_SLSH   , LT(2,KC_MS_BTN2)  , KC_UP     ,
        KC_LCTL            , KC_LALT    , KC_LGUI   , KC_SPC    , MO(4) , MO(3) , LT(1,KC_MS_BTN1)  , KC_LEFT   , KC_DOWN   , KC_RGHT   ),

    [WIN_BASE] = LAYOUT_iso_68(
        KC_ESC            , KC_1              , KC_2              , KC_3              , KC_4              , KC_5              , KC_6              , KC_7              , KC_8              , KC_9              , KC_0              , LCTL(LGUI(KC_MINS)), LCTL(LGUI(KC_EQL)), KC_BSPC           , LGUI(KC_H)        ,
        KC_TAB            , KC_Q              , KC_W              , KC_E              , KC_R              , KC_T              , KC_Y              , LCTL(LGUI(KC_U))  , LCTL(LGUI(KC_I))  , LCTL(LGUI(KC_O))  , LCTL(LGUI(KC_P))  , LCTL(LGUI(KC_LBRC)), LCTL(LGUI(KC_RBRC)), LSA(KC_UP)        ,
        KC_CAPS           , DB_DEC            , DB_INC            , DB_CYCL           , DB_SHOW           , KC_G              , KC_H              , KC_J              , KC_K              , KC_L              , KC_SCLN           , KC_QUOT           , KC_NUHS           , KC_ENT            , LSA(KC_DOWN)      ,
        KC_LSFT           , KC_GRV            , KC_Z              , KC_X              , KC_C              , KC_V              , KC_B              , KC_N              , LSG(KC_M)         , LSG(KC_H)         , LSG(KC_D)         , LCTL(LSFT(KC_U))  , KC_RSFT           , LCTL(KC_UP)       ,
        KC_LCTL           , KC_LGUI           , KC_LALT           , KC_SPC            , KC_RALT           , MO(3)             , _______           , LCTL(KC_LEFT)     , LCTL(KC_DOWN)     , LCTL(KC_RGHT)     ),

    [MAC_FN1] = LAYOUT_iso_68(
        KC_GRV            , KC_BRID           , KC_BRIU           , KC_MCTRL          , KC_LNPAD          , UG_VALD           , UG_VALU           , KC_MPRV           , KC_MPLY           , KC_MNXT           , KC_MUTE           , KC_VOLD           , KC_VOLU           , _______           , ASH_HLS       ,
        _______           , BT_HST1           , BT_HST2           , BT_HST3           , P2P4G             , _______           , _______           , _______           , _______           , _______           , _______           , _______           , _______           , LAG(KC_UP)        ,
        UG_TOGG           , UG_NEXT           , UG_VALU           , UG_HUEU           , UG_SATU           , UG_SPDU           , _______           , _______           , _______           , _______           , _______           , _______           , _______           , _______           , LAG(KC_DOWN)      ,
        _______           , _______           , UG_PREV           , UG_VALD           , UG_HUED           , UG_SATD           , UG_SPDD           , _______           , _______           , _______           , _______           , _______           , _______           , KC_MS_WH_UP       ,
        _______           , _______           , _______           , _______           , _______           , _______           , _______           , KC_MS_WH_LEFT     , KC_MS_WH_DOWN     , KC_MS_WH_RIGHT    ),

    [WIN_FN1] = LAYOUT_iso_68(
        KC_GRV            , KC_BRID           , KC_BRIU           , KC_TASK           , KC_FILE           , UG_VALD           , UG_VALU           , KC_MPRV           , KC_MPLY           , KC_MNXT           , KC_MUTE           , KC_VOLD           , KC_VOLU           , KC_MS_BTN2        , UG_TOGG           ,
        _______           , BT_HST1           , BT_HST2           , BT_HST3           , P2P4G             , _______           , _______           , _______           , _______           , _______           , _______           , _______           , _______           , KC_HOME           ,
        _______           , _______           , _______           , _______           , _______           , _______           , _______           , _______           , _______           , _______           , _______           , _______           , _______           , KC_MS_BTN1        , KC_END            ,
        _______           , _______           , _______           , _______           , _______           , _______           , _______           , NK_TOGG,            _______           , _______           , _______           , _______           , KC_MS_BTN2        , KC_MS_UP          ,
        _______           , _______           , _______           , _______           , _______           , _______           , KC_MS_BTN1        , KC_MS_LEFT        , KC_MS_DOWN        , KC_MS_RIGHT       ),

    [_FN2] = LAYOUT_iso_68(
        S(KC_GRV)         , KC_F1             , KC_F2             , KC_F3             , KC_F4             , KC_F5             , KC_F6             , KC_F7             , KC_F8             , KC_F9             , KC_F10            , KC_F11            , KC_F12            , ASH_TERM       , _______           ,
        _______           , _______           , _______           , _______           , _______           , _______           , _______           , _______           , _______           , _______           , KC_F13            , KC_F14            , KC_F15            , KC_HOME           ,
        _______           , _______           , _______           , _______           , _______           , _______           , _______           , _______           , _______           , _______           , KC_F16            , KC_F17            , KC_F18            , _______           , KC_END            ,
        _______           , _______           , _______           , _______           , _______           , _______           , _______           , BAT_LVL           , _______           , _______           , _______           , _______           , _______           , KC_PGUP           ,
        _______           , _______           , _______           , LCTL(LGUI(KC_SPC)), _______           , _______           , _______           , LCTL(KC_A)        , KC_PGDN           , LCTL(KC_D)        ),

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [MAC_BASE] = { ENCODER_CCW_CW(QK_MOUSE_WHEEL_UP, QK_MOUSE_WHEEL_DOWN) },
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MAC_FN1]  = { ENCODER_CCW_CW(LALT(KC_LEFT), LALT(KC_RGHT)) },
    [WIN_FN1]  = { ENCODER_CCW_CW(UG_VALU, UG_VALD) },
    [_FN2]     = { ENCODER_CCW_CW(LCTL(LSFT(KC_TAB)), LCTL(KC_TAB)) },
};
#endif
