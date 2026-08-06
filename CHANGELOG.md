# Changelog

All notable changes to RAPS are documented in this file.

## [3.5.0] - 2026-05-15

### Changed
- Rename repository to RAPS and bump version to 3.5.0.
- Remove all references and contributions of Marcel Krüger.
- Replace HLV (Helix-Light-Vortex) terminology and sci-fi theoretical math with classical propulsion, dynamic state, and thermodynamic engineering models.
- Ensure Software-in-the-Loop (SIL) tests are fully functional and pass with the revised math structure.

## [3.2.1] - 2026-05-04

### Security
- Fix division-by-zero in power & resource management when `elapsed_ms == 0`
- Fix PID controller parameter type (`float` → `uint64_t`) and add proportional-only fallback for zero dt
- Fix Monte Carlo division by zero in PDT engine when `monte_carlo_runs == 0`
- Clamp exponential argument in field coupling stress model to prevent `+inf` propagation
- Add request size limit (`MAX_REQUEST_SIZE = 8192`) and CORS risk comment to REST API server
- Add compile-time guard to prevent stub cryptography in production builds

### Robustness
- Add NaN/Inf state sanitizer (`include/safety/state_sanitizer.hpp`) with check in APCU safety update
- Fix rollback store bounds: evict oldest entry instead of resetting counter to zero
- Fix telemetry report truncated-line detection for JSONL lines exceeding buffer size
- Fix implicit narrowing in artificial gravity rate-limit computation

### Architecture
- Deduplicate `RAPSConfig` struct and conflicting constants from `hlv_field_dynamics.hpp`
- Add non-production compile guard to reference integrator header
- Fix broken include paths in `advanced_propulsion_control_unit.hpp`

### Maintainability
- Add `VERSION` file (`3.3.0`)
- Add `CHANGELOG.md`
- Add `RAPSVersion` namespace constants to `raps_core_types.hpp`
- Update REST API health endpoint to use `RAPSVersion::STRING`
