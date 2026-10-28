#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "test_keymap_key.hpp"

extern "C" {
#include "imper0502.h"
}

using testing::_;
using testing::Invoke;

/* current_dance() decides which action every tap dance runs, so pin down its table. */
static td_state_t dance(uint8_t count, bool pressed, bool interrupted) {
    tap_dance_state_t state = {};
    state.count             = count;
    state.pressed           = pressed;
    state.interrupted       = interrupted;
    return current_dance(&state);
}

TEST(CurrentDance, OneTap) {
    EXPECT_EQ(dance(1, false, false), JUST_TAP);
    EXPECT_EQ(dance(1, true, false), JUST_HOLD);
    EXPECT_EQ(dance(1, true, true), TAPPING);
    EXPECT_EQ(dance(1, false, true), TAPPING);
}

TEST(CurrentDance, TwoTaps) {
    EXPECT_EQ(dance(2, false, false), DUAL_TAP);
    EXPECT_EQ(dance(2, true, false), TAP_AND_HOLD);
    EXPECT_EQ(dance(2, true, true), DUAL_TAPPING);
    EXPECT_EQ(dance(2, false, true), DUAL_TAPPING);
}

TEST(CurrentDance, ThreeTaps) {
    EXPECT_EQ(dance(3, false, false), TRI_TAP);
    EXPECT_EQ(dance(3, true, false), TAP_TAP_HOLD);
    EXPECT_EQ(dance(3, true, true), TRI_TAPPING);
    EXPECT_EQ(dance(3, false, true), TRI_TAPPING);
}

TEST(CurrentDance, FourTaps) {
    EXPECT_EQ(dance(4, false, false), QUAD_TAP);
    EXPECT_EQ(dance(4, false, true), QUAD_TAP);
    EXPECT_EQ(dance(4, true, true), QUAD_TAP);
    EXPECT_EQ(dance(4, true, false), TRI_TAP_HOLD);
}

TEST(CurrentDance, OutOfRange) {
    EXPECT_EQ(dance(0, false, false), OTHERWISE);
    EXPECT_EQ(dance(5, false, false), OTHERWISE);
    EXPECT_EQ(dance(9, true, false), OTHERWISE);
}

/* Whatever a tap dance registers must be released again, for every tap count and for tap or hold.
 * Which key a dance sends is the part that gets remapped, so only look for stuck keys. */
class TapDanceRelease : public TestFixture {
   protected:
    void expect_released_after(uint16_t keycode, unsigned taps, bool hold) {
        SCOPED_TRACE(testing::Message() << "keycode=0x" << std::hex << keycode << std::dec << " taps=" << taps << (hold ? " hold" : " tap"));

        TestDriver        driver;
        report_keyboard_t last = {};
        EXPECT_CALL(driver, send_keyboard_mock(_)).WillRepeatedly(Invoke([&](report_keyboard_t& report) { last = report; }));

        layer_clear();
        auto key = KeymapKey{0, 0, 0, keycode};
        set_keymap({key});

        for (unsigned i = 1; i < taps; i++) {
            tap_key(key);
        }
        if (hold) {
            key.press();
            run_one_scan_loop();
            idle_for(TAPPING_TERM * 2);
            key.release();
            run_one_scan_loop();
        } else {
            tap_key(key);
        }
        idle_for(TAPPING_TERM * 2);

        EXPECT_EQ(last.mods, 0);
        for (unsigned i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
            EXPECT_EQ(last.keys[i], 0);
        }
        clear_keyboard();
    }

    void check(uint16_t keycode) {
        for (unsigned taps = 1; taps <= 5; taps++) {
            expect_released_after(keycode, taps, false);
            expect_released_after(keycode, taps, true);
        }
    }
};

TEST_F(TapDanceRelease, LeftControl) { check(TD(CONTROL_DANCE)); }
TEST_F(TapDanceRelease, Enter) { check(TD(ENTER_DANCE)); }
TEST_F(TapDanceRelease, Space) { check(TD(SPACE_DANCE)); }
TEST_F(TapDanceRelease, Backspace) { check(TD(BACKSPACE_DANCE)); }
TEST_F(TapDanceRelease, Grave) { check(TD(GRAVE_DANCE)); }
TEST_F(TapDanceRelease, InsertPlus) { check(TD(INSERT_PLUS)); }
