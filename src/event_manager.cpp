#include "event_manager.h"
#include "utils.h"
#include "world.h"

#include <unordered_map>

namespace {
    using Key = sf::Keyboard::Key;
    std::unordered_map<sf::Keyboard::Key, KeyCode> sf_key_mappings {
        {Key::Left, KeyCode::Left},
        {Key::Right, KeyCode::Right},
        {Key::Up, KeyCode::Up},
        {Key::Down, KeyCode::Down},
        {Key::A, KeyCode::A},
        {Key::B, KeyCode::B}, {Key::C, KeyCode::C}, {Key::D, KeyCode::D},
        {Key::E, KeyCode::E}, {Key::F, KeyCode::F}, {Key::G, KeyCode::G},
        {Key::H, KeyCode::H}, {Key::I, KeyCode::I}, {Key::J, KeyCode::J},
        {Key::K, KeyCode::K}, {Key::L, KeyCode::L}, {Key::M, KeyCode::M},
        {Key::N, KeyCode::N}, {Key::O, KeyCode::O}, {Key::P, KeyCode::P},
        {Key::Q, KeyCode::Q}, {Key::R, KeyCode::R}, {Key::S, KeyCode::S},
        {Key::T, KeyCode::T}, {Key::U, KeyCode::U}, {Key::V, KeyCode::V},
        {Key::W, KeyCode::W}, {Key::X, KeyCode::X}, {Key::Y, KeyCode::Y},
        {Key::Z, KeyCode::Z}
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
