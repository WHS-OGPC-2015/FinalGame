#include "SimpleButton.h"

 SimpleButton::SimpleButton(ofVec2f loc, ofTexture& norm, ofTexture& click, ofTrueTypeFont& f, std::string t)
{

    position = loc;
    normal = &norm;
    clicked = &click;
    font = &f;
    requiresMouseData = true;//this class will need data about the mouse to function
    nowClicked = false;
    text = t;

}

 SimpleButton::SimpleButton(ofVec2f loc, ofTexture& norm, ofTexture& click)
{

    position = loc;
    normal = &norm;
    clicked = &click;
    font = NULL;//set font pointer to NULL if there is no text
    requiresMouseData = true;//this class will need data about the mouse to function
    nowClicked = false;
    text = "";

}

void SimpleButton::setButtonTextString(std::string newString)
{
    text = newString;
}

std::string SimpleButton::getButtonTextString()
{
    return text;
}

void SimpleButton::update(ofVec2f& mousePos, bool& clicked, bool& pressed)
{

    //test to see if the mouse is clicked
    if(clicked)
    {
        //nowClicked = !nowClicked; //toggle clicked status

            //if it is...test to see if a point is not inside the button
        if(mousePos.x < textureTLPos.x ||
           mousePos.y < textureTLPos.y ||
           mousePos.x > textureBRPos.x ||
           mousePos.y > textureBRPos.y   )
        {
        }
        else//if the points not outside its inside
        {
            nowClicked = !nowClicked; //toggle clicked status
        }
    }

}

void SimpleButton::draw()
{

    //the BR/TL positions are for keeping track of the coordinates for purposes
    //of the mouse collision logic in update()
    if(nowClicked == true)//if the button has been clicked draw that texture
    {
        //reset BR and TL corner positions for collision
        textureTLPos = ofVec2f((position.x-(clicked->getWidth()/2)), (position.y-(clicked->getHeight()/2)));
        textureBRPos = ofVec2f((textureTLPos.x+(clicked->getWidth())), (textureTLPos.y+(clicked->getHeight())));
        clicked->draw(textureTLPos);

    }
    else//otherwise draw the non-clicked texture
    {
        //reset BR and TL corner positions for collision
        textureTLPos = ofVec2f((position.x-(normal->getWidth()/2)), (position.y-(normal->getHeight()/2)));
        textureBRPos = ofVec2f((textureTLPos.x+(normal->getWidth())), (textureTLPos.y+(normal->getHeight())));
        normal->draw(textureTLPos);
    }
    if(font != NULL)
    {
        //center the text
        font->drawString(text, textureTLPos.x+((normal->getWidth()-(font->stringWidth(text)))/2), textureTLPos.y+((normal->getHeight()-(font->stringHeight(text)))/2));
    }

}

void SimpleButton::update()
{
    //this is just here so the compiler doesn't complain when calling update(void) in menu
}

bool SimpleButton::getEventDataBool()
{
    if(nowClicked == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int SimpleButton::getEventDataInt()
{
    //here for abstract parent
}
