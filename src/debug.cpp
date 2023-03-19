#include "debug.h"

void pause() {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1000ms);
}
