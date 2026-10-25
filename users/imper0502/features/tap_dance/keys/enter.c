/* TD_ENT. Built when IMPER0502_TD_THUMB is 1. */

#include "imper0502.h"

#if IMPER0502_TD_THUMB
static td_state_t td_enter_state;

void td_enter_finished(tap_dance_state_t *state, void *user_data) {
    td_enter_state = current_dance(state);
    switch (td_enter_state)
    {
    case DUAL_TAPPING ... TAP_AND_HOLD:
        register_mods(MOD_LSFT|MOD_LALT);
        layer_on(_FN);
        break;
    case TAPPING ... JUST_HOLD:
        register_mods(MOD_LALT);
        layer_on(_FN);
        break;
    case TRI_TAP:
        tap_code(KC_ENT);
    case DUAL_TAP:
        tap_code(KC_ENT);
    default:
        register_code(KC_ENT); 
        return;
    }
    return;
}

void td_enter_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_enter_state) 
    {    
    case DUAL_TAPPING ... TAP_AND_HOLD:
        layer_off(_FN);
        unregister_mods(MOD_LSFT|MOD_LALT);
        break;
    case TAPPING ... JUST_HOLD:
        layer_off(_FN);
        tap_code(KC_F18);
        unregister_mods(MOD_LALT);
        break;
    default:
        unregister_code(KC_ENT);
        return;
    }
    return;
}
#endif
