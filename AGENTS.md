# Agent Instructions

## Scope

- Keep application behavior board-neutral and use Zephyr APIs; isolate board-specific pins, radio, storage, and crypto behind adapters.
- ESP32-C6-DevKitC-1 is the first evaluation board, not the only supported target. Do not claim portability until another board is built and tested.
- The project license is undecided. Do not add a license or redistribute assets/blobs until ownership and terms are reviewed.
- Never commit credentials, Wi-Fi configuration, device keys, signing keys, generated builds, or fetched binary blobs.
- Keep outputs inactive at boot. Do not add mains control or replay commands after reconnect.
- Distinguish command acceptance, device-reported state, GPIO state, and physical/contact confirmation.
- Do not claim real sensor telemetry until its source, units, observation time, and failure behavior are implemented and tested.

## Verification

- Zephyr is pinned in `app/west.yml`; use separate build directories for `native_sim` and each board.
- Host tests do not prove hardware, radio, secure storage, or portability behavior.
- Do not fetch Espressif RF blobs until their terms and CI retrieval process are reviewed.
