#ifndef PHYSINE_EVENT_MANAGER_H_
#define PHYSINE_EVENT_MANAGER_H_

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <functional>

#include "event.h"
#include "callback_list.h"

class EventManager {
    private:
        std::unordered_map<EventType, CallbackList<Event>> event_listeners_;

    public:
        void check_events(sf::RenderWindow& window);
        void add_listener(EventType type, const std::function<void(Event)>&);
};

#endif
