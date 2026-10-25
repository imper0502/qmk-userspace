/* Included by keymap.c only: QMK reads the tables below from the keymap itself. */
#pragma once

#include "imper0502.h"

#ifdef TAP_DANCE_ENABLE
#    include "features/tap_dance/tap_dance_actions.h"
#endif

#ifdef KEY_OVERRIDE_ENABLE
#    include "features/key_override/key_overrides.h"
#endif

#ifdef COMBO_ENABLE
#    include "features/combo/combos.h"
#endif

#define WC_LEFT LWIN(C(KC_LEFT))
#define WC_RGHT LWIN(C(KC_RIGHT))

#define MT_ESC  GUI_T(KC_ESC)
#define MT_SLSH RGUI_T(KC_SLASH)
#define OS_LSFT OSM(MOD_LSFT)

#define LA_LCTL LALT(KC_LCTL)
#define RA_RCTL RALT(KC_RCTL)

#if IMPER0502_TD_MINUS
#define TD_MINS TD(MINUS_DANCE)
#endif
#if IMPER0502_TD_GRAVE
#define TD_GRV  TD(GRAVE_DANCE)
#endif
#if IMPER0502_TD_BACKSLASH
#define TD_BSLS TD(BACKSLASH_DANCE)
#endif
#if IMPER0502_TD_TABLE
#define TD_RTAB TD(TABLE_DANCE)
#endif
#if IMPER0502_TD_COMMA_DOT
#define TD_COMM TD(COMMA_DANCE)
#define TD_DOT  TD(DOT_DANCE)
#endif
