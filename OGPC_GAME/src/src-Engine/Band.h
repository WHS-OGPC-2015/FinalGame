#pragma once
#include "ofMain.h"
#include "Tile.h"
#include "../src-Game/Vec2i.h"
#include "../src-MenuAPI/MenuInclude.h"
#include "../XML/src/ofxXmlSettings.h"
#include "ResourceManager.h"
#include "TileManager.h"
//#include "../Engine/ResourceManager.h"
class Band
{
public:

    Band();
    Band(bool incog, bool incarn, int startnum, int mov, std::string incarnName, std::string TN[], std::string HLTName, int /*set as "" if incarn is false*/);

    void draw();
    int update(ofVec2f& mousePos, bool& clicked, bool& pressed);
    void turnlyUpdate();
    int getClickedData(ofVec2f& mousePos, bool& clicked, bool& pressed);


    void setTextures(ResourceManager* res);
    void setTile(int t);
    int getIndex();
    ofVec2i getCoords();
    vector<std::string> getTextureNames();

    void setBandMenu(Menu* fillme);

    void fillMenu();
    void alignButtons();

    void findActions();

    void setTileManager(TileManager* tilm);
    //these are all boring -- just sets, gets, and swaps
    int convertTo1dindex(ofVec2i v);

    void setIncarnation(bool b, std::string incarnName);
    bool getIncarnation();

    void setDiscipleNum(int i);
    void changeDiscipleNum(int i);
    int getDiscipleNum();

    vector<int> getMoves();

    void swapIncognito();
    bool getIncognito();

    void setExtremeTiles(ofVec2i v1, ofVec2i v2);

    void resetBandType();
    int getBandType();

    void switchSelect();
    bool getSelect();
    void setTileWidth(double d);

    //until here

    void saveObjectData(ofxXmlSettings&);
    void loadObjectData(ofxXmlSettings&);

private:



    Tile* boundTile;
    ofVec2i boundTileCoords;
    int boundTileIndex;

    ofTexture* BandTextures[4]; // 0 = reg, 1 = incog, 2 = incarn, 3 = incog and incarn
    std::string TextureNames[4];
    ofTexture* HLTex;
    std::string HLTexName;


    int discipleNum;
    int begDisNum; // beginning disciple number -- doesn't change as opposed to disciple num

    bool incarnation;
    std::string incarnationName;

    bool incognito;

    int bandType;

    bool selected;
    int clickedData;
    bool hovered;

    bool movable;
    int actionState;
    ofVec2i extremeTiles[2]; // e.g., [(0,0),(100,100)] -- useful for  finding possible moves


    int movement;

    double tileWidth;

    ofVec2f TLpos;
    ofVec2f BRpos;


    Menu* bandMenu;
    HoverButton* actionButtons[3];

    vector<ofVec2i> possibleMovesCoords;
    vector<int> possibleMovesIndex;
    TileManager* allTiles;

    bool startup;
    bool HLdraw;

    ofVec2i hoveredTile;
};
