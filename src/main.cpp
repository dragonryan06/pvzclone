#include <vector>
#include "FEHLCD.h"
#include "FEHUtility.h"
#include "global.h"
#include "engine/input.h"
#include "engine/interface.h"

int main() {
    bool running = true;

    bool mainMenu = true;
    
    CanvasItem testItem(100,100,50,50);
    Button testButton(25,25,50,50);
    TextureButton testTextureButton(150,50,10,10,"testbutton1.png","testbutton2.png");
    Sprite testSprite(150,150,10,10,"testasset.png");

    std::vector<CanvasItem*> mainMenuCanvas = {
        &testItem,
        &testButton,
        &testTextureButton,
        &testSprite
    };

    std::vector<Button*> mainMenuClickables = {
        &testButton,
        &testTextureButton
    };

    while (running) {
        LCD.Clear(BLACK);

        ClickEvent* event = Input::instance().update();
        if (event != NULL) {
            if (mainMenu) {
                // Poll buttons and clickables
                for (Button* b : mainMenuClickables) {
                    (*b).poll(event);
                }
            } else {
                // Poll buttons and clickables
            }
        }

        if (mainMenu) {
            for (CanvasItem* c : mainMenuCanvas) {
                (*c).draw();
            }
        } else {
            // draw game
        }

        LCD.Update();
        Sleep(0.01);
    }
}