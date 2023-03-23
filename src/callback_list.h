#ifndef PHYSINE_CALLBACK_LIST_H_
#define PHYSINE_CALLBACK_LIST_H_

#include <functional>
#include <vector>

template <class... Args>
class CallbackList {
    private:
        std::vector<std::function<void(Args...)>> callbacks_;

    public:
        void add_callback(const std::function<void(Args...)>& callback) {
            callbacks_.push_back(callback);
        }

        void execute_all(Args... args) const {
            for (const auto& func : callbacks_) {
                func(std::forward<Args>(args)...);
            }
        }
};

#endif
