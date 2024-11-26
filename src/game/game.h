#ifndef GAME_H
#define GAME_H

#include "entity.h"
#include <vector>
#include <memory>
#include <string>

// Game state singleton
class Game {
    private:
        // Game params
        long long tick {0};
        int startTime {0};
        int sunAmount {0};
        std::vector<std::shared_ptr<Entity>> entities;

        Game();
        int randiRange(int,int);
        float randfRange(float,float);
        void spawnSunParticle();

    public:
        // Tracked stats
        int timeSurvived {0};
        int totalSun {0};
        int totalKills {0};
        int plantsPlaced {0};

        static Game& instance() {
            static Game INSTANCE;
            return INSTANCE;
        }
        // Initialize game state
        void init();
        // Return true if player lost this tick.
        bool updateGame(std::shared_ptr<ClickEvent>);
        // Clean up so the game is in a pre-init state.
        void cleanUp();
};

#endif