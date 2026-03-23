# doxygen-guard-example

Example IoT project demonstrating doxygen-guard features: validation, traceability, sequence diagram generation, and change-impact analysis.

## Two Requirements Models

This example ships with two configurations showing that doxygen-guard works with both product-level and software-level requirements:

### Product-level requirements (CSV — default)

```bash
doxygen-guard --config .doxygen-guard.yaml trace --all src/
```

Uses `requirements.csv` with `Subsystem` as the participant field. Product requirements like `REQ-PROD-001 Device Environmental Monitoring` span multiple software modules — many functions trace to one requirement. This is how product teams typically write requirements.

### Software-level requirements (YAML — alternate)

```bash
doxygen-guard --config .doxygen-guard-sw.yaml trace --all src/
```

Uses `requirements.yaml` with `module` as the participant field. Each requirement maps tightly to a single software module with acceptance criteria. This is how embedded software teams decompose architecture.

### Dual-tagging

Source functions carry both levels simultaneously:

```c
/**
 * @brief Read raw temperature from the sensor hardware.
 * @req REQ-0010          ← software-level (Sensor Driver module)
 * @req REQ-PROD-001      ← product-level (Device Environmental Monitoring)
 */
```

The `participant_field` config key determines which column/field resolves the diagram participant names. Switch configs to see different diagram perspectives of the same codebase.

## Tag Taxonomy

Functions relate to requirements in three ways:

| Tag | Meaning | Diagram behavior |
|-----|---------|-----------------|
| `@req REQ-XXX` | Function fulfills the requirement | Appears as participant/edge in REQ-XXX's sequence diagram |
| `@supports REQ-XXX` | Function is shared infrastructure backing the requirement | Excluded from REQ-XXX's feature diagram; listed in infrastructure table |
| `@assumes REQ-XXX` | Function's sequence starts after REQ-XXX is satisfied | Rendered as "Preconditions: REQ-XXX" in diagram header |

### Examples in this codebase

**@supports** — `MsgBus_RegisterCallback()` is infrastructure that multiple features depend on:
```c
/**
 * @brief Register the MCU event callback for message dispatch.
 * @utility
 * @supports REQ-0030
 * @supports REQ-0020
 * @supports REQ-0040
 */
```

**@assumes** — OTA requires comm to be initialized:
```c
/**
 * @brief Handle cloud notification of available firmware update.
 * @req REQ-0040
 * @assumes REQ-0020
 * @handles EVENT:CLOUD_OTA_AVAILABLE
 */
```

The `trace --all` command also generates `docs/generated/infrastructure.md` showing which utility functions back which requirements.

## Project Structure

```
src/
├── sensor/          Sensor hardware abstraction
├── controller/      Control loop and message dispatch
├── comm/            MQTT communication and shadow sync
├── ota/             Over-the-air firmware update
├── event_bus/       Event registration and dispatch
└── analytics/       Python data pipeline (demonstrates Python support)
```

## Running

```bash
# Validate all source files
doxygen-guard validate --no-git src/**/*.c src/**/*.py

# Generate sequence diagrams for all requirements
doxygen-guard trace --all src/

# Generate for a single requirement
doxygen-guard trace --req REQ-0040 src/
```
