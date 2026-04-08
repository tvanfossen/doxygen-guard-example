# doxygen-guard-example

Example IoT project demonstrating doxygen-guard features: validation, traceability, sequence diagram generation, and change-impact analysis.

## Requirements

Requirements are defined in `requirements.yaml`. Each requirement has an `id`, `name`, `module` (used for diagram participant resolution), `description`, and `acceptance_criteria`.

Functions carry both software-level and product-level requirement tags:

```c
/**
 * @brief Read raw temperature from the sensor hardware.
 * @req REQ-0010          ← software-level (Sensor Driver module)
 * @req REQ-PROD-001      ← product-level (Device Environmental Monitoring)
 */
```

The `participant_field` config key (`module` in `.doxygen-guard.yaml`) determines which field resolves diagram participant names.

## Tag Taxonomy

Functions relate to requirements in three ways:

| Tag | Meaning | Diagram behavior |
|-----|---------|-----------------|
| `@req REQ-XXX` | Function fulfills the requirement | Appears as participant/edge in REQ-XXX's sequence diagram |
| `@utility REQ-XXX` | Function is shared infrastructure backing the requirement | Excluded from REQ-XXX's feature diagram; listed in infrastructure table |
| `@after REQ-XXX` | Function's sequence starts after REQ-XXX is satisfied | Rendered as "Preconditions: REQ-XXX" in diagram header |

### Examples in this codebase

**@utility** — `MsgBus_RegisterCallback()` is infrastructure that multiple features depend on:
```c
/**
 * @brief Register the MCU event callback for message dispatch.
 * @utility
 * @utility REQ-0030
 * @utility REQ-0020
 * @utility REQ-0040
 */
```

**@after** — OTA requires comm to be initialized:
```c
/**
 * @brief Handle cloud notification of available firmware update.
 * @req REQ-0040
 * @after REQ-0020
 * @receives EVENT:CLOUD_OTA_AVAILABLE
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
├── provisioning/    Device provisioning state machine
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
