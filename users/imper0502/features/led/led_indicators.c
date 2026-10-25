/* RX/TX LED indicators (caps lock and active layer). */

#include "imper0502.h"

void keyboard_pre_init_user(void) {
#if defined(LED_PIN_ON_STATE) && defined(TXLED) && defined(RXLED)
    gpio_set_pin_output(TXLED);
    gpio_set_pin_output(RXLED);
#endif
}

#if defined(LED_PIN_ON_STATE) && defined(TXLED) && defined(RXLED)
typedef enum {
    OFF, FLASH, ON
} led_status_t;

led_status_t  rx_led_status;
led_status_t  tx_led_status;

uint16_t _timer = 0;
bool next_led_pins_state = !LED_PIN_ON_STATE;
#endif

void led_indicators_task(void) {
#if defined(LED_PIN_ON_STATE) && defined(TXLED) && defined(RXLED)
    switch (tx_led_status) {
    case ON:
        next_led_pins_state = LED_PIN_ON_STATE;
        break;
    case FLASH:
        if (timer_elapsed(_timer) > TAPPING_TERM) {
            next_led_pins_state = !next_led_pins_state;
            _timer = timer_read();
        }
        break;
    default:
        next_led_pins_state = !LED_PIN_ON_STATE;
        break;
    }
    switch (rx_led_status) {
    case FLASH:
        gpio_write_pin(RXLED, !next_led_pins_state);
        break;
    default:
        gpio_write_pin(RXLED, !host_keyboard_led_state().caps_lock);
        break;
    }
    gpio_write_pin(TXLED, next_led_pins_state);
#endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
#if defined(LED_PIN_ON_STATE) && defined(TXLED) && defined(RXLED)
    switch (get_highest_layer(state)) {
    case _MK:
        tx_led_status = FLASH;
        break;
    case _NP:
    case _FN:
        tx_led_status = ON;
        break;
    default:
        tx_led_status = OFF;
        rx_led_status = OFF;
        break;
    }
#endif
  return state;
}
