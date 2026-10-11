#include <stdint.h>

#include <zephyr/drivers/sensor.h>
#include <zephyr/ztest.h>

#include "smarthome/temperature.h"

ZTEST_SUITE(temperature_micro_celsius, NULL, NULL, NULL, NULL, NULL);

ZTEST(temperature_micro_celsius, test_positive_fraction)
{
    const struct sensor_value temperature = {.val1 = 23, .val2 = 456789};
    int64_t micro_celsius;

    zassert_true(smarthome_temperature_to_micro_celsius(&temperature, &micro_celsius),
                 "positive reading conversion succeeded");
    zassert_equal(micro_celsius, INT64_C(23456789), "positive fraction conversion");
}

ZTEST(temperature_micro_celsius, test_negative_fraction)
{
    const struct sensor_value temperature = {.val1 = -1, .val2 = -500000};
    int64_t micro_celsius;

    zassert_true(smarthome_temperature_to_micro_celsius(&temperature, &micro_celsius),
                 "negative reading conversion succeeded");
    zassert_equal(micro_celsius, INT64_C(-1500000), "negative fraction conversion");
}

ZTEST(temperature_micro_celsius, test_negative_subunit)
{
    const struct sensor_value temperature = {.val1 = 0, .val2 = -125000};
    int64_t micro_celsius;

    zassert_true(smarthome_temperature_to_micro_celsius(&temperature, &micro_celsius),
                 "negative subunit conversion succeeded");
    zassert_equal(micro_celsius, INT64_C(-125000), "negative subunit conversion");
}

ZTEST(temperature_micro_celsius, test_zero)
{
    const struct sensor_value temperature = {.val1 = 0, .val2 = 0};
    int64_t micro_celsius;

    zassert_true(smarthome_temperature_to_micro_celsius(&temperature, &micro_celsius), "zero conversion succeeded");
    zassert_equal(micro_celsius, 0, "zero conversion");
}

ZTEST(temperature_micro_celsius, test_invalid_arguments)
{
    const struct sensor_value temperature = {.val1 = 1, .val2 = 0};
    int64_t micro_celsius;

    zassert_false(smarthome_temperature_to_micro_celsius(NULL, &micro_celsius), "null reading is rejected");
    zassert_false(smarthome_temperature_to_micro_celsius(&temperature, NULL), "null output is rejected");
}
