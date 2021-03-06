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
    void setIncog(bool b);
    void switchEBandoc();

    bool getCityoc();
    int getBandoc();
    bool getEBandoc();
    bool getIncog();

private:
    ofTexture* texture;
    ofVec2f location;
    bool Cityoc;
    int Bandoc;
    bool EBandoc;
    bool incog;

};



