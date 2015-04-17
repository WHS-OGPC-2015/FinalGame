#include "PauseMenu.h"


PauseMenu::PauseMenu()
{
    pauseActive = false; //activating the pause menu

    PauseManager = new MenuManager;
    Menu defaultMenu(ofVec2f(xpos, ypos));
    Menu opMenu(ofVec2f(xpos, ypos));
                                                                    //adding textures and fonts to the manager
    PauseManager->addTexture("StandardNormal", "StandardNormal.png");
    PauseManager->addTexture("StandardPressed", "StandardPressed.png");
    PauseManager->addTexture("StandardHovered", "StandardHovered.png");

    PauseManager->addTexture("PauseBackground" , "PauseBackground.png");
    PauseManager->addFont("NormalFont", "MySimpleFont.ttf", 16);

    //making buttons for the menu
    MenuEntity *background; // Orange Background
    background = new MenuBackground(
                            ofVec2f(ofGetWindowWidth()/2, ofGetWindowHeight()/2), // in the middle of the window
                            PauseManager->getTexturePointer("PauseBackground"),
                            false
                                  );
    MenuEntity *ResumeBut;
    ResumeBut = new HoverButton(
                            ofVec2f(ofGetWindowWidth()/2, (ofGetScreenHeight()/2)-150),
                            PauseManager->getTexturePointer("StandardNormal.png"),
                            PauseManager->getTexturePointer("StandardHovered.png"),
                            PauseManager->getTexturePointer("StandardPressed.png"),
                            PauseManager->getTexturePointer("StandardPressed.png"),
                            PauseManager->getTexturePointer("StandardPressed.png"),
                            PauseManager->getTexturePointer("StandardPressed.png"),
                            PauseManager->getFontPointer("NormalFont"),
                                ""
                                );
    MenuEntity *OptionsBut;
    OptionsBut = new HoverButton(
                            ofVec2f(ofGetWindowWidth()/2, ofGetScreenHeight()/2),
                            PauseManager->getTexturePointer("StandardNormal.png"),
                            PauseManager->getTexturePointer("StandardHovered.png"),
                            PauseManager->getTexturePointer("StandardPressed.png"),
                            PauseManager->getTexturePointer("StandardPressed.png"),
                            PauseManager->getTexturePointer("StandardPressed.png"),
                            PauseManager->getTexturePointer("StandardPressed.png"),
                            PauseManager->getFontPointer("NormalFont"),
                                 ""
                                );

    MenuEntity *QuitBut;
    QuitBut = new HoverButton(
                            ofVec2f(ofGetWindowWidth()/2, (ofGetScreenHeight()/2)+150),
                            PauseManager->getTexturePointer("StandardNormal.png"),
                            PauseManager->getTexturePointer("StandardHovered.png"),
                            PauseManager->getTexturePointer("StandardPressed.png"),
                            PauseManager->getTexturePointer("StandardPressed.png"),
                            PauseManager->getTexturePointer("StandardPressed.png"),
                            PauseManager->getTexturePointer("StandardPressed.png"),
                            PauseManager->getFontPointer("NormalFont"),
                              ""
                                );

    //adding buttons to the menu and the options menu to the manager as well

    defaultMenu.addEntity(*background , "PauseBackground");
    defaultMenu.addEntity(*ResumeBut , "ResumeButton");
    defaultMenu.addEntity(*OptionsBut , "OptionsButton");
    defaultMenu.addEntity(*QuitBut , "QuitButton");

    PauseManager->addMenu(defaultMenu , "DefaultMenu");

    regularMenu = PauseManager->getMenuPointerByName("DefaultMenu");
    regularMenu->setActive();

    Resume = regularMenu->getPointerToChildByName<HoverButton>("ResumeButton");
    Options = regularMenu->getPointerToChildByName<HoverButton>("OptionsButton");
    Quit = regularMenu->getPointerToChildByName<HoverButton>("QuitButton");


}
int PauseMenu::update(ofVec2f& pos, bool c, bool n)
{
    if(pauseActive)
    {
        PauseManager->update(pos, c, n);
        if(Quit->getEventDataInt() > 2)        //return 0 to exit to main menu
        {
            return 0;
        }
        else if(Resume->getEventDataInt() > 2)//return 1 to go back to game
        {
            toggleActive();
        }
    }
    return 2;   //return 2 to remain in pause menu

}
void PauseMenu::draw()
{
    if(pauseActive)
    {
        PauseManager->draw();
    }
}

bool PauseMenu::isActive()
{
    if(pauseActive)
    {
        return true;
    }
    return false;
}

void PauseMenu::toggleActive()
{
    pauseActive = !pauseActive;
}


