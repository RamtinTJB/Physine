#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest.h>
#include <cmath>

#include "rect.h"
#include "common.h"

SCENARIO("Test Constructors and Operators") {
    Rect<double> r(5, 5, 10, 10);
    Rect<double> r2(r);
    Rect<double> r3 = r2;
    CHECK(r == r2);
    CHECK(r == r3);
    CHECK(r2 == r3);
    r.x = 6;
    CHECK(r != r2);
}

SCENARIO("Test Contains") {
    Rect<double> r(5, 5, 10, 10);
    CHECK(r.contains(Vector2f{7, 7}));
    CHECK(r.contains(15, 15));
    CHECK(r.contains(5, 5));
    CHECK(!r.contains(15, 16));
}

SCENARIO("Test Intersect") {
    // TODO Add intersection test 
}
