#ifndef SCENES_HPP
#define SCENES_HPP
#include "Define.hpp"
#include <vector>

class Home_Screen : public Scene {
public:
    void init(SDL_Window *window, SDL_Renderer *renderer)
    {
        this->window = window;
        this->renderer = renderer;
    }
    change_scene update(float deltaTime) {
        return change_scene{false, nullptr};
    }

    void render() {

    }

    void clean() {

    }

    void handleEvent(SDL_Event *event) {

    }

private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    std::vector<SDL_Texture *> textures;
};

class Logo_and_Title_Screen : public Scene
{
public:
    void init(SDL_Window *window, SDL_Renderer *renderer)
    {
        this->window = window;
        this->renderer = renderer;
        cpp_logo = IMG_LoadTexture(this->renderer, "assets/cplusplus.jpg");
        SDL_logo = IMG_LoadTexture(this->renderer, "assets/SDL_logo.png");
    }
    change_scene update(float deltaTime)
    {
        frame_count++;
        if (frame_count / FPS >= 5)
        {
            return change_scene{true, new Home_Screen()};
        }
        auto ks = SDL_GetKeyboardState(NULL);
        if (ks[SDL_SCANCODE_ESCAPE])
        {
            isRunning = false;
        }
        return change_scene{false, nullptr};
    }
    void render()
    {
        // TODO: Fade in/out Show
        SDL_Rect cpp_logo_rect = {windowWidth / 2 - 200, windowHeight / 2 - 70, 140, 140};
        SDL_Rect SDL_logo_rect = {windowWidth / 2 + 100, windowHeight / 2 - 50, 179, 99};
        SDL_RenderCopy(renderer, cpp_logo, NULL, &cpp_logo_rect);
        SDL_RenderCopy(renderer, SDL_logo, NULL, &SDL_logo_rect);
    }
    void clean()
    {
        for (auto i : textures)
        {
            SDL_DestroyTexture(i);
        }
    }
    void handleEvent(SDL_Event *event)
    {
    }

private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *cpp_logo = nullptr;
    SDL_Texture *SDL_logo = nullptr;
    std::vector<SDL_Texture *> textures;
    long long frame_count = 0;
};

#endif