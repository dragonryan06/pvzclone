#include "FEHLCD.h"
#include "../global.h"
#include "input.h"

// Input is a singleton; no construction allowed.
Input::Input() { } 

// Update touch states, send a ClickEvent object containing drag information
ClickEvent Input::update() {
    Vector2 newPos;
    ClickEvent e;
    bool newState = LCD.Touch(&position.x, &position.y, false);
    if (pressed && !newState) {
        // This is a mouse up.
        e.start = Vector2(startPosition);
        e.end = Vector2(position);

        Vector2 relative;
        relative.x = position.x-startPosition.x;
        relative.y = position.y-startPosition.y;

        e.relative = relative;
        e.mouse_down = false;
        e.empty = false;
    } else if (!pressed && newState) {
        // This is a mouse down.
        startPosition = Vector2(position);
        e.start = Vector2(position);
        e.end = Vector2{-1, -1};
        e.relative = Vector2{-1, -1};
        e.mouse_down = true;
        e.empty = false;
    }
    
    position = Vector2(newPos);
    pressed = newState;
    return e;
}
bool Input::isPressed() { return pressed; }
Vector2 Input::getPosition() { return Vector2(position); }
