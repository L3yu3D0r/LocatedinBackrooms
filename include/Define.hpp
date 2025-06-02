#ifndef DEFINE_H
#define DEFINE_H

#include <SDL.h>
#include <vector>
#include <string>

class Scene;

struct change_scene
{
    bool code;
    Scene *scene;
};

static const change_scene noChange = {false, nullptr};

#ifndef SCENE_CLASS_DEFINE
#define SCENE_CLASS_DEFINE
class Scene
{
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void init(SDL_Window *window, SDL_Renderer *renderer) = 0;
    virtual change_scene update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual void clean() = 0;
    virtual void handleEvent(SDL_Event *event) = 0;

private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    std::vector<SDL_Texture *> textures;
};

static int FPS = 60;
static bool isRunning = true;
static int windowWidth = 1600;
static int windowHeight = 900;
static TTF_Font *MapleMono_Regular_24;
static TTF_Font *VonwaonBitmap_16px_24;
static bool renderNoClean = false;
static long long unreal_game_time = FPS;

class BaseButton
{
public:
    virtual bool assertPosition(int x, int y) = 0;
    virtual void draw() = 0;
};

class BaseButtonRect : public BaseButton
{
public:
    BaseButtonRect() : renderer(nullptr), rect({0,0,0,0}), color({0,0,0,0}) {}  // default constructor
    BaseButtonRect(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color) : renderer(renderer), rect(rect), color(color) {}

    void draw()
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
    }

    bool assertPosition(int x, int y)
    {
        return x >= rect.x && y >= rect.y && x <= (rect.x + rect.w) && y <= (rect.y + rect.h);
    }

    SDL_Renderer *renderer;
    SDL_Rect rect;
    SDL_Color color;
};

class BaseButtonRectText : public BaseButtonRect
{
public:
    /**
     * @brief BaseButtonRectText 类的构造函数
     *
     * 初始化 BaseButtonRectText 对象，包括渲染器、矩形区域、颜色、文本、字体和文本颜色。
     * 支持UTF-8
     *
     * @param renderer SDL_Renderer* 类型的渲染器指针，用于绘制按钮
     * @param rect SDL_Rect 类型的矩形区域，表示按钮的位置和大小
     * @param color SDL_Color 类型的颜色，表示按钮的背景颜色
     * @param text std::string 类型的文本，表示按钮上显示的文字
     * @param font TTF_Font* 类型的字体指针，用于渲染文本
     * @param text_color SDL_Color 类型的颜色，表示文本的颜色
     */
    BaseButtonRectText(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color, std::string text, TTF_Font *font, SDL_Color text_color)
        : renderer(renderer), rect(rect), color(color), text(text), font(font), text_color(text_color) {}
    
    void draw()
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
        SDL_Surface *sf = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), text_color, rect.w);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, sf);
        text_rect = {rect.x + (rect.w - sf->w) / 2, rect.y + (rect.h - sf->h) / 2, sf->w, sf->h};
        SDL_RenderCopy(renderer, texture, NULL, &text_rect);
        SDL_FreeSurface(sf);
        SDL_DestroyTexture(texture);
    }

    bool assertPosition(int x, int y)
    {
        return x >= rect.x && y >= rect.y && x <= (rect.x + rect.w) && y <= (rect.y + rect.h);
    }

    SDL_Renderer *renderer;
    SDL_Rect rect;
    SDL_Color color;
    std::string text;
    TTF_Font *font;
    SDL_Color text_color;
    SDL_Rect text_rect;
};

std::vector<BaseButton *> buttons;

BaseButton *getTopButtonofPosition(int x, int y)
{
    for (auto button : buttons)
    {
        if (button->assertPosition(x, y))
        {
            return button;
        }
    }
    return nullptr;
}

#endif
#endif