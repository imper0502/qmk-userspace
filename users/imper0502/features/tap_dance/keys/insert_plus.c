#include "imper0502.h"

#if IMPER0502_TD_INSERT_PLUS
static uint8_t td_insert_plus_mods;
static td_state_t td_insert_plus_state;

void td_insert_plus_finished(tap_dance_state_t *state, void *user_data) {
    td_insert_plus_mods = get_mods();
    td_insert_plus_state = current_dance(state);
    if (td_insert_plus_mods == 0) {
        switch (td_insert_plus_state) {
            case JUST_TAP: register_code16(C(KC_V)); return;
            case DUAL_TAP: register_code16(C(KC_A)); return;
            case TRI_TAP:       tap_code16(C(KC_A)); return;
            default:            tap_code16(C(KC_X)); return;
        }
    } else if (td_insert_plus_mods & MOD_MASK_GUI) {
        switch (td_insert_plus_state) {
            case JUST_TAP: register_code16(SWIN(KC_S)); return;
            default:                                    return;
        }
    }
    register_code(KC_INS);
}

void td_insert_plus_reset(tap_dance_state_t *state, void *user_data) {
    if (td_insert_plus_mods == 0) {
        switch (td_insert_plus_state) {
            case JUST_TAP: unregister_code16(C(KC_V)); return;
            case DUAL_TAP: unregister_code16(C(KC_A)); return;
            case TRI_TAP:                              return;
            default:              tap_code16(C(KC_V)); return;
        }
    } else if (td_insert_plus_mods & MOD_MASK_GUI)  {
        switch (td_insert_plus_state) {
            case JUST_TAP: unregister_code16(SWIN(KC_S)); return;
            default:                                      return;
        }
    }
    unregister_code(KC_INS);
}
#endif
