#include "MenuBackground.h"


MenuBackground::MenuBackground(ofVec2f loc, ofTexture& textu)
{
    position = loc;
    backTexture = &textu;
    fitToWindow = true;
    requiresMouseData = false;
}

MenuBackground::MenuBackground(ofVec2f loc, ofTexture& textu, bool fit)
{
    position = loc;
    backTexture = &textu;
    fitToWindow = fit;
    requiresMouseData = false;
}

void MenuBackground::update()//MenuBackground doesn't update
{

}
void MenuBackground::update(ofVec2f& mousePos, bool& clicked, bool& pressed)//MenuBackground doesn't update
{

}

void MenuBackground::setPosition(ofVec2f loc)
{
    position = loc;
}

void MenuBackground::addPosition(ofVec2f dpos)
{
    position.x += dpos.x;
    position.y += dpos.y;
}
void MenuBackground::draw()
{
    // draws the center at the position
    //std::cout << backTexture->getWidth() << std::endl;
    if(fitToWindow)
    {
       backTexture->draw(0,0,ofGetWindowWidth(), ofGetWindowHeight()) ;
    }
    else
    {
       backTexture->draw(position.x-backTexture->getWidth()/2, position.y-backTexture->getHeight()/2);
    }

}
bool MenuBackground::getEventDataBool()//no use
{

}
int MenuBackground::getEventDataInt()//not going to use this function, Dear Nathan
{

}


