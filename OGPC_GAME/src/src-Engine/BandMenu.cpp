#include "BandMenu.h"

void createBandMenu(MenuManager* man, ofVec2f pos)
{
    double consta = 50;
    double constc = 50;


    int borderWidth = 25;
    Menu bandMenu(ofVec2f(0, 0));

    double halfmenuHeight = man->getTexturePointer("BMBackground").getHeight()/2;
    double halfmenuWidth = man->getTexturePointer("BMBackground").getWidth()/2;
    //---------------------------------------------------------------------------

    MenuEntity* bandBG;
    bandBG = new MenuBackground(
                    pos,
                    man->getTexturePointer("BMBackground"),
                    false
                     );



    MenuEntity* incarnName;
    incarnName = new TextBox(
                        "BAND_NAME",
                        ofVec2f((ofGetWindowWidth()/8)*5, pos.y - halfmenuHeight + borderWidth + man->getFontPointer("BMText").stringHeight("BAND_NAME")/2),
                        man->getFontPointer("BMText")
                            );
    MenuEntity* discBox;
    discBox = new TextBox(
                        "Number of Disciples:",
                       ofVec2f(pos.x - halfmenuWidth + borderWidth + man->getFontPointer("BMText").stringWidth("Number of Disciples:") / 2, pos.y - consta /*a constant*/),
                        man->getFontPointer("BMText")
                            );

    MenuEntity* discNum;
    discNum = new TextBox(
                    "X",
                    ofVec2f(pos.x - halfmenuWidth + 2 * borderWidth + man->getFontPointer("BMText").stringWidth("Number of Disciples:"), pos.y - consta + 3),
                    man->getFontPointer("BMText")
                    );

    MenuEntity* BreakUp;
    BreakUp = new HoverButton(
                        ofVec2f(pos.x - borderWidth - man->getTexturePointer("BMBreakUpButNormal").getWidth()/2, pos.y + constc),
                        man->getTexturePointer("BMBreakUpButNormal"),           // adding textures, we have done this before...
                        man->getTexturePointer("BMBreakUpButHovered"),
                        man->getTexturePointer("BMBreakUpButPressed"),
                        man->getTexturePointer("BMBreakUpButPressed"),
                        man->getTexturePointer("BMBreakUpButPressed"),
                        man->getTexturePointer("BMBreakUpButPressed")
                                );

    MenuEntity* MoveBut;
    MoveBut = new HoverButton(
                        ofVec2f(pos.x + borderWidth + man->getTexturePointer("BMMoveButNormal").getWidth()/2, pos.y + constc),
                        man->getTexturePointer("BMMoveButNormal"),           // adding textures, we have done this before...
                        man->getTexturePointer("BMMoveButHovered"),
                        man->getTexturePointer("BMMoveButPressed"),
                        man->getTexturePointer("BMMoveButPressed"),
                        man->getTexturePointer("BMMoveButPressed"),
                        man->getTexturePointer("BMMoveButPressed")
                                );

    MenuEntity* IncogBut;
    IncogBut = new HoverButton(
                        ofVec2f(pos.x, pos.y + borderWidth + man->getTexturePointer("BMIncogButNormal").getHeight() + constc),
                        man->getTexturePointer("BMIncogButNormal"),           // adding textures, we have done this before...
                        man->getTexturePointer("BMIncogButHovered"),
                        man->getTexturePointer("BMIncogButPressed"),
                        man->getTexturePointer("BMUnIncogButPressed"),
                        man->getTexturePointer("BMUnIncogButPressed"),
                        man->getTexturePointer("BMUnIncogButPressed")
                                );

    //bandMenu.addEntity(*bandBG, "BandMenuBackground");
    bandMenu.addEntity(*incarnName, "IncarnationName");
    bandMenu.addEntity(*discBox, "DiscipleBox");
    bandMenu.addEntity(*discNum, "DiscipleNumber");
    bandMenu.addEntity(*BreakUp, "BreakUpButton");
    bandMenu.addEntity(*MoveBut, "MoveButton");
    bandMenu.addEntity(*IncogBut, "IncognitoButton");

   man->addMenu(bandMenu, "BandMenu");
}

void resetBandMenuPositions(Menu& bandmenu, ofVec2f deltaPos)
{
    TextBox* texbox[3];

    texbox[0] = bandmenu.getPointerToChildByName<TextBox>("IncarnationName");

    texbox[1] = bandmenu.getPointerToChildByName<TextBox>("DiscipleNumber");

    texbox[2] = bandmenu.getPointerToChildByName<TextBox>("DiscipleBox");


    for (int i = 0; i < 3; i++)
    {
        texbox[i]->addPosition(deltaPos);
    }

//-------------------------------------------------------------------------------------
    MenuBackground* bandlBG = bandmenu.getPointerToChildByName<MenuBackground>("BandMenuBackground");
    bandlBG->addPosition(deltaPos);
//----------------------------------------------------------------------------------------------------------
    HoverButton* buttons[3];

    buttons[0] =   bandmenu.getPointerToChildByName<HoverButton>("BreakUpButton");

    buttons[1] =   bandmenu.getPointerToChildByName<HoverButton>("MoveButton");

    buttons[2] =   bandmenu.getPointerToChildByName<HoverButton>("IncognitoButton");

    for (int i = 0; i < 3; i++)
    {
        buttons[i]->addPosition(deltaPos);
    }
}

//void loadTextures(MenuManager& man)
//{
//    man.reloadTexture("CMBackground", "CMBackground.png");
//    //man.reloadTexture()
//};
