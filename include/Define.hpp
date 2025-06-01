#ifndef DEFINE_H
#define DEFINE_H

#include <SDL.h>
#include <vector>

class Scene;

struct change_scene {
    bool code;
    Scene *scene;
};

#ifndef SCENE_CLASS_DEFINE
#define SCENE_CLASS_DEFINE
class Scene{
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void init(SDL_Window* window, SDL_Renderer* renderer) = 0;
    virtual change_scene update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual void clean() = 0;
    virtual void handleEvent(SDL_Event* event) = 0;

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    std::vector<SDL_Texture*> textures;
};

static int FPS = 60;
static bool isRunning = true;
static int windowWidth = 1600;
static int windowHeight = 900;

#endif
#endif