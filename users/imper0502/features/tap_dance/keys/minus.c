/* TD_MINS. Built when IMPER0502_TD_MINUS is 1. */

#include "imper0502.h"

#if IMPER0502_TD_MINUS
static td_state_t td_minus_state;

void td_minus_finished(tap_dance_state_t *state, void *user_data) {
    td_minus_state = current_dance(state);
    switch (td_minus_state) {
        case JUST_TAP:
            if (!state->pressed) {
                register_code(KC_MINUS); break;
            }
            td_minus_state = JUST_HOLD;
        case JUST_HOLD:             
            register_mods(MOD_LCTL);
            layer_on(_FN);
            break;     
        case DUAL_TAP:     
            register_code(KC_EQUAL); break;
        case TAP_AND_HOLD: 
            register_mods(MOD_LSFT|MOD_LCTL);
            layer_on(_FN);
            break;
        default:
            return;
    }
    return;
}

void td_minus_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_minus_state) {
        case JUST_TAP:                 
            unregister_code(KC_MINUS); break;
        case JUST_HOLD: 
            layer_off(_FN);
            unregister_mods(MOD_LCTL); break;
        case DUAL_TAP:               
            unregister_code(KC_EQUAL); break;
        case TAP_AND_HOLD: 
            layer_off(_FN);
            unregister_mods(MOD_LSFT|MOD_LCTL);
            break;
        default:
            return;
    }
    return;
}
#endif
