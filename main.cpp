
#ifndef TYPES_H
#include "Types.h"
#endif

#ifndef GAME_H
#include "Game.h"
#endif

int main(int argc, char** argv) {
    Game GAME_MAIN;
    if (!GAME_MAIN.init()) // if init has no error
        GAME_MAIN.loop(); // start game loop
    GAME_MAIN.close(); // close game
    return 0;
}

