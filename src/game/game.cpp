#include "game.h"
#include <memory>

// Game is a singleton; no construction allowed.
Game::Game() { }

void Game::init() {
    std::shared_ptr<Entity> testZomb (new Zombie(320,120));
    entities.push_back(testZomb);
}

// One tick of the game; return true if the player lost this tick.
bool Game::updateGame() {
    for (auto&& entity : entities) {
        entity->update();
    }
}