#include <vector>
#include "FEHLCD.h"
#include "FEHUtility.h"
#include "global.h"
#include "engine/input.h"
#include "engine/interface.h"

int main() {
    bool running = true;

    bool mainMenu = true;
    
    // MAIN MENU
    Sprite background(0,0,320,240,"res/mainmenu.png");
    TextureButton play(182,66,96,24,"res/playbutton_def.png","res/playbutton_prs.png");
    TextureButton how(182,106,96,25,"res/howbutton_def.png","res/howbutton_prs.png");
    TextureButton stats(203,213,40,11,"res/statbutton_def.png","res/statbutton_prs.png");
    TextureButton credits(261,216,42,11,"res/creditbutton_def.png","res/creditbutton_prs.png");

    std::vector<CanvasItem*> mainMenuCanvas = {
        &background,
        &play,
        &how,
        &stats,
        &credits
    };

    std::vector<Button*> mainMenuClickables = {
        &play,
        &how,
        &stats,
        &credits
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