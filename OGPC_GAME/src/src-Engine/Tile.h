#pragma once
#include "ofMain.h"


class Tile
{
public:
    Tile();         //constructor

    void update();
    void draw();

    ofVec2f getLocation();
    void setLocation(ofVec2f);

    void setTexture(ofTexture&);    //sets tile texture

    void switchCityoc();
    void setBandoc(int i);
    void switchEBandoc();

    bool getCityoc();
    int getBandoc();
    bool getEBandoc();

private:
    ofTexture* texture;
    ofVec2f location;
    bool Cityoc;
    int Bandoc;
    bool EBandoc;

};



