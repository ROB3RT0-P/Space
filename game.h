#ifndef GAME_H
#define GAME_H

#include "space.h"

class Game {

public:
	void init();
	void tickLogic();

private:
	Space* space;
	const float deltaTime = 0.016f;
	const int screenWidth = 1200;
	const int screenHeight = 800;
	const int numStars = 1000;
	const int numDistantStars = 1000;
};

#endif // GAME_H