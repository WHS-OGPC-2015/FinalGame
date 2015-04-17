
#pragma once
#include "ofMain.h"


class GenTile
{
    public:
    GenTile(int alt, std::string text);
    GenTile();
    void setAltitude(int a);
    int altitude;
    std::string texture;
    bool aset;
};
