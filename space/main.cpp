/*******************************************
    Written by Robert Parry [RJP] - 2023    
*******************************************/

#include "game.h"
#include <SDL.h>

int main(int argc, char* argv[]) {
    Game game;
    SDL_Event e;     
    bool quit = false;

    game.init();
    
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true; // Quit on window close event
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true; // Quit when the Escape key is pressed
                }
            }
        }
        game.tickLogic();
    }

    return 0;
}
