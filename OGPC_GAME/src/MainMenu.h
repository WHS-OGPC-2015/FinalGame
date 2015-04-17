#pragma once
#include "ofMain.h"
#include "src-MenuAPI/MenuInclude.h"


class MainMenu
{
public:
    // in public, we have simple functions
    MainMenu();
    void draw();
    bool update(ofVec2f& mousePos, bool& clicked, bool& pressed);
    void switchActive();
    bool getActive();

private:
   MenuManager *Manager; // this is the menumanager for the main menu
   Menu* optionsMenu; // pointer to options menu
   Menu* defaultMenu; // pointer to default menu
   Menu* creditsMenu; // pointer to credits menu
   Menu* quitGameMenu; //pointer to quit menu
   bool active; // is the main menu active or not

   // make pointers to every button
   HoverButton* Exit; // pointer to exit button
   HoverButton* OptionsBut; // pointer to options button, etc...
   HoverButton* StartGameButton;
   HoverButton* CreditsBut;
   HoverButton* CancelBut;
   HoverButton* QuitGameBut;
   HoverButton* YesQuitBut;
   HoverButton* NoQuitBut;
    Slider* BrightnessSlider;
};
