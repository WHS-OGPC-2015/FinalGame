#include "Slider.h"

Slider::Slider(ofVec2f p, ofTexture& bg, ofTexture& slider, double M, double m, double start, ofTrueTypeFont& f, std::string t)
{
    font = &f;
    text = t;
    background = &bg;
    sliderThing = &slider;
    currentValue = start;
    maxValue = M;
    minValue = m;
    position = p;
    cordScale = background->getWidth()/(maxValue-minValue);
    //std::cout << cordScale;
}

bool Slider::getEventDataBool(){}//here so its not abstract

int Slider::getEventDataInt()
{
    return currentValue;
}
void Slider::setButtonTextString(std::string newString)
{
    text = newString;
}
std::string Slider::getButtonTextString()
{
    return text;
}
void Slider::update(){}//also just here to prevent error

void Slider::update(ofVec2f& mousePos, bool& clicked, bool& pressed)
{
    if(pressed == true)
    {
       // std::cout << "here1" << std::endl;
        //nowClicked = !nowClicked; //toggle clicked status

            //if it is...test to see if a point is not inside the button
        if(mousePos.x < bgTLPos.x ||
           mousePos.y < bgTLPos.y ||
           mousePos.x > bgBRPos.x ||
           mousePos.y > bgBRPos.y   )
        {

        }
        else
        {
            //std::cout<<cordScale<<endl<<minValue<<endl;
            //std::cout << bgTLPos.x <<endl<< bgBRPos.x<<endl;
            std::cout <<mousePos.x - bgTLPos.x<<endl;
            std::cout << currentValue << std::endl;
            currentValue = (mousePos.x - bgTLPos.x)/cordScale + minValue;
        }
    }
    if(currentValue > maxValue)
    {
        currentValue = maxValue;
    }
    else if(currentValue < minValue)
    {
        currentValue = minValue;
    }
}

void Slider::draw()
{
        //reset BR and TL corner positions for collision
        ofSetColor(currentValue * 2 + 100, currentValue * 2 + 100, currentValue * 2 + 100); // simple brightness changer
        bgTLPos = ofVec2f((position.x-(background->getWidth()/2)), (position.y-(background->getHeight()/2)));
        bgBRPos = ofVec2f((bgTLPos.x+(background->getWidth())), (bgTLPos.y+(background->getHeight())));
        background->draw(bgTLPos);

        font->drawString(text, position.x - font->stringWidth(text)/2, position.y - sliderThing->getHeight()/2 - font->stringHeight(text)/2 - 10); //sets position of text
        sliderThing->draw(ofVec2f(bgTLPos.x+((currentValue-minValue)*cordScale)-sliderThing->getWidth()/2, (bgTLPos.y+((background->getHeight()/2)-(sliderThing->getHeight()/2))))); //needs to be centered

//        ofCircle(bgTLPos, 10);
//        ofCircle(bgBRPos, 10);


}
