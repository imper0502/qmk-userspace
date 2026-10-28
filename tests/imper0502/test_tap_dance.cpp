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
TEST_F(TapDanceRelease, Quote) { check(TD(QUOTE_DANCE)); }
TEST_F(TapDanceRelease, Backslash) { check(TD(BACKSLASH_DANCE)); }
TEST_F(TapDanceRelease, InsertPlus) { check(TD(INSERT_PLUS)); }

class InsertPlusKey : public TestFixture {
   protected:
    bool sent(uint8_t keycode, uint8_t mods) const {
        for (const auto& report : reports) {
            if (report.mods != mods) continue;
            for (unsigned i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
                if (report.keys[i] == keycode) return true;
            }
        }
        return false;
    }

    TestDriver                     driver;
    std::vector<report_keyboard_t> reports;
};

TEST_F(InsertPlusKey, ThreeTapsSelectAllWithoutPastingOverIt) {
    EXPECT_CALL(driver, send_keyboard_mock(_)).WillRepeatedly(Invoke([&](report_keyboard_t& report) { reports.push_back(report); }));
    layer_clear();
    auto key = KeymapKey{0, 0, 0, TD(INSERT_PLUS)};
    set_keymap({key});
    for (int i = 0; i < 3; i++) tap_key(key);
    idle_for(TAPPING_TERM * 2);
    EXPECT_TRUE(sent(KC_A, MOD_BIT(KC_LCTL)));
    EXPECT_FALSE(sent(KC_V, MOD_BIT(KC_LCTL)));
}

class LeftControl : public TestFixture {
   protected:
    KeymapKey key = KeymapKey{0, 0, 0, TD(CONTROL_DANCE)};

    void SetUp() override {
        layer_clear();
        set_keymap({key});
        EXPECT_CALL(driver, send_keyboard_mock(_)).WillRepeatedly(Invoke([&](report_keyboard_t& report) { reports.push_back(report); }));
    }

    /* How many times Left Ctrl went from up to down. */
    int ctrl_presses() const {
        int  presses = 0;
        bool down    = false;
        for (const auto& report : reports) {
            bool now = report.mods & MOD_BIT(KC_LCTL);
            if (now && !down) presses++;
            down = now;
        }
        return presses;
    }

    uint8_t last_mods() const { return reports.empty() ? 0 : reports.back().mods; }

    void tap_times(int taps) {
        for (int i = 0; i < taps; i++) tap_key(key);
        idle_for(TAPPING_TERM * 2);
    }

    /* Tap `taps` times, then press and keep the key down. */
    void tap_then_hold(int taps) {
        for (int i = 0; i < taps; i++) tap_key(key);
        key.press();
        run_one_scan_loop();
        idle_for(TAPPING_TERM * 2);
    }

    TestDriver                     driver;
    std::vector<report_keyboard_t> reports;
};

TEST_F(LeftControl, OneTapSendsOneCtrl) {
    tap_times(1);
    EXPECT_EQ(ctrl_presses(), 1);
    EXPECT_EQ(last_mods(), 0);
}

TEST_F(LeftControl, TwoTapsSendTwoCtrl) {
    tap_times(2);
    EXPECT_EQ(ctrl_presses(), 2);
    EXPECT_EQ(last_mods(), 0);
}

TEST_F(LeftControl, ThreeTapsSendThreeCtrl) {
    tap_times(3);
    EXPECT_EQ(ctrl_presses(), 3);
    EXPECT_EQ(last_mods(), 0);
}

TEST_F(LeftControl, HoldKeepsCtrlDown) {
    tap_then_hold(0);
    EXPECT_EQ(last_mods(), MOD_BIT(KC_LCTL));
    key.release();
    run_one_scan_loop();
    EXPECT_EQ(last_mods(), 0);
}

TEST_F(LeftControl, TwoTapsThenHoldSendsAltAndShift) {
    tap_then_hold(1);
    EXPECT_EQ(last_mods(), MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT));
    key.release();
    run_one_scan_loop();
    EXPECT_EQ(last_mods(), 0);
}

