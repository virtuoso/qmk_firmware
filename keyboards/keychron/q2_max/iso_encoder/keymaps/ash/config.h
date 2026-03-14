#pragma once

/* Default RGB mode (solid red) */
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR

/* ---- Mousekey tuning (classic mode) ---- */
/* Delay before movement starts (ms) */
#define MOUSEKEY_DELAY 0

/* Interval between movement steps (ms); lower = smoother */
#define MOUSEKEY_INTERVAL 5

/* Pixels per step at maximum speed */
#define MOUSEKEY_MAX_SPEED 20

/* Steps to reach max speed; lower = more aggressive acceleration */
#define MOUSEKEY_TIME_TO_MAX 255

/* ---- Scroll wheel tuning ---- */
#define MOUSEKEY_WHEEL_DELAY 6
#define MOUSEKEY_WHEEL_INTERVAL 40
#define MOUSEKEY_WHEEL_MAX_SPEED 12
#define MOUSEKEY_WHEEL_TIME_TO_MAX 20

/* ---- Tap/hold tuning ---- */
/* Threshold (ms) for LT() and MT() tap vs hold */
//#define TAPPING_TERM 180

