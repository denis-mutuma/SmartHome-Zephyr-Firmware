#pragma once

#include <zephyr/drivers/gpio.h>

int smarthome_status_led_configure_inactive(const struct gpio_dt_spec *led);