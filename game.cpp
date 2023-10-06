#include "game.h"
#include "space.h"
#include <SDL.h>

void Game::init()
{   
    Space *space = new Space(screenWidth, screenHeight, numStars, numDistantStars);
}

void Game::tickLogic() 
{
    space->Update(deltaTime);
    space->Render();
}