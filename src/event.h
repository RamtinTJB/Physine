#ifndef PHYSINE_EVENT_H_
#define PHYSINE_EVENT_H_

#include "keyboard.h"

enum class EventType {
    KeyPressed, KeyReleased, Closed
};

struct KeyEvent {
    KeyCode code;
};

struct CloseEvent { };

struct Event {
    bool happened = false;
    EventType type;
    union {
        KeyEvent key;   
        CloseEvent close;
    };
};

inline Event make_key_event(EventType type, KeyCode code) {
    Event e = {true, type, .key = {code}};
    return e;
}

inline Event make_close_event() {
    return {true, EventType::Closed, .close = {}};
}

#endif
