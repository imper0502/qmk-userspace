/* Tap dance keys. They need TAP_DANCE_ENABLE = yes. */
#pragma once

#ifndef IMPER0502_TD_THUMB          /* TD_LCTL, TD_ENT, TD_SPC, TD_SFT */
#    define IMPER0502_TD_THUMB 1
#endif
#ifndef IMPER0502_TD_GRAVE          /* TD_GRV */
#    define IMPER0502_TD_GRAVE 1
#endif
#ifndef IMPER0502_TD_INSERT_PLUS    /* TD_INSP */
#    define IMPER0502_TD_INSERT_PLUS 0
#endif
#ifndef IMPER0502_TD_TABLE          /* TD_RTAB */
#    define IMPER0502_TD_TABLE 0
#endif
#ifndef IMPER0502_TD_ALT_TABLE      /* TD_TABA */
#    define IMPER0502_TD_ALT_TABLE 0
#endif
#ifndef IMPER0502_TD_COMMA_DOT      /* TD_COMM, TD_DOT */
#    define IMPER0502_TD_COMMA_DOT 0
#endif

#if !defined(TAP_DANCE_ENABLE) && (IMPER0502_TD_THUMB || IMPER0502_TD_GRAVE || IMPER0502_TD_INSERT_PLUS || IMPER0502_TD_TABLE || IMPER0502_TD_ALT_TABLE || IMPER0502_TD_COMMA_DOT)
#    error "IMPER0502_TD_* switches are on but TAP_DANCE_ENABLE is not yes: set TAP_DANCE_ENABLE = yes in rules.mk, or set those switches to 0 in config.h"
#endif
