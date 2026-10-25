/* Feature switches: 1 = on, 0 = off.
 * Each folder under features/ owns the switches of one feature and their defaults.
 * Override a default with #define in a layout's config.h.
 * Always test switches with #if, never #ifdef: a switch defined as 0 is still "defined". */
#pragma once

#include "tap_dance/switches.h"
#include "key_override/switches.h"
