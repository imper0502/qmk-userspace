#pragma once

#include "test_common.h"

/* The tests are not built for a keyboard, so imper0502.h gets its QMK headers from here. */
#define QMK_KEYBOARD_H "quantum.h"

/* The tap dances under test. */
#define IMPER0502_TD_THUMB 1
#define IMPER0502_TD_GRAVE 1
#define IMPER0502_TD_EDGE 1
#define IMPER0502_TD_INSERT_PLUS 1
