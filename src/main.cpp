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
    Sprite background(0,0,320,240,"res/backdrop/mainmenu.png");
    TextureButton play(182,66,96,24,"res/ui/playbutton_def.png","res/ui/playbutton_prs.png");
    TextureButton how(182,106,96,25,"res/ui/howbutton_def.png","res/ui/howbutton_prs.png");
    TextureButton stats(203,213,40,11,"res/ui/statbutton_def.png","res/ui/statbutton_prs.png");
    TextureButton credits(261,216,42,11,"res/ui/creditbutton_def.png","res/ui/creditbutton_prs.png");

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

    // GAME
    Sprite gameBackground(0,0,320,240,"res/backdrop/gamedrop.png");

    std::vector<CanvasItem*> gameCanvas = {
        &gameBackground
    };

    // MAIN LOOP
    while (running) {
        LCD.Clear(BLACK);

        ClickEvent* event = Input::instance().update();
        if (event != NULL) {
            if (mainMenu) {
                // Poll buttons and clickables
                // (This is a kind of messy way of doing these pop-ups, I don't want to over-engineer it.)
                for (Button* b : mainMenuClickables) {
                    bool release = (*b).poll(event);
                    if (release && b == &play) {
                        mainMenu = false;
                    } else if (release && b == &how) {
                        Sprite howBackdrop(0,0,320,240,"res/backdrop/howtoplaymenu.png");
                        TextureButton back(10,10,25,25,"res/ui/backbutton_def.png","res/ui/backbutton_prs.png");
                        mainMenuCanvas.push_back(&howBackdrop);
                        mainMenuCanvas.push_back(&back);
                        mainMenuClickables.push_back(&back);
                    } else if (release && b == &stats) {
                        Sprite statsBackdrop(0,0,320,240,"res/backdrop/statsmenu.png");
                        TextureButton back(10,10,25,25,"res/ui/backbutton_def.png","res/ui/backbutton_prs.png");
                        mainMenuCanvas.push_back(&statsBackdrop);
                        mainMenuCanvas.push_back(&back);
                        mainMenuClickables.push_back(&back);
                    } else if (release && b == &credits) {
                        Sprite creditsBackdrop(0,0,320,240,"res/backdrop/creditsmenu.png");
                        TextureButton back(10,10,25,25,"res/ui/backbutton_def.png","res/ui/backbutton_prs.png");
                        mainMenuCanvas.push_back(&creditsBackdrop);
                        mainMenuCanvas.push_back(&back);
                        mainMenuClickables.push_back(&back);
                    } else if (release) { // Back button
                        // free the popup
                        delete mainMenuCanvas.back();
                        mainMenuCanvas.pop_back();
                        delete mainMenuCanvas.back();
                        mainMenuCanvas.pop_back();

                        delete mainMenuClickables.back();
                        mainMenuClickables.pop_back();
                    }
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
            for (CanvasItem* c : gameCanvas) {
                (*c).draw();
            }
        }

        LCD.Update();
        Sleep(0.01);
    }
}