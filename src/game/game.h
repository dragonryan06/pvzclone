#ifndef GAME_H
#define GAME_H

#include "entity.h"
#include <vector>
#include <memory>
#include <string>

// Game state singleton
class Game {
    private:
        // Game constants
        const int lanes[5] {54,93,133,173,213};

        // Game params
        long long tick {0};
        int startTime {0};
        int sunAmount {0};
        std::vector<std::shared_ptr<Entity>> entities;

        /// @brief -1 = none, 0 = peashooter, 1 = sunflower
        int selectedPlant = -1;
        /// @brief Whether or not a sunflower is spawning a sun this frame.
        bool requestedSun = false;

        Game();
        int randiRange(int,int);
        float randfRange(float,float);

        void spawnZombie();

    public:
        /// @brief The top left corner of the grid.
        const Vector2 topLeft {9,36};
        /// @brief The bottom right corner of the grid.
        const Vector2 bottomRight {311,232};
        /// @brief The dimensions of one cell.
        const Vector2 cellDim {33,40};

        /// @brief The cell states
        std::vector<std::vector<bool>> grid {
            {false, false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false, false}
        };

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

        void spawnSunParticle();

        /**
         * Sets the value of selectedPlant to the value of which.
         *      @param which The value to set it to.
         * @author Ryan
         */
        void selectPlant(int which);

        /**
         * Converts a screen position Vector2 to a grid position.
         *      @param pos The screen position.
         *      @returns The position, in grid coordinates.
         * @author Daniel and Ryan
         */
        Vector2 screenToGrid(Vector2 pos);

        /**
         * Sets an individual cell to an incoming occupied state.
         *      @param gridpos The grid cell to target.
         *      @param state The state to set it to.
         * @author Daniel and Ryan
         */
        void setCellState(Vector2 gridpos, bool state);

        /**
         * Check if the cell at gridpos is occupied.
         *      @param gridpos The grid cell to check.
         * @author Ryan
         */
        bool isCellOccupied(Vector2 gridpos);

        /**
         * Allows sunflowers to create sun particles (cant pass pointer from other scope).
         * @author Ryan
         */
        void requestSpawnSun();
};

#endif