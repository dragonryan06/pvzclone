#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>

/**
 * A two-dimensional vector, inspired by the Godot Game Engine.
 * 
 * @author Ryan
 */
typedef struct Vector2 {
    /// @brief The Vector2's x-dimension.
    float x;
    /// @brief The Vector2's y-dimension.
    float y;
} Vector2;

/**
 * Converts an integer number of seconds into a string of format mm:ss.
 *      @param int The time, in seconds.
 *      @returns A std::string of the format mm:ss.
 * 
 * @author Ryan
 */
std::string stringifyTime(int);

#endif