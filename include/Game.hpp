#ifndef GAME_H
#define GAME_H

#include "Define.hpp"

class SceneMain;  // 前向声明

class Game
{
public:
    static Game &getInstance()
    {
        static Game instance;
        return instance;
    }
    ~Game()
    {
        clean();
    };
    void run()
    {
        while (isRunning)
        {
            auto frameStart = SDL_GetTicks(); // 记录帧开始时间

            SDL_Event event;
            handleEvent(&event);
            update(deltaTime); // 传递deltaTime
            render();

            auto frameEnd = SDL_GetTicks();    // 记录帧结束时间
            auto diff = frameEnd - frameStart; // 计算帧处理时间

            // 帧率限制和deltaTime计算
            if (diff < frameTime)
            {
                SDL_Delay(frameTime - diff);     // 如果处理太快，延迟一下
                deltaTime = frameTime / 1000.0f; // 转换为秒
            }
            else
            {
                deltaTime = diff / 1000.0f; // 如果处理较慢，使用实际时间
            }
        }
    };
    void Game::init()
    {
        // al 初始化
        al::Scoped_Log_Init raii;
        // SDL 初始化
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
            isRunning = false;
        }
        // IMG 初始化
        if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG))
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "IMG could not initialize! IMG_Error: %s\n", IMG_GetError());
            isRunning = false;
        }
        // SDL_Mixer初始化
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
            isRunning = false;
        }
        // TTF 初始化
        if (TTF_Init() != 0)
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
            isRunning = false;
        }

        al::log_d("Init sucessfully");
        // 创建窗口
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
        if (window == nullptr)
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
            isRunning = false;
        }
        // 创建渲染器
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr)
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
            isRunning = false;
        }
        // currentScene将在源文件中初始化
    };
    void clean()
    {
        SDL_Quit();
    };
    void changeScene(Scene *scene) {   
    };
    void handleEvent(SDL_Event *event) {
    };
    void update(float deltaTime) {
    };
    void render() {
    };

private:
    Game &operator=(const Game &) = delete;
    bool isRunning = true;
    Scene *currentScene = nullptr;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    int windowWidth = 600;
    int windowHeight = 800;
    int FPS = 60;     // 目标帧率
    Uint32 frameTime; // 每帧的目标时间（毫秒）
    float deltaTime;
};

#endif