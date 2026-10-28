#pragma once

#ifdef RXLED
    #define LED_CAPS_LOCK_PIN RXLED
#endif

/* One Shot Keys Config. */
#define ONESHOT_TIMEOUT 4096

/* Retro Tapping Config. */
#define RETRO_TAPPING
#define DUMMY_MOD_NEUTRALIZER_KEYCODE KC_RIGHT_CTRL
#define MODS_TO_NEUTRALIZE { MOD_BIT(KC_LEFT_ALT), MOD_BIT(KC_RIGHT_ALT), MOD_BIT(KC_LEFT_GUI), MOD_BIT(KC_RIGHT_GUI)}

/* Feature switches: 1 = on, 0 = off. Defaults are in the switches.h in each folder of users/imper0502/features */
#define IMPER0502_TD_THUMB 1
#define IMPER0502_TD_GRAVE 1
#define IMPER0502_TD_INSERT_PLUS 1
#define IMPER0502_TD_TABLE 0
#define IMPER0502_TD_ALT_TABLE 0
#define IMPER0502_TD_COMMA_DOT 0
#define IMPER0502_OVERRIDE_PUNCT 0

/* Tapping Config. */
#define TAPPING_TERM 275
#define TAPPING_TERM_PER_KEY
#define TAPPING_FORCE_HOLD_PER_KEY
