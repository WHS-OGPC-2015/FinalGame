#pragma once
#include "MenuEntity.h"

class SimpleButton : public MenuEntity //child of MenuEntity class
{
public:
    SimpleButton(ofVec2f loc, ofTexture& norm, ofTexture& hov, ofTrueTypeFont& f, std::string text);//initialize button with position and textures and text
    SimpleButton(ofVec2f loc, ofTexture& norm, ofTexture& hov);//initialize button with position and textures without text

    //!!!!!!functions not declared in MenuEntity but declared here are mostly totally non-usable!!!!!!
    void setPosition(ofVec2f);
    ofVec2f getPosition();

    void setButtonTextString(std::string);
    std::string getButtonTextString();
    //!!!!!!!!

    void update(ofVec2f& mousePos, bool& clicked, bool& pressed);
    void draw();
    void update();

    bool getEventDataBool();//return nowClicked value
    int getEventDataInt();

private:
    ofTexture* normal; //pointer to default texture
    ofTexture* clicked; //pointer to texture used on mouse click
    ofTrueTypeFont* font; //pointer to font for button text
    std::string text;//text to draw

    ofVec2f position;//position of the buttons center
    ofVec2f textureTLPos;//location of current top left corner of the texture
    ofVec2f textureBRPos;//location of current bottom right corner of the Texture
    bool nowClicked;//true if the button is currently in its clicked state


};
