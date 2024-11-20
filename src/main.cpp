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
    TextureButton play(150,150,100,50,"res/playbutton_def.png","res/playbutton_prs.png");
    TextureButton how(150,200,100,50,"res/howbutton_def.png","res/howbutton_prs.png");
    TextureButton stats(200,300,100,50,"res/statbutton_def.png","res/statbutton_prs.png");
    TextureButton credits(300,300,100,50,"res/creditbutton_def.png","res/creditbutton_prs.png");

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