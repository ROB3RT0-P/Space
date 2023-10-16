#include "game.h"
#include "space.h"
#include <SDL.h>

void Game::init()
{
    space = new Space(screenWidth, screenHeight, numStars, numDistantStars);
}

Game::~Game()
{
    delete space;
}

void Game::tickLogic() 
{
    space->Update(deltaTime);
    space->Render();
}