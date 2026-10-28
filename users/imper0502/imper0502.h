/* Included by every shared .c file: only what that code itself needs (layers, idle and LT_BTN3).
 * Key macros for keymaps and the QMK tables live in keymap.h, which only keymap.c includes. */
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
#if IMPER0502_TD_THUMB || IMPER0502_TD_GRAVE
extern bool is_idle_timeout;
extern uint16_t is_idle_timer;
void idle_timer_task(void);
#else
#    define is_idle_timeout true
#endif

void led_indicators_task(void);


#define LT_BTN3 LT(_FN, MS_BTN3)

