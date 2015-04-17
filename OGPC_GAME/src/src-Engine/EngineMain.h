#pragma once
#include "ofMain.h"
#include "ObjectManager.h"

class Engine
{
public:
    Engine();
    ~Engine();

    void setup(std::string tileData, std::string objectData, std::string gameData, ofVec2f&, ResourceManager* rec);
    void update(ofVec2f& mousePos, bool& clicked, bool& pressed);
    void draw();
    void mainThreadFunction();
    void drawNoTranslate();
    void updateNoTranslate(ofVec2f& mousePos, bool& clicked, bool& pressed);
private:
    TileManager* tiles;
    ResourceManager* resources;
    ObjectManager* objects;

    ofVec2f* tFactor;



};
