#ifndef PHYSINE_EVENT_H_
#define PHYSINE_EVENT_H_

#include "keyboard.h"

enum class EventType {
    KeyPressed, KeyReleased
};

struct KeyEvent {
    KeyCode code;
};

struct Event {
    bool happened = false;
    EventType type;
    union {
        KeyEvent key;   
    };
};

inline Event make_key_event(EventType type, KeyCode code) {
    Event e = {true, type, .key = {code}};
    return e;
}

#endif
