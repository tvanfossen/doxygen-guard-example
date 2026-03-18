"""Analytics data pipeline module."""


## @brief Aggregate sensor readings over a time window.
#  @version 1.0
#  @req REQ-0010
#  @req REQ-0011
def aggregate_readings(readings, window_seconds):
    cutoff = time.time() - window_seconds
    return [r for r in readings if r.timestamp >= cutoff]


## @brief Compute rolling average from aggregated data.
#  @version 1.0
#  @req REQ-0010
def compute_average(readings):
    if not readings:
        return 0.0
    return sum(r.value for r in readings) / len(readings)


## @brief Format telemetry payload for transmission.
#  @version 1.0
#  @req REQ-0020
#  @emits EVENT:TELEMETRY_READY
def build_telemetry_payload(avg_temp, avg_humidity):
    return {
        "temperature": avg_temp,
        "humidity": avg_humidity,
        "timestamp": time.time(),
    }


## @brief Scale a value by a constant factor.
#  @version 1.0
#  @utility
def scale_value(x):
    return x * 2
