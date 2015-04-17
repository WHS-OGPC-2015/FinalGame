#include "CityMenu.h"

void createCityMenu(MenuManager* man, ofVec2f pos, ResourceManager* R)
{
    int borderWidth = 10;
    double pcrad = 50;
    Menu cityMenu(ofVec2f(0, 0));
    double consta = 2;

    man->addTexture("CMBackground", R->getTexture("CMBackground"));
    man->addFont("CMText", R->getFont("CMFont"));


    double halfmenuHeight = man->getTexturePointer("CMBackground").getHeight()/2;
    double halfmenuWidth = man->getTexturePointer("CMBackground").getWidth()/2;

    //textures for band menu
    man->addTexture("BMBackground", R->getTexture("BMBackground"));

    man->addTexture("BMBreakUpButNormal", R->getTexture("BreakUpButNormal"));
    man->addTexture("BMBreakUpButHovered", R->getTexture("BreakUpButHovered"));
    man->addTexture("BMBreakUpButPressed", R->getTexture("BreakUpButPressed"));

    man->addTexture("BMIncogButNormal", R->getTexture("IncogButNormal"));
    man->addTexture("BMIncogButHovered", R->getTexture("IncogButHovered"));
    man->addTexture("BMIncogButPressed", R->getTexture("IncogButPressed"));
    man->addTexture("BMUnIncogButNormal", R->getTexture("UnIncogButNormal"));
    man->addTexture("BMUnIncogButHovered", R->getTexture("UnIncogButHovered"));
    man->addTexture("BMUnIncogButPressed", R->getTexture("UnIncogButPressed"));



    man->addTexture("BMMoveButNormal", R->getTexture("MoveButNormal"));
    man->addTexture("BMMoveButHovered", R->getTexture("MoveButHovered"));
    man->addTexture("BMMoveButPressed", R->getTexture("MoveButPressed"));

    man->addFont("BMText", R->getFont("MySimpleFont"));

    //textures for next menu
    man->addTexture("TMBackground", R->getTexture("TMBackground"));
    man->addTexture("turnButNormal", R->getTexture("turnButNormal"));
    man->addTexture("turnButHovered", R->getTexture("turnButHovered"));
    man->addTexture("turnButPressed", R->getTexture("turnButPressed"));

    MenuEntity* citBG;
    citBG = new MenuBackground{
                    ofVec2f(ofGetScreenWidth()/2, ofGetScreenHeight()-150),
                    man->getTexturePointer("TMBackground"),
                    false
                     };

    MenuEntity* nameBox;
    nameBox = new TextBox{
                    "CITY_NAME",
                    ofVec2f(pos.x,
                            pos.y - halfmenuHeight + borderWidth),
                    man->getFontPointer("CMText")
                    };

    MenuEntity* PCBox;
    PCBox = new TextBox{
                    "Converted Population",
                    ofVec2f(pos.x,
                            pos.y + halfmenuHeight - 2 * borderWidth - 2 * pcrad - man->getFontPointer("CMText").stringHeight("Converted Population")/2),
                    man->getFontPointer("CMText")
                    };

    MenuEntity* discBox;
    discBox = new TextBox{
                    "Disciples Inside:",
                    ofVec2f(pos.x - halfmenuWidth + borderWidth + man->getFontPointer("CMText").stringWidth("Disciples Inside:")/2,
                            pos.y - 2*(halfmenuHeight - borderWidth)/3),
                    man->getFontPointer("CMText")
                    };

    MenuEntity* difBox;
    difBox = new TextBox{
                    "Difficulty:",
                    ofVec2f(pos.x - halfmenuWidth + borderWidth + man->getFontPointer("CMText").stringWidth("Difficulty:")/2,
                            pos.y - (halfmenuHeight - borderWidth)/3),
                    man->getFontPointer("CMText")
                    };

    MenuEntity* discNum;
    discNum = new TextBox{
                    "1",
                    ofVec2f(pos.x - halfmenuWidth + 2*borderWidth + man->getFontPointer("CMText").stringWidth("Disciples Inside:"),
                            pos.y - 2*(halfmenuHeight - borderWidth)/3) + consta,
                    man->getFontPointer("CMText")
                    };

    MenuEntity* difNum;
    difNum = new TextBox{
                    "0",
                    ofVec2f(pos.x - halfmenuWidth + 2*borderWidth + man->getFontPointer("CMText").stringWidth("Difficulty:"),
                            pos.y - (halfmenuHeight - borderWidth)/3) + consta,
                    man->getFontPointer("CMText")
                    };

    MenuEntity* converted;
    converted = new PieChart{
                    3,
                    1,
                    pcrad,
                    ofVec2f(pos.x,
                            pos.y + halfmenuHeight - borderWidth - pcrad),
                    ofColor::blue,
                    ofColor::darkBlue
                    };

    cityMenu.addEntity(*citBG, "CityBackground");
    cityMenu.addEntity(*nameBox, "CityName");
    cityMenu.addEntity(*discNum, "DiscipleNumber");
    cityMenu.addEntity(*difNum, "Difficulty");
    cityMenu.addEntity(*converted, "BelieverPie");
    cityMenu.addEntity(*discBox, "DiscipleBox");
    cityMenu.addEntity(*difBox, "DifficultyBox");
    cityMenu.addEntity(*PCBox, "PieChartText");

    man->addMenu(cityMenu, "CityMenu");
};

void resetCityMenuPositions(Menu& citymenu, ofVec2f deltaPos)
{
    TextBox* texbox[6];

    texbox[0] = citymenu.getPointerToChildByName<TextBox>("CityName");

    texbox[1] = citymenu.getPointerToChildByName<TextBox>("DiscipleNumber");

    texbox[2] = citymenu.getPointerToChildByName<TextBox>("Difficulty");

    texbox[3] = citymenu.getPointerToChildByName<TextBox>("DiscipleBox");

    texbox[4] = citymenu.getPointerToChildByName<TextBox>("DifficultyBox");

    texbox[5] = citymenu.getPointerToChildByName<TextBox>("PieChartText");

    for (int i = 0; i < 6; i++)
    {
        texbox[i]->addPosition(deltaPos);
    }

    MenuBackground* cityBG = citymenu.getPointerToChildByName<MenuBackground>("CityBackground");
    cityBG->addPosition(deltaPos);

    PieChart* Pchart = citymenu.getPointerToChildByName<PieChart>("BelieverPie");
    Pchart->addPosition(deltaPos);
}

void loadTextures(MenuManager& man)
{
    man.reloadTexture("CMBackground", "CMBackground.png");
    //man.reloadTexture()
};


