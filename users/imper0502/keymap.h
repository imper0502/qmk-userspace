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
#define MT_QUOT LALT_T(KC_QUOT)
#define OS_LSFT OSM(MOD_LSFT)

#define LA_LCTL LALT(KC_LCTL)
#define LS_LCTL LSFT(KC_LCTL)
#define LA_LSFT LALT(KC_LSFT)

#define LT_SPC  LT(_FN, KC_SPACE)
#define LM_AFN  LM(_FN, MOD_LALT)
#define LM_CFN  LM(_FN, MOD_LCTL)
#define LM_ACFN LM(_FN, MOD_LALT | MOD_LCTL)
#define RA_RCTL RALT(KC_RCTL)

/* Tap dance keys: each exists only while its IMPER0502_TD_* switch is 1. */
#if IMPER0502_TD_THUMB
#define TD_LCTL TD(CONTROL_DANCE)
#define TD_ENT  TD(ENTER_DANCE)
#define TD_SPC  TD(SPACE_DANCE)
#endif
#if IMPER0502_TD_INSERT_PLUS
#define TD_INSP TD(INSERT_PLUS)
#endif
#if IMPER0502_TD_ALT_TABLE
#define TD_TABA TD(ALT_TABLE)
#endif
#if IMPER0502_TD_GRAVE
#define TD_GRV  TD(GRAVE_DANCE)
#endif
#if IMPER0502_TD_TABLE
#define TD_RTAB TD(TABLE_DANCE)
#endif
#if IMPER0502_TD_COMMA_DOT
#define TD_COMM TD(COMMA_DANCE)
#define TD_DOT  TD(DOT_DANCE)
#endif