TEST_F(LeftControl, ThreeTapsThenHoldTogglesTheMouseKeyLayer) {
    tap_then_hold(2);
    EXPECT_TRUE(layer_state_is(_MK));
    EXPECT_EQ(ctrl_presses(), 0);
    key.release();
    run_one_scan_loop();
    EXPECT_FALSE(layer_state_is(_MK));
    EXPECT_EQ(last_mods(), 0);
}

/* The space bar and the grave key follow the same rules: n taps type n of their key, a hold opens the _FN layer,
 * one tap then hold adds a second modifier set, two or more taps then hold repeat the key, and a tap that another key interrupts is
 * a layer hold after a pause but the key itself while typing. They differ in the modifiers they add. */
struct DanceKeyShape {
    uint16_t dance;         /* the tap dance keycode */
    uint8_t  output;        /* what n taps type */
    uint8_t  hold_mods;     /* modifiers held with the _FN layer on a plain hold */
    uint8_t  tap_hold_mods; /* modifiers held after one tap then hold */
};

class DanceKeyTest : public TestFixture {
   protected:
    explicit DanceKeyTest(DanceKeyShape shape) : shape(shape), dance(KeymapKey{0, 0, 0, shape.dance}) {}

    void SetUp() override {
        layer_clear();
        /* The _FN layer is transparent, so keys pressed while it is on still resolve. */
        set_keymap({dance, key_a, key_b,
                    KeymapKey{_FN, 0, 0, KC_TRNS}, KeymapKey{_FN, 1, 0, KC_TRNS}, KeymapKey{_FN, 2, 0, KC_TRNS}});
        EXPECT_CALL(driver, send_keyboard_mock(_)).WillRepeatedly(Invoke([&](report_keyboard_t& report) { reports.push_back(report); }));
        /* QMK does not call matrix_scan_user in unit tests, so the idle timer never runs: say it has been idle. */
        is_idle_timeout = true;
    }

    static bool has(const report_keyboard_t& report, uint8_t keycode) {
        for (unsigned i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
            if (report.keys[i] == keycode) return true;
        }
        return false;
    }

    /* How many times the key went from up to down. */
    int presses() const {
        int  presses = 0;
        bool down    = false;
        for (const auto& report : reports) {
            bool now = has(report, shape.output);
            if (now && !down) presses++;
            down = now;
        }
        return presses;
    }

    bool    output_is_down() const { return !reports.empty() && has(reports.back(), shape.output); }

    /* How many times the modifier `mod` went from up to down, and whether `also_held` was down at those moments. */
    int mod_edges(uint8_t mod, uint8_t also_held = 0, bool* also_held_ok = nullptr) const {
        int  count = 0;
        bool down  = false;
        if (also_held_ok) *also_held_ok = true;
        for (const auto& report : reports) {
            bool now = report.mods & mod;
            if (now && !down) {
                count++;
                if (also_held_ok && (report.mods & also_held) != also_held) *also_held_ok = false;
            }
            down = now;
        }
        return count;
    }
    uint8_t last_mods() const { return reports.empty() ? 0 : reports.back().mods; }

    void tap_times(int taps) {
        for (int i = 0; i < taps; i++) tap_key(dance);
        idle_for(TAPPING_TERM * 2);
    }

    void tap_then_hold(int taps) {
        for (int i = 0; i < taps; i++) tap_key(dance);
        dance.press();
        run_one_scan_loop();
        idle_for(TAPPING_TERM * 2);
    }

    DanceKeyShape                  shape;
    KeymapKey                      dance;
    KeymapKey                      key_a = KeymapKey{0, 1, 0, KC_A};
    KeymapKey                      key_b = KeymapKey{0, 2, 0, KC_B};
    TestDriver                     driver;
    std::vector<report_keyboard_t> reports;
};

