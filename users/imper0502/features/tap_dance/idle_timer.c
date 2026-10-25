/* Detects whether the keyboard has been idle for longer than TAPPING_TERM. Only the thumb tap dances read it. */

#include "imper0502.h"

#if IMPER0502_TD_THUMB
bool is_idle_timeout = true;
uint16_t is_idle_timer = 0;

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_BSPC:
    case MT_BSPC:
        return;
    case TO(_BS):
        clear_mods();
    default:
        if (!record->event.pressed) {
            is_idle_timeout = false;
            is_idle_timer = timer_read();
        }
        return;
    }
}

void idle_timer_task(void) {
    if (!is_idle_timeout) {
        is_idle_timeout = timer_elapsed(is_idle_timer) > TAPPING_TERM;
    }
}
#endif
