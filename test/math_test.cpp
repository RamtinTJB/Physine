#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest.h>

#include "ph_math.h"

SCENARIO("Approx Test") {
    CHECK(1.0 == Approx(1.000001));
    CHECK(100.0 == Approx(95.0).epsilon_ratio(0.06));
}

SCENARIO("Rotation Test") {
    Vector2f output = rotate(Vector2f{3, 4}, Vector2f(), 30);
    CHECK(output.x() == Approx(4.598076));
    CHECK(output.y() == Approx(1.964101));

    output = rotate(Vector2f{3, 4}, Vector2f() , -30);
    CHECK(output.x() == Approx(0.5980762));
    CHECK(output.y() == Approx(4.9641016));

    output = rotate(Vector2f{4, 8}, Vector2f{2, 5}, 47);
    CHECK(output.x() == Approx(5.558057825));
    CHECK(output.y() == Approx(5.583287677));
}
