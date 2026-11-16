#include "imper0502.h"

#if IMPER0502_TD_THUMB
static td_state_t td_alt_state;

void td_alt_finished(tap_dance_state_t *state, void *user_data) {
    td_alt_state = current_dance(state);
    switch (td_alt_state)
    {
    case TD_HOLD_2:
        register_mods(MOD_LSFT|MOD_LCTL);
        break;
    case DUAL_TAP:
    case TRI_TAP:
        for (uint8_t i = 1; i < state->count; i++) {
            tap_code(KC_LALT);
        }
        register_mods(MOD_LALT);
        break;
    default:
        register_mods(MOD_LALT);
        break;
    }
    return;
}

void td_alt_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_alt_state)
    {
    case TD_HOLD_2:
        unregister_mods(MOD_LSFT|MOD_LCTL);
        break;
    default:
        unregister_mods(MOD_LALT);
        return;
    }
    return;
}
#endif
