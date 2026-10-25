/* TD_RTAB. Built when IMPER0502_TD_TABLE is 1. */

#include "imper0502.h"

#if IMPER0502_TD_TABLE
static td_state_t td_table_state;

void td_table_finished(tap_dance_state_t *state, void *user_data) {
    td_table_state = current_dance(state);
    switch (td_table_state) {
    case TAPPING ... JUST_HOLD:
        register_mods(MOD_LCTL);
        layer_on(_FN);
        break;
    case DUAL_TAPPING ... TAP_AND_HOLD:
        register_mods(MOD_LSFT|MOD_LCTL);
        layer_on(_FN);
        break;
    case TRI_TAPPING ... TAP_TAP_HOLD:
        register_mods(MOD_LSFT);
        layer_on(_FN);
        break;
    case TRI_TAP:
        tap_code(KC_TAB);
    case DUAL_TAP:
        tap_code(KC_TAB);
    case JUST_TAP:
    default:
        register_code(KC_TAB); 
        return;
    }
    return;
}

void td_table_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_table_state) {
    case TAPPING ... JUST_HOLD:
        layer_off(_FN); 
        unregister_mods(MOD_LCTL);
        break;
    case DUAL_TAPPING ... TAP_AND_HOLD:
        layer_off(_FN);
        unregister_mods(MOD_LSFT|MOD_LCTL);
        break;
    case TRI_TAPPING ... TAP_TAP_HOLD:
        layer_off(_FN);
        unregister_mods(MOD_LSFT);
        break;
    default:
        unregister_code(KC_TAB);
        return;
    }
    return;
}
#endif
