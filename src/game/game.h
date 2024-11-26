#ifndef GAME_H
#define GAME_H

#include "entity.h"
#include <vector>
#include <memory>

// Game state singleton
class Game {
    private:
        long long tick {0};
        int sunAmount {0};
        std::vector<std::shared_ptr<Entity>> entities;

        Game();
        int randiRange(int,int);
        float randfRange(float,float);
        void spawnSunParticle();

    public:
        static Game& instance() {
            static Game INSTANCE;
            return INSTANCE;
        }
        // Initialize game state
        void init();
        // Return true if player lost this tick.
        bool updateGame(std::shared_ptr<ClickEvent>);
};

#endif