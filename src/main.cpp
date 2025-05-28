#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "log.h"
#include "Game.hpp"

int main(int, char**) {
    al::Scoped_Log_Init raii;
    al::log_i("Game initing");
    Game game = Game::getInstance();
    game.init();
    game.run();
    al::log_i("Game quitting");
    return 0;
}