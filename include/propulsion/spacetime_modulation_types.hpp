#pragma once

#include <cstdint>
#include "raps/core/raps_core_types.hpp"

// =====================================================
// Core Data Structures - Classical Propulsion Dynamics
// =====================================================

struct SpacetimeModulationState {
    float power_draw_GW{0.0f};                  // Thermal/Electrical Power Draw (GW)

    // Primary propulsion control fields (mapped to classical nozzle & thrust systems)
    float warp_field_strength{0.0f};            // Core thrust intensity factor (unitless)
    float gravito_flux_bias{0.0f};              // Nozzle/exhaust deflection bias (unitless)
    float spacetime_curvature_magnitude{0.0f};   // Main chamber structural stress/load magnitude

    float time_dilation_factor{1.0f};           // Nozzle expansion thermal dilation ratio
    float induced_gravity_g{0.0f};              // Thrust-induced forward acceleration (g's)

    float subspace_efficiency_pct{0.0f};        // Combustion/thermodynamic efficiency (%)
    double total_displacement_km{0.0};          // Integrated flight trajectory distance (km)

    float remaining_antimatter_kg{0.0f};        // Primary propellant mass (kg)
    float quantum_fluid_level{0.0f};            // Main loop coolant fluid level (L)

    float field_coupling_stress{0.0f};          // System structural coupling stress
    float spacetime_stability_index{1.0f};      // Overall mechanical/dynamic stability index
    float control_authority_remaining{1.0f};    // Controller authority margin (0.0 to 1.0)

    bool emergency_mode_active{false};          // Safe-state fallback active flag

    uint64_t timestamp_ms{0};
    Hash256 state_hash{};
};

struct SpacetimeModulationCommand {
    float target_warp_field_strength{0.0f};     // Target core thrust intensity factor
    float target_gravito_flux_bias{0.0f};       // Target exhaust deflection bias
    float target_time_dilation_factor{1.0f};    // Target nozzle thermal expansion ratio
    float target_artificial_gravity_g{0.0f};    // Target vehicle acceleration in G's

    float target_quantum_fluid_flow_rate{0.0f}; // Target coolant flow rate (L/s)
    float target_power_budget_GW{0.0f};         // Maximum allowed thermal/electrical power budget (GW)

    bool enable_emergency_damping{false};       // Enable dynamic stress damping
    bool enable_resonance_suppression{false};   // Enable active chamber resonance suppression
    bool enable_time_dilation_coupling{true};   // Enable coupled thermal expansion feedback
};
