/* TD_BSLS. Built when IMPER0502_TD_BACKSLASH is 1. */

#include "imper0502.h"

#if IMPER0502_TD_BACKSLASH
static td_state_t td_backslash_state;

void td_backslash_finished(tap_dance_state_t *state, void *user_data) {
    td_backslash_state = current_dance(state);
    switch (td_backslash_state) {
        case TAPPING ... JUST_HOLD:           
            if (IS_LAYER_OFF(_QW)) {
                register_mods(MOD_LCTL);
                layer_on(_FN);
            } else {
                register_code(KC_BSLS);
            }
            break;
        case DUAL_TAPPING ... TAP_AND_HOLD:
            if (IS_LAYER_OFF(_QW)) {
                register_mods(MOD_LSFT|MOD_LCTL);
                layer_on(_FN);
            } else {
                tap_code(KC_BSLS);
                register_code(KC_BSLS);
            }
            break;
        case TRI_TAPPING ... TAP_TAP_HOLD:
            if (IS_LAYER_OFF(_QW)) {
                register_mods(MOD_LSFT);
                layer_on(_FN);
            } else {
                tap_code(KC_BSLS);
                tap_code(KC_BSLS);
                register_code(KC_BSLS);
            }
            break;
        case TRI_TAP:
            tap_code(KC_BSLS);
        case DUAL_TAP:
            tap_code(KC_BSLS);
        case JUST_TAP:
        default:
            register_code(KC_BSLS); 
            return;
    }
    return;
}

void td_backslash_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_backslash_state) {
        case TAPPING ... JUST_HOLD:
            if (IS_LAYER_OFF(_QW)) {
                layer_off(_FN); 
                unregister_mods(MOD_LCTL);
            } else {
                unregister_code(KC_BSLS);
            }
            break;
        case DUAL_TAPPING ... TAP_AND_HOLD:
            if (IS_LAYER_OFF(_QW)) {
                layer_off(_FN);
                unregister_mods(MOD_LSFT|MOD_LCTL);
            } else {
                unregister_code(KC_BSLS);
            }
            break;
        case TRI_TAPPING ... TAP_TAP_HOLD:
            if (IS_LAYER_OFF(_QW)) {
                layer_off(_FN);
                unregister_mods(MOD_LSFT);
            } else {
                unregister_code(KC_BSLS);
            }
            break;
        default:
            unregister_code(KC_BSLS);
            return;
    }
    return;
}
#endif
