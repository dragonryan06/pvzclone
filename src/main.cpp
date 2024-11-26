#include <vector>
#include <memory>
#include "FEHLCD.h"
#include "FEHUtility.h"
#include "global.h"
#include "engine/input.h"
#include "engine/interface.h"
#include "game/game.h"

int main() {
    bool running = true;

    bool mainMenu = true;

    // SESSION STATS
    int longestTime = 0;
    int mostSun = 0;
    int mostKills = 0;
    int mostPlanted = 0;

    
    // MAIN MENU
    Sprite background(0,0,320,240,"res/backdrop/mainmenu.png");
    TextureButton play(182,66,96,24,"res/ui/playbutton_def.png","res/ui/playbutton_prs.png");
    TextureButton how(182,106,96,25,"res/ui/howbutton_def.png","res/ui/howbutton_prs.png");
    TextureButton stats(203,213,40,11,"res/ui/statbutton_def.png","res/ui/statbutton_prs.png");
    TextureButton credits(261,216,42,11,"res/ui/creditbutton_def.png","res/ui/creditbutton_prs.png");
    
    // Back button
    TextureButton back(10,10,25,25,"res/ui/backbutton_def.png","res/ui/backbutton_prs.png");
    back.hide();

    // How to play menu
    Sprite howBackground(0,0,320,240,"res/backdrop/howtoplaymenu.png");
    howBackground.hide();
    // Stats menu
    Sprite statsBackground(0,0,320,240,"res/backdrop/statsmenu.png");
    statsBackground.hide();
    // Credits menu
    Sprite creditsBackground(0,0,320,240,"res/backdrop/creditsmenu.png");
    creditsBackground.hide();
    

    std::vector<CanvasItem*> mainMenuCanvas = {
        &background,
        &play,
        &how,
        &stats,
        &credits,
        &howBackground,
        &statsBackground,
        &creditsBackground,
        &back
    };

    std::vector<Button*> mainMenuClickables = {
        &play,
        &how,
        &stats,
        &credits,
        &back
    };

    // GAME
    Sprite gameBackground(0,0,320,240,"res/backdrop/gamedrop.png");

    std::vector<CanvasItem*> gameCanvas = {
        &gameBackground
    };

    // MAIN LOOP
    while (running) {
        LCD.Clear(BLACK);

        ClickEvent event = Input::instance().update();
        if (!event.empty) {
            if (mainMenu) {
                // Poll buttons and clickables
                // (This is a kind of messy way of doing these pop-ups, I don't want to over-engineer it.)
                for (Button* b : mainMenuClickables) {
                    bool release = (*b).poll(std::shared_ptr<ClickEvent>(&event));
                    if (release && b == &play) {
                        Game::instance().init();
                        mainMenu = false;
                    } else if (release && b == &how) {
                        howBackground.show();
                        back.show();
                    } else if (release && b == &stats) {
                        statsBackground.show();
                        back.show();
                    } else if (release && b == &credits) {
                        creditsBackground.show();
                        back.show();
                    } else if (release) { // Back button
                        howBackground.hide();
                        statsBackground.hide();
                        creditsBackground.hide();
                        back.hide();
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
            if (statsBackground.isVisible()) {
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
            // draw game
            gameBackground.draw();
            if (Game::instance().updateGame(std::shared_ptr<ClickEvent>(&event))) {
                // Draw game over screen and wait for touch to continue
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