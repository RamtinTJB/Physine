#ifndef PHYSINE_TIMER_H_
#define PHYSINE_TIMER_H_

#include <iostream>
#include <functional>
#include <chrono>
#include <thread>

class Timer {
    private:
        std::function<void(void)> func_;
        long interval_;
        std::thread thread_;
        bool running_ = false;

    public:
        Timer() {}
        Timer(std::function<void(void)> func, const long& interval):
            func_ {func}, interval_ {interval} {}

        void start() {
            running_ = true;
            thread_ = std::thread([this]() {
                    while (running_) {
                        auto delta = std::chrono::steady_clock::now() +
                            std::chrono::milliseconds(interval_);
                        std::this_thread::sleep_until(delta);
                        std::cout << "Hello";
                        func_();
                    }
                    });
            thread_.detach();
        }

        void stop() {
            running_ = false;
            thread_.~thread();
        }

        void restart() {
            stop();
            start();
        }

        bool is_running() {
            return running_;
        }

        Timer* set_func(std::function<void(void)> func) {
            func_ = func;
            return this;
        }

        long get_interval() {
            return interval_;
        }

        Timer* set_interval(const long& interval) {
            interval_ = interval;
            return this;
        }

        ~Timer() {
            stop();
        }
};

#endif
