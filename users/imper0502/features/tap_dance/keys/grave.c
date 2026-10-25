/* TD_GRV. Built when IMPER0502_TD_GRAVE is 1. */

#include "imper0502.h"

#if IMPER0502_TD_GRAVE
static td_state_t td_grave_state;

void td_grave_finished(tap_dance_state_t *state, void *user_data) {
    td_grave_state = current_dance(state);
    switch (td_grave_state) {
        case TAPPING ... JUST_HOLD:           
            register_mods(MOD_LCTL);
            layer_on(_FN);
            break;
        case DUAL_TAPPING ... TAP_AND_HOLD:
            register_mods(MOD_LSFT|MOD_LCTL);
            layer_on(_FN);
            break;
        case TRI_TAP:
            tap_code(KC_GRV);
        case DUAL_TAP:
            tap_code(KC_GRV);
        case JUST_TAP:
        default:
            register_code(KC_GRV); 
            return;
    }
    return;
}

void td_grave_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_grave_state) {
        case TAPPING ... JUST_HOLD:
            layer_off(_FN); 
            unregister_mods(MOD_LCTL);
            break;
        case DUAL_TAPPING ... TAP_AND_HOLD:
            layer_off(_FN);
            unregister_mods(MOD_LSFT|MOD_LCTL);
            break;
        default:
            unregister_code(KC_GRV);
            return;
    }
    return;
}
#endif
