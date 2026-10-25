/* TD_LCTL. Built when IMPER0502_TD_THUMB is 1. */

#include "imper0502.h"

#if IMPER0502_TD_THUMB
static td_state_t td_control_state;

void td_left_control_finished(tap_dance_state_t *state, void *user_data) {
    td_control_state = current_dance(state);
    switch (td_control_state)
    {
    case TRI_TAPPING ... TAP_TAP_HOLD:
        layer_invert(_MK);
        break;
    case DUAL_TAPPING ... TAP_AND_HOLD:
        register_mods(MOD_LSFT|MOD_LCTL);
        break;
    case TRI_TAP:
        tap_code(KC_LCTL);
    case DUAL_TAP:
        tap_code(KC_LCTL);
    default:
        register_mods(MOD_LCTL);
        return;
    }
    return;
}

void td_left_control_plus_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_control_state) 
    {
    case TRI_TAPPING ... TAP_TAP_HOLD:
        layer_invert(_MK); 
        break;
    case DUAL_TAPPING ... TAP_AND_HOLD:
        unregister_mods(MOD_LSFT|MOD_LCTL); 
        break;
    default:
        unregister_mods(MOD_LCTL);
        return;
    }
    return;
}
#endif
