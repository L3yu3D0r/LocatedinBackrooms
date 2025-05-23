#ifndef GAME_H
#define GAME_H

#include <Scene.hpp>

class Game {
public:
    static Game& getInstance(){
        static Game instance;
        return instance;
    }
    ~Game();
    void run();
    void init();
    void clean();
    void changeScene(Scene* scene);

    void handleEvent(SDL_Event *event);
    void update(float deltaTime);  // 修改update方法
    void render();
};

#endif