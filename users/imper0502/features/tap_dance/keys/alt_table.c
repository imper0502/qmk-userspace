/* TD_TABA. Built when IMPER0502_TD_ALT_TABLE is 1. */

#include "imper0502.h"

#if IMPER0502_TD_ALT_TABLE
void td_alt_tab_each_tap(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1: add_mods(MOD_LALT);
        default:  tap_code(KC_TAB);
    }
}

void td_alt_tab_finished(tap_dance_state_t *state, void *user_data) {
    del_mods(MOD_LALT);
}
#endif
