#pragma once

#include "ofMain.h"
#include "Menu.h"
#include <Map>

class MenuManager
{
public:
    void addTexture(std::string name, std::string fileName);//add texture to array by filename and mapped name
    void addTexture(std::string name, ofTexture tex);
    ofTexture& getTexturePointer(std::string tex);//retrieve texture reference by name
    ofTexture& getTexturePointer(int tex);//retrieve texture reference my position in array
    void reloadTexture(std::string, std::string);

    void addFont(std::string name, std::string fileName, int fontSize);//add TrueTypeFont to array by filename
    ofTrueTypeFont& getFontPointer(std::string name);//retrieve font by reference by name
    ofTrueTypeFont& getFontPointer(int pos);//retrieve font reference by position in array
    void addFont(std::string name, ofTrueTypeFont);

    void addMenu(Menu, std::string name);//add Menu to menu array
    Menu* getMenuPointerByName(std::string name); //get menu by name

    void update(ofVec2f&, bool&, bool&);//updates menus
    void draw();//draws menus
private:
    std::vector <ofTexture> textures;//holds textures
    std::map <std::string, int> textureNames;//holds strings mapped to spots in the textures array
    std::vector <Menu> menus;//holds menus
    std::map <std::string, int> menuNames;//holds string mapped to spots in string array
    std::vector <ofTrueTypeFont> fonts;//holds fonts
    std::map <std::string, int> fontNames;//holds strings mapped to spots in fonts array
};
