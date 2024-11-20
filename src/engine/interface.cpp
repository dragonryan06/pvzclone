#include "FEHLCD.h"
#include "FEHImages.h"
#include "input.h"
#include "../global.h"
#include "interface.h"

// constructors
CanvasItem::CanvasItem(Vector2 pos, Vector2 siz) {
    position = Vector2(pos);
    size = Vector2(siz);
}
CanvasItem::CanvasItem(float posx, float posy, float sizx, float sizy) {
    position = Vector2{posx,posy};
    size = Vector2{sizx,sizy};
}

// setget
Vector2 CanvasItem::getPosition() { return Vector2(position); }
Vector2 CanvasItem::getSize() { return Vector2(size); }
void CanvasItem::setPosition(Vector2 pos) { position = Vector2(pos); }
void CanvasItem::setPosition(float x, float y) { position = Vector2{x, y}; }
void CanvasItem::setSize(Vector2 siz) { size = Vector2(siz); }
void CanvasItem::setSize(float w, float h) { size = Vector2{w, h}; }

void CanvasItem::draw() {
    LCD.SetFontColor(RED);
    LCD.DrawRectangle(position.x,position.y,size.x,size.y);
}

// constructors
Button::Button(Vector2 pos, Vector2 siz) : CanvasItem(pos, siz) {

}
Button::Button(float posx, float posy, float sizx, float sizy) : CanvasItem(posx, posy, sizx, sizy) {

}

void Button::draw() {
    if (state) {
        LCD.SetFontColor(WHITE);
    } else {
        LCD.SetFontColor(GRAY);
    }
    LCD.FillRectangle(position.x,position.y,size.x,size.y);
}

void Button::poll(ClickEvent* eventPtr) {
    ClickEvent event = *eventPtr;

    if (event.start.x > position.x && event.start.x < position.x+size.x && event.start.y > position.y && event.start.y < position.y+size.y) {
        state = event.mouse_down;
    }
}

// constructors
TextureButton::TextureButton(Vector2 pos, Vector2 siz, char tex[], char pressTex[]) : Button(pos, siz) {
    defaultTexture = FEHImage();
    defaultTexture.Open(tex);
    pressedTexture = FEHImage();
    pressedTexture.Open(pressTex);
}
TextureButton::TextureButton(float posx, float posy, float sizx, float sizy, char tex[], char pressTex[]) : Button(posx, posy, sizx, sizy) {
    defaultTexture = FEHImage();
    defaultTexture.Open(tex);
    pressedTexture = FEHImage();
    pressedTexture.Open(pressTex);
}

void TextureButton::draw() {
    if (state) {
        pressedTexture.Draw(position.x, position.y);
    } else {
        defaultTexture.Draw(position.x, position.y);
    }
}

// constuctors
Sprite::Sprite(Vector2 pos, Vector2 siz, char tex[]) : CanvasItem(pos, siz) {
    texture = FEHImage();
    texture.Open(tex);
}
Sprite::Sprite(float posx, float posy, float sizx, float sizy, char tex[]) : CanvasItem(posx, posy, sizx, sizy) {
    texture = FEHImage();
    texture.Open(tex);
}

void Sprite::draw() {
    texture.Draw(position.x, position.y);
}

void Sprite::setTexture(FEHImage tex) {
    texture = tex;
}