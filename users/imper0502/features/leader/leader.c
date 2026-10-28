#include "imper0502.h"

#ifdef LEADER_ENABLE
__attribute__ ((weak))
void leader_start_user(void) {
}

__attribute__ ((weak))
void leader_end_user(void) {
    if (leader_sequence_one_key(KC_F)) {
        SEND_STRING("QMK is awesome.");
    } else if (leader_sequence_two_keys(KC_D, KC_D)) {
        SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
    } else if (leader_sequence_three_keys(KC_D, KC_D, KC_S)) {
        SEND_STRING("https://start.duckduckgo.com\n");
    } else if (leader_sequence_two_keys(KC_A, KC_S)) {
        tap_code16(LGUI(KC_S));
    }
}
#endif
