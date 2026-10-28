SRC += imper0502.c
SRC += features/tap_dance/idle_timer.c
SRC += features/led/led_indicators.c
SRC += features/tap_dance/tapping_term.c
SRC += features/encoder/encoder.c
SRC += features/leader/leader.c

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += features/tap_dance/tap_dance.c
    SRC += features/tap_dance/layer_dance.c
    SRC += features/tap_dance/keys/control.c
    SRC += features/tap_dance/keys/enter.c
    SRC += features/tap_dance/keys/space.c
    SRC += features/tap_dance/keys/shift.c
    SRC += features/tap_dance/keys/backspace.c
    SRC += features/tap_dance/keys/grave.c
    SRC += features/tap_dance/keys/insert_plus.c
    SRC += features/tap_dance/keys/table.c
    SRC += features/tap_dance/keys/alt_table.c
endif

