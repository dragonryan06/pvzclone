#ifndef GAME_H
#define GAME_H

#include "entity.h"
#include <vector>
#include <memory>
#include <string>

/**
 * A singleton object for tracking and managing the overall game state.
 * https://stackoverflow.com/questions/1008019/how-do-you-implement-the-singleton-design-pattern
 * 
 * @author Ryan
 */
class Game {
    private:
        /// @brief The on-screen vertical positions of the lanes.
        const int lanes[5] {54,93,133,173,213};

        /// @brief The current tick number (incremented each update).
        long long tick {0};
        /// @brief The time(0) recorded at game start.
        int startTime {0};
        /// @brief The amount of sun the player has in the bank.
        int sunAmount {0};
        /// @brief The game objects' update & draw buffer.
        std::vector<std::shared_ptr<Entity>> entities;

        /// @brief Privated constructor to prevent double-instantiation.
        Game();
        /**
         * Pick a random integer between min and max.
         *      @param min The minimum value of the range.
         *      @param max The maximum value of the range.
         *      @returns A random integer on range [min, max].
         * @author Ryan
         */
        int randiRange(int min, int max);
        /**
         * Pick a random float between min and max.
         *      @param min The minimum value of the range.
         *      @param max The maximum value of the range.
         *      @returns A random float on range [min, max].
         * @author Ryan
         */
        float randfRange(float min, float max);
        /**
         * Spawn a SunParticle at a random position and have it fly onscreen.
         * @author Ryan
         */
        void spawnSunParticle();
        /**
         * Spawn a Zombie at a random position.
         * @author Ryan
         */
        void spawnZombie();

    public:
        /// @brief The player's time survived, for display in the stats menu.
        int timeSurvived {0};
        /// @brief The total sun collected by the player, for display in the stats menu.
        int totalSun {0};
        /// @brief The total zombies killed by the player, for display in the stats menu.
        int totalKills {0};
        /// @brief The total plants placed by the player, for display in the stats menu.
        int plantsPlaced {0};

        /**
         * Access the one instance of the singleton.
         *      @returns A reference to the one instance of Game.
         * @author Ryan
         */
        static Game& instance() {
            static Game INSTANCE;
            return INSTANCE;
        }
        /**
         * Initializes the game state, called exactly once upon starting (or re-starting) the game.
         * Inspired by the Godot Game Engine's _ready() method.
         * @author Ryan
         */
        void init();
        /**
         * Updates the game one tick into the future. Ideally, called every frame.
         * Inspired by the Godot Game Engine's _process(float) and _input(InputEvent) methods.
         *      @param event A std::shared_ptr<ClickEvent> to a possibly-valid click that happened between ticks.
         *      @returns true if the player has lost this tick, else false.
         * @author Ryan
         */
        bool updateGame(std::shared_ptr<ClickEvent> event);
        /**
         * Cleans up and sets the game to a pre-init() state. Makes replay possible.
         * @author Ryan
         */
        void cleanUp();
};

#endif