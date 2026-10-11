#include <errno.h>
#include <stdbool.h>
#include <stdint.h>

#include <zephyr/drivers/sensor.h>
#include <zephyr/sys/printk.h>

#include "smarthome/temperature.h"

int smarthome_format_temperature_celsius(char *buffer, size_t buffer_size, const struct sensor_value *temperature)
{
    if (buffer == NULL || buffer_size == 0 || temperature == NULL) {
        return -EINVAL;
    }

    const int64_t micro_celsius = sensor_value_to_micro(temperature);
    const bool negative = micro_celsius < 0;
    const uint64_t magnitude = negative ? (uint64_t)-micro_celsius : (uint64_t)micro_celsius;

    return snprintk(buffer, buffer_size, "%s%llu.%06llu", negative ? "-" : "",
                    (unsigned long long)(magnitude / 1000000), (unsigned long long)(magnitude % 1000000));
}
