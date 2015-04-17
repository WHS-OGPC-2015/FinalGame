#include "TileManager.h"
#include "../XML/src/ofxXmlSettings.h"
TileManager::TileManager(std::string file, ofVec2f& trans, ResourceManager& recMan) : tFactor(trans), resources(recMan)
{

    loadFromFile(file);

    for(int ii = 0; ii<tiles.size(); ii++)//initialize all members of array to false
    {
        toDraw.push_back(false);
    }


}

void TileManager::loadFromFile(std::string file)
{

    ofxXmlSettings theMap;      //create new XML object for loading the tileset
    if(theMap.loadFile(file))   //if the xml document successfully loads
    {
        mapSize.x = theMap.getValue("mapSizeX", 0.0);   //retrieve width of tile map
        mapSize.y = theMap.getValue("mapSizeY", 0.0);   //retrieve height of tile map
        tileSize.x = theMap.getValue("tileSizeX", 0.0); //retrieve width of individual tile
        tileSize.y = theMap.getValue("tileSizeY", 0.0); //retrieve height of individual tile
        int tilesPushed = theMap.getValue("pushedTileCount", 0);

        int numSame = 0;
        int indice = 0;
        theMap.pushTag("tileArray");    //go into tile tag section

        for(int ii = 0; ii < tilesPushed; ii++)
        {
            theMap.pushTag("tile", ii); //enter individual tile tag

            std::string tex = theMap.getValue("texture", "");
            numSame = theMap.getValue("numSame", 0);



            for(int bb = 0; bb<numSame; bb++)
            {

                Tile tmp; //create temporary tile

                //set texture of tile by getting string from xml doc
                tmp.setTexture(resources.getTextureReference(tex));


                ofVec2f pos = tileArrayCoordsByIndice(indice);
                ofVec2f location = ofVec2f(pos.x*tileSize.x,
                                            pos.y*tileSize.y);
                tmp.setLocation(location);
                //std::cout << location.x << ", " << location.y << std::endl;
                tiles.push_back(tmp);
                indice++;
            }
            theMap.popTag();

        }
        theMap.popTag();


    }
    else
    {
        //tell open frameworks to print an error if the XML doc did not load
        ofLogError("Position file did not load!");
    }

}

void TileManager::update()
{

    maxDisplayDim = ofVec2f(trunc(ofGetWindowWidth()/tileSize.x)+1, trunc(ofGetWindowHeight()/tileSize.y)+1);//max number of tiles that can be displayed on the screen
    topLeftTile = ofVec2f(fabs(trunc(tFactor.x/tileSize.x)) , fabs(trunc(tFactor.y/tileSize.y)));               //number of tiles the map has been translated
    bottomRightTile = ofVec2f(topLeftTile.x+maxDisplayDim.x, topLeftTile.y+maxDisplayDim.y);
    topLeftScalar = tileIndiceByArrayCoords(topLeftTile);
    bottomRightScalar = tileIndiceByArrayCoords(bottomRightTile);
    //std::cout << topLeftScalar << ",! " << bottomRightScalar << std::endl;
    //std::cout <<topLeftScalar << std::endl;


    for(int ii = 0; ii<tiles.size(); ii++)//reset all values
    {
        toDraw[ii] = false;
    }

    for(int ii = abs(topLeftScalar); ii < bottomRightScalar; ii+=mapSize.x)//increment by row
    {
        for(int bb = ii; bb< ii+maxDisplayDim.x+3; bb++)//increment by number of tile to draw per row
        {

            //std::cout << bb << std::endl;
            toDraw[bb] = true;
        }

    }

}

void TileManager::draw()
{
    for(int ii = 0; ii<tiles.size(); ii++)
    {
        if(toDraw[ii] == true)
        {
            tiles[ii].draw();
        }
    }
}

ofVec2f TileManager::tileArrayCoordsByIndice(int indice)
{
    float row = (indice/mapSize.x);
    row = trunc(row);
    float fcolumn = indice%(int)mapSize.x;
    int icolumn = fcolumn;
    return ofVec2f(icolumn, row);
}

int TileManager::tileIndiceByArrayCoords(ofVec2f coords)
{
    coords = ofVec2f(trunc(coords.x), trunc(coords.y));
    return (coords.y*mapSize.y)+coords.x;
}

ofVec2f TileManager::getTileDim()
{
    return tileSize;
}
Tile* TileManager::getTileByIndice(int indice)
{
    Tile* tmp = &tiles[indice];
    return tmp;
}

Tile* TileManager::getTileByCoords(ofVec2f coords)
{
    return getTileByIndice(tileIndiceByArrayCoords(coords));
}

int TileManager::getTileAmt()
{
    return tiles.size();
}
