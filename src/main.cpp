#include "FEHLCD.h"
#include "FEHUtility.h"
#include "global.h"
#include "engine/input.h"
#include "engine/interface.h"

#include <vector>
#include <memory>
#include <iostream>

int main() {
    bool running = true;

    bool mainMenu = true;
    
    // Instantiate the main menu canvas
    // Note: order of this vector corresponds to draw order.
    std::vector<std::shared_ptr<CanvasItem>> mainMenuCanvas = {
        std::shared_ptr<CanvasItem>(new Sprite(0,0,320,240,"res/backdrop/mainmenu.png")),
        std::shared_ptr<CanvasItem>(new TextureButton(182,66,96,24,"res/ui/playbutton_def.png","res/ui/playbutton_prs.png")),
        std::shared_ptr<CanvasItem>(new TextureButton(182,106,96,25,"res/ui/howbutton_def.png","res/ui/howbutton_prs.png")),
        std::shared_ptr<CanvasItem>(new TextureButton(203,213,40,11,"res/ui/statbutton_def.png","res/ui/statbutton_prs.png")),
        std::shared_ptr<CanvasItem>(new TextureButton(261,216,42,11,"res/ui/creditbutton_def.png","res/ui/creditbutton_prs.png")),
        std::shared_ptr<CanvasItem>(new Sprite(0,0,320,240,"res/backdrop/howtoplaymenu.png")),
        std::shared_ptr<CanvasItem>(new Sprite(0,0,320,240,"res/backdrop/statsmenu.png")),
        std::shared_ptr<CanvasItem>(new Sprite(0,0,320,240,"res/backdrop/creditsmenu.png")),
        std::shared_ptr<CanvasItem>(new TextureButton(10,10,25,25,"res/ui/backbutton_def.png","res/ui/backbutton_prs.png"))
    };
    // Set menus and back button to invisible
    mainMenuCanvas.at(5)->hide(); mainMenuCanvas.at(6)->hide();
    mainMenuCanvas.at(7)->hide(); mainMenuCanvas.at(8)->hide();

    // Register buttons
    std::vector<std::shared_ptr<Button>> mainMenuClickables = {
        std::shared_ptr<Button>(static_cast<Button*>(mainMenuCanvas.at(1).get())),
        std::shared_ptr<Button>(static_cast<Button*>(mainMenuCanvas.at(2).get())),
        std::shared_ptr<Button>(static_cast<Button*>(mainMenuCanvas.at(3).get())),
        std::shared_ptr<Button>(static_cast<Button*>(mainMenuCanvas.at(4).get())),
        std::shared_ptr<Button>(static_cast<Button*>(mainMenuCanvas.at(8).get()))
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
                // (This is a kind of messy way of doing these pop-ups, but I don't want to over-engineer it.)
                int idx = 0;
                for (auto&& button : mainMenuClickables) {
                    bool release = button->poll(event);
                    if (release) {
                        switch (idx) {
                            case 0: // PLAY
                                mainMenu = false;
                                break;
                            case 1: // HOW TO PLAY
                                mainMenuCanvas.at(5)->show();
                                mainMenuCanvas.at(8)->show();
                                break;
                            case 2: // STATS
                                mainMenuCanvas.at(6)->show();
                                mainMenuCanvas.at(8)->show();
                                break;
                            case 3: // CREDITS
                                mainMenuCanvas.at(7)->show();
                                mainMenuCanvas.at(8)->show();
                                break;
                            case 4: // BACK
                                mainMenuCanvas.at(5)->hide();
                                mainMenuCanvas.at(6)->hide();
                                mainMenuCanvas.at(7)->hide();
                                mainMenuCanvas.at(8)->hide();
                                break;
                            default:
                                std::cout << "Button registry error!";
                        }
                    }
                    idx++;
                }
            } else {
                // Poll buttons and clickables
            }
        }

        if (mainMenu) {
            for (auto&& item : mainMenuCanvas) {
                item->draw();
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