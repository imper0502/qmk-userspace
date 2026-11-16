#include "imper0502.h"

#if IMPER0502_TD_THUMB
#    ifndef CAPS_WORD_ENABLE
#        error "td_shift_finished uses Caps Word: set CAPS_WORD_ENABLE = yes in rules.mk"
#    endif
static uint8_t td_shift_mods;

void td_shift_finished(tap_dance_state_t *state, void *user_data) {
    td_shift_mods = 0;
    if (!state->pressed) {
        if (is_caps_word_on()) {
            caps_word_off();
        } else if (state->count == 1) {
            set_oneshot_mods(MOD_LSFT);
        } else {
            caps_word_on();
        }
        return;
    }
    td_shift_mods = (state->count == 1) ? MOD_LSFT : (MOD_LCTL | MOD_LALT);
    register_mods(td_shift_mods);
}

void td_shift_reset(tap_dance_state_t *state, void *user_data) {
    unregister_mods(td_shift_mods);
    td_shift_mods = 0;
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));
            return true;

        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case TD(SHIFT_DANCE):
        case TD(BACKSPACE_DANCE):
            return true;

        default:
            return false;
    }
}
#endif
