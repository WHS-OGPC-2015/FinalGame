#pragma once
#include "ofMain.h"
#include "Tile.h"
#include "../src-Game/Vec2i.h"
#include "../src-MenuAPI/MenuInclude.h"
#include "../XML/src/ofxXmlSettings.h"
#include "ResourceManager.h"
#include "Band.h"

class EnemyBand
{
public:

    EnemyBand();
    EnemyBand(std::string str, int i);

    void draw();
    void update(ofVec2f&, bool&, bool&);
    void turnlyUpdate();

    void setTexture(ResourceManager* res);
    void setTile(int i);
    void setBandVec(vector<Band>* vec);
    void setTileManager(TileManager* tilMan);
//    void setExtremeTiles(ofVec2i v1, ofVec2i v2);
    int getIndex();

    int convertTo1dindex(ofVec2i v);

    void saveObjectData(ofxXmlSettings& file);
    void loadObjectData(ofxXmlSettings& file);

private:

    Tile* boundTile;
    ofVec2i boundTileCoords;
    int boundTileIndex;

    ofTexture* enemyTexture;
    std::string textureName;

    ofVec2i extremeTiles[2];

    bool movable;
    int movement;

    int nextMoveIndex;
    vector<Band>* pointerToBandVector;
    TileManager* allTile;
};