#define DANCE_KEY_TESTS(Fixture)                                                      \
    TEST_F(Fixture, TapsTypeAsManyAsTaps) {                                           \
        for (int taps = 1; taps <= 5; taps++) {                                       \
            reports.clear();                                                          \
            SCOPED_TRACE(testing::Message() << "taps=" << taps);                      \
            tap_times(taps);                                                          \
            EXPECT_EQ(presses(), taps);                                               \
            EXPECT_FALSE(output_is_down());                                           \
        }                                                                             \
    }                                                                                 \
    TEST_F(Fixture, HoldOpensTheFnLayer) {                                            \
        tap_then_hold(0);                                                             \
        EXPECT_TRUE(layer_state_is(_FN));                                             \
        EXPECT_EQ(last_mods(), shape.hold_mods);                                      \
        EXPECT_EQ(presses(), 0);                                                      \
        dance.release();                                                              \
        run_one_scan_loop();                                                          \
        EXPECT_FALSE(layer_state_is(_FN));                                            \
        EXPECT_EQ(last_mods(), 0);                                                    \
    }                                                                                 \
    TEST_F(Fixture, OneTapThenHoldAddsModifiers) {                                    \
        tap_then_hold(1);                                                             \
        EXPECT_TRUE(layer_state_is(_FN));                                             \
        EXPECT_EQ(last_mods(), shape.tap_hold_mods);                                  \
        EXPECT_EQ(presses(), 0);                                                      \
        dance.release();                                                              \
        run_one_scan_loop();                                                          \
        EXPECT_FALSE(layer_state_is(_FN));                                            \
        EXPECT_EQ(last_mods(), 0);                                                    \
    }                                                                                 \
    TEST_F(Fixture, TwoTapsThenHoldRepeats) {                                         \
        tap_then_hold(2);                                                             \
        EXPECT_FALSE(layer_state_is(_FN));                                            \
        EXPECT_TRUE(output_is_down());                                                \
        dance.release();                                                              \
        run_one_scan_loop();                                                          \
        EXPECT_FALSE(output_is_down());                                               \
    }                                                                                 \
    TEST_F(Fixture, InterruptedAfterAPauseIsALayerHold) {                             \
        dance.press();                                                                \
        run_one_scan_loop();                                                          \
        key_a.press();                                                                \
        run_one_scan_loop();                                                          \
        EXPECT_TRUE(layer_state_is(_FN));                                             \
        EXPECT_EQ(presses(), 0);                                                      \
        key_a.release();                                                              \
        dance.release();                                                              \
        idle_for(TAPPING_TERM * 2);                                                   \
        EXPECT_FALSE(layer_state_is(_FN));                                            \
        EXPECT_EQ(last_mods(), 0);                                                    \
    }                                                                                 \
    TEST_F(Fixture, InterruptedWhileTypingIsTheKey) {                                 \
        tap_key(key_a); /* typing: the keyboard is not idle */                        \
        dance.press();                                                                \
        run_one_scan_loop();                                                          \
        key_b.press();                                                                \
        run_one_scan_loop();                                                          \
        EXPECT_FALSE(layer_state_is(_FN));                                            \
        EXPECT_EQ(presses(), 1);                                                      \
        key_b.release();                                                              \
        dance.release();                                                              \
        idle_for(TAPPING_TERM * 2);                                                   \
        EXPECT_FALSE(output_is_down());                                               \
    }

class SpaceKey : public DanceKeyTest {
   public:
    SpaceKey() : DanceKeyTest({TD(SPACE_DANCE), KC_SPC, 0, MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT)}) {}
};
DANCE_KEY_TESTS(SpaceKey)

class GraveKey : public DanceKeyTest {
   public:
    GraveKey() : DanceKeyTest({TD(GRAVE_DANCE), KC_GRV, MOD_BIT(KC_LCTL), MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT)}) {}
};
DANCE_KEY_TESTS(GraveKey)

class EnterKey : public DanceKeyTest {
   public:
    EnterKey() : DanceKeyTest({TD(ENTER_DANCE), KC_ENT, MOD_BIT(KC_LSFT), MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT)}) {}
};
DANCE_KEY_TESTS(EnterKey)

class ShiftKey : public TestFixture {
   protected:
    KeymapKey shift = KeymapKey{0, 0, 0, TD(SHIFT_DANCE)};
    KeymapKey key_a = KeymapKey{0, 1, 0, KC_A};

