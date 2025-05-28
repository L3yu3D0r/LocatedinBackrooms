// SceneMain.h
#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "Define.hpp"
#include "Game.hpp"

class SceneMain : public Scene
{
public:
    SceneMain() : game(Game::getInstance()) {
    };
    ~SceneMain();

    void update(float deltaTime) {};
    void render() override;
    void handleEvent(SDL_Event *event) override;
    void init() override;
    void clean() override;

private:
    Game &game;
};

#endif // SCENE_MAIN_H