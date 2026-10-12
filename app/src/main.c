#include <stdbool.h>
#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "smarthome/temperature.h"

#if DT_HAS_ALIAS(status_led0)
#define STATUS_LED_NODE DT_ALIAS(status_led0)
static const struct gpio_dt_spec status_led = GPIO_DT_SPEC_GET(STATUS_LED_NODE, gpios);
#endif

static void initialize_status_led(void)
{
#if DT_HAS_ALIAS(status_led0)
    if (!gpio_is_ready_dt(&status_led)) {
        printk("Status LED unavailable: GPIO device not ready\n");
        return;
    }

    const int error = gpio_pin_configure_dt(&status_led, GPIO_OUTPUT_INACTIVE);
    if (error < 0) {
        printk("Status LED unavailable: GPIO configuration error %d\n", error);
    }
#endif
}

#if DT_HAS_COMPAT_STATUS_OKAY(maxim_ds18b20)
int main(void)
{
    initialize_status_led();
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
    initialize_status_led();
    printk("SmartHome firmware booted\n");
    return 0;
}
#endif
