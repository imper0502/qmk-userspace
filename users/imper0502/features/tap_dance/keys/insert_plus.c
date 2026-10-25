/* TD_INSP. Built when IMPER0502_TD_INSERT_PLUS is 1. */

#include "imper0502.h"

#if IMPER0502_TD_INSERT_PLUS
static uint8_t mod_state;
static td_state_t td_state;
void td_insert_plus_finished(tap_dance_state_t *state, void *user_data) {
    mod_state = get_mods();
    td_state = current_dance(state);
    if (mod_state == 0) {
        switch (td_state) {
            case JUST_TAP: register_code16(C(KC_V)); return;
            case DUAL_TAP: register_code16(C(KC_A)); return;
            case TRI_TAP:       tap_code16(C(KC_A)); return;
            default:            tap_code16(C(KC_X)); return;
        }
    } else if (mod_state & (MOD_MASK_GUI | MOD_MASK_SHIFT)) {
        switch (td_state) {
            case JUST_TAP: register_code16(SWIN(KC_S)); return;
            default:      /* This line is necessary. */ return;
        }
    }
    register_code(KC_INS);
}

void td_insert_plus_reset(tap_dance_state_t *state, void *user_data) {
    if (mod_state == 0) {
        switch (td_state) {
            case JUST_TAP: unregister_code16(C(KC_V)); return;
            case DUAL_TAP: unregister_code16(C(KC_A)); return;
            default:              tap_code16(C(KC_V)); return;
        }
    } else if (mod_state & (MOD_MASK_GUI | MOD_MASK_SHIFT))  {
        switch (td_state) {
            case JUST_TAP: unregister_code16(SWIN(KC_S)); return;
            default:      /* This line is necessary. */   return;
        }
    }
    unregister_code(KC_INS);
}
#endif
