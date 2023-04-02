#include "event_manager.h"
#include "utils.h"
#include "world.h"

#include <unordered_map>

namespace {
    std::unordered_map<sf::Keyboard::Key, KeyCode> sf_key_mappings {
        {sf::Keyboard::Key::Left, KeyCode::Left},
        {sf::Keyboard::Key::Right, KeyCode::Right},
        {sf::Keyboard::Key::Up, KeyCode::Up},
        {sf::Keyboard::Key::Down, KeyCode::Down}
    };
}

void EventManager::check_events(sf::RenderWindow& window) {
    sf::Event e;
    while (window.pollEvent(e)) {
        if (e.type == sf::Event::Closed && map_contains(event_listeners_, EventType::Closed)) {
            event_listeners_[EventType::Closed].execute_all(make_close_event()); 
        }
        if (e.type == sf::Event::KeyPressed) {
            if (map_contains(sf_key_mappings, e.key.code) && map_contains(event_listeners_, EventType::KeyPressed)) {
                event_listeners_[EventType::KeyPressed].execute_all(make_key_event(
                            EventType::KeyPressed, sf_key_mappings[e.key.code]));
            }
        }
        if (e.type == sf::Event::KeyReleased) {
            if (map_contains(sf_key_mappings, e.key.code) && map_contains(event_listeners_, EventType::KeyReleased)) {
                event_listeners_[EventType::KeyReleased].execute_all(make_key_event(
                            EventType::KeyReleased, sf_key_mappings[e.key.code]));
            }
        }
    }
}

void EventManager::add_listener(EventType type, const std::function<void(Event)>& listener) {
    event_listeners_[type].add_callback(listener);
}
