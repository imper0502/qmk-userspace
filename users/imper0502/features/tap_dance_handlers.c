/* Tap dance handlers declared in tap_dance.h. */

#include "imper0502.h"

/* Tap Dance Behavior */
static td_state_t td_control_state;

void td_left_control_finished(tap_dance_state_t *state, void *user_data) {
    td_control_state = current_dance(state);
    switch (td_control_state)
    {
    case TRI_TAPPING ... TAP_TAP_HOLD:
        layer_invert(_MK);
        break;
    case DUAL_TAPPING ... TAP_AND_HOLD:
        register_mods(MOD_LSFT|MOD_LCTL);
        break;
    case TRI_TAP:
        tap_code(KC_LCTL);
    case DUAL_TAP:
        tap_code(KC_LCTL);
    default:
        register_mods(MOD_LCTL);
        return;
    }
    return;
}

void td_left_control_plus_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_control_state) 
    {
    case TRI_TAP ... TAP_TAP_HOLD: 
        layer_invert(_MK); 
        break;
    case DUAL_TAPPING ... TAP_AND_HOLD:
        unregister_mods(MOD_LSFT|MOD_LCTL); 
        break;
    default:
        unregister_mods(MOD_LCTL);
        return;
    }
    return;
}

static td_state_t td_enter_state;

void td_enter_finished(tap_dance_state_t *state, void *user_data) {
    td_enter_state = current_dance(state);
    switch (td_enter_state)
    {
    case DUAL_TAPPING ... TAP_AND_HOLD:
        register_mods(MOD_LSFT|MOD_LALT);
        layer_on(_FN);
        break;
    case TAPPING ... JUST_HOLD:
        register_mods(MOD_LALT);
        layer_on(_FN);
        break;
    case TRI_TAP:
        tap_code(KC_ENT);
    case DUAL_TAP:
        tap_code(KC_ENT);
    default:
        register_code(KC_ENT); 
        return;
    }
    return;
}

void td_enter_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_enter_state) 
    {    
    case DUAL_TAPPING ... TAP_AND_HOLD:
        layer_off(_FN);
        unregister_mods(MOD_LSFT|MOD_LALT);
        break;
    case TAPPING ... JUST_HOLD:
        layer_off(_FN);
        tap_code(KC_F18);
        unregister_mods(MOD_LALT);
        break;
    default:
        unregister_code(KC_ENT);
        return;
    }
    return;
}

typedef struct {
    bool is_hold_on_action;
    td_state_t state;
} td_tap_t;

static td_tap_t td_space_tapping = {
    .is_hold_on_action = true,
    .state = OTHERWISE
};

void td_space_each_tap(tap_dance_state_t *state, void *user_data) {
    switch (state->count)
    {
    case 1 ... 2:
        break;
    case 3:
        tap_code(KC_SPACE);
    default:
        tap_code(KC_SPACE);
        break;
    }
    return;
}

void td_space_finished(tap_dance_state_t *state, void *user_data) {
    td_space_tapping.state = current_dance(state);
    switch (td_space_tapping.state)
    {
    case DUAL_TAPPING ... TAP_AND_HOLD:        
        register_mods(MOD_LSFT);
        layer_on(_FN);
        break;
    case DUAL_TAP:
        tap_code(KC_SPC);
        register_code(KC_SPC);
        break;
    case JUST_HOLD:       
        layer_on(_FN);
        break;
    case TAPPING:
        if (is_idle_timeout) {
            td_space_tapping.is_hold_on_action = true;
            layer_on(_FN);
        } else {
            td_space_tapping.is_hold_on_action = false;
            register_code(KC_SPC);
        }
        break;
    default:
        register_code(KC_SPC); 
        return;
    }
    return;
}

void td_space_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_space_tapping.state)
    {
    case DUAL_TAPPING ... TAP_AND_HOLD:
        layer_off(_FN);
        unregister_mods(MOD_LSFT);
        break;
    case JUST_HOLD:
        layer_off(_FN);
        break;
    case TAPPING:
        if (td_space_tapping.is_hold_on_action) {
            layer_off(_FN);
        } else {
            unregister_code(KC_SPC);
        }
        break;
    default:
        unregister_code(KC_SPC);
        return;
    }
    return;
}

