#include "game/game.h"

// Game is a singleton; no construction allowed.
Game::Game() { }

// One tick of the game; return true if the player lost this tick.
bool Game::updateGame() {
    for (auto&& entity : entities) {
        entity->update();
    }
}