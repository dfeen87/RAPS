#include "policy/mission_policy.hpp"

#include <chrono>
#include <iostream>
#include <limits>

namespace {
int failures = 0;

void expect_violation(const apms::policy::PolicyResult& result, const char* message) {
    if (!result.violated) {
        ++failures;
        std::cerr << "FAIL: " << message << '\n';
    }
}
} // namespace

int main() {
    using namespace apms::policy;
    ScalarLimit scalar{0.0, 1.0, Severity::HardLimit, "normalized input"};
    expect_violation(scalar.evaluate(std::numeric_limits<double>::quiet_NaN()),
                     "NaN scalar input must not pass a safety envelope");
    ScalarLimit malformed{2.0, 1.0, Severity::HardLimit, "malformed bounds"};
    expect_violation(malformed.evaluate(1.5),
                     "an inverted scalar envelope must fail closed");

    SlewRateLimit slew{1.0, Severity::HardLimit, "command slew"};
    expect_violation(slew.evaluate(0.0, 1.0, Duration::zero()),
                     "a non-positive interval must not bypass a slew limit");
    expect_violation(slew.evaluate(0.0, std::numeric_limits<double>::infinity(),
                                   std::chrono::seconds(1)),
                     "non-finite slew input must fail closed");

    DurationLimit duration{std::chrono::seconds(1), Severity::HardLimit, "active time"};
    expect_violation(duration.evaluate(Duration{-1}),
                     "a negative observed duration must fail closed");

    if (failures != 0) return 1;
    std::cout << "Mission policy fail-closed tests passed.\n";
    return 0;
}
