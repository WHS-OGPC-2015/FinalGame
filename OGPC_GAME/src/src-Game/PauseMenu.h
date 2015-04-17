#pragma once
#include "../src-MenuAPI/MenuInclude.h"


class PauseMenu
{
    public:
        PauseMenu();

        void draw();
        int update(ofVec2f& pos, bool c, bool n);
        int xpos = ofGetWindowWidth()/3;
        int ypos = ofGetWindowWidth()/3;
        bool isActive();
        void toggleActive();
    private:
        MenuManager* PauseManager; //different manager for pause menu
        Menu* regularMenu;
        Menu* optionsMenu;  //pointer to options menu
        HoverButton* Resume; // resume button
        HoverButton* Options; // options button
        HoverButton* Quit; //quit button
        bool pauseActive; //tells if the menu is displayed or not (if the game is paused or not)

};

