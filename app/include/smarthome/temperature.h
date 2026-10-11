#ifndef SMARTHOME_TEMPERATURE_H
#define SMARTHOME_TEMPERATURE_H

#include <stdbool.h>
#include <stdint.h>

#include <zephyr/drivers/sensor.h>

bool smarthome_temperature_to_micro_celsius(const struct sensor_value *temperature, int64_t *micro_celsius);

#endif
