#include <zephyr/drivers/sensor.h>

#include "smarthome/temperature.h"

bool smarthome_temperature_to_micro_celsius(const struct sensor_value *temperature, int64_t *micro_celsius)
{
    if (temperature == NULL || micro_celsius == NULL) {
        return false;
    }

    *micro_celsius = sensor_value_to_micro(temperature);
    return true;
}
