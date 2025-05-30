#ifndef DEFINE_H
#define DEFINE_H

#include <SDL.h>

#ifndef SCENE_CLASS_DEFINE
#define SCENE_CLASS_DEFINE
class Scene{
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void init() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual void clean() = 0;
    virtual void handleEvent(SDL_Event* event) = 0;
};
#endif

#endif