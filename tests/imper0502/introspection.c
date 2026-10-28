/* QMK reads tap_dance_actions[] from the keymap, so the code under test is built into it. */
#include "quantum.h"
#include "imper0502.h"
#include "features/tap_dance/tap_dance_actions.h"
#include "features/tap_dance/tap_dance.c"
#include "features/tap_dance/layer_dance.c"
#include "features/tap_dance/keys/control.c"
#include "features/tap_dance/keys/enter.c"
#include "features/tap_dance/keys/space.c"
#include "features/tap_dance/keys/shift.c"
#include "features/tap_dance/keys/backspace.c"
#include "features/tap_dance/keys/grave.c"
#include "features/tap_dance/keys/insert_plus.c"
#include "features/tap_dance/idle_timer.c"

void matrix_scan_user(void) {
    idle_timer_task();
}
