# SmartHome-Zephyr-Firmware

Board-neutral Zephyr firmware evaluation project. The ESP32-C6-DevKitC-1 is the first build target; no second board or hardware behavior has been validated.

## Status

The application reads one DS18B20 through Zephyr's UART-backed 1-Wire sensor driver on the ESP32-C6-DevKitC target. Other targets without a configured sensor retain the startup-only path. The reading is reported as signed microdegrees Celsius with a monotonic uptime observation time; sensor errors are reported as unavailable, not as a value. No network or relay behavior is implemented, and no mains wiring is part of this project.

The C6 overlay assigns UART1 RX to GPIO3 and TX to GPIO11. Zephyr's UART-backed 1-Wire driver is experimental and requires an external open-drain interface. Do not connect the sensor's data line directly to the UART pins. No physical wiring, sensor read, or electrical behavior has been validated; the board build only checks compilation and devicetree configuration.

The project license is undecided. Do not redistribute or assume reuse rights for this repository, binaries, or upstream Espressif radio blobs until their terms and provenance have been reviewed.

## Workspace setup

Install Python 3 and Git, then install west:

```sh
python -m pip install west
git clone https://github.com/denis-mutuma/SmartHome-Zephyr-Firmware.git firmware-workspace
cd firmware-workspace
west init -l app
west update
west sdk install --toolchains riscv64-zephyr-elf
```

Build the portable host target on a supported Linux host and the first board target:

```sh
west build -b native_sim -d app/build/native_sim app
west build -b esp32c6_devkitc/esp32c6/hpcore -d app/build/esp32c6_devkitc app
west build -b native_sim -d app/build/temperature_tests app/tests/temperature
app/build/temperature_tests/zephyr/zephyr.exe
```

The CI runs the temperature-conversion test on `native_sim` and compiles the app for `native_sim` and ESP32-C6. It does not execute firmware on a board or validate radio, sensor wiring/readings, security, or portability. The ESP32-C6 Wi-Fi/IEEE 802.15.4 path requires Espressif RF binary blobs; review their license and fetch/build process before enabling connectivity or publishing firmware.

The manifest pins Zephyr v4.4.0. Update it deliberately and rerun both builds before changing the supported baseline.
