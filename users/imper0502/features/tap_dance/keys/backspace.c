#include "imper0502.h"

#if IMPER0502_TD_THUMB
static td_state_t td_backspace_state;

void td_backspace_finished(tap_dance_state_t *state, void *user_data) {
    td_backspace_state = current_dance(state);
    switch (td_backspace_state)
    {
    case TD_HOLD_2:
        register_mods(MOD_LCTL|MOD_LSFT);
        break;
    default:
        for (uint8_t i = 1; i < state->count; i++) {
            tap_code(KC_BSPC);
        }
        register_code(KC_BSPC);
        break;
    }
}

void td_backspace_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_backspace_state)
    {
    case TD_HOLD_2:
        unregister_mods(MOD_LCTL|MOD_LSFT);
        break;
    default:
        unregister_code(KC_BSPC);
        break;
    }
}
#endif
