#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include "../engine/interface.h"
#include "../global.h"

class Entity {
    protected:
        Vector2 position {-1, -1};
        Vector2 velocity {0, 0};
        Sprite sprite {-1,-1,-1,-1,"res/placeholdertex.png"};
    public:
        Entity(Vector2, Vector2, char[]);
        Entity(float, float, float, float, char[]);
        Vector2 getPosition();
        virtual void update();
};

class Zombie : public Entity {
    protected:
        int health=5;
    public:
        Zombie(Vector2);
        int width=9,height=28;
        Zombie(float, float);

        // Method to check if the zombie has been hit by a projectile
        bool checkHit(Vector2 projPos, int projWidth, int projHeight) {
            // Check if the projectile intersects with the zombie's position
            bool hitX = projPos.x >= position.x && projPos.x <= position.x + width;
            bool hitY = projPos.y >= position.y && projPos.y <= position.y + height;

            return hitX && hitY;
            void update();
        }
};

class SunParticle : public Entity {
    private:
        const float DRAG_FACTOR = 0.15;
        bool clickable {true};
    public:
        SunParticle(Vector2,Vector2);
        SunParticle(float,float,float,float);
        bool poll(std::shared_ptr<ClickEvent>);
        void flyOut();
        void update();
};

class PeaProjectile : public Entity {
    public:
        PeaProjectile(Vector2);
        PeaProjectile(float, float);
        void update();
};

class Plant : public Entity {
    protected:
        int cooldown;
        int health=4;
    public:
        Plant(Vector2);
        Plant(float, float);
        const char *type;
        void update();
};


#endif