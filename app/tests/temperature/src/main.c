#include <errno.h>
#include <string.h>

#include <zephyr/drivers/sensor.h>
#include <zephyr/ztest.h>

#include "smarthome/temperature.h"

ZTEST_SUITE(temperature_formatting, NULL, NULL, NULL, NULL, NULL);

ZTEST(temperature_formatting, test_positive_fraction)
{
    const struct sensor_value temperature = {.val1 = 23, .val2 = 456789};
    char formatted[32];

    zassert_equal(smarthome_format_temperature_celsius(formatted, sizeof(formatted), &temperature), 9,
                  "positive output length");
    zassert_equal(strcmp(formatted, "23.456789"), 0, "positive fraction formatting");
}

ZTEST(temperature_formatting, test_negative_fraction)
{
    const struct sensor_value temperature = {.val1 = -1, .val2 = -500000};
    char formatted[32];

    zassert_equal(smarthome_format_temperature_celsius(formatted, sizeof(formatted), &temperature), 9,
                  "negative output length");
    zassert_equal(strcmp(formatted, "-1.500000"), 0, "negative fraction formatting");
}

ZTEST(temperature_formatting, test_negative_subunit)
{
    const struct sensor_value temperature = {.val1 = 0, .val2 = -125000};
    char formatted[32];

    zassert_equal(smarthome_format_temperature_celsius(formatted, sizeof(formatted), &temperature), 9,
                  "negative subunit output length");
    zassert_equal(strcmp(formatted, "-0.125000"), 0, "negative subunit formatting");
}

ZTEST(temperature_formatting, test_zero)
{
    const struct sensor_value temperature = {.val1 = 0, .val2 = 0};
    char formatted[32];

    zassert_equal(smarthome_format_temperature_celsius(formatted, sizeof(formatted), &temperature), 8,
                  "zero output length");
    zassert_equal(strcmp(formatted, "0.000000"), 0, "zero formatting");
}

ZTEST(temperature_formatting, test_invalid_arguments)
{
    const struct sensor_value temperature = {.val1 = 1, .val2 = 0};
    char formatted[32];

    zassert_equal(smarthome_format_temperature_celsius(NULL, sizeof(formatted), &temperature), -EINVAL,
                  "null buffer is rejected");
    zassert_equal(smarthome_format_temperature_celsius(formatted, 0, &temperature), -EINVAL,
                  "empty buffer is rejected");
    zassert_equal(smarthome_format_temperature_celsius(formatted, sizeof(formatted), NULL), -EINVAL,
                  "null reading is rejected");
}
