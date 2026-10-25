/* Tap Dance */
#pragma once

enum tap_dance_names {
#ifdef THUMB_DANCE_ENABLE
    CONTROL_DANCE,
    ENTER_DANCE,
    SPACE_DANCE,
#endif
#ifdef ALT_PLUS_DANCE_ENABLE
    ALT_PLUS,
#endif
#ifdef MINUS_DANCE_ENABLE
    MINUS_DANCE,
#endif
#ifdef GRAVE_DANCE_ENABLE
    GRAVE_DANCE,
#endif
#ifdef BACKSLASH_DANCE_ENABLE
    BACKSLASH_DANCE,
#endif
#ifdef TABLE_DANCE_ENABLE
    TABLE_DANCE,
#endif
#ifdef INSERT_PLUS_DANCE_ENABLE 
    INSERT_PLUS,
#endif
#ifdef ALT_TABLE_DANCE_ENABLE    
    ALT_TABLE,
#endif
    COMMA_DANCE,
    DOT_DANCE,
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

#ifdef THUMB_DANCE_ENABLE
void td_left_control_finished(tap_dance_state_t *state, void *user_data);
void td_left_control_plus_reset(tap_dance_state_t *state, void *user_data);

void td_enter_finished(tap_dance_state_t *state, void *user_data);
void td_enter_reset(tap_dance_state_t *state, void *user_data);

void td_space_each_tap(tap_dance_state_t *state, void *user_data);
void td_space_finished(tap_dance_state_t *state, void *user_data);
void td_space_reset(tap_dance_state_t *state, void *user_data);
#endif
#ifdef ALT_PLUS_DANCE_ENABLE
void td_alt_plus_finished(tap_dance_state_t *state, void *user_data);
void td_alt_plus_reset(tap_dance_state_t *state, void *user_data);
#endif

#ifdef MINUS_DANCE_ENABLE
void td_minus_finished(tap_dance_state_t *state, void *user_data);
void td_minus_reset(tap_dance_state_t *state, void *user_data);
#endif
#ifdef GRAVE_DANCE_ENABLE
void td_grave_finished(tap_dance_state_t *state, void *user_data);
void td_grave_reset(tap_dance_state_t *state, void *user_data);
#endif
#ifdef BACKSLASH_DANCE_ENABLE
void td_backslash_finished(tap_dance_state_t *state, void *user_data);
void td_backslash_reset(tap_dance_state_t *state, void *user_data);
#endif
#ifdef TABLE_DANCE_ENABLE
void td_table_finished(tap_dance_state_t *state, void *user_data);
void td_table_reset(tap_dance_state_t *state, void *user_data);
#endif
#ifdef INSERT_PLUS_DANCE_ENABLE
void td_insert_plus_finished(tap_dance_state_t *state, void *user_data);
void td_insert_plus_reset(tap_dance_state_t *state, void *user_data);
#endif
#ifdef ALT_TABLE_DANCE_ENABLE
void td_alt_tab_each_tap(tap_dance_state_t *state, void *user_data);
void td_alt_tab_finished(tap_dance_state_t *state, void *user_data);
#endif

#ifdef THUMB_DANCE_ENABLE
#define TD_LCTL TD(CONTROL_DANCE)
#define TD_ENT  TD(ENTER_DANCE)
#define TD_SPC  TD(SPACE_DANCE)
#endif
