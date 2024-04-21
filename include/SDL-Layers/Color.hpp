/******************************************************************************************************
 * @file  Color.hpp
 * @brief Definition of the Color struct
 ******************************************************************************************************/

#pragma once

extern "C" {
#include <SDL2/SDL.h>
}

/**
 * @struct Color
 * @brief Functions as a child of the C like struct SDL_Color,
 *        in order to add C++ like functionality such as constructors
 *        and methods.
 */
struct Color : public SDL_Color {
    /**
     * Default constructor
     */
    Color();

    /**
     * @brief Constructs a color with its respective components
     * @param r The red component of the color
     * @param g The green component of the color
     * @param b The blue component of the color
     * @param a The alpha (transparancy) component of the color
     */
    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    /**
     * @brief Constructs a solid color with its respective components
     * @param r The red component of the color
     * @param g The green component of the color
     * @param b The blue component of the color
     */
    Color(Uint8 r, Uint8 g, Uint8 b);

    /**
     * @brief Constructs a grayscale color
     * @param value The value of all three rgb components
     * @param a The alpha (transparancy) component of the color
     */
    Color(Uint8 value, Uint8 alpha);

    /**
     * @brief Constructs a solid grayscale color
     * @param value The value of all three rgb components
     */
    Color(Uint8 value);
};