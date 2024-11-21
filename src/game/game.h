#ifndef GAME_H
#define GAME_H

#include "game/entity.h"
#include <vector>

// Game state singleton
class Game {
    private:
        std::vector<std::unique_ptr<Entity>> entities;

        Game();

    public:
        static Game& instance() {
            static Game INSTANCE;
            return INSTANCE;
        }
        // Return true if player lost this tick.
        bool updateGame();
};

#endif