#pragma once
#include "ofMain.h"
#include "MenuEntity.h"

class Slider : public MenuEntity
{
public:

    Slider(ofVec2f position, ofTexture& bg, ofTexture& slider, double M, double m, double start, ofTrueTypeFont& f, std::string t);

    bool getEventDataBool();//so that the class is not abstract
    int getEventDataInt();//returns slider value

    void setButtonTextString(std::string);
    std::string getButtonTextString();

    void draw();
    void update(ofVec2f&, bool&, bool&);
    void update();//so that the class is not abstract

private:
    int currentValue, maxValue, minValue;
    float cordScale;
    ofTrueTypeFont* font;
    std::string text;
    ofVec2f position;
    ofVec2f textureTLPos;
    ofTexture* background;
    ofTexture* sliderThing;
    ofVec2f bgTLPos, bgBRPos;



};

