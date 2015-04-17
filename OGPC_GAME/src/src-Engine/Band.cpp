#include "Band.h"
#include "sstream"


int Band::convertTo1dindex(ofVec2i v)
{
    return (v.y * (fabs(extremeTiles[1].x - extremeTiles[0].x)) + v.x); // converts an ofVec2i to an int based on the amount of tiles in the map
}

int turnToInt(double d) // returns an int -- probably something built in, but I'm lazy
{
    int i = d;
    return i;
}

Band::Band() // empty constructor
{
    incognito = false;
    incarnation = false;
    selected = false;
    begDisNum = 10; // arbitrary
    movement = 3; // arbitrary
    discipleNum = begDisNum;
    incarnationName = "";
    movable = true;
    actionState = 0;
    startup = true;
    HLdraw = false;
    hoveredTile = ofVec2i(-1,-1);

}

//you can change anything that would be have a possibility of being different at the start, including arbitrary things
Band::Band(bool incog, bool incarn, int startnum, int mov, std::string incarnName, std::string TN[], std::string HLTName, int index /*set as "" if incarn is false*/)
{
    incognito = incog;
    incarnation = incarn;
    selected = false;
    movable = true;
    begDisNum = startnum;
    movement = mov;
    discipleNum = begDisNum;
    incarnationName = incarnName;
    actionState = 0;
    startup = true;
    boundTileIndex = index;
    HLdraw = false;
    hoveredTile = ofVec2i(-1,-1);

    for (int i = 0; i < 4; i++)
    {
        TextureNames[i] = TN[i];
    }
    HLTexName = HLTexName;
}


void Band::resetBandType() // updates if you are normal, in incog, the incarnation, or if you are both
{
    if (incognito == true)
    {
        if (incarnation == true)
        {
            bandType = 3;
        }
        else
        {
            bandType = 1;
        }
    }
    else if (incarnation == true)
    {
       bandType = 2;
    }
    else
    {
        bandType = 0;
    }
}

int Band::getBandType()
{
    return bandType;
}


void Band::draw() // draws the current texture at the bound tile
{

        for (int i = 0; i < possibleMovesCoords.size(); i++)
        {
            if (HLdraw == true)
            {
                HLTex->draw(ofVec2f(possibleMovesCoords[i].x * tileWidth, possibleMovesCoords[i].y * tileWidth));
            }

            if (hoveredTile.x == possibleMovesCoords[i].x and hoveredTile.y == possibleMovesCoords[i].y)
            {
                ofSetColor(255,255,255,100);
                ofVec2f temp = ofVec2f(hoveredTile.x, hoveredTile.y);
                ofRect(allTiles->getTileByCoords(temp)->getLocation().x,
                       allTiles->getTileByCoords(temp)->getLocation().y,
                       tileWidth, tileWidth);
                ofSetColor(255,255,255,255);
            }
        }


    if (boundTile->getCityoc() == false)
    {

        BandTextures[bandType]->draw(boundTile->getLocation());

    }
}


//returns 0 if not on the city, 1 if hovering, 2 if pressing, and 3 if clicked (for 1 frame)
int Band::getClickedData(ofVec2f& mousePos, bool& clicked, bool& pressed)
{
    if (mousePos.x < TLpos.x || mousePos.x > BRpos.x ||
        mousePos.y < TLpos.y || mousePos.y > BRpos.y)
    {
        return 0;
        // its ouside
    }
    else
    {
        if (clicked == true)
        {

            return 3;

        }
        else if (pressed == true)
        {

            return 2;
        }
        else
        {

            return 1;
        }
    }
}


//give the band a menu to point to
void Band::setBandMenu(Menu* fillme)
{
    bandMenu = fillme;
    alignButtons();
}

void Band::setTileManager(TileManager* tilm)
{
    allTiles = tilm;
    tileWidth = allTiles->getTileDim().x;
    extremeTiles[0] = ofVec2i(0,0);
    ofVec2f tmp = allTiles->tileArrayCoordsByIndice(allTiles->getTileAmt()-1);
    extremeTiles[1] = ofVec2i(tmp.x, tmp.y);


}
// fills the menu
void Band::fillMenu()
{
    ostringstream convert;

    TextBox* bandName = bandMenu->getPointerToChildByName<TextBox>("IncarnationName");
    bandName->setText(incarnationName);

    discipleNum = 5;
    TextBox* disNum = bandMenu->getPointerToChildByName<TextBox>("DiscipleNumber");
    convert << discipleNum;
    disNum->setText(convert.str());
}

// sets button pointer to menu buttons
void Band::alignButtons()
{
    actionButtons[0] = bandMenu->getPointerToChildByName<HoverButton>("MoveButton");
    actionButtons[1] = bandMenu->getPointerToChildByName<HoverButton>("BreakUpButton");
    actionButtons[2] = bandMenu->getPointerToChildByName<HoverButton>("IncognitoButton");
}

