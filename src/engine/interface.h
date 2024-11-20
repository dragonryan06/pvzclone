#ifndef INTERFACE_H
#define INTERFACE_H

#include "input.h"
#include "../global.h"

class CanvasItem {
    protected:
        Vector2 position {-1, -1};
        Vector2 size {-1, -1};
    
    public:
        CanvasItem(Vector2, Vector2);
        CanvasItem(float, float, float, float);
        Vector2 getPosition();
        Vector2 getSize();
        void setPosition(Vector2);
        void setPosition(float, float);
        void setSize(Vector2);
        void setSize(float, float);
        virtual void draw();
};

class Button : public CanvasItem {
    protected:
        bool toggle {false};
        bool state {false};
    
    public:
        Button(Vector2, Vector2);
        Button(float, float, float, float);
        void poll(ClickEvent*);
        void draw();
};

#endif