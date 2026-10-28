/* Per-key tapping term. */

#include "imper0502.h"

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#if IMPER0502_TD_ALT_TABLE
    case TD(ALT_TABLE):
        return TAPPING_TERM * 4;
#endif
#if IMPER0502_TD_THUMB
    case TD(CONTROL_DANCE):
    case TD(ENTER_DANCE):
    case TD(SPACE_DANCE):
    case TD(SHIFT_DANCE):
    case TD(BACKSPACE_DANCE):
#endif
#if IMPER0502_TD_GRAVE
    case TD(GRAVE_DANCE):
#endif
#if IMPER0502_TD_EDGE
    case TD(QUOTE_DANCE):
    case TD(BACKSLASH_DANCE):
#endif
#if IMPER0502_TD_INSERT_PLUS
    case TD(INSERT_PLUS):
#endif
    case LT_BTN3:
        return TAPPING_TERM - 64;
    default:
        return TAPPING_TERM;
    }
}
