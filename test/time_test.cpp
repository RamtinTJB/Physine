#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest.h>
#include <chrono>
#include <thread>

#include "clock.h"

SCENARIO("Sleep Test") {
    using namespace std::chrono_literals;
    Clock c;
    std::this_thread::sleep_for(100ms);
    CHECK(c.delta_time() == doctest::Approx(0.1).epsilon(0.01));
}
