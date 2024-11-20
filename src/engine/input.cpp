#include "FEHLCD.h"
#include "../global.h"
#include "input.h"

// Input is a singleton; no construction allowed.
Input::Input() { } 

// Update touch states, send a ref to a ClickEvent containing drag information
ClickEvent* Input::update() {
    ClickEvent* event = NULL;
    Vector2 newPos;
    bool newState = LCD.Touch(&position.x, &position.y, false);
    if (pressed && !newState) {
        // This is a mouse up.
        ClickEvent e;
        e.start = Vector2(startPosition);
        e.end = Vector2(position);

        Vector2 relative;
        relative.x = position.x-startPosition.x;
        relative.y = position.y-startPosition.y;

        e.relative = relative;
        e.mouse_down = false;
        event = &e;
    } else if (!pressed && newState) {
        // This is a mouse down.
        startPosition = Vector2(position);
        ClickEvent e;
        e.start = Vector2(position);
        e.end = Vector2{-1, -1};
        e.relative = Vector2{-1, -1};
        e.mouse_down = true;
        event = &e;
    }
    
    position = Vector2(newPos);
    pressed = newState;
    return event;
}
bool Input::isPressed() { return pressed; }
Vector2 Input::getPosition() { return Vector2(position); }
