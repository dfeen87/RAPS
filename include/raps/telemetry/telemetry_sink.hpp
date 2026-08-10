#pragma once
/*
 * Telemetry sink interface: keeps the core logger decoupled from export mechanisms.
 *
 * Copyright (c) 2026 Don Michael Feeney Jr.
 * Licensed under the MIT License.
 */

#include "telemetry_event.hpp"

namespace raps::telemetry {

class ITelemetrySink {
public:
  virtual ~ITelemetrySink() = default;

  // Called by exporter / drain loop. Must be fast and must not throw.
  virtual void on_event(const TelemetryEvent& ev) noexcept = 0;

  // Called for summary stats, optional.
  virtual void on_dropped(uint64_t dropped_total) noexcept {}
};

} // namespace raps::telemetry
