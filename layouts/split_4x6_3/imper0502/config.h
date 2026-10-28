#pragma once

#ifdef RXLED
    #define LED_CAPS_LOCK_PIN RXLED
#endif

/* One Shot Keys Config. */
#define ONESHOT_TIMEOUT 4096

/* Retro Tapping Config. */
#define RETRO_TAPPING
#define DUMMY_MOD_NEUTRALIZER_KEYCODE KC_RIGHT_CTRL

/* Feature switches: 1 = on, 0 = off. Defaults are in the switches.h in each folder of users/imper0502/features */
#define IMPER0502_TD_THUMB 1
#define IMPER0502_TD_GRAVE 1
#define IMPER0502_TD_EDGE 1
#define IMPER0502_TD_INSERT_PLUS 0
#define IMPER0502_TD_TABLE 0
#define IMPER0502_TD_ALT_TABLE 0
#define IMPER0502_TD_COMMA_DOT 0
#define IMPER0502_OVERRIDE_PUNCT 0

/* Mouse Keys Config. */
#define MK_KINETIC_SPEED
#define MOUSEKEY_INTERVAL 32
#define MOUSEKEY_MOVE_DELTA 4
#define MOUSEKEY_INITIAL_SPEED 128
#define MOUSEKEY_ACCELERATED_SPEED 128