#ifdef MINUS_DANCE_ENABLE
static td_state_t td_minus_state;

void td_minus_finished(tap_dance_state_t *state, void *user_data) {
    td_minus_state = current_dance(state);
    switch (td_minus_state) {
        case JUST_TAP:
            if (!state->pressed) {
                register_code(KC_MINUS); break;
            }
            td_minus_state = JUST_HOLD;
        case JUST_HOLD:             
            register_mods(MOD_LCTL);
            layer_on(_FN);
            break;     
        case DUAL_TAP:     
            register_code(KC_EQUAL); break;
        case TAP_AND_HOLD: 
            register_mods(MOD_LSFT|MOD_LCTL);
            layer_on(_FN);
            break;
        default:
            return;
    }
    return;
}

void td_minus_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_minus_state) {
        case JUST_TAP:                 
            unregister_code(KC_MINUS); break;
        case JUST_HOLD: 
            layer_off(_FN);
            unregister_mods(MOD_LCTL); break;
        case DUAL_TAP:               
            unregister_code(KC_EQUAL); break;
        case TAP_AND_HOLD: 
            layer_off(_FN);
            unregister_mods(MOD_LSFT|MOD_LCTL);
            break;
        default:
            return;
    }
    return;
}
#endif

#ifdef GRAVE_DANCE_ENABLE
static td_state_t td_grave_state;

void td_grave_finished(tap_dance_state_t *state, void *user_data) {
    td_grave_state = current_dance(state);
    switch (td_grave_state) {
        case TAPPING ... JUST_HOLD:           
            register_mods(MOD_LCTL);
            layer_on(_FN);
            break;
        case DUAL_TAPPING ... TAP_AND_HOLD:
            register_mods(MOD_LSFT|MOD_LCTL);
            layer_on(_FN);
            break;
        case TRI_TAP:
            tap_code(KC_GRV);
        case DUAL_TAP:
            tap_code(KC_GRV);
        case JUST_TAP:
        default:
            register_code(KC_GRV); 
            return;
    }
    return;
}

void td_grave_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_grave_state) {
        case TAPPING ... JUST_HOLD:
            layer_off(_FN); 
            unregister_mods(MOD_LCTL);
            break;
        case DUAL_TAPPING ... TAP_AND_HOLD:
            layer_off(_FN);
            unregister_mods(MOD_LSFT|MOD_LCTL);
            break;
        default:
            unregister_code(KC_GRV);
            return;
    }
    return;
}
#endif

#ifdef BACKSLASH_DANCE_ENABLE
static td_state_t td_backslash_state;

void td_backslash_finished(tap_dance_state_t *state, void *user_data) {
    td_backslash_state = current_dance(state);
    switch (td_backslash_state) {
        case TAPPING ... JUST_HOLD:           
            if (IS_LAYER_OFF(_QW)) {
                register_mods(MOD_LCTL);
                layer_on(_FN);
            } else {
                register_code(KC_BSLS);
            }
            break;
        case DUAL_TAPPING ... TAP_AND_HOLD:
            if (IS_LAYER_OFF(_QW)) {
                register_mods(MOD_LSFT|MOD_LCTL);
                layer_on(_FN);
            } else {
                tap_code(KC_BSLS);
                register_code(KC_BSLS);
            }
            break;
        case TRI_TAPPING ... TAP_TAP_HOLD:
            if (IS_LAYER_OFF(_QW)) {
                register_mods(MOD_LSFT);
                layer_on(_FN);
            } else {
                tap_code(KC_BSLS);
                tap_code(KC_BSLS);
                register_code(KC_BSLS);
            }
            break;
        case TRI_TAP:
            tap_code(KC_BSLS);
        case DUAL_TAP:
            tap_code(KC_BSLS);
        case JUST_TAP:
        default:
            register_code(KC_BSLS); 
            return;
    }
    return;
}

