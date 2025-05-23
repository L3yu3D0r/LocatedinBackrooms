// Scene.h
#ifndef SCENE_H
#define SCENE_H

#include <SDL.h>

// Scene.h
class Scene{
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void init() = 0;
    virtual void update(float deltaTime) = 0;  // 添加deltaTime参数
    virtual void render() = 0;
    virtual void clean() = 0;
    virtual void handleEvent(SDL_Event* event) = 0;
};

#endif // SCENE_H