#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include "../engine/interface.h"
#include "../global.h"

/**
 * A generic game object.
 * @author Ryan
 */
class Entity {
    protected:
        /// @brief This Entity's position onscreen.
        Vector2 position {-1, -1};
        /// @brief This Entity's velocity; how many pixels it moves this tick.
        Vector2 velocity {0, 0};
        /// @brief This Entity's Sprite.
        Sprite sprite {-1,-1,-1,-1,"res/placeholdertex.png"};
    public:
        /**
         * Constructs an Entity from Vector2 position and size.
         *      @param pos Position.
         *      @param siz The Sprite's size.
         *      @param spr Filepath to a valid png.
         * @author Ryan
         */
        Entity(Vector2 pos, Vector2 siz, char spr[]);
        /**
         * Constructs an Entity from float positions and sizes.
         *      @param x X position.
         *      @param y Y position.
         *      @param xsiz The Sprite's X size.
         *      @param ysiz The Sprite's Y size.
         *      @param spr Filepath to a valid png.
         * @author Ryan
         */
        Entity(float x, float y, float xsiz, float ysiz, char spr[]);
        /**
         * Accessor method for Entity::position.
         *      @returns Vector2 representing the Entity's position.
         * @author Ryan
         */
        Vector2 getPosition();
        /**
         * Virtual update&draw method for all subclasses of Entity to implement.
         * @author Ryan
         */
        virtual void update();
};

/**
 * A zombie. The enemy in the game. 
 * Walks from the right side of the screen towards the left until killed.
 * @author Ryan
 */
class Zombie : public Entity {
    protected:
        /// @brief This Zombie's hitpoints.
        int health=5;
    public:
        /**
         * Constructs a Zombie from a Vector2 position.
         *      @param pos The position.
         * @author Ryan
         */
        Zombie(Vector2 pos);
        /**
         * Constructs a Zombie from two float positions.
         *      @param x The X position.
         *      @param y The Y position.
         * @author Ryan
         */
        Zombie(float x, float y);
        /**
         * Lowers this zombie's hitpoints by 1, returns true if killed.
         *      @returns True if the zombie was killed by this hit.
         * @author Ryan
         */
        bool hurt();

        /**
         * Local implementation of virtual void Entity::update()
         * @author Ryan
         */
        void update();
};

/**
 * A particle of sun. Sun is the currency used by the player to place plants.
 * @author Ryan
 */
class SunParticle : public Entity {
    private:
        /// @brief The amount of unsigned deceleration experienced per-frame.
        const float DRAG_FACTOR = 0.15;
        /// @brief If false, this SunParticle will ignore input.
        bool clickable {true};
    public:
        /**
         * Constructs a SunParticle from a Vector2 position and velocity.
         *      @param pos The position.
         *      @param init_vel The initial velocity.
         * @author Ryan
         */
        SunParticle(Vector2 pos, Vector2 init_vel);
        /**
         * Constructs a SunParticle from float positions and velocity.
         *      @param x The X position.
         *      @param y The Y position.
         *      @param vx The X velocity.
         *      @param vy The Y velocity.
         * @author Ryan
         */
        SunParticle(float x, float y, float vx, float vy);
        /**
         * Polls this SunParticle to see if it was clicked by event.
         *      @param event A std::shared_ptr<ClickEvent> to test collision with.
         *      @returns True if the event occured within this SunParticle's bounds.
         * @author Ryan
         */
        bool poll(std::shared_ptr<ClickEvent> event);
        /**
         * Disables input for this SunParticle and flies it offscreen.
         * @author Ryan
         */
        void flyOut();
        /**
         * Local implementation of virtual void Entity::update()
         * @author Ryan
         */
        void update();
};

/**
 * Base class for plants. Due to complications with implementing grid system, holds no reference to grid.
 * @author Ryan and Daniel
 */
class Plant : public Entity {
    protected:
        /// @brief The current ticks since last activation.
        int cooldown {0};
    public:
        /**
         * Constructs a plant at a grid position, using the texture.
         *      @param grid_x The grid X position.
         *      @param grid_y The grid Y position. 
         *      @param tex A valid png filepath to the texture.
         */
        Plant(int grid_x, int grid_y, char tex[]);
};

/**
 * Sunflower, one of two plants.
 * @author Ryan
 */
class Sunflower : public Plant {
    private:
        /// @brief The value of cooldown at which another activation occurs.
        const int cooldownMax = 250;
    public:
        /**
         * Constructs a sunflower at a grid position.
         *      @param grid_x The grid X position.
         *      @param grid_y The grid Y position.
         * @author Ryan
         */
        Sunflower(int grid_x, int grid_y);
        /**
         * Local implementation of virtual void Entity::update()
         * @author Ryan
         */
        void update();
};

/**
 * Peashooter, the other of two plants.
 * @author Ryan
 */
class Peashooter : public Plant {
    private:
        /// @brief The value of cooldown at which another activation occurs.
        const int cooldownMax = 50;
    public:
        /**
         * Constructs a peashooter at a grid position.
         *      @param grid_x The grid X position. 
         *      @param grid_y The grid Y position.
         * @author Ryan
         */
        Peashooter(int grid_x, int grid_y);
        /**
         * Local implementation of virtual void Entity::update()
         * @author Ryan
         */
        void update();
};

/**
 * A PeaProjectile, fired from a Peashooter.
 * @author Ryan
 */
class PeaProjectile : public Entity {
    public:
        /**
         * Constructs a PeaProjectile at the given position.
         *      @param pos The position.
         * @author Ryan
         */
        PeaProjectile(Vector2 pos);
        /**
         * Local implementation of virtual void Entity::update()
         * @author Ryan
         */
        void update();
};

#endif