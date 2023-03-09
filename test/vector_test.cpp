#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest.h>
#include <cmath>
#include <stdexcept>

#include "common.h"

SCENARIO("Magnitude Test") {
    Vector3 v1 {1, 1, 1};
    CHECK(v1.magnitude() == doctest::Approx(std::sqrt(3)));
    CHECK(v1.magnitude() == v1.size());

    Vector2 v2 {3, 4};
    CHECK(v2.magnitude() == doctest::Approx(5));

    Vector<int, 2> v3 {3, 4};
    CHECK(v3.magnitude() == 5);

    Vector<double, 4> v4 {1, 2, 3, 4};
    CHECK(v4.magnitude() == doctest::Approx(std::sqrt(30)));

    Vector3 v5;
    CHECK(v5.magnitude() == 0);
}

SCENARIO("Empty Vector") {
    Vector3 v;
    REQUIRE(v.dimension() == 3);
    CHECK(v.magnitude() == doctest::Approx(0));

    Vector<int, 4> v1;
    REQUIRE(v1.dimension() == 4);
    CHECK(v1.magnitude() == 0);
}

void invalid_initialization() { Vector3 v {1, 2, 3, 4}; }
SCENARIO("Exceptions") {
    Vector3 v {1, 1, 1};
    CHECK_THROWS_AS(v.at(3), const std::out_of_range&);
    CHECK_THROWS_AS(v.at(-1), const std::out_of_range&);
    CHECK_THROWS_AS(invalid_initialization(), const std::invalid_argument&);
    Vector<double, 4> v1 {1, 1, 1, 1};
    CHECK_THROWS_AS(v1.cross(v), const std::logic_error);
}

SCENARIO("Equality Test") {
    Vector3 v1 {1.1, 2, 3};
    Vector3 v2 {1.1, 2, 3};
    Vector<double, 4> v3 {1, 2, 3, 4};
    Vector3 v4{1, 2, 4};
    Vector3 v5{2.1, 4, 7};

    CHECK(v1 == v2);
    CHECK(v1 != v3);
    CHECK(v1 != v4);
    CHECK(v1 + v4 == v5);
}

SCENARIO("Operators") {
    Vector3 v1 {1, 1, 1};
    Vector3 v2 {1, 2, 3};
    Vector3 res {2, 3, 4};
    Vector3 v4 {3, 3, 3};
    CHECK(v1 + v2 == res);
    CHECK(res - v1 == v2);
    CHECK(v1 - res == v2.opposite());
    CHECK(-(v1-res) == v2);
    CHECK(3.0*v1 == v4);

    v1 += v2;
    CHECK(v1 == res);

    v1 -= v2;
    CHECK(v1 == Vector3{1, 1, 1});
}

SCENARIO("Constructors") {
    Vector3 v1 {1, 1, 1};
    Vector3 v2(v1);
    Vector3 v3 = v1;

    CHECK(v1 == v2);
    CHECK(v1 == v3);
    CHECK(v2 == v3);
}

SCENARIO("Dot Product") {
    Vector3 v1 {1, 2, 3};
    Vector3 v2 {4, 5, 6};

    CHECK(v1.dot(v2) == v2.dot(v1));
    CHECK(v1.dot(v1) == doctest::Approx(std::pow(v1.magnitude(), 2)));
    CHECK(v2.dot(v2) == doctest::Approx(std::pow(v2.magnitude(), 2)));
    CHECK(v1.dot(v2) == 32);
    CHECK(v1.dot(v1.cross(v2)) == doctest::Approx(0));
    CHECK(v1.dot(v2.cross(v1)) == doctest::Approx(0));
}

SCENARIO("Cross Product") {
    Vector3 v1 {1, 2, 3};
    Vector3 v2 {4, 5, 6};
    Vector3 res {-3, 6, -3};

    CHECK(v1.cross(v2) == res);
    CHECK(v2.cross(v1) == res.opposite());
}

SCENARIO("Projection:") {
    Vector2 v1 {3, 4};
    Vector2 v2 {5, -12};

    CHECK(v1.projection_unto(v2) == Vector2{-165.0/169, 396.0/169});
}
