# SmartHome-Zephyr-Firmware

Board-neutral Zephyr firmware evaluation project. The ESP32-C6-DevKitC-1 is the first build target; no second board or hardware behavior has been validated.

## Status

The current application only prints a startup message. It does not configure GPIO, connect to a network, read sensors, or control a relay. No mains wiring is part of this project.

The project license is undecided. Do not redistribute or assume reuse rights for this repository, binaries, or upstream Espressif radio blobs until their terms and provenance have been reviewed.

## Workspace setup

Install Python 3 and Git, then install west:

```sh
python -m pip install west
mkdir firmware-workspace
git clone https://github.com/denis-mutuma/SmartHome-Zephyr-Firmware.git firmware-workspace/app
cd firmware-workspace
west init -l app
west update
west sdk install --toolchains riscv64-zephyr-elf
```

Build the portable host target on a supported Linux host and the first board target:

```sh
west build -b native_sim -d app/build/native_sim app
west build -b esp32c6_devkitc -d app/build/esp32c6_devkitc app
```

The ESP32-C6 Wi-Fi/IEEE 802.15.4 path requires Espressif RF binary blobs. Their license and the fetch/build process must be reviewed before enabling connectivity or publishing firmware. The CI currently checks compilation only; it does not claim host simulation, board execution, radio, sensor, security, or portability validation.

The manifest pins Zephyr v4.4.0. Update it deliberately and rerun both builds before changing the supported baseline.
