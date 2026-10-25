/* Included by keymap.c only: QMK reads the tables below from the keymap itself. */
#pragma once

#include "imper0502.h"

#ifdef TAP_DANCE_ENABLE
#    include "features/tap_dance_actions.h"
#endif

#ifdef KEY_OVERRIDE_ENABLE
#    include "features/key_overrides.h"
#endif

#ifdef COMBO_ENABLE
#    include "features/combos.h"
#endif

#define WC_LEFT LWIN(C(KC_LEFT))
#define WC_RGHT LWIN(C(KC_RIGHT))

#define MT_ESC  GUI_T(KC_ESC)
#define MT_SLSH RGUI_T(KC_SLASH)
#define OS_LSFT OSM(MOD_LSFT)

#define LA_LCTL LALT(KC_LCTL)
#define RA_RCTL RALT(KC_RCTL)

#ifdef MINUS_DANCE_ENABLE
#define TD_MINS TD(MINUS_DANCE)
#endif
#ifdef GRAVE_DANCE_ENABLE
#define TD_GRV  TD(GRAVE_DANCE)
#endif
#ifdef BACKSLASH_DANCE_ENABLE
#define TD_BSLS TD(BACKSLASH_DANCE)
#endif
#ifdef TABLE_DANCE_ENABLE
#define TD_RTAB TD(TABLE_DANCE)
#endif
