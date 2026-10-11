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
            int64_t micro_celsius;
            if (!smarthome_temperature_to_micro_celsius(&temperature, &micro_celsius)) {
                printk("DS18B20 unavailable: conversion error\n");
            } else {
                printk("DS18B20: %lld micro-C uptime_ms=%lld\n", (long long)micro_celsius, (long long)k_uptime_get());
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
