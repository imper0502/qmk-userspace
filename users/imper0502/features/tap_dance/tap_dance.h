/* Tap Dance */
#pragma once

enum tap_dance_names {
#if IMPER0502_TD_THUMB
    CONTROL_DANCE,
    ENTER_DANCE,
    SPACE_DANCE,
#endif
#if IMPER0502_TD_ALT_PLUS
    ALT_PLUS,
#endif
#if IMPER0502_TD_MINUS
    MINUS_DANCE,
#endif
#if IMPER0502_TD_GRAVE
    GRAVE_DANCE,
#endif
#if IMPER0502_TD_BACKSLASH
    BACKSLASH_DANCE,
#endif
#if IMPER0502_TD_TABLE
    TABLE_DANCE,
#endif
#if IMPER0502_TD_INSERT_PLUS
    INSERT_PLUS,
#endif
#if IMPER0502_TD_ALT_TABLE
    ALT_TABLE,
#endif
#if IMPER0502_TD_COMMA_DOT
    COMMA_DANCE,
    DOT_DANCE,
#endif
};

/* Tap Dance */
typedef enum {
    JUST_TAP, TAPPING     , JUST_HOLD   ,
    DUAL_TAP, DUAL_TAPPING, TAP_AND_HOLD,
    TRI_TAP , TRI_TAPPING , TAP_TAP_HOLD,
    QUAD_TAP,               TRI_TAP_HOLD, 
    OTHERWISE
} td_state_t;

td_state_t current_dance(tap_dance_state_t *state);

#if IMPER0502_TD_THUMB
void td_left_control_finished(tap_dance_state_t *state, void *user_data);
void td_left_control_plus_reset(tap_dance_state_t *state, void *user_data);

void td_enter_finished(tap_dance_state_t *state, void *user_data);
void td_enter_reset(tap_dance_state_t *state, void *user_data);

void td_space_each_tap(tap_dance_state_t *state, void *user_data);
void td_space_finished(tap_dance_state_t *state, void *user_data);
void td_space_reset(tap_dance_state_t *state, void *user_data);
#endif
#if IMPER0502_TD_ALT_PLUS
void td_alt_plus_finished(tap_dance_state_t *state, void *user_data);
void td_alt_plus_reset(tap_dance_state_t *state, void *user_data);
#endif

#if IMPER0502_TD_MINUS
void td_minus_finished(tap_dance_state_t *state, void *user_data);
void td_minus_reset(tap_dance_state_t *state, void *user_data);
#endif
#if IMPER0502_TD_GRAVE
void td_grave_finished(tap_dance_state_t *state, void *user_data);
void td_grave_reset(tap_dance_state_t *state, void *user_data);
#endif
#if IMPER0502_TD_BACKSLASH
void td_backslash_finished(tap_dance_state_t *state, void *user_data);
void td_backslash_reset(tap_dance_state_t *state, void *user_data);
#endif
#if IMPER0502_TD_TABLE
void td_table_finished(tap_dance_state_t *state, void *user_data);
void td_table_reset(tap_dance_state_t *state, void *user_data);
#endif
#if IMPER0502_TD_INSERT_PLUS
void td_insert_plus_finished(tap_dance_state_t *state, void *user_data);
void td_insert_plus_reset(tap_dance_state_t *state, void *user_data);
#endif
#if IMPER0502_TD_ALT_TABLE
void td_alt_tab_each_tap(tap_dance_state_t *state, void *user_data);
void td_alt_tab_finished(tap_dance_state_t *state, void *user_data);
#endif

#if IMPER0502_TD_THUMB
#define TD_LCTL TD(CONTROL_DANCE)
#define TD_ENT  TD(ENTER_DANCE)
#define TD_SPC  TD(SPACE_DANCE)
#endif
