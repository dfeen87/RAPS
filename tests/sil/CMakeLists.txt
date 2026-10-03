# ============================================================
# RAPS — Software-in-the-Loop (SIL) Test Suite
# ============================================================

cmake_minimum_required(VERSION 3.16)

project(raps_sil_tests LANGUAGES CXX)

# ------------------------------------------------------------
# Build options
# ------------------------------------------------------------

option(RAPS_ENABLE_SIL_FAULTS
    "Enable SIL fault injection in PlatformHAL"
    ON
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

function(raps_configure_test target)
    target_include_directories(${target} PRIVATE
        ${PROJECT_SOURCE_DIR}/../../include
        ${PROJECT_SOURCE_DIR}/../../src
    )
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        target_compile_options(${target} PRIVATE
            -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wno-unused-parameter
            -UNDEBUG
        )
    endif()
endfunction()

# ------------------------------------------------------------
# Test executable
# ------------------------------------------------------------

add_executable(raps_sil_fault_tests
    test_fault_injection.cpp
    ../../src/platform/platform_hal.cpp
)

# ------------------------------------------------------------
# Include paths
# ------------------------------------------------------------

target_include_directories(raps_sil_fault_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/../../include
    ${PROJECT_SOURCE_DIR}/../../src
)

# ------------------------------------------------------------
# Compile definitions
# ------------------------------------------------------------

if (RAPS_ENABLE_SIL_FAULTS)
    target_compile_definitions(raps_sil_fault_tests PRIVATE
        RAPS_ENABLE_SIL_FAULTS=1
    )
endif()

# ------------------------------------------------------------
# Warnings & safety flags
# ------------------------------------------------------------

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(raps_sil_fault_tests PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wconversion
        -Wno-unused-parameter
    )
endif()

# ------------------------------------------------------------
# Optional coverage instrumentation
# (enabled later when we add coverage gates)
# ------------------------------------------------------------

option(RAPS_ENABLE_COVERAGE "Enable coverage instrumentation" OFF)

if (RAPS_ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    message(STATUS "SIL coverage instrumentation enabled")

    target_compile_options(raps_sil_fault_tests PRIVATE
        -O0
        -g
        --coverage
    )

    target_link_options(raps_sil_fault_tests PRIVATE
        --coverage
    )
endif()

# ------------------------------------------------------------
# Register with CTest
# ------------------------------------------------------------

enable_testing()

add_test(
    NAME raps_sil_fault_injection
    COMMAND raps_sil_fault_tests
)

# ------------------------------------------------------------
# Rollback Execution Tests
# ------------------------------------------------------------

add_executable(raps_sil_rollback_tests
    test_rollback_execution.cpp
    ../../src/platform/platform_hal.cpp
)

target_include_directories(raps_sil_rollback_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/../../include
    ${PROJECT_SOURCE_DIR}/../../src
)

if (RAPS_ENABLE_SIL_FAULTS)
    target_compile_definitions(raps_sil_rollback_tests PRIVATE
        RAPS_ENABLE_SIL_FAULTS=1
    )
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(raps_sil_rollback_tests PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wconversion
        -Wno-unused-parameter
    )
endif()

add_test(
    NAME raps_sil_rollback_test
    COMMAND raps_sil_rollback_tests
)

# ------------------------------------------------------------
# Version Tests
# ------------------------------------------------------------
add_executable(raps_sil_version_tests
    test_version.cpp
)

target_include_directories(raps_sil_version_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/../../include
    ${PROJECT_SOURCE_DIR}/../../src
)

add_test(
    NAME raps_sil_version_test
    COMMAND raps_sil_version_tests
)
set_tests_properties(raps_sil_version_test PROPERTIES
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/../.."
)

# ------------------------------------------------------------
# Stability Indicator Tests
# ------------------------------------------------------------
add_executable(raps_sil_stability_tests
    test_stability_indicator.cpp
)

target_include_directories(raps_sil_stability_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/../../include
    ${PROJECT_SOURCE_DIR}/../../src
)

add_test(
    NAME raps_sil_stability_test
    COMMAND raps_sil_stability_tests
)

# ------------------------------------------------------------
# DSM WNN Enforcement Tests
# ------------------------------------------------------------
add_executable(raps_sil_dsm_wnn_tests
    test_dsm_wnn.cpp
    ../../src/platform/platform_hal.cpp
)

target_include_directories(raps_sil_dsm_wnn_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/../../include
    ${PROJECT_SOURCE_DIR}/../../src
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(raps_sil_dsm_wnn_tests PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wconversion
        -Wno-unused-parameter
    )
endif()

add_test(
    NAME raps_sil_dsm_wnn_test
    COMMAND raps_sil_dsm_wnn_tests
)

add_executable(raps_sil_policy_tests test_mission_policy.cpp)
raps_configure_test(raps_sil_policy_tests)
add_test(NAME raps_sil_policy_test COMMAND raps_sil_policy_tests)

find_package(Threads REQUIRED)
add_executable(raps_sil_hil_tcp_tests
    test_hil_tcp_device.cpp
    ../../src/hil/hil_tcp_device.cpp
    ../../src/hil/hil_device_interface.cpp
)
raps_configure_test(raps_sil_hil_tcp_tests)
target_link_libraries(raps_sil_hil_tcp_tests PRIVATE Threads::Threads)
add_test(NAME raps_sil_hil_tcp_test COMMAND raps_sil_hil_tcp_tests)
set_tests_properties(raps_sil_hil_tcp_test PROPERTIES TIMEOUT 5)

# Assertions in legacy behavioral tests remain active in Release builds.
raps_configure_test(raps_sil_version_tests)
raps_configure_test(raps_sil_stability_tests)
