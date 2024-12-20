#include "game.h"
#include "../global.h"
#include <memory>
#include <time.h>
#include <string>

// Game is a singleton; no construction allowed.
Game::Game() { }

void Game::init() {
    sunAmount=50; //Start with 50 sun
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
    if (tick%250 == 0 || requestedSun) { // every 250 ticks, spawn a new sun from the sky.
        spawnSunParticle();
        requestedSun = false;
    }
    if (requestedPea.x != -1) {
        std::shared_ptr<PeaProjectile> p (new PeaProjectile(requestedPea));
        projectiles.push_back(p);
        requestedPea = Vector2{-1,-1};
    }
    if (tick%(300-tick/50) == 0) { // every 300 ticks, increasing as ticks increases.
        spawnZombie();
    }

    // List of indicies of entities that are being removed this tick.
    std::vector<int> removing;
    // List of indicies of projectiles that collided this tick.
    std::vector<int> removingProjectiles;

    if (!event->empty && !event->mouse_down && selectedPlant != -1) {
        Vector2 gridPos = screenToGrid(event->start);
        if ((int)gridPos.x >= 0 && (int)gridPos.y >= 0 && (int)gridPos.x < 9 && (int)gridPos.y < 5 && !isCellOccupied(gridPos)) {
            if (selectedPlant == 0 && sunAmount >= 100) { // Peashooter
                setCellState(gridPos,true);
                std::shared_ptr<Entity> newPeashooter (new Peashooter(gridPos.x,gridPos.y));
                entities.push_back(newPeashooter);
                sunAmount -= 100;
                plantsPlaced++;
                // Deselect
                selectedPlant = -1;
            } else if (selectedPlant == 1 && sunAmount >= 50) { // Sunflower
                setCellState(gridPos,true);
                std::shared_ptr<Entity> newSunflower (new Sunflower(gridPos.x,gridPos.y));
                entities.push_back(newSunflower);
                sunAmount -= 50;
                plantsPlaced++;
                // Deselect
                selectedPlant = -1;
            }
        }
    }

    int idx = 0;
    for (auto&& entity : entities) {
        entity->update();

        if (dynamic_cast<SunParticle*>(entity.get())) {// Test if the entity is a sun particle
            std::shared_ptr<SunParticle> sun = std::dynamic_pointer_cast<SunParticle>(entity);
            if (!event->empty && sun->poll(event)) {
                sun->flyOut();
                sunAmount += 25;
                totalSun += 25;
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
            int p_idx = 0;
            for (auto&& pea : projectiles) {
                Vector2 p = pea->getPosition(), z = zombie->getPosition();
                // Quick rectangle collision
                if (p.x > z.x && p.x < z.x+35 && p.y > z.y && p.y < z.y+60) {
                    if (zombie->hurt()) {
                        removing.push_back(idx);
                        totalKills++;
                    }
                    removingProjectiles.push_back(p_idx);
                }
                if (pea->getPosition().x > 320) {
                    removingProjectiles.push_back(p_idx);
                }
                p_idx++;
            }
        }
        idx++;
    }

    // Draw projectiles
    for (auto && projectile : projectiles) {
        projectile->update();
    }

    // Remove entities
    for (int i : removing) {
        entities.erase(entities.begin() + i);
    }
    for (int i : removingProjectiles) {
        projectiles.erase(projectiles.begin() + i);
    }

    // Writing twice to do a word shadow thing; first in black then in font color
    int currentTime = time(0)-startTime;
    LCD.SetFontColor(BLACK);
    LCD.WriteAt(sunAmount,245,11);
    LCD.WriteAt(stringifyTime(currentTime),5,5);

    LCD.SetFontColor(YELLOW);
    LCD.WriteAt(sunAmount,244,10);
    LCD.SetFontColor(RED);
    LCD.WriteAt(stringifyTime(currentTime),4,4);
    tick++;
    return false;
}

void Game::spawnSunParticle() {
    std::shared_ptr<Entity> s(
        new SunParticle(randiRange(20, 300),0,randfRange(-4,4),randfRange(3,7))
    );
    entities.push_back(s);
}

void Game::spawnZombie() {
    std::shared_ptr<Entity> z(
        new Zombie(320,lanes[randiRange(0, 4)]-30)
    );
    entities.push_back(z);
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
    grid = {
        {false, false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false, false, false}
    };
    selectedPlant = -1;
}

void Game::selectPlant(int which) {
    selectedPlant = which;
}

Vector2 Game::screenToGrid(Vector2 pos) {
    return Vector2{(pos.x)/cellDim.x, (pos.y)/cellDim.y - 1};
}

void Game::setCellState(Vector2 gridpos, bool state) {
    grid.at((int)gridpos.y).at((int)gridpos.x) = state;
}

bool Game::isCellOccupied(Vector2 gridpos) {
    return grid.at((int)gridpos.y).at((int)gridpos.x);
}

void Game::requestSpawnSun() {
    requestedSun = true;
}

void Game::shootPea(Vector2 pos) {
    requestedPea = Vector2(pos);
}