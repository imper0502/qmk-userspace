/* Key Override */
#pragma once

const key_override_t at_override   = ko_make_basic(MOD_MASK_SHIFT, KC_AT         , KC_AUDIO_MUTE);       // @  
const key_override_t hash_override = ko_make_basic(MOD_MASK_SHIFT, KC_HASH       , KC_AUDIO_VOL_DOWN);   // #
const key_override_t lprn_override = ko_make_basic(MOD_MASK_SHIFT, KC_LEFT_PAREN , KC_AUDIO_VOL_UP);     // (
const key_override_t rprn_override = ko_make_basic(MOD_MASK_SHIFT, KC_RIGHT_PAREN, SWIN(KC_S));          // )

const key_override_t circ_override = ko_make_basic(MOD_MASK_SHIFT, KC_CIRCUMFLEX , KC_CALCULATOR);       // ^
const key_override_t ampr_override = ko_make_basic(MOD_MASK_SHIFT, KC_AMPERSAND  , KC_MEDIA_PREV_TRACK); // & 
const key_override_t astr_override = ko_make_basic(MOD_MASK_SHIFT, KC_ASTERISK   , KC_MEDIA_PLAY_PAUSE); // * 
const key_override_t dlr_override  = ko_make_basic(MOD_MASK_SHIFT, KC_DOLLAR     , KC_MEDIA_NEXT_TRACK); // $

#if IMPER0502_OVERRIDE_PUNCT
const key_override_t comm_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_COMMA, KC_SEMICOLON, ~(1 << 1));                // ,;
#endif
#if IMPER0502_OVERRIDE_PUNCT
const key_override_t dot_override  = ko_make_with_layers(MOD_MASK_SHIFT, KC_DOT  , KC_COLON    , ~(1 << 1));                // .:
#endif
#if IMPER0502_OVERRIDE_PUNCT
const key_override_t rgui_tap_slsh_override = ko_make_with_layers(MOD_MASK_SHIFT, RGUI_T(KC_SLASH), KC_PERCENT, ~(1 << 1)); // /%
#endif

const key_override_t *key_overrides[] = {
    &at_override  ,
    &hash_override,
    &lprn_override,
    &rprn_override,

    &circ_override,
    &ampr_override,
    &astr_override,
    &dlr_override ,

#if IMPER0502_OVERRIDE_PUNCT
    &comm_override,
#endif
#if IMPER0502_OVERRIDE_PUNCT
    &dot_override ,
#endif
#if IMPER0502_OVERRIDE_PUNCT
    &rgui_tap_slsh_override,
#endif

};
