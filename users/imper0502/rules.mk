SRC += imper0502.c
SRC += features/idle_timer.c
SRC += features/led_indicators.c
SRC += features/tapping_term.c

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += features/tap_dance.c
    SRC += features/tap_dance_handlers.c
endif

