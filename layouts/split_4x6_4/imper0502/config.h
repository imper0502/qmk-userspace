#pragma once

#ifdef RXLED
    #define LED_CAPS_LOCK_PIN RXLED
#endif

/* One Shot Keys Config. */
#define ONESHOT_TIMEOUT 4096
#define ONESHOT_TAP_TOGGLE 4

/* Retro Tapping Config. */
#define RETRO_TAPPING
#define DUMMY_MOD_NEUTRALIZER_KEYCODE KC_RIGHT_CTRL
#define MODS_TO_NEUTRALIZE { MOD_BIT(KC_LEFT_ALT), MOD_BIT(KC_RIGHT_ALT), MOD_BIT(KC_LEFT_GUI), MOD_BIT(KC_RIGHT_GUI)}

/* Tap Dance Keys Toggle */
#define THUMB_DANCE_ENABLE
#define MINUS_DANCE_ENABLE false
#define GRAVE_DANCE_ENABLE true
#define BACKSLASH_DANCE_ENABLE false
#define TABLE_DANCE_ENABLE false
#define INSERT_PLUS_DANCE_ENABLE true
#define ALT_TABLE_DANCE_ENABLE false

/* Key Override Toggle (1 = on, 0 = off) */
#define PUNCT_OVERRIDE_ENABLE 1

/* Mouse Keys Config. */
#define MK_KINETIC_SPEED
#define MOUSEKEY_INTERVAL 32
#define MOUSEKEY_MOVE_DELTA 4
#define MOUSEKEY_INITIAL_SPEED 128
#define MOUSEKEY_ACCELERATED_SPEED 128