// determine, based on the buttons, which actionState to be in
void Band::findActions()
{
    if (selected == true and movable == true)
    {
        if (actionButtons[0]->getEventDataInt() > 2)
        {
            actionState = 1;

        }
        else if (actionButtons[1]->getEventDataInt() > 2)
        {
            actionState = 2;
        }
        else if (actionButtons[2]->getEventDataInt() == 3 and incognito == false)
        {
            swapIncognito();
           // movable = false;
        }
        else if (actionButtons[2]->getEventDataInt() == 7 and incognito == true)
        {
            swapIncognito();
           // movable = false;
        }
        else
        {
            actionState = 0;
        }

    }
    else
    {
        actionState = 0;
    }
}



/*--------------------------------------------------------------------------------
-------------------UPDATE---------------------------------------------------------------
--------------------------------------------------------------------------------*/

int Band::update(ofVec2f& mousePos, bool& clicked, bool& pressed)
{
 //   bandMenu->setInactive(); // start the update with this

    clickedData = getClickedData(mousePos, clicked, pressed);
    HLdraw = false;
    hoveredTile = ofVec2i(-1,-1);

    findActions();
    if (movable == false or startup == true)
    {
        turnlyUpdate();
        startup = false;
    }

    if (actionState == 0) // normal
    {
       if(clickedData == 1 or clickedData == 2)
        {
            hovered = true;
        }

        else if (clickedData == 3)
        {
            selected = true;
        }

        else if (clickedData == 0 and mousePos.y < 724)
        {
            hovered = false;
            if (clicked == true)
            {
                selected = false;
            }
        }

        if (selected == true)
        {
            //bandMenu->setActive();
            fillMenu();
        }
        return -1;
    }



//-------------------MOVING-----------------------------------------------------
    else if (actionState == 1)
    {
        HLdraw = true;
        hoveredTile = ofVec2i(mousePos.x / tileWidth, mousePos.y / tileWidth);

        if (clicked == true)
        {
//            // finds the 2d coord of your mose click, based on the tiles
            ofVec2i temptile = ofVec2i(turnToInt(mousePos.x / tileWidth), turnToInt(mousePos.y / tileWidth));
            for (int i = 0; i < possibleMovesCoords.size(); i++)
            {
                if (temptile.x == possibleMovesCoords[i].x and temptile.y == possibleMovesCoords[i].y)// check every possible move if there is a match
                {
                    boundTile->setBandoc(0);
                    ofVec2f tm = ofVec2f(temptile.x, temptile.y);
                    boundTile = allTiles->getTileByCoords(tm);
                    boundTile->setBandoc(discipleNum);


                    boundTileCoords = temptile;
                    boundTileIndex = allTiles->tileIndiceByArrayCoords(tm);
                    actionState  = 1;
                    actionButtons[0]->setClicked(false);
                    movable = false;
                }
            }

        }
        return -2;
    }



//------------------DISPATCHING----------------------------------------------------------
    else if (actionState == 2)
    {
       if (clicked == true)
        {
            ofVec2i temptila = ofVec2i(turnToInt(mousePos.x / tileWidth), turnToInt(mousePos.y / tileWidth));

            ofVec2i possibleTiles[4];

            possibleTiles[0] = ofVec2i(boundTile->getLocation().x / tileWidth - 1, boundTile->getLocation().y / tileWidth);
            possibleTiles[1] = ofVec2i(boundTile->getLocation().x / tileWidth + 1, boundTile->getLocation().y / tileWidth);
            possibleTiles[2] = ofVec2i(boundTile->getLocation().x / tileWidth, boundTile->getLocation().y / tileWidth + 1);
            possibleTiles[3] = ofVec2i(boundTile->getLocation().x / tileWidth, boundTile->getLocation().y / tileWidth - 1);

            for (int i = 0; i < 4; i++)
            {
                if (temptila.x ==  possibleTiles[i].x and temptila.y ==  possibleTiles[i].y)
                {
                    int q = convertTo1dindex(temptila);
                    return q;
                    movable = false;
                }
            }


        }
        return -3;
    }
}



/*--------------------------------------------------------------------------------
-------------------TURNLY__UPDATE---------------------------------------------------------------
--------------------------------------------------------------------------------*/


void Band::turnlyUpdate()
{

    //reset the TL and BR positions for collisions
    TLpos = ofVec2f(boundTile->getLocation().x, boundTile->getLocation().y);
    BRpos = ofVec2f(boundTile->getLocation().x + BandTextures[bandType]->getWidth(), boundTile->getLocation().y + BandTextures[bandType]->getHeight());

    // reset every turn
    actionState = 0;
    movable = true;
    possibleMovesCoords.clear();
    possibleMovesIndex.clear();

    ofVec2i temp;
    for (int i = -movement; i <= movement; i++)
    {
        for (int j = (fabs(i) - movement); j <= (movement - fabs(i)); j++)
        {
            temp = ofVec2i(boundTileCoords.x - i, boundTileCoords.y - j);

            if (temp.x < extremeTiles[0].x
                or temp.x > extremeTiles[1].x
                or temp.y < extremeTiles[0].y
                or temp.y > extremeTiles[1].y)
            {
            }
            else
            {
                possibleMovesCoords.push_back(temp);
                possibleMovesIndex.push_back(convertTo1dindex(temp));
            }
        }
    }
}


