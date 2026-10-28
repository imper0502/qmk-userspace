/* Copyright 2021 imper0502
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#include "keymap.h"
#define ALT_SFT LALT(KC_LSFT)
#define CTL_ALT LCTL(LALT(KC_NO))
#define CTL_SFT LCTL(KC_LSFT)
#define fCTLALT LM(_FN, MOD_LCTL | MOD_LALT)
#define fCTLSFT LM(_FN, MOD_LCTL | MOD_LSFT)
#define fALTSFT LM(_FN, MOD_LALT | MOD_LSFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BS] = LAYOUT_split_4x6_2x3(
        WC_LEFT, WC_RGHT, KC_AT  , KC_HASH, KC_LPRN, KC_RPRN,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_DLR , KC_INS , KC_DEL ,
        KC_TAB , KC_Q   , KC_W   , KC_F   , KC_P   , KC_B   ,                   KC_J   , KC_L   , KC_U   , KC_Y   , KC_MINS, KC_EQL ,
        MT_ESC , KC_A   , KC_R   , KC_S   , KC_T   , KC_G   ,                   KC_M   , KC_N   , KC_E   , KC_I   , KC_O   , TD_QUOT,
        KC_LALT, KC_Z   , KC_X   , KC_C   , KC_D   , KC_V   ,                   KC_K   , KC_H   , KC_COMM, KC_DOT , KC_SLSH, TD_BSLS,
                                            KC_LCTL, TD_SFT , KC_BSPC, TD_ENT , LT_SPC , TD_GRV ,
                                            ALT_SFT, CTL_ALT, CTL_SFT, fCTLALT, fCTLSFT, fALTSFT
    ),
    [_QW] = LAYOUT_split_4x6_2x3(
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                   KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_EQL ,
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                   KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_MINS,
        MT_ESC , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                   KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                   KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                                            _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______, _______, _______, _______
    ),
    [_NP] = LAYOUT_split_4x6_2x3(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, MS_WHLU, MS_WHLL, MS_UP  , MS_WHLR, MS_BTN4,                   KC_PAST, KC_7   , KC_8   , KC_9   , KC_PPLS, XXXXXXX,
        XXXXXXX, MS_WHLD, MS_LEFT, MS_DOWN, MS_RGHT, MS_BTN5,                   KC_PSLS, KC_4   , KC_5   , KC_6   , KC_PMNS, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG(_NP),                   KC_PERC, KC_1   , KC_2   , KC_3   , KC_EQL , XXXXXXX,
                                            MS_BTN1, MS_BTN3, MS_BTN2, KC_PENT, KC_0   , KC_DOT ,
                                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_MK] = LAYOUT_split_4x6_2x3(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_TAB , TG(_QW), CG_TOGG, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, MS_WHLL, MS_UP  , MS_WHLR, MS_WHLU, XXXXXXX,
        KC_ESC , KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, XXXXXXX,                   XXXXXXX, MS_LEFT, MS_DOWN, MS_RGHT, MS_WHLD, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   TG(_MK), XXXXXXX, MS_BTN4, MS_BTN5, XXXXXXX, XXXXXXX,
                                            KC_LCTL, KC_LSFT, KC_LALT, MS_BTN1, LT_BTN3, MS_BTN2,
                                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_FN] = LAYOUT_split_4x6_2x3(
        KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,                   KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,
        KC_TAB , KC_LCBR, KC_7   , KC_8   , KC_9   , TO(_BS),                   TO(_BS), KC_HOME, KC_UP  , KC_END , KC_RCBR, KC_TAB ,
        KC_ESC , KC_LBRC, KC_4   , KC_5   , KC_6   , KC_CAPS,                   CW_TOGG, KC_LEFT, KC_DOWN, KC_RGHT, KC_RBRC, KC_ESC ,
        _______, KC_EXLM, KC_1   , KC_2   , KC_3   , TG(_NP),                   TG(_MK), KC_PGUP, KC_SCLN, KC_COLN, KC_PERC, _______,
                                            KC_DOT , KC_0   , KC_BSPC, KC_ENT , KC_PSCR, KC_PGDN,
                                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};
