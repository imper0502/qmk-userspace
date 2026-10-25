/* Per-key tapping term. */

#include "imper0502.h"

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef ALT_TABLE_DANCE_ENABLE
    case TD_TABA:
        return TAPPING_TERM * 4;
#endif
#ifdef INSERT_PLUS_DANCE_ENABLE
    case TD_INSP:
#endif
    case MT_BSPC:
    case LT_BTN3:
        return TAPPING_TERM - 64;
    default:
        return TAPPING_TERM;
    }
}
