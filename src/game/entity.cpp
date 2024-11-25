#include "../engine/interface.h"
#include "entity.h"
#include "../global.h"

#include <iostream>

Entity::Entity(Vector2 pos, Vector2 siz, char spr[]) {
    position = Vector2(pos);
    sprite = Sprite(pos,siz,spr);
}
Entity::Entity(float x, float y, float xsiz, float ysiz, char spr[]) {
    position = Vector2{x, y};
    sprite = Sprite(x,y,xsiz,ysiz,spr);
}

void Entity::update() {
    position.x += velocity.x;
    position.y += velocity.y;
    Vector2 oldPos = sprite.getPosition();
    sprite.setPosition(Vector2{oldPos.x+velocity.x, oldPos.y+velocity.y});
    sprite.draw();
}

Zombie::Zombie(Vector2 pos) : Entity(pos, Vector2{35,60}, "res/entity/zombieadam.png") {
    velocity = Vector2{-1, 0};
}
Zombie::Zombie(float x, float y) : Entity(x, y, 35, 60, "res/entity/zombieadam.png") {
    velocity = Vector2{-1, 0};
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

void SunParticle::update() {
    // Standard entity motion
    position.x += velocity.x;
    position.y += velocity.y;
    Vector2 oldPos = sprite.getPosition();
    sprite.setPosition(Vector2{oldPos.x+velocity.x, oldPos.y+velocity.y});

    // Apply drag
    if (velocity.x > 0.0) velocity.x -= DRAG_FACTOR;
    else if (velocity.x < 0.0) velocity.x += DRAG_FACTOR;
    else if (velocity.y > 0.0) velocity.y -= DRAG_FACTOR;
    else if (velocity.y < 0.0) velocity.y += DRAG_FACTOR; 

    sprite.draw();
}