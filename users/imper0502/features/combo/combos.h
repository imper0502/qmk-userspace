#pragma once

const uint16_t PROGMEM left_outside_up_row_combo[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM left_inside_up_row_combo[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM right_inside_up_row_combo[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM right_outside_up_row_combo[] = {KC_U, KC_Y, COMBO_END};

const uint16_t PROGMEM left_home_row_combo[] = {KC_R, KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM double_home_row_combo[] = {KC_S, KC_T, KC_N, KC_E, COMBO_END};
const uint16_t PROGMEM right_home_row_combo[] = {KC_N, KC_E, KC_I, COMBO_END};

const uint16_t PROGMEM left_outside_down_row_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM left_inside_down_row_combo[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM right_inside_down_row_combo[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM right_outside_down_row_combo[] = {KC_COMM, KC_DOT, COMBO_END};

const uint16_t PROGMEM left_outside_col_combo[] = {KC_F, KC_S, COMBO_END};
const uint16_t PROGMEM left_center_col_combo[] = {KC_P, KC_T, COMBO_END};
const uint16_t PROGMEM left_inside_col_combo[] = {KC_B, KC_G, COMBO_END};
const uint16_t PROGMEM right_inside_col_combo[] = {KC_J, KC_M, COMBO_END};
const uint16_t PROGMEM right_center_col_combo[] = {KC_L, KC_N, COMBO_END};
const uint16_t PROGMEM right_outside_col_combo[] = {KC_U, KC_E, COMBO_END};

enum combos {
  RC_LOU, RC_LIU, RC_DU, RC_RIU, RC_ROU,
  RC_LH ,         RC_DH,         RC_RH ,
  RC_LOD, RC_LID, RC_DD, RC_RID, RC_ROD,
  CC_LO, CC_LC, CC_LI,
  CC_RI, CC_RC, CC_RO,
  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

combo_t key_combos[] = {
  [RC_LOU] = COMBO(left_outside_up_row_combo, KC_ENT),   [RC_ROU] = COMBO(right_outside_up_row_combo, KC_BSPC),
  [RC_LH]  = COMBO(left_home_row_combo, MO(_MK)),        [RC_RH]  = COMBO(right_home_row_combo, MO(_NP)),
  [RC_LOD] = COMBO(left_outside_down_row_combo, KC_DEL), [RC_ROD] = COMBO(right_outside_down_row_combo, KC_INS),

  [CC_LO] = COMBO(left_outside_col_combo, KC_LCBR),
  [CC_LC] = COMBO(left_center_col_combo, KC_LPRN),
  [CC_LI] = COMBO(left_inside_col_combo, KC_BSLS),

  [CC_RI] = COMBO(right_inside_col_combo, KC_SLSH),
  [CC_RC] = COMBO(right_center_col_combo, KC_RPRN),
  [CC_RO] = COMBO(right_outside_col_combo, KC_RCBR)
};
