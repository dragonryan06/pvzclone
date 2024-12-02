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
        Zombie(float, float);
        void update();
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
        int cooldown {0};
    public:
        Plant(int grid_x, int grid_y, char tex[]);
};

class Sunflower : public Plant {
    private:
        const int cooldownMax = 100;
    public:
        Sunflower(int grid_x, int grid_y);
        void update();
};

class Peashooter : public Plant {
    private:
        const int cooldownMax = 50;
    public:
        Peashooter(int grid_x, int grid_y);
        void update();
};


#endif