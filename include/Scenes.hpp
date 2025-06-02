#ifndef SCENES_HPP
#define SCENES_HPP
#include "Define.hpp"
#include <vector>
#include <random>
#include <iostream>

class Home_Screen : public Scene
{
public:
    void init(SDL_Window *window, SDL_Renderer *renderer)
    {
        this->window = window;
        this->renderer = renderer;
        Games = new BaseButtonRectText(renderer, {windowWidth / 3, windowHeight / 3, windowWidth / 3, windowHeight / 3}, {0,0,0,255}, "游戏...", VonwaonBitmap_16px_24, {255,255,255,255});
        buttons.push_back(Games);
    }
    change_scene update(float deltaTime)
    {
        return noChange;
    }

    void render()
    {
        for (auto i : buttons) {
            i->draw();
        }
    }

    void clean()
    {
        for (auto i : buttons) {
            delete i;
        }
    }

    void handleEvent(SDL_Event *event)
    {
        if (event->type == SDL_MOUSEBUTTONDOWN) {
            if (event->button.button == SDL_BUTTON_LEFT) {
                auto topbutton = getTopButtonofPosition(event->button.x, event->button.y);
                if (topbutton != nullptr) {
                    if (topbutton == Games) {
                        std::cout << "Games button clicked";
                    }
                }
            }
        }
    }

private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    std::vector<SDL_Texture *> textures;
    BaseButtonRectText* Games;
    BaseButton *lastframetopbutton = nullptr;
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
        textures.push_back(cpp_logo);
        textures.push_back(SDL_logo);
        sf = TTF_RenderUNICODE_LCD_Wrapped(
            MapleMono_Regular_24, (const Uint16 *)(L"LocatedinBackrooms"),
            {255, 255, 255, 255}, {0, 0, 0, 255}, 0
        );
        text = SDL_CreateTextureFromSurface(renderer, sf);
        textures.push_back(text);
        cpp_logo_rect = {windowWidth / 2 - 200, windowHeight / 2 - 70, 140, 140};
        SDL_logo_rect = {windowWidth / 2 + 100, windowHeight / 2 - 50, 179, 99};
        tr = {windowWidth / 2 - sf->w / 2, windowHeight / 2 - sf->h / 2, sf->w, sf->h};
        gen.seed(rd());
        idisw = std::uniform_int_distribution<int>(0, windowWidth);
        idish = std::uniform_int_distribution<int>(0, windowHeight);
    }
    change_scene update(float deltaTime)
    {
        frame_count++;
        if (frame_count / FPS >= 3)
        {
            if (!c)
            {
                renderNoClean = true;
                c = true;
                frame_count = 0;
            }
            else
            {
                // renderNoClean = false;
                return change_scene{true, new Home_Screen()};
            }
        }
        auto ks = SDL_GetKeyboardState(NULL);
        if (ks[SDL_SCANCODE_ESCAPE])
        {
            isRunning = false;
        }
        return noChange;
    }
    void render()
    {
        if (!c)
        {
            // TODO: Fade in/out Show
            SDL_RenderCopy(renderer, cpp_logo, NULL, &cpp_logo_rect);
            SDL_RenderCopy(renderer, SDL_logo, NULL, &SDL_logo_rect);
        }
        else
        {
            tr = {idisw(gen), idish(gen), sf->w, sf->h};
            sf = TTF_RenderUNICODE_LCD_Wrapped(
                MapleMono_Regular_24, (const Uint16 *)(L"LocatedinBackrooms"),
                {
                    static_cast<unsigned char>(idis255(gen)), static_cast<unsigned char>(idis255(gen)),
                    static_cast<unsigned char>(idis255(gen)), static_cast<unsigned char>(idis255(gen))
                },
                {
                    static_cast<unsigned char>(idis255(gen)), static_cast<unsigned char>(idis255(gen)),
                    static_cast<unsigned char>(idis255(gen)), static_cast<unsigned char>(idis255(gen))
                }, 0
            );
            SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, sf);
            textures.push_back(text);
            SDL_RenderCopy(renderer, text, NULL, &tr);
        }
    }
    void clean()
    {
        for (auto i : textures)
        {
            SDL_DestroyTexture(i);
        }
        SDL_FreeSurface(sf);
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
    bool c = false;
    SDL_Surface *sf;
    SDL_Texture *text = nullptr;
    SDL_Rect cpp_logo_rect;
    SDL_Rect SDL_logo_rect;
    std::vector<SDL_Texture *> texts;
    SDL_Rect tr;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> idisw;
    std::uniform_int_distribution<int> idish;
    std::uniform_int_distribution<int> idis255;
};

#endif