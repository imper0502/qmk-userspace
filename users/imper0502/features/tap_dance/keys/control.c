#include "imper0502.h"

#if IMPER0502_TD_THUMB
static td_state_t td_control_state;

void td_control_finished(tap_dance_state_t *state, void *user_data) {
    td_control_state = current_dance(state);
    switch (td_control_state)
    {
    case TD_HOLD_3:
        layer_invert(_MK);
        break;
    case TD_HOLD_2:
        register_mods(MOD_LALT|MOD_LSFT);
        break;
    case DUAL_TAP:
    case TRI_TAP:
        for (uint8_t i = 1; i < state->count; i++) {
            tap_code(KC_LCTL);
        }
        register_mods(MOD_LCTL);
        break;
    default:
        register_mods(MOD_LCTL);
        break;
    }
    return;
}

void td_control_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_control_state)
    {
    case TD_HOLD_3:
        layer_invert(_MK);
        break;
    case TD_HOLD_2:
        unregister_mods(MOD_LALT|MOD_LSFT);
        break;
    default:
        unregister_mods(MOD_LCTL);
        return;
    }
    return;
}
#endif
