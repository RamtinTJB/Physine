#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest.h>
#include <cmath>
#include <stdexcept>

#include "circle.h"
#include "common.h"

void bad_circle() { Circle<double> c{1, 2, 3, 4}; }
SCENARIO("Test constructors and Operators") {
    Circle<double> c1 {100, 100, 20};
    Circle<double> c2 = c1;
    Circle<double> c3(c1);
    Circle<double> c4(200, 200, 10);
    Circle<double> c5(100, 100, 20);

    CHECK(c1 == c2);
    CHECK(c1 == c3);
    CHECK(c2 == c2);
    CHECK(c1 == c5);
    CHECK(c3 != c4);
    CHECK_THROWS_AS(bad_circle(), const std::invalid_argument&);

    c1 += Vector2f{10, 20};
    CHECK(c1.x == 110);
    CHECK(c1.y == 120);
}

SCENARIO("Test Contains") {
    Circle<double> c {200, 200, 50};
    CHECK(c.contains(Vector2f{200, 200}));
    CHECK(c.contains(190, 190));
    CHECK(c.contains(200, 151));
    CHECK(!c.contains(200, 150));
    CHECK(!c.contains(250, 200));
}

SCENARIO("Test Intersects") {
    Circle<double> c1 {200, 200, 50};
    Circle<double> c2 {200, 100, 51};
    Circle<double> c3 {200, 100, 50};
    Circle<double> c4 {200, 200, 40};

    CHECK(c1.intersects(c2));
    CHECK(c2.intersects(c1));
    CHECK(!c1.intersects(c3));
    CHECK(c1.intersects(c4));
}
