#include "UtilMenus.h"

void createNextTurnMenu(MenuManager* man, ofVec2f pos)
{
    Menu turnMenu(ofVec2f(0, 0));

    double halfMenuHeight = man->getTexturePointer("TMBackground").getHeight()/2;
    double halfMenuWidth = man->getTexturePointer("TMBackground").getWidth()/2;
    //---------------------------------------------------------------------------
    MenuEntity* nextTurnBut;
    nextTurnBut = new HoverButton(
                        ofVec2f(ofGetScreenWidth()/8, ofGetScreenHeight()-150),
                        man->getTexturePointer("turnButNormal"),           // adding textures, we have done this before...
                        man->getTexturePointer("turnButHovered"),
                        man->getTexturePointer("turnButPressed"),
                        man->getTexturePointer("turnButPressed"),
                        man->getTexturePointer("turnButPressed"),
                        man->getTexturePointer("turnButPressed")
                                );

    turnMenu.addEntity(*nextTurnBut, "NextTurnButton");

   man->addMenu(turnMenu, "TurnMenu");
}