    void SetUp() override {
        layer_clear();
        clear_oneshot_mods();
        caps_word_off();
        set_keymap({shift, key_a});
        EXPECT_CALL(driver, send_keyboard_mock(_)).WillRepeatedly(Invoke([&](report_keyboard_t& report) { reports.push_back(report); }));
    }

    static bool has(const report_keyboard_t& report, uint8_t keycode) {
        for (unsigned i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
            if (report.keys[i] == keycode) return true;
        }
        return false;
    }

    /* The modifiers that were down while the n-th A went down (n starts at 1), or -1 if there was no such A. */
    int mods_of_a(int n) const {
        int  seen = 0;
        bool down = false;
        for (const auto& report : reports) {
            bool now = has(report, KC_A);
            if (now && !down && ++seen == n) return report.mods;
            down = now;
        }
        return -1;
    }

    uint8_t last_mods() const { return reports.empty() ? 0 : reports.back().mods; }

    void tap_times(int taps) {
        for (int i = 0; i < taps; i++) tap_key(shift);
        idle_for(TAPPING_TERM * 2);
    }

    TestDriver                     driver;
    std::vector<report_keyboard_t> reports;
};

TEST_F(ShiftKey, TapShiftsOnlyTheNextKey) {
    tap_times(1);
    tap_key(key_a);
    tap_key(key_a);
    EXPECT_EQ(mods_of_a(1), MOD_BIT(KC_LSFT));
    EXPECT_EQ(mods_of_a(2), 0);
}

TEST_F(ShiftKey, TapFollowedByAQuickKeyShiftsIt) {
    tap_key(shift);
    tap_key(key_a); /* before the dance is over */
    idle_for(TAPPING_TERM * 2);
    EXPECT_EQ(mods_of_a(1), MOD_BIT(KC_LSFT));
    tap_key(key_a);
    EXPECT_EQ(mods_of_a(2), 0);
}

TEST_F(ShiftKey, TwoOrMoreTapsToggleCapsWordInsteadOfShiftingTheNextKey) {
    for (int taps = 2; taps <= 4; taps++) {
        SCOPED_TRACE(testing::Message() << "taps=" << taps);
        caps_word_off();
        tap_times(taps);
        EXPECT_TRUE(is_caps_word_on());
        EXPECT_EQ(get_oneshot_mods(), 0);
        EXPECT_EQ(get_oneshot_locked_mods(), 0);
        tap_times(taps);
        EXPECT_FALSE(is_caps_word_on());
    }
}

TEST_F(ShiftKey, ATapEndsCapsWordWithoutShiftingTheNextKey) {
    caps_word_on();
    tap_times(1);
    EXPECT_FALSE(is_caps_word_on());
    EXPECT_EQ(get_oneshot_mods(), 0);
    tap_key(key_a);
    EXPECT_EQ(mods_of_a(1), 0);
}

TEST_F(ShiftKey, HoldIsShift) {
    shift.press();
    run_one_scan_loop();
    idle_for(TAPPING_TERM * 2);
    EXPECT_EQ(last_mods(), MOD_BIT(KC_LSFT));
    shift.release();
    run_one_scan_loop();
    EXPECT_EQ(last_mods(), 0);
}

TEST_F(ShiftKey, AKeyPressedWhileHeldIsShifted) {
    shift.press();
    run_one_scan_loop();
    key_a.press();
    run_one_scan_loop();
    key_a.release();
    shift.release();
    idle_for(TAPPING_TERM * 2);
    EXPECT_EQ(mods_of_a(1), MOD_BIT(KC_LSFT));
    EXPECT_EQ(last_mods(), 0);
}

TEST_F(ShiftKey, TapsThenHoldAreCtrlAndAlt) {
    for (int taps = 1; taps <= 4; taps++) {
        reports.clear();
        SCOPED_TRACE(testing::Message() << "taps=" << taps);
        for (int i = 0; i < taps; i++) tap_key(shift);
        shift.press();
        run_one_scan_loop();
        idle_for(TAPPING_TERM * 2);
        EXPECT_EQ(last_mods(), MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT));
        shift.release();
        run_one_scan_loop();
        EXPECT_EQ(last_mods(), 0);
    }
}
