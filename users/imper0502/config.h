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

/* Mouse Keys Config: a keyboard that sets its own speeds keeps them. */
#ifndef MK_KINETIC_SPEED
    #define MK_KINETIC_SPEED
#endif
#ifndef MOUSEKEY_INTERVAL
    #define MOUSEKEY_INTERVAL 32
#endif
#ifndef MOUSEKEY_MOVE_DELTA
    #define MOUSEKEY_MOVE_DELTA 4
#endif
#ifndef MOUSEKEY_INITIAL_SPEED
    #define MOUSEKEY_INITIAL_SPEED 128
#endif
#ifndef MOUSEKEY_ACCELERATED_SPEED
    #define MOUSEKEY_ACCELERATED_SPEED 128
#endif
