#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/gpio/gpio_emul.h>
#include <zephyr/ztest.h>

#include "smarthome/status_led.h"

#define STATUS_LED_NODE DT_ALIAS(status_led0)

static const struct gpio_dt_spec status_led = GPIO_DT_SPEC_GET(STATUS_LED_NODE, gpios);

ZTEST_SUITE(status_led_initial_state, NULL, NULL, NULL, NULL, NULL);

ZTEST(status_led_initial_state, test_active_high_led_starts_output_low)
{
	gpio_flags_t flags;

	zassert_true(gpio_is_ready_dt(&status_led), "emulated GPIO controller is ready");
	zassert_false((status_led.dt_flags & GPIO_ACTIVE_LOW) != 0, "LED is active high");
	zassert_ok(smarthome_status_led_configure_inactive(&status_led), "configure LED inactive");
	zassert_ok(gpio_emul_flags_get(status_led.port, status_led.pin, &flags), "read emulated GPIO flags");
	zassert_true((flags & GPIO_OUTPUT) != 0, "LED pin is configured as an output");
	zassert_equal(gpio_emul_output_get(status_led.port, status_led.pin), 0, "active-high LED output is low");
}