/******************************************************************************************************
 * @file  Point.hpp
 * @brief Declaration of the Point struct
 ******************************************************************************************************/

#pragma once

extern "C" {
#include <SDL2/SDL.h>
}

/**
 * @struct Point
 * @brief Functions as a child of the C like struct SDL_Point,
 *        in order to add C++ like functionality such as constructors
 *        and methods.
 */
struct Point : public SDL_Point {
    /**
     * @brief Default constructor.
     */
    Point();

    /**
     * @brief Constructs a point at coordinates (x ; y)
     * @param x The x coordinate of the point
     * @param y The y coordinate of the point
     */
    Point(int x, int y);

    /**
     * @brief Constructs a point at coordinates (value ; value)
     * @param value The value of the coordinates of the point
     */
    Point(int value);
};