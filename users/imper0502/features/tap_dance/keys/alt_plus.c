/* TD_ALTP. Built when IMPER0502_TD_ALT_PLUS is 1. */

#include "imper0502.h"

#if IMPER0502_TD_ALT_PLUS
static td_state_t td_alt_plus_state;

void td_alt_plus_finished(tap_dance_state_t *state, void *user_data) {
    td_alt_plus_state = current_dance(state);
    switch (td_alt_plus_state) {
        case JUST_TAP:
        case TAPPING:
        case JUST_HOLD:     register_mods(MOD_BIT(KC_LALT)); return;
        case DUAL_TAP:
        case DUAL_TAPPING:  register_code(KC_CAPS);          return;
        case TAP_AND_HOLD:  layer_invert(_FN);               return;
        default:            /* This line is necessary. */    return;
    }
}

void td_alt_plus_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_alt_plus_state) {
        case JUST_TAP:
        case TAPPING:
        case JUST_HOLD:     unregister_mods(MOD_BIT(KC_LALT)); return;
        case DUAL_TAP:
        case DUAL_TAPPING:  unregister_code(KC_CAPS);          return;
        case TAP_AND_HOLD:  layer_invert(_FN);                 return;
        default:            /* This line is necessary. */      return;
    }
}
#endif
