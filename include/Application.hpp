/******************************************************************************************************
 * @file  Application.hpp
 * @brief Declaration of the Application class
 ******************************************************************************************************/

#pragma once

extern "C" {
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
}

#include <string>
#include <unordered_map>
#include <vector>

#include "Color.hpp"
#include "HSL.hpp"
#include "Particle.hpp"
#include "Point.hpp"
#include "Rect.hpp"

#define WINDOW_FLAGS (SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)

typedef SDL_Surface Surface;
typedef SDL_Texture Texture;

/**
 * @class Application
 * @brief
 */
class Application {
public:
    Application(int numParticles);
    ~Application();

    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Event event;

    int width, height;

    bool stop;
    bool fullscreen;
    std::unordered_map<SDL_Scancode, bool> keysFlags;

    int numParticles;
    std::vector<Particle> particles;
    void updateParticles();

    Point mouse;

    float oldTime;
    float deltaTime;

    Texture* createTextureFromSurface(Surface* surface, bool freeSurface = true);

    void drawText(int x, int y, const Color& color, const std::string& text);
    void drawText(int x, int y, const Color& textColor, const Color& background, const std::string& text);
    void drawCenteredText(const Rect& reference, const Color& color, const std::string& text);

    void handleEvents();
    void handleInputs();

    static float random(float min, float max);
};