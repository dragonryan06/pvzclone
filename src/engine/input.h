#ifndef INPUT_H
#define INPUT_H

#include "FEHLCD.h"
#include "../global.h"

typedef struct ClickEvent {
    /// @brief If false, this ClickEvent should be ignored.
    bool empty {true};
    /// @brief If this is a mouse up or down event (if up, then end and relative are useful)
    bool mouse_down {true};
    /// @brief The position of the mouse down
    Vector2 start {-1,-1};
    /// @brief The position of the mouse up (-1, -1) if mouse_down
    Vector2 end {-1,-1};
    /// @brief The vector between the mouse down and up (-1, -1) if mouse_down
    Vector2 relative {-1,-1};
} ClickEvent;

// Input singleton
class Input {
    private:
        Vector2 startPosition {-1, -1};
        Vector2 position {-1, -1};
        bool pressed {false};

        Input();

    public:
        static Input& instance() {
            static Input INSTANCE;
            return INSTANCE;
        }
        ClickEvent update();
        bool isPressed();
        Vector2 getPosition();
};

#endif