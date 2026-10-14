# SmartHome-Zephyr-Firmware

Board-neutral Zephyr firmware evaluation project. The ESP32-C6-DevKitC-1 is the first build target; no second board or hardware behavior has been validated.

## Status

The application reads one DS18B20 through Zephyr's UART-backed 1-Wire sensor driver on the ESP32-C6-DevKitC target. Other targets without a configured sensor retain the startup-only path. The reading is reported as signed microdegrees Celsius with a monotonic uptime observation time; sensor errors are reported as unavailable, not as a value. No network or relay behavior is implemented, and no mains wiring is part of this project.

The C6 overlay assigns UART1 TX to GPIO2 (J1 pin 12) and RX to GPIO3 (J1 pin 13), leaving GPIO11 (J1 pin 11) for the external LED. The user reports an active-high circuit: GPIO11 → 220 Ω series resistor → LED anode, with the cathode to GND; this wiring has not been independently inspected or tested. Firmware configures the LED output inactive (low) at startup and does not blink or otherwise toggle it. A native_sim GPIO-emulator test verifies the shared initialization code requests an inactive output; it does not verify physical pin behavior. C6 GPIOs are 3.3-V-only; do not apply 5 V directly. Zephyr's UART-backed 1-Wire driver is experimental and requires an external open-drain interface; do not connect the DS18B20 data line directly to the UART pins. No physical wiring, sensor read, or LED behavior has been validated; the board build only checks compilation and devicetree configuration.

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
west build -b native_sim -d app/build/status_led_tests app/tests/status_led
app/build/status_led_tests/zephyr/zephyr.exe
```

The CI runs the temperature-conversion and status LED initialization tests on `native_sim`, and compiles the app for `native_sim` and ESP32-C6. It does not execute firmware on a board or validate radio, sensor wiring/readings, physical LED behavior, security, or portability. The ESP32-C6 Wi-Fi/IEEE 802.15.4 path requires Espressif RF binary blobs; review their license and fetch/build process before enabling connectivity or publishing firmware.

The manifest pins Zephyr v4.4.0. Update it deliberately and rerun both builds before changing the supported baseline.
