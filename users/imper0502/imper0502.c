#include "imper0502.h"

__attribute__ ((weak))
void matrix_scan_user(void) {
#if IMPER0502_TD_THUMB || IMPER0502_TD_GRAVE
    idle_timer_task();
#endif
    led_indicators_task();
}

__attribute__ ((weak))
void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
    debug_enable = true;
    debug_matrix = true;
    debug_keyboard = true;
    debug_mouse = true;
#endif
}

__attribute__ ((weak))
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    dprintf(
        "KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n",
        keycode,
        record->event.key.col,
        record->event.key.row,
        record->event.pressed,
        record->event.time,
        record->tap.interrupted,
        record->tap.count
    );
#endif
    return true;
}
