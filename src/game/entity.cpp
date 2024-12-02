#include <memory>
#include <iostream>
#include "../engine/interface.h"
#include "entity.h"
#include "../global.h"
#include "game.h"


Entity::Entity(Vector2 pos, Vector2 siz, char spr[]) {
    position = Vector2(pos);
    sprite = Sprite(pos,siz,spr);
}
Entity::Entity(float x, float y, float xsiz, float ysiz, char spr[]) {
    position = Vector2{x, y};
    sprite = Sprite(x,y,xsiz,ysiz,spr);
}

Vector2 Entity::getPosition() { return Vector2(position); }

void Entity::update() {
    position.x += velocity.x;
    position.y += velocity.y;
    Vector2 oldPos = sprite.getPosition();
    sprite.setPosition(Vector2{oldPos.x+velocity.x, oldPos.y+velocity.y});
    sprite.draw();
}

Zombie::Zombie(Vector2 pos) : Entity(pos, Vector2{35,60}, "res/entity/zombieadam.png") {
    velocity = Vector2{-0.25, 0};
}
Zombie::Zombie(float x, float y) : Entity(x, y, 35, 60, "res/entity/zombieadam.png") {
    velocity = Vector2{-0.25, 0};
}

void Zombie::update() {
    position.x += velocity.x;
    position.y += velocity.y;
    Vector2 oldPos = sprite.getPosition();
    sprite.setPosition(Vector2{oldPos.x+velocity.x, oldPos.y+velocity.y});
    sprite.draw();
}

SunParticle::SunParticle(Vector2 pos, Vector2 init_vel) : Entity(pos, Vector2{15,15}, "res/entity/sunlight.png") {
    velocity = init_vel;
}
SunParticle::SunParticle(float x, float y, float vx, float vy) : Entity(x, y, 15, 15, "res/entity/sunlight.png") {
    velocity = {vx, vy};
}

bool SunParticle::poll(std::shared_ptr<ClickEvent> event) {
    if (!clickable) {
        return false;
    }

    bool clicked = false;
    if (event->start.x > position.x && event->start.x < position.x+15 && event->start.y > position.y && event->start.y < position.y+15) {
        clicked = true;
    }
    return clicked;
}

void SunParticle::flyOut() {
    clickable = false;
    // Fly it towards the origin by setting velocity to -1/5 position vector
    velocity = Vector2{-position.x/5.0f,-position.y/5.0f};
}

void SunParticle::update() {
    // Standard entity motion
    position.x += velocity.x;
    position.y += velocity.y;
    Vector2 oldPos = sprite.getPosition();
    sprite.setPosition(Vector2{oldPos.x+velocity.x, oldPos.y+velocity.y});

    // Apply drag
    if (velocity.x > DRAG_FACTOR) velocity.x -= DRAG_FACTOR;
    else if (velocity.x < -DRAG_FACTOR) velocity.x += DRAG_FACTOR;
    else velocity.x = 0;
    if (velocity.y > DRAG_FACTOR) velocity.y -= DRAG_FACTOR;
    else if (velocity.y < -DRAG_FACTOR) velocity.y += DRAG_FACTOR; 
    else velocity.y = 0;

    sprite.draw();
}

Plant::Plant(int grid_x, int grid_y, char tex[]) : Entity((grid_x*Game::instance().cellDim.x)+Game::instance().topLeft.x,(grid_y*Game::instance().cellDim.y)+Game::instance().topLeft.y,31,41,tex) {

}

Sunflower::Sunflower(int grid_x, int grid_y) : Plant(grid_x,grid_y,"res/entity/sunflower.png") {

}

void Sunflower::update() {
    cooldown++;
    if (cooldown > cooldownMax) {
        cooldown = 0;
        // Can't just call spawnSunParticle, due to pointer stuff.
        // Plus, this limits the sun per tick.
        Game::instance().requestSpawnSun();
    }
    sprite.draw();
}