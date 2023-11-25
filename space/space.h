/*******************************************
    Written by Robert Parry [RJP] - 2023    
*******************************************/

#ifndef SPACE_H
#define SPACE_H

#include <SDL.h>
#include <vector>
#include <random>

struct Star {
    float x, y, depth, size;
};

class Space {
public:
    Space(int screenWidth, int screenHeight, int numStars, int numDistantStars);
    ~Space();

    bool IsInitialized() const;
    void Init();
    void Render();
    void Update(float deltaTime);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int screenWidth;
    int screenHeight;
    int numStars;
    int numDistantStars;
    int numStaticStars;
    std::vector<Star> stars;
    std::vector<Star> distantStars;
    std::default_random_engine randomEngine;
    float maxDepth;
};

#endif // SPACE_H
