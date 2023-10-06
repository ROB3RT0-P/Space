#include "Space.h"
#include <SDL_image.h>
#include <iostream>
#include <cmath>

Space::Space(int screenWidth, int screenHeight, int numStars, int numDistantStars)
    : screenWidth(screenWidth), screenHeight(screenHeight), numStars(numStars), numDistantStars(numDistantStars),
    maxDepth(2000.0f) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL Initialization failed: " << SDL_GetError() << std::endl;
        return;
    }

    window = SDL_CreateWindow("Space Travel", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        screenWidth, screenHeight, SDL_WINDOW_RESIZABLE);

    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    Init();
}

Space::~Space() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Space::IsInitialized() const {
    return renderer != nullptr;
}

void Space::Init() {
    std::uniform_real_distribution<float> xDistribution(-screenWidth * 0.5f, screenWidth * 0.5f);
    std::uniform_real_distribution<float> yDistribution(-screenHeight * 0.5f, screenHeight * 0.5f);
    std::uniform_real_distribution<float> depthDistribution(500.0f, maxDepth);
    std::uniform_real_distribution<float> sizeDistribution(0.5f, 10.0f);

    for (int i = 0; i < numStars; ++i) {
        float x = xDistribution(randomEngine);
        float y = yDistribution(randomEngine);
        float depth = depthDistribution(randomEngine);
        float size = sizeDistribution(randomEngine);

        stars.push_back({ x, y, depth, size });
    }

    // Initialize the distant stars
    std::uniform_real_distribution<float> distantDepthDistribution(maxDepth * 0.5f, maxDepth * 2.0f);
    for (int i = 0; i < numDistantStars; ++i) {
        float x = xDistribution(randomEngine);
        float y = yDistribution(randomEngine);
        float depth = distantDepthDistribution(randomEngine);
        float size = sizeDistribution(randomEngine);

        distantStars.push_back({ x, y, depth, size });
    }
}

void Space::Render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (const Star& star : distantStars) {
        float size = star.size / star.depth; // Adjust size based on depth
        int pixelSize = static_cast<int>(size * 0.5f); // Smaller scaling for distant stars

        int screenX = static_cast<int>(star.x / star.depth + screenWidth * 0.5f);
        int screenY = static_cast<int>(star.y / star.depth + screenHeight * 0.5f);

        SDL_Rect starRect = { screenX - pixelSize / 2, screenY - pixelSize / 2,
                             pixelSize, pixelSize };
        SDL_RenderFillRect(renderer, &starRect);
    }

    for (const Star& star : stars) {
        float size = star.size / star.depth; // Adjust size based on depth
        int pixelSize = static_cast<int>(size * 2.0f);

        int screenX = static_cast<int>(star.x / star.depth + screenWidth * 0.5f);
        int screenY = static_cast<int>(star.y / star.depth + screenHeight * 0.5f);

        SDL_Rect starRect = { screenX - pixelSize / 2, screenY - pixelSize / 2,
                             pixelSize, pixelSize };
        SDL_RenderFillRect(renderer, &starRect);
    }

    SDL_RenderPresent(renderer);
}

void Space::Update(float deltaTime) {
    for (Star& star : stars) {
        // Increase the speed as stars get closer
        float speed = 100.0f + (maxDepth - star.depth) * 0.1f;
        star.depth -= deltaTime * speed/10;

        // Reset stars that go beyond the near plane
        if (star.depth < 0.0f) {
            star.depth = maxDepth;
        }
    }

    for (Star& star : distantStars) {
        // Increase the speed as stars get closer
        float speed = 50.0f + (maxDepth * 5.0f - star.depth) * 0.1f;
        star.depth -= deltaTime * speed/10;

        // Reset distant stars that go beyond the near plane
        if (star.depth < maxDepth * 5.0f) {
            star.depth = maxDepth * 20.0f;
        }
    }
}

