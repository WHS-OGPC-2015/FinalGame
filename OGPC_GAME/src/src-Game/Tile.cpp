#include "Tile.h"



GenTile::GenTile(int alt, std::string text)
{
    altitude = alt;
    texture = text;
    aset = true;
}
GenTile::GenTile()
{
}
void GenTile::setAltitude(int a)
{
    if (aset == false)
    {
        altitude = a;
        if (altitude < 0)
        {
            altitude = 0;
        }
        aset = true;
    }
}
