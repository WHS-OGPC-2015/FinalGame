#include "Tile.h"

Tile::Tile()
{
    //??
    Cityoc = false;
    Bandoc = 0;
    EBandoc = false;
}

void Tile::update()
{
    //??
}

void Tile::draw()
{
    texture->draw(location.x, location.y);
}

ofVec2f Tile::getLocation()
{
    return location;
}

void Tile::setLocation(ofVec2f newLocation)
{
    location = newLocation;
}

void Tile::setTexture(ofTexture& tex)
{
    texture = &tex;
}


void Tile::switchCityoc()
{
    Cityoc = !Cityoc;
}

void Tile::setBandoc(int i)
{
    Bandoc = i;
}

void Tile::switchEBandoc()
{
    EBandoc = !EBandoc;
}

bool Tile::getCityoc()
{
    return Cityoc;
}

int Tile::getBandoc()
{
    return Bandoc;
}

bool Tile::getEBandoc()
{
    return EBandoc;
}

