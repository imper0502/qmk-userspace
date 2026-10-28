#include "imper0502.h"

#ifdef ENCODER_ENABLE
static uint8_t mod_state;
__attribute__ ((weak))
bool encoder_update_user(uint8_t index, bool clockwise) {
    mod_state = get_mods();
    switch (index) {
    case 0:
        if (IS_LAYER_ON(_FN)) {
            if (mod_state & MOD_MASK_CS) {
                clockwise ? tap_code(KC_BRIU) : tap_code(KC_BRID);
            } else {
                clockwise ? tap_code(KC_VOLU) : tap_code(KC_VOLD);
            }
        } else {
            if (mod_state == (MOD_LCTL | MOD_LSFT) ||
                mod_state == (MOD_LCTL | MOD_RSFT) ||
                mod_state == (MOD_RCTL | MOD_LSFT) ||
                mod_state == (MOD_RCTL | MOD_RSFT)) {
                del_mods(MOD_MASK_CS);
                clockwise ? tap_code(KC_PGDN) : tap_code(KC_PGUP);
                set_mods(mod_state);
            } else if (mod_state & MOD_MASK_ALT) {
                del_mods(MOD_MASK_ALT);
                clockwise ? tap_code(MS_BTN5) : tap_code(MS_BTN4);
                set_mods(mod_state);
            } else if (mod_state & MOD_MASK_SG) {
                clockwise ? tap_code16(C(KC_RGHT)) : tap_code16(C(KC_LEFT));
            } else if (mod_state & MOD_MASK_CTRL) {
                clockwise ? tap_code(KC_Y) : tap_code(KC_Z);
            } else {
                clockwise ? tap_code(MS_WHLD) : tap_code(MS_WHLU);
            }
        }
        break;
    }
    return false;
}
#endif
