#include "imper0502.h"

#if IMPER0502_TD_TABLE
static td_state_t td_table_state;

void td_table_finished(tap_dance_state_t *state, void *user_data) {
    td_table_state = current_dance(state);
    switch (td_table_state) {
    case TD_HOLD_1:
        register_mods(MOD_LCTL);
        layer_on(_FN);
        break;
    case TD_HOLD_2:
        register_mods(MOD_LSFT|MOD_LCTL);
        layer_on(_FN);
        break;
    case TD_HOLD_3:
        register_mods(MOD_LSFT);
        layer_on(_FN);
        break;
    case DUAL_TAP:
    case TRI_TAP:
        for (uint8_t n = 1; n < state->count; n++) {
            tap_code(KC_TAB);
        }
        register_code(KC_TAB);
        break;
    default:
        register_code(KC_TAB);
        break;
    }
    return;
}

void td_table_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_table_state) {
    case TD_HOLD_1:
        layer_off(_FN);
        unregister_mods(MOD_LCTL);
        break;
    case TD_HOLD_2:
        layer_off(_FN);
        unregister_mods(MOD_LSFT|MOD_LCTL);
        break;
    case TD_HOLD_3:
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
