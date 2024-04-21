/******************************************************************************************************
 * @file  Application.cpp
 * @brief Implementation of the Application class
 ******************************************************************************************************/

#include "Application.hpp"

#include <stdexcept>
#include <random>

Application::Application(int numParticles)
    : window(), renderer(), font(), event(),
      width(1280), height(960),
      stop(), fullscreen(), keysFlags(),
      numParticles(numParticles), particles(),
      oldTime(), deltaTime() {

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(std::string("SDL_Init failed : ") + SDL_GetError());
    }

    if(IMG_Init(IMG_INIT_PNG) <= 0) {
        throw std::runtime_error(std::string("IMG_Init failed : ") + SDL_GetError());
    }

    if(TTF_Init() != 0) {
        throw std::runtime_error(std::string("TTF_Init failed : ") + SDL_GetError());
    }

    window = SDL_CreateWindow("Particle Simulation",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width, height,
                              WINDOW_FLAGS);
    if(!window) {
        throw std::runtime_error(std::string("Window was not created : ") + SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer) {
        throw std::runtime_error(std::string("Renderer was not created : ") + SDL_GetError());
    }

    font = TTF_OpenFont("data/fonts/courbd.ttf", 20);
    if(!font) {
        throw std::runtime_error(std::string("Font was not opened : ") + SDL_GetError());
    }

    Surface* icon = IMG_Load("data/images/icon.png");
    if(!icon) {
        throw std::runtime_error(std::string("Failed to load app icon : ") + SDL_GetError());
    }

    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);

    for(int i = 0 ; i < numParticles ; ++i) {
        particles.emplace_back(
            vec2::random(0, width, 0, height),
            vec2(), vec2(),
            1.0f);
    }

    SDL_WarpMouseInWindow(window, width / 2, height / 2);
}

Application::~Application() {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Application::run() {
    Color color(255);
    vec2 temp;

//    SDL_ShowCursor(false);

    mouse.x = width / 2.0f;
    mouse.y = height / 2.0f;

    while(!stop) {
        handleEvents();

        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

//        SDL_GetMouseState(&mouse.x, &mouse.y);

        float time = static_cast<float>(SDL_GetTicks64()) / 1000.f;
        deltaTime = 10.0f * (time - oldTime);
        oldTime = time;

        for(const Particle& particle: particles) {
            temp.x = particle.pos.x - mouse.x;
            temp.y = particle.pos.y - mouse.y;

//            color = HSL::hueToRGBA(temp.length() / 2.0f);
//            color = HSL::hueToRGBA(time*10.0f);

            SDL_SetRenderDrawColor(renderer, particle.pos.x / static_cast<float>(width) * 255.0f, particle.pos.y / static_cast<float>(height) * 255.0f, 255, 255);
            SDL_RenderDrawPointF(renderer, particle.pos.x, particle.pos.y);
        }

        updateParticles();
    }
}

void Application::updateParticles() {
    const float pull = 1.0f;
    float len;

    vec2 acceleration;

    for(Particle& particle: particles) {
        particle.force.x = mouse.x - particle.pos.x;
        particle.force.y = mouse.y - particle.pos.y;

        len = particle.force.length();

        particle.force.x /= len;
        particle.force.y /= len;

        particle.force.x *= pull;
        particle.force.y *= pull;

        acceleration.x = particle.force.x / particle.mass;
        acceleration.y = particle.force.y / particle.mass;

        particle.speed.x += deltaTime * acceleration.x;
        particle.speed.y += deltaTime * acceleration.y;

        particle.pos.x += deltaTime * (particle.speed.x + deltaTime * acceleration.x / 2.0f);
        particle.pos.y += deltaTime * (particle.speed.y + deltaTime * acceleration.y / 2.0f);


        if(particle.pos.x < 0) {
            particle.speed.x *= -1.0f;
        }
        if(particle.pos.x > width) {
            particle.speed.x *= -1.0f;
        }
        if(particle.pos.y < 0) {
            particle.speed.y *= -1.0f;
        }
        if(particle.pos.y > height) {
            particle.speed.y *= -1.0f;
        }
    }
}

Texture* Application::createTextureFromSurface(Surface* surface, bool freeSurface) {
    if(!surface) {
        throw std::runtime_error(std::string("Surface wasn't defined (nullptr) : ") + SDL_GetError());
    }

    Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    if(freeSurface) {
        SDL_FreeSurface(surface);
    }

    if(!texture) {
        SDL_FreeSurface(surface);
        throw std::runtime_error(std::string("Couldn't create texture from surface : ") + SDL_GetError());
    }

    return texture;
}

void Application::drawText(int x, int y, const Color& color, const std::string& text) {
    Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if(!surface) {
        throw std::runtime_error{std::string("TTF_RenderText_Solid failed : ") + SDL_GetError()};
    }

    Texture* texture = createTextureFromSurface(surface, false);

    SDL_Rect rect(x, y, surface->w, surface->h);
    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Application::drawText(int x, int y, const Color& textColor, const Color& background, const std::string& text) {
    Surface* surface = TTF_RenderText(font, text.c_str(), textColor, background);
    if(!surface) {
        throw std::runtime_error{std::string("TTF_RenderText failed : ") + SDL_GetError()};
    }

    Texture* texture = createTextureFromSurface(surface, false);

    SDL_Rect rect(x, y, surface->w, surface->h);
    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Application::drawCenteredText(const Rect& reference, const Color& color, const std::string& text) {
    Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if(!surface) {
        throw std::runtime_error{std::string("TTF_RenderText failed : ") + SDL_GetError()};
    }

    Texture* texture = createTextureFromSurface(surface, false);

    SDL_Rect rect(reference.x + (reference.w - surface->w) / 2, reference.y + (reference.h - surface->h) / 2, surface->w, surface->h);
    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Application::handleEvents() {
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN:
                handleInputs();

                break;
            case SDL_KEYUP:
                if(keysFlags.contains(event.key.keysym.scancode)) {
                    keysFlags[event.key.keysym.scancode] = false;
                }

                break;
            case SDL_QUIT:
                stop = true;

                break;
            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    SDL_GetWindowSize(window, &width, &height);
                }

                break;
            default:
                break;
        }
    }
}

void Application::handleInputs() {
    vec2 rand;

    switch(event.key.keysym.scancode) {
        case SDL_SCANCODE_ESCAPE:
            stop = true;

            break;
        case SDL_SCANCODE_F11:
            if(!keysFlags[SDL_SCANCODE_F11]) {
                SDL_SetWindowFullscreen(window, fullscreen ? 0 : SDL_WINDOW_FULLSCREEN);
                fullscreen = !fullscreen;
                keysFlags[SDL_SCANCODE_F11] = true;
            }

            break;
        case SDL_SCANCODE_SPACE:
            for(Particle& particle: particles) {
                particle.speed.x = particle.speed.y = 0;
            }

            break;
        case SDL_SCANCODE_R:
            for(Particle& particle: particles) {
                rand = vec2::random(-200, 200);
                particle.pos.x = mouse.x - rand.x;
                particle.pos.y = mouse.y - rand.y;
            }

            break;
        case SDL_SCANCODE_C:
            SDL_WarpMouseInWindow(window, width / 2, height / 2);
        default:
            break;
    }
}

float Application::random(float min, float max) {
    std::random_device device;
    std::mt19937 generator(device());

    std::uniform_real_distribution<float> distribution(min, max);

    return distribution(generator);
}
