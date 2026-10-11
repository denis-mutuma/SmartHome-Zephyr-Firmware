#ifndef SMARTHOME_TEMPERATURE_H
#define SMARTHOME_TEMPERATURE_H

#include <stddef.h>

#include <zephyr/drivers/sensor.h>

int smarthome_format_temperature_celsius(char *buffer, size_t buffer_size, const struct sensor_value *temperature);

#endif