void Band::saveObjectData(ofxXmlSettings& file)
{
    file.addValue("incognito", incognito);
    file.addValue("selected", selected);
    file.addValue("incarnation", incarnation);
    file.addValue("name", incarnationName);
    file.addValue("movable", movable);
    file.addValue("actionState", actionState);
    file.addValue("bandType", bandType);
    file.addValue("boundTileCoordsx", boundTileCoords.x);
    file.addValue("boundTileCoordsy", boundTileCoords.y);
    file.addValue("boundTileIndex", boundTileIndex);
    file.addValue("discipleNumber", discipleNum);

    file.addValue("TextureName0", TextureNames[0]);
    file.addValue("TextureName1", TextureNames[1]);
    file.addValue("TextureName2", TextureNames[2]);
    file.addValue("TextureName3", TextureNames[3]);
    file.addValue("HLTexName", HLTexName);

    file.addValue("extremeTile0x", extremeTiles[0].x);
    file.addValue("extremeTile0y", extremeTiles[0].y);
    file.addValue("extremeTile1x", extremeTiles[1].x);
    file.addValue("extremeTile1y", extremeTiles[1].y);
    file.addValue("HLdraw", HLdraw);

}

void Band::loadObjectData(ofxXmlSettings& file)
{
    incognito = file.getValue("incognito", 0);
    selected = file.getValue("selected", 0);
    incarnation = file.getValue("incarnation", 0);
    incarnationName = file.getValue("name", "");
    movable =  file.getValue("movable", 0);
    actionState =  file.getValue("actionState", 0);
    bandType =  file.getValue("bandType", 0);
    boundTileCoords.x =  file.getValue("boundTileCoordsx", 0);
    boundTileCoords.y =  file.getValue("boundTileCoordsy", 0);
    boundTileIndex =  file.getValue("boundTileIndex", 0);
    discipleNum =  file.getValue("discipleNum", 0);

    TextureNames[0] = file.getValue("TextureName0", "");
    TextureNames[1] = file.getValue("TextureName1", "");
    TextureNames[2] = file.getValue("TextureName2", "");
    TextureNames[3] = file.getValue("TextureName3", "");
    HLTexName = file.getValue("HLTexName", "");

    extremeTiles[0].x = file.getValue("extremeTile0x", 0);
    extremeTiles[0].y = file.getValue("extremeTile0y", 0);
    extremeTiles[1].x = file.getValue("extremeTile1x", 0);
    extremeTiles[1].y = file.getValue("extremeTile1y", 0);
    HLdraw = file.getValue("HLdraw", 0);


}



//the rest are boring
void Band::setIncarnation(bool b, std::string incarnName)
{
    incarnation = b;
    incarnationName = incarnName;
    resetBandType();
}

bool Band::getIncarnation()
{
    return incarnation;
}



void Band::setDiscipleNum(int i)
{
    discipleNum = i;
}

void Band::changeDiscipleNum(int i)
{
    discipleNum += i;
}

int Band::getDiscipleNum()
{
    return discipleNum;
}


void Band::swapIncognito()
{
    incognito = !incognito;
    resetBandType();
}

bool Band::getIncognito()
{
    return incognito;
}



void Band::setExtremeTiles(ofVec2i v1, ofVec2i v2)
{
    extremeTiles[0] = v1;
    extremeTiles[1] = v2;
    int temp = fabs(extremeTiles[1].x - extremeTiles[0].x);
    boundTileCoords = ofVec2i(boundTileIndex % temp, boundTileIndex / temp);

}

//set ALL of the textures
void Band::setTextures(ResourceManager* res)
{
    for (int i = 0; i < 4; i++)
    {
        BandTextures[i] = &res->getTextureReference(TextureNames[i]);
        HLTex = &res->getTextureReference(HLTexName);
    }
    TLpos = ofVec2f(boundTile->getLocation().x, boundTile->getLocation().y);
    BRpos = ofVec2f(boundTile->getLocation().x + BandTextures[bandType]->getWidth(), boundTile->getLocation().y + BandTextures[bandType]->getHeight());
}
void Band::setTile(int t)
{
    boundTile = allTiles->getTileByIndice(t);
    boundTile->setBandoc(discipleNum);
    boundTileIndex = t;

    ofVec2f tmp = allTiles->tileArrayCoordsByIndice(t);
    boundTileCoords = ofVec2i(tmp.x, tmp.y);
}

int Band::getIndex()
{
    return boundTileIndex;
}

ofVec2i Band::getCoords()
{
    return boundTileCoords;
}

void Band::switchSelect()
{
    selected = !selected;
}

bool Band::getSelect()
{
    return selected;
}

void Band::setTileWidth(double d)
{
    tileWidth = d;
}

vector<std::string> Band::getTextureNames()
{
    vector<std::string> names;
    for (int i = 0; i < 4; i++)
    {
        names.push_back(TextureNames[i]);
    }

    return names;
}
