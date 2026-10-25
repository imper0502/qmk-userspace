/* Per-key tapping term. */

#include "imper0502.h"

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#if IMPER0502_TD_ALT_TABLE
    case TD_TABA:
        return TAPPING_TERM * 4;
#endif
#if IMPER0502_TD_INSERT_PLUS
    case TD_INSP:
#endif
    case MT_BSPC:
    case LT_BTN3:
        return TAPPING_TERM - 64;
    default:
        return TAPPING_TERM;
    }
}
