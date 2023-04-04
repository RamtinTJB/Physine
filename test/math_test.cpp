#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest.h>

#include "ph_math.h"

SCENARIO("Approx Test") {
    CHECK(1.0 == Approx(1.000001));
    CHECK(100.0 == Approx(95.0).epsilon_ratio(0.06));
}
