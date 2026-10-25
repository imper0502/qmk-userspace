#pragma once

#include QMK_KEYBOARD_H

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

enum layer_names {
    _BS,
    _QW,
    _NP,
    _MK,
    _FN
};

#ifdef TAP_DANCE_ENABLE
#    include "features/tap_dance.h"
#endif

/* Idle detection, see features/idle_timer.c */
extern bool is_idle_timeout;
extern uint16_t is_idle_timer;

#define MT_BSPC ALT_T(KC_BSPC)

#define LT_BTN3 LT(_FN, MS_BTN3)

#ifdef INSERT_PLUS_DANCE_ENABLE
#define TD_INSP TD(INSERT_PLUS)
#endif
#ifdef ALT_TABLE_DANCE_ENABLE
#define TD_TABA TD(ALT_TABLE)
#endif
