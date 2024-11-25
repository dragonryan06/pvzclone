#include "game.h"
#include <memory>
#include <time.h>

// Game is a singleton; no construction allowed.
Game::Game() { }

void Game::init() {
    std::shared_ptr<Entity> testZomb (new Zombie(320,120));
    entities.push_back(testZomb);
    // Seed the generator to seconds since 1970
    srand(time(0));
}

int Game::randiRange(int min, int max) {
    return rand() % (max + 1 - min) + min;
}

float Game::randfRange(float min, float max) {
    float val = (float)(rand()) / (float)(RAND_MAX);
    return (min+(max-min)*val);
}

// One tick of the game; return true if the player lost this tick.
bool Game::updateGame() {
    if (tick%250 == 0) { // every 250 ticks, spawn a new sun from the sky.
        spawnSunParticle();
    }

    for (auto&& entity : entities) {
        entity->update();
    }
    tick++;
}

void Game::spawnSunParticle() {
    std::shared_ptr<Entity> s(
        new SunParticle(randiRange(20, 300),0,randfRange(-4,4),randfRange(3,7))
    );
    entities.push_back(s);
}