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
        
        // Tracked stats
        int timeSurvived {0};
        int totalSun {0};
        int totalKills {0};
        int plantsPlaced {0};

        Game();
        int randiRange(int,int);
        float randfRange(float,float);
        void spawnSunParticle();
        std::string stringifyTime(int);

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