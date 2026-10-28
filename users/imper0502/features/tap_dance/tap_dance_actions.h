/* Read by QMK from the keymap itself, so this is included by keymap.c only. */
#pragma once

#define TD_LAYER(key) {.fn = {td_layer_each_tap, td_layer_finished, td_layer_reset, NULL}, .user_data = (void *)&(key)}

tap_dance_action_t tap_dance_actions[] = {
#if IMPER0502_TD_THUMB
    [CONTROL_DANCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_left_control_finished, td_left_control_plus_reset),
    [ENTER_DANCE] = TD_LAYER(td_enter),
    [SPACE_DANCE] = TD_LAYER(td_space),
#endif
#if IMPER0502_TD_GRAVE
    [GRAVE_DANCE] = TD_LAYER(td_grave),
#endif
#if IMPER0502_TD_TABLE
    [TABLE_DANCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_table_finished, td_table_reset),
#endif
#if IMPER0502_TD_INSERT_PLUS
    [INSERT_PLUS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_insert_plus_finished, td_insert_plus_reset),
#endif
#if IMPER0502_TD_ALT_TABLE
    [ALT_TABLE] = ACTION_TAP_DANCE_FN_ADVANCED(td_alt_tab_each_tap, td_alt_tab_finished, NULL),
#endif
#if IMPER0502_TD_COMMA_DOT
    [COMMA_DANCE] = ACTION_TAP_DANCE_DOUBLE(KC_COMMA, KC_SEMICOLON),
    [DOT_DANCE] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_COLON),
#endif
};
