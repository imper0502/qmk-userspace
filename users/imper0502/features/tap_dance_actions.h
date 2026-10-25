/* Read by QMK from the keymap itself, so this is included by keymap.c only. */
#pragma once

tap_dance_action_t tap_dance_actions[] = {
#ifdef THUMB_DANCE_ENABLE
    [CONTROL_DANCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_left_control_finished, td_left_control_plus_reset),
    [ENTER_DANCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_enter_finished, td_enter_reset),
    [SPACE_DANCE] = ACTION_TAP_DANCE_FN_ADVANCED(td_space_each_tap, td_space_finished, td_space_reset),
#endif
#ifdef ALT_PLUS_DANCE_ENABLE
    [ALT_PLUS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_alt_plus_finished, td_alt_plus_reset),
#endif
#ifdef MINUS_DANCE_ENABLE
    [MINUS_DANCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_minus_finished, td_minus_reset),
#endif
#ifdef GRAVE_DANCE_ENABLE
    [GRAVE_DANCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_grave_finished, td_grave_reset),
#endif
#ifdef BACKSLASH_DANCE_ENABLE
    [BACKSLASH_DANCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_backslash_finished, td_backslash_reset),
#endif
#ifdef TABLE_DANCE_ENABLE
    [TABLE_DANCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_table_finished, td_table_reset),
#endif
#ifdef INSERT_PLUS_DANCE_ENABLE
    [INSERT_PLUS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_insert_plus_finished, td_insert_plus_reset),
#endif
#ifdef ALT_TABLE_DANCE_ENABLE
    [ALT_TABLE] = ACTION_TAP_DANCE_FN_ADVANCED(td_alt_tab_each_tap, td_alt_tab_finished, NULL),
#endif
    [COMMA_DANCE] = ACTION_TAP_DANCE_DOUBLE(KC_COMMA, KC_SEMICOLON),
    [DOT_DANCE] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_COLON)
};