void td_backslash_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_backslash_state) {
        case TAPPING ... JUST_HOLD:
            if (IS_LAYER_OFF(_QW)) {
                layer_off(_FN); 
                unregister_mods(MOD_LCTL);
            } else {
                unregister_code(KC_BSLS);
            }
            break;
        case DUAL_TAPPING ... TAP_AND_HOLD:
            if (IS_LAYER_OFF(_QW)) {
                layer_off(_FN);
                unregister_mods(MOD_LSFT|MOD_LCTL);
            } else {
                unregister_code(KC_BSLS);
            }
            break;
        case TRI_TAPPING ... TAP_TAP_HOLD:
            if (IS_LAYER_OFF(_QW)) {
                layer_off(_FN);
                unregister_mods(MOD_LSFT);
            } else {
                unregister_code(KC_BSLS);
            }
            break;
        default:
            unregister_code(KC_BSLS);
            return;
    }
    return;
}
#endif

#ifdef TABLE_DANCE_ENABLE
static td_state_t td_table_state;

void td_table_finished(tap_dance_state_t *state, void *user_data) {
    td_table_state = current_dance(state);
    switch (td_table_state) {
    case TAPPING ... JUST_HOLD:
        register_mods(MOD_LCTL);
        layer_on(_FN);
        break;
    case DUAL_TAPPING ... TAP_AND_HOLD:
        register_mods(MOD_LSFT|MOD_LCTL);
        layer_on(_FN);
        break;
    case TRI_TAPPING ... TAP_TAP_HOLD:
        register_mods(MOD_LSFT);
        layer_on(_FN);
        break;
    case TRI_TAP:
        tap_code(KC_TAB);
    case DUAL_TAP:
        tap_code(KC_TAB);
    case JUST_TAP:
    default:
        register_code(KC_TAB); 
        return;
    }
    return;
}

void td_table_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_table_state) {
    case TAPPING ... JUST_HOLD:
        layer_off(_FN); 
        unregister_mods(MOD_LCTL);
        break;
    case DUAL_TAPPING ... TAP_AND_HOLD:
        layer_off(_FN);
        unregister_mods(MOD_LSFT|MOD_LCTL);
        break;
    case TRI_TAPPING ... TAP_TAP_HOLD:
        layer_off(_FN);
        unregister_mods(MOD_LSFT);
        break;
    default:
        unregister_code(KC_TAB);
        return;
    }
    return;
}
#endif

#ifdef INSERT_PLUS_DANCE_ENABLE
static uint8_t mod_state;
static td_state_t td_state;
void td_insert_plus_finished(tap_dance_state_t *state, void *user_data) {
    mod_state = get_mods();
    td_state = current_dance(state);
    if (mod_state == 0) {
        switch (td_state) {
            case JUST_TAP: register_code16(C(KC_V)); return;
            case DUAL_TAP: register_code16(C(KC_A)); return;
            case TRI_TAP:       tap_code16(C(KC_A)); return;
            default:            tap_code16(C(KC_X)); return;
        }
    } else if (mod_state & (MOD_MASK_GUI | MOD_MASK_SHIFT)) {
        switch (td_state) {
            case JUST_TAP: register_code16(SWIN(KC_S)); return;
            default:      /* This line is necessary. */ return;
        }
    }
    register_code(KC_INS);
}

void td_insert_plus_reset(tap_dance_state_t *state, void *user_data) {
    if (mod_state == 0) {
        switch (td_state) {
            case JUST_TAP: unregister_code16(C(KC_V)); return;
            case DUAL_TAP: unregister_code16(C(KC_A)); return;
            default:              tap_code16(C(KC_V)); return;
        }
    } else if (mod_state & (MOD_MASK_GUI | MOD_MASK_SHIFT))  {
        switch (td_state) {
            case JUST_TAP: unregister_code16(SWIN(KC_S)); return;
            default:      /* This line is necessary. */   return;
        }
    }
    unregister_code(KC_INS);
}
#endif

#ifdef ALT_TABLE_DANCE_ENABLE
void td_alt_tab_each_tap(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1: add_mods(MOD_LALT);
        default:  tap_code(KC_TAB);
    }
}

void td_alt_tab_finished(tap_dance_state_t *state, void *user_data) {
    del_mods(MOD_LALT);
}
#endif
