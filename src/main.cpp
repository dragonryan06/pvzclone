#include "FEHLCD.h"
#include "FEHUtility.h"
#include "global.h"
#include "engine/input.h"
#include "engine/interface.h"
#include "game/game.h"

#include <vector>
#include <memory>
#include <iostream>

int main() {
    bool running = true;

    bool mainMenu = true;

    // SESSION STATS
    int longestTime = 0;
    int mostSun = 0;
    int mostKills = 0;
    int mostPlanted = 0;

    
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
    // PlantPlacement plantPlacement;

    // Instantiate the game canvas
    std::vector<std::shared_ptr<CanvasItem>> gameCanvas = {
        std::shared_ptr<CanvasItem>(new Sprite(0,0,320,240,"res/backdrop/gamedrop.png")),
        std::shared_ptr<CanvasItem>(new TextureButton(156,3,24,29, "res/ui/peashooterbutton_def.png", "res/ui/peashooterbutton_prs.png")),
        std::shared_ptr<CanvasItem>(new TextureButton(183,3,24,29, "res/ui/sunflowerbutton_def.png", "res/ui/sunflowerbutton_prs.png"))
    };

    // Register buttons
    std::vector<std::shared_ptr<Button>> gameClickables = {
        std::shared_ptr<Button>(static_cast<Button*>(gameCanvas.at(1).get())),
        std::shared_ptr<Button>(static_cast<Button*>(gameCanvas.at(2).get())),
    };

    // MAIN LOOP
    while (running) {
        LCD.Clear(BLACK);

        ClickEvent event = Input::instance().update();
        if (!event.empty) {
            if (mainMenu) {
                // Poll buttons and clickables
                // (This is a kind of messy way of doing these pop-ups, but I don't want to over-engineer it.)
                int idx = 0;
                for (auto&& button : mainMenuClickables) {
                    bool release = button->poll(std::shared_ptr<ClickEvent>(&event));
                    if (release) {
                        switch (idx) {
                            case 0: // PLAY
                                mainMenu = false;
                                Game::instance().init();
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
                int idx = 0;
                for (auto&& button : gameClickables) {
                    bool release = button->poll(std::shared_ptr<ClickEvent>(&event));
                    if (release) {
                        switch (idx) {
                            case 0: // Peashooter
                                Game::instance().selectPlant(0);
                                break;
                            case 1: // Sunflower
                                Game::instance().selectPlant(1);
                                break;
                            default:
                                std::cout << "Button registry error!";
                        }
                    }
                    idx++;
                }
            }
        }

        if (mainMenu) {
            for (auto&& item : mainMenuCanvas) {
                item->draw();
            }
            if (mainMenuCanvas.at(6)->isVisible()) {
                // Writing twice for word shadow
                LCD.SetFontColor(BLACK);
                LCD.WriteAt(stringifyTime(longestTime),131,70);
                LCD.WriteAt(mostSun,141,120);
                LCD.WriteAt(mostKills,141,165);
                LCD.WriteAt(mostPlanted,141,210);

                LCD.SetFontColor(WHITE);
                LCD.WriteAt(stringifyTime(longestTime),130,69);
                LCD.WriteAt(mostSun,140,119);
                LCD.WriteAt(mostKills,140,164);
                LCD.WriteAt(mostPlanted,140,209);
            }
        } else {
            for (auto&& item : gameCanvas) {
                item->draw();
            }
            if (Game::instance().updateGame(std::shared_ptr<ClickEvent>(&event))) {
                // Draw game over screen and wait for touch to continue

                FEHImage gameOverScreen("res/backdrop/gameover.png");
                int _x, _y;
                while (!LCD.Touch(&_x,&_y)) {
                    gameOverScreen.Draw(0,0);
                }

                // Update stats
                if (Game::instance().timeSurvived > longestTime) longestTime = Game::instance().timeSurvived;
                if (Game::instance().totalSun > mostSun) mostSun = Game::instance().totalSun;
                if (Game::instance().totalKills > mostKills) mostKills = Game::instance().totalKills;
                if (Game::instance().plantsPlaced > mostPlanted) mostPlanted = Game::instance().plantsPlaced;
                Game::instance().cleanUp();
                mainMenu = true;
            }
        }

        LCD.Update();
        Sleep(0.01);
    }
}