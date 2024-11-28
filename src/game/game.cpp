#include "game.h"
#include "../global.h"
#include <memory>
#include <time.h>
#include <string>

// Game is a singleton; no construction allowed.
Game::Game() { }

void Game::init() {
    std::shared_ptr<Entity> testZomb (new Zombie(320,120));
    entities.push_back(testZomb);
    // Seed the generator to seconds since 1970
    srand(time(0));
    // Record start time
    startTime = time(0);
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

    // List of indicies of entities that are being removed this tick.
    std::vector<int> removing;

    int idx = 0;
    for (auto&& entity : entities) {
        entity->update();

        if (dynamic_cast<SunParticle*>(entity.get())) {// Test if the entity is a sun particle
            std::shared_ptr<SunParticle> sun = std::dynamic_pointer_cast<SunParticle>(entity);
            if (!event->empty && sun->poll(event)) {
                sun->flyOut();
                sunAmount += 50;
                totalSun += 50;
            }
            // This sun has flown out; we can mark it for deletion.
            if (sun->getPosition().x < 0 && sun->getPosition().y < 0) {
                removing.push_back(idx);
            }
        } else if (dynamic_cast<Zombie*>(entity.get())) {// Test if the entity is a zombie
            std::shared_ptr<Zombie> zombie = std::dynamic_pointer_cast<Zombie>(entity);
            if (zombie->getPosition().x < -30) {
                // GAME OVER!
                timeSurvived = time(0)-startTime;
                return true;
            }
        }
        idx++;
    }

    // Remove entities
    for (int i : removing) {
        entities.erase(entities.begin() + i);
    }

    // Writing twice to do a word shadow thing; first in black then in font color
    int currentTime = time(0)-startTime;
    LCD.SetFontColor(BLACK);
    LCD.WriteAt(sunAmount,5,5);
    LCD.WriteAt(stringifyTime(currentTime),131,5);

    LCD.SetFontColor(YELLOW);
    LCD.WriteAt(sunAmount,4,4);
    LCD.SetFontColor(RED);
    LCD.WriteAt(stringifyTime(currentTime),130,4);
    tick++;
    return false;
}

void Game::spawnSunParticle() {
    std::shared_ptr<Entity> s(
        new SunParticle(randiRange(20, 300),0,randfRange(-4,4),randfRange(3,7))
    );
    entities.push_back(s);
}

void Game::cleanUp() {
    tick = 0;
    startTime = 0;
    sunAmount = 0;
    entities.clear();
    timeSurvived = 0;
    totalSun = 0;
    totalKills = 0;
    plantsPlaced = 0;
}