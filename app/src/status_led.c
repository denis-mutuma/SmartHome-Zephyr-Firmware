#include "smarthome/status_led.h"

int smarthome_status_led_configure_inactive(const struct gpio_dt_spec *led)
{
    return gpio_pin_configure_dt(led, GPIO_OUTPUT_INACTIVE);
}