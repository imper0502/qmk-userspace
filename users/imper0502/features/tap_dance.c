/* Tap Dance */

#include "imper0502.h"

td_state_t current_dance(tap_dance_state_t *state) {
#ifdef CONSOLE_ENABLE
    dprintf(
        "TD: pressed: %u, int: %u, count: %u\n",
        state->pressed,
        state->interrupted,
        state->count
    );
#endif
    switch (state->count) {
        case 1:
            return state->interrupted
                    ? TAPPING
                    : state->pressed 
                        ? JUST_HOLD
                        : JUST_TAP;
        case 2:  
            return state->interrupted
                    ? DUAL_TAPPING
                    : state->pressed 
                            ? TAP_AND_HOLD 
                            : DUAL_TAP;
        case 3:  
            return state->interrupted
                    ? TRI_TAPPING
                    : state->pressed
                            ? TAP_TAP_HOLD
                            : TRI_TAP;
        case 4:  
            return (state->interrupted || !state->pressed)
                    ? QUAD_TAP 
                    : TRI_TAP_HOLD;
        default:
            return OTHERWISE;
    }
}
