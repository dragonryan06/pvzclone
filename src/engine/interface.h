#ifndef INTERFACE_H
#define INTERFACE_H

#include <memory>
#include "input.h"
#include "../global.h"
#include "FEHImages.h"

/**
 * A generic object drawn to the screen.
 * Inspired by the Godot Game Engine's CanvasItem
 * @author Ryan
 */
class CanvasItem {
    protected:
        /// @brief The screen position of this CanvasItem.
        Vector2 position {-1, -1};
        /// @brief The size of this CanvasItem.
        Vector2 size {-1, -1};
        /// @brief If false, this CanvasItem will not draw.
        bool visible {true};
    
    public:
        /**
         * Constructs a CanvasItem for a Vector2 position and size.
         *      @param pos The position.
         *      @param siz The size.
         * @author Ryan
         */
        CanvasItem(Vector2 pos, Vector2 siz);
        /**
         * Constructs a CanvasItem for float positions and size.
         *      @param posx The X position.
         *      @param posy The Y position.
         *      @param sizx The X size.
         *      @param sizy The Y size.
         * @author Ryan
         */
        CanvasItem(float posx, float posy, float sizx, float sizy);
        /**
         * Accessor method for this CanvasItem's position.
         *      @returns A Vector2 representing this CanvasItem's position.
         * @author Ryan
         */
        Vector2 getPosition();
        /**
         * Accessor method for this CanvasItem's size.
         *      @returns A Vector2 representing this CanvasItem's size.
         * @author Ryan
         */
        Vector2 getSize();
        /**
         * Sets this CanvasItem's position to a Vector2.
         *      @param pos The position to set to.
         * @author Ryan
         */
        void setPosition(Vector2 pos);
        /**
         * Sets this CanvasItem's position to floats.
         *      @param x The X position to set to.
         *      @param y The Y position to set to.
         * @author Ryan
         */
        void setPosition(float x, float y);
        /**
         * Sets this CanvasItem's size to a Vector2.
         *      @param siz The size to set to.
         * @author Ryan
         */
        void setSize(Vector2 siz);
        /**
         * Sets this CanvasItem's size to floats.
         *      @param w The width to set to.
         *      @param h The height to set to.
         * @author Ryan
         */
        void setSize(float w, float h);
        /**
         * Reports whether this CanvasItem is visible.
         *      @returns Whether or not this CanvasItem is visible.
         * @author Ryan
         */
        bool isVisible();
        /**
         * Makes this CanvasItem visible.
         * @author Ryan
         */
        void show();
        /**
         * Makes this CanvasItem not visible.
         * @author Ryan
         */
        void hide();
        /**
         * Virtual draw method for all subclasses to implement.
         * @author Ryan
         */
        virtual void draw();
};

/**
 * A CanvasItem that can recieve click input.
 * @author Ryan
 */
class Button : public CanvasItem {
    protected:
        /// @brief The current state of this Button.
        bool state {false};
    
    public:
        /**
         * Constructs a Button at a Vector2 position and size.
         *      @param pos The Vector2 position.
         *      @param siz The Vector2 size.
         * @author Ryan
         */
        Button(Vector2 pos, Vector2 siz);
        /**
         * Constructs a Button at float positions and size.
         *      @param posx The X position.
         *      @param posy The Y position.
         *      @param sizx The X size.
         *      @param sizy The Y size.
         * @author Ryan
         */
        Button(float posx, float posy, float sizx, float sizy);
        /**
         * Polls this Button to check if eventPtr's click happened within bounds.
         *      @param eventPtr A std::shared_ptr<ClickEvent> representing a possibly-applicable click.
         *      @returns True if eventPtr's click was a mouse_up within bounds, else false.
         * @author Ryan
         */
        bool poll(std::shared_ptr<ClickEvent> eventPtr);
        /**
         * Reports whether this Button is currently pressed.
         *      @returns state.
         * @author Ryan
         */
        bool isPressed();
        /**
         * Local implementation of virtual void CanvasItem::draw()
         * @author Ryan
         */
        void draw();
};

/**
 * A Button that draws as a two-state texture onscreen.
 * @author Ryan
 */
class TextureButton : public Button {
    protected:
        /// @brief The texture this Button assumes when not pressed.
        FEHImage defaultTexture;
        /// @brief The texture this Button assumes when pressed.
        FEHImage pressedTexture;
    
    public:
        /**
         * Constructs a TextureButton from Vector2 position and size.
         *      @param pos The position.
         *      @param siz The texture's dimensions.
         *      @param tex A filepath to a valid png for the default state.
         *      @param pressTex A filepath to a valid png for the pressed state.
         * @author Ryan
         */
        TextureButton(Vector2 pos, Vector2 siz, char tex[], char pressTex[]);
        /**
         * Constructs a TextureButton from float positions and size.
         *      @param posx The X position.
         *      @param posy The Y position.
         *      @param sizx The texture's X size.
         *      @param sizy The texture's Y size.
         *      @param tex A filepath to a valid png for the default state.
         *      @param pressTex A filepath to a valid png for the pressed state.
         * @author Ryan  
         */
        TextureButton(float posx, float posy, float sizx, float sizy, char tex[], char pressTex[]);
        /**
         * Local implementation of virtual void CanvasItem::draw()
         * @author Ryan
         */
        void draw();
};

/**
 * A CanvasItem that is a static image loaded from file.
 * @author Ryan
 */
class Sprite : public CanvasItem {
    protected:
        /// @brief The Sprite's texture.
        FEHImage texture;
    
    public:
        /**
         * Constructs a Sprite at a Vector2 position and size.
         *      @param pos The position.
         *      @param siz The texture's size.
         *      @param tex A filepath to a valid png for the Sprite.
         * @author Ryan
         */
        Sprite(Vector2 pos, Vector2 siz, char tex[]);
        /**
         * Constructs a Sprite at float positions and size.
         *      @param posx The X position.
         *      @param posy The Y position.
         *      @param sizx The texture's X size.
         *      @param sizy The texture's Y size.
         *      @param tex A filepath to a valid png for the Sprite.
         * @author Ryan
         */
        Sprite(float posx, float posy, float sizx, float sizy, char tex[]);
        /**
         * Sets the texture of this Sprite to a new FEHImage.
         *      @param tex An FEHImage to set the texture to.
         * @author Ryan
         */
        void setTexture(FEHImage tex);
        /**
         * Local implementation of virtual void CanvasItem::draw()
         * @author Ryan
         */
        void draw();
};

#endif