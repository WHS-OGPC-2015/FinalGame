#include "EnemyBand.h"


int EnemyBand::convertTo1dindex(ofVec2i v)
{
    return (v.y * fabs(extremeTiles[1].x - extremeTiles[0].x) + v.x); // converts an ofVec2i to an int based on the amount of tiles in the map
}

EnemyBand::EnemyBand()
{
    textureName = "";
    movable = true;
}

EnemyBand::EnemyBand(std::string str)
{
    textureName = str;
    movable = true;
}
//---------------------------------------------------
void EnemyBand::update()
{

}

void EnemyBand::turnlyUpdate()
{
    bool found;
    bool done = false;
    int siz = pointerToBandVector->size();
    int discipleNum = 0;
    int followIndex = -1;
    ofVec2i newCoord;
    ofVec2i coords = ofVec2i(-1, -1);
    for (int i = 0; i < siz; i++)
    {
        if (pointerToBandVector->at(i).getIncognito() == false)
        {
            if(pointerToBandVector->at(i).getCoords().x +
               pointerToBandVector->at(i).getCoords().y <= movement)
            {
                boundTile = allTile->getTileByCoords(ofVec2f(pointerToBandVector->at(i).getCoords().x, pointerToBandVector->at(i).getCoords().y));
                done = true;
            }

            if (pointerToBandVector->at(i).getDiscipleNum() > discipleNum)
            {
                discipleNum = pointerToBandVector->at(i).getDiscipleNum();
                coords = pointerToBandVector->at(i).getCoords();
                followIndex = i;
                found = true;
            }
        }
    }

    if (done == false)
    {
        if (found == true)
        {
            double rise = (boundTileCoords.y - coords.y);
            double run =  (boundTileCoords.x - coords.x);
            if (rise + run != 0)
            {
                double nrise = (rise * movement)/(rise + run);
                double nrun = (run * movement)/(rise + run);
                if (nrise > nrun)
                {
                    newCoord = ofVec2i(nrise, nrun + .5);
                }
                else
                {
                    newCoord = ofVec2i(nrise + .5 + boundTileCoords.x, nrun + boundTileCoords.y);
                }
            }
            else
            {
                newCoord = boundTileCoords;
            }
        }
        else
        {
            newCoord = boundTileCoords;
        }
        boundTile = allTile->getTileByCoords(ofVec2f(newCoord.x, newCoord.y));


    }
}


void EnemyBand::setBandVec(vector<Band>* vec)
{
    pointerToBandVector = vec;
}

void EnemyBand::draw()
{

}


//---------------------------------------------------
void EnemyBand::setTexture(ResourceManager* res)
{
    enemyTexture = &res->getTextureReference(textureName);
}

void EnemyBand::setTile(int i)
{
    boundTile = allTile->getTileByIndice(i);
    boundTile->switchEBandoc();
    boundTileIndex = i;

    ofVec2f tmp = allTile->tileArrayCoordsByIndice(i);
    boundTileCoords = ofVec2i(tmp.x, tmp.y);
}

void EnemyBand::setTileManager(TileManager* tilman)
{
    allTile = tilman;
    extremeTiles[0] = ofVec2i(0,0);
    ofVec2f temp = allTile->tileArrayCoordsByIndice(allTile->getTileAmt()-1);
    extremeTiles[1] = ofVec2i(temp.x, temp.y);
}
//void EnemyBand::setExtremeTiles(ofVec2i v1, ofVec2i v2)
//{
//    extremeTiles[0] = v1;
//    extremeTiles[1] = v2;
//    int temp = fabs(extremeTiles[1].x - extremeTiles[0].x);
//    boundTileCoords = ofVec2i(boundTileIndex % temp, boundTileIndex / temp);
//}

int EnemyBand::getIndex()
{
    return boundTileIndex;
}


void EnemyBand::saveObjectData(ofxXmlSettings& file)
{
    file.addValue("movable", movable);
    file.addValue("textureName", textureName);
    file.addValue("boundTileIndex", boundTileIndex);

    file.addValue("boundTileCoordsx", boundTileCoords.x);
    file.addValue("boundTileCoordsy", boundTileCoords.y);

    file.addValue("extremeTile0x", extremeTiles[0].x);
    file.addValue("extremeTile0y", extremeTiles[0].y);
    file.addValue("extremeTile1x", extremeTiles[1].x);
    file.addValue("extremeTile1y", extremeTiles[1].y);
}

void EnemyBand::loadObjectData(ofxXmlSettings& file)
{
    movable = file.getValue("movable", 0);
    textureName = file.getValue("textureName", "");
    boundTileIndex = file.getValue("boundTileIndex", 0);
    boundTileCoords.x = file.getValue("boundTileCoordsx", 0);
    boundTileCoords.y = file.getValue("boundTileCoordsy", 0);

    extremeTiles[0].x = file.getValue("extremeTile0x", 0);
    extremeTiles[0].y = file.getValue("extremeTile0y", 0);
    extremeTiles[1].x = file.getValue("extremeTile1x", 0);
    extremeTiles[1].y = file.getValue("extremeTile1y", 0);
}
