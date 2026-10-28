/* Tap Dance */
#pragma once

enum tap_dance_names {
#if IMPER0502_TD_THUMB
    CONTROL_DANCE,
    ENTER_DANCE,
    SPACE_DANCE,
#endif
#if IMPER0502_TD_GRAVE
    GRAVE_DANCE,
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

/* The dance ended while the key was held, or cut short by another key, during the 1st, 2nd or 3rd press.
 * Use these in a case label rather than spelling the range out: they rely on the order of td_state_t above,
 * which tap_dance.c checks. */
#define TD_HOLD_1 TAPPING ... JUST_HOLD
#define TD_HOLD_2 DUAL_TAPPING ... TAP_AND_HOLD
#define TD_HOLD_3 TRI_TAPPING ... TAP_TAP_HOLD

td_state_t current_dance(tap_dance_state_t *state);

typedef struct {
    uint8_t keycode;
    uint8_t hold_mods;
    uint8_t tap_hold_mods;
    uint8_t mods;
    bool    layer;
} td_layer_t;

void td_layer_each_tap(tap_dance_state_t *state, void *user_data);
void td_layer_finished(tap_dance_state_t *state, void *user_data);
void td_layer_reset(tap_dance_state_t *state, void *user_data);

#if IMPER0502_TD_THUMB
void td_left_control_finished(tap_dance_state_t *state, void *user_data);
void td_left_control_plus_reset(tap_dance_state_t *state, void *user_data);

extern td_layer_t td_enter;
extern td_layer_t td_space;
#endif

#if IMPER0502_TD_GRAVE
extern td_layer_t td_grave;
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

