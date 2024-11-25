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
bool Game::updateGame(std::shared_ptr<ClickEvent> event) {
    if (tick%250 == 0) { // every 250 ticks, spawn a new sun from the sky.
        spawnSunParticle();
    }

    int idx = 0;
    for (auto&& entity : entities) {
        entity->update();

        if (dynamic_cast<SunParticle*>(entity.get())) {// Test if the entity is a sun particle
            std::shared_ptr<SunParticle> sun = std::dynamic_pointer_cast<SunParticle>(entity);
            if (!event->empty && sun->poll(event)) {
                sun->flyOut();
            }
            // This sun has flown out; we can kill it.
            if (sun->getPosition().x < 0 && sun->getPosition().y < 0) {
                entities.erase(entities.begin() + idx);
            }
        }
        idx++;
    }
    tick++;
}

void Game::spawnSunParticle() {
    std::shared_ptr<Entity> s(
        new SunParticle(randiRange(20, 300),0,randfRange(-4,4),randfRange(3,7))
    );
    entities.push_back(s);
}