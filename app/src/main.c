#include <stdbool.h>
#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "smarthome/temperature.h"

#if DT_HAS_COMPAT_STATUS_OKAY(maxim_ds18b20)
int main(void)
{
    printk("SmartHome firmware booted\n");

    const struct device *sensor = DEVICE_DT_GET(DT_NODELABEL(ds18b20));
    if (!device_is_ready(sensor)) {
        printk("DS18B20 unavailable: device not ready\n");
        return 0;
    }

    while (true) {
        struct sensor_value temperature;
        int error = sensor_sample_fetch(sensor);
        if (error == 0) {
            error = sensor_channel_get(sensor, SENSOR_CHAN_AMBIENT_TEMP, &temperature);
        }

        if (error < 0) {
            printk("DS18B20 unavailable: error %d\n", error);
        } else {
            char formatted_temperature[32];
            const int formatted_length = smarthome_format_temperature_celsius(
                formatted_temperature, sizeof(formatted_temperature), &temperature);
            if (formatted_length < 0 || (size_t)formatted_length >= sizeof(formatted_temperature)) {
                printk("DS18B20 unavailable: formatting error %d\n", formatted_length);
            } else {
                printk("DS18B20: %s C uptime_ms=%lld\n", formatted_temperature, (long long)k_uptime_get());
            }
        }

        k_sleep(K_SECONDS(60));
    }
}
#else
int main(void)
{
    printk("SmartHome firmware booted\n");
    return 0;
}
#endif
