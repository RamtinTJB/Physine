#ifndef PHYSINE_CLOCK_H_
#define PHYSINE_CLOCK_H_

#include <chrono>

class Clock {
    private:
        std::chrono::time_point<std::chrono::steady_clock> now_;

    public:
        Clock() {
            restart();
        }

        void restart() {
            now_ = std::chrono::steady_clock::now();
        }

        double delta_time() const {
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> diff = end - now_;
            return diff.count();
        }
};

#endif
