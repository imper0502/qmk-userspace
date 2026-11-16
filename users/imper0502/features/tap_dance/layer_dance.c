#include "imper0502.h"

#if IMPER0502_TD_LAYER
static void td_layer_on(td_layer_t *key, uint8_t mods) {
    key->layer = true;
    key->mods = mods;
    register_mods(mods);
    layer_on(_FN);
}

void td_layer_each_tap(tap_dance_state_t *state, void *user_data) {
    td_layer_t *key = user_data;
    if (state->count < 3) {
        return;
    }
    tap_code(key->keycode);
    if (state->count == 3) {
        tap_code(key->keycode);
    }
}

void td_layer_finished(tap_dance_state_t *state, void *user_data) {
    td_layer_t *key = user_data;
    switch (current_dance(state)) {
    case TD_HOLD_2:
        td_layer_on(key, key->tap_hold_mods);
        return;
    case JUST_HOLD:
        td_layer_on(key, key->hold_mods);
        return;
    case TAPPING:
        if (is_idle_timeout) {
            td_layer_on(key, key->hold_mods);
            return;
        }
        break;
    case DUAL_TAP:
        tap_code(key->keycode);
        break;
    default:
        break;
    }
    key->layer = false;
    register_code(key->keycode);
}

void td_layer_reset(tap_dance_state_t *state, void *user_data) {
    td_layer_t *key = user_data;
    if (key->layer) {
        layer_off(_FN);
#ifdef DUMMY_MOD_NEUTRALIZER_KEYCODE
        neutralize_flashing_modifiers(get_mods());
#endif
        unregister_mods(key->mods);
    } else {
        unregister_code(key->keycode);
    }
}
#endif
