#ifndef INPUT_H
#define INPUT_H

#include "FEHLCD.h"
#include "../global.h"

/**
 * A simple type representing an input event.
 * Stores all possible FEHLCD input by containing information about clicking down, up, and dragging.
 * @author Ryan
 */
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

/**
 * A singleton object for tracking and managing input. Inspired by the Godot Game Engine's Input singleton.
 * https://stackoverflow.com/questions/1008019/how-do-you-implement-the-singleton-design-pattern
 * 
 * @author Ryan
 */
class Input {
    private:
        /// @brief If the mouse is currently down, the position it was pressed down at.
        Vector2 startPosition {-1, -1};
        /// @brief If the mouse is currently down, its current position, else the last position it went up.
        Vector2 position {-1, -1};
        /// @brief Whether or not the mouse is down.
        bool pressed {false};

        /// @brief Privated constructor to prevent double-instantiation.
        Input();

    public:
        /**
         * Access the one instance of the singleton.
         *      @returns A reference to the one instance of Input.
         * @author Ryan
         */
        static Input& instance() {
            static Input INSTANCE;
            return INSTANCE;
        }
        /**
         * Checks if the mouse state has changed, if so, the returned ClickEvent will be valid.
         *      @returns A ClickEvent that is valid if the mouse has changed state.
         * @author Ryan
         */
        ClickEvent update();
        /**
         * Reports whether or not the mouse is down (screen is being touched).
         *      @returns True if the mouse is down.
         * @author Ryan
         */
        bool isPressed();
        /**
         * Reports the last location of an input event (possibly the position of the mouse).
         *      @returns Last location of an input event (mouse position).
         * @author Ryan
         */
        Vector2 getPosition();
};

#endif