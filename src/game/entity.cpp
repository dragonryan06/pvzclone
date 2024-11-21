#include "engine/interface.h"
#include "game/entity.h"
#include "global.h"

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
    sprite.draw();
}

Zombie::Zombie(Vector2 pos) : Entity(pos, Vector2{35,60}, "res/entity/zombieadam.png") { };
Zombie::Zombie(float x, float y) : Entity(x, y, 35, 60, "res/entity/zombieadam.png") { };

void Zombie::update() {
    std::cout << "zombie ticking!";
    position.x += velocity.x;
    position.y += velocity.y;
    sprite.draw();
}