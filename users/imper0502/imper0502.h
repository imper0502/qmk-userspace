#pragma once

#include QMK_KEYBOARD_H

#include "features/switches.h"

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
#    include "features/tap_dance/tap_dance.h"
#endif

/* Idle detection, see features/tap_dance/idle_timer.c */
#if IMPER0502_TD_THUMB
extern bool is_idle_timeout;
extern uint16_t is_idle_timer;
void idle_timer_task(void);
#else
#    define is_idle_timeout true
#endif

void led_indicators_task(void);

#define MT_BSPC ALT_T(KC_BSPC)

#define LT_BTN3 LT(_FN, MS_BTN3)

#if IMPER0502_TD_INSERT_PLUS
#define TD_INSP TD(INSERT_PLUS)
#endif
#if IMPER0502_TD_ALT_PLUS
#define TD_ALTP TD(ALT_PLUS)
#endif
#if IMPER0502_TD_ALT_TABLE
#define TD_TABA TD(ALT_TABLE)
#endif
