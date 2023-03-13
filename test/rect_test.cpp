#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest.h>
#include <cmath>
#include <stdexcept>

#include "rect.h"
#include "common.h"

void bad_rect() { Rect<double> r{1, 2, 3}; }
SCENARIO("Test Constructors and Operators") {
    Rect<double> r(5, 5, 10, 10);
    Rect<double> r2(r);
    Rect<double> r3 = r2;
    Rect<double> r4 {5, 5, 10, 10};
    CHECK(r == r2);
    CHECK(r == r3);
    CHECK(r == r4);
    CHECK(r2 == r3);
    r.x = 6;
    CHECK(r != r2);
    CHECK_THROWS_AS(bad_rect(), const std::invalid_argument&);

    r += Vector2f{5, 5};
    CHECK(r.x == 11);
    CHECK(r.y == 10);
}

SCENARIO("Test Contains") {
    Rect<double> r(5, 5, 10, 10);
    CHECK(r.contains(Vector2f{7, 7}));
    CHECK(r.contains(15, 15));
    CHECK(r.contains(5, 5));
    CHECK(!r.contains(15, 16));
}

SCENARIO("Test Intersect") {
    Rect<double> r1(5, 5, 10, 10);
    Rect<double> r2(7, 7, 20, 20);
    Rect<double> r3(2, 2, 50, 50);
    Rect<double> r4(20, 20, 5, 50);

    CHECK(r1.intersects(r2));
    CHECK(r2.intersects(r1));
    CHECK(r1.intersects(r3));
    CHECK(r2.intersects(r3));
    CHECK(r3.intersects(r4));
    CHECK(!r1.intersects(r4));

    Rect<double> int1 = r1.intersection(r2);
    Rect<double> int2 = r2.intersection(r1);
    CHECK(int1 == int2);
    CHECK(int1 == Rect<double>{7, 7, 8, 8});
}
