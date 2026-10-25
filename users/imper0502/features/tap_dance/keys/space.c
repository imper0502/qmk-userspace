/* TD_SPC. Built when IMPER0502_TD_THUMB is 1. */

#include "imper0502.h"

#if IMPER0502_TD_THUMB
typedef struct {
    bool is_hold_on_action;
    td_state_t state;
} td_tap_t;

static td_tap_t td_space_tapping = {
    .is_hold_on_action = true,
    .state = OTHERWISE
};

void td_space_each_tap(tap_dance_state_t *state, void *user_data) {
    switch (state->count)
    {
    case 1 ... 2:
        break;
    case 3:
        tap_code(KC_SPACE);
    default:
        tap_code(KC_SPACE);
        break;
    }
    return;
}

void td_space_finished(tap_dance_state_t *state, void *user_data) {
    td_space_tapping.state = current_dance(state);
    switch (td_space_tapping.state)
    {
    case DUAL_TAPPING ... TAP_AND_HOLD:        
        register_mods(MOD_LSFT);
        layer_on(_FN);
        break;
    case DUAL_TAP:
        tap_code(KC_SPC);
        register_code(KC_SPC);
        break;
    case JUST_HOLD:       
        layer_on(_FN);
        break;
    case TAPPING:
        if (is_idle_timeout) {
            td_space_tapping.is_hold_on_action = true;
            layer_on(_FN);
        } else {
            td_space_tapping.is_hold_on_action = false;
            register_code(KC_SPC);
        }
        break;
    default:
        register_code(KC_SPC); 
        return;
    }
    return;
}

void td_space_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_space_tapping.state)
    {
    case DUAL_TAPPING ... TAP_AND_HOLD:
        layer_off(_FN);
        unregister_mods(MOD_LSFT);
        break;
    case JUST_HOLD:
        layer_off(_FN);
        break;
    case TAPPING:
        if (td_space_tapping.is_hold_on_action) {
            layer_off(_FN);
        } else {
            unregister_code(KC_SPC);
        }
        break;
    default:
        unregister_code(KC_SPC);
        return;
    }
    return;
}
#endif
