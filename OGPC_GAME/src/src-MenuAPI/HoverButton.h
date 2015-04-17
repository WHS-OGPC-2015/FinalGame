//
//  HoverButton.h
//  Game
//
//  Created by WilsonCS on 2/20/15.
//
//


#pragma once
#include "MenuEntity.h"

class HoverButton : public MenuEntity //child of MenuEntity class
{
public:
    HoverButton(ofVec2f loc, ofTexture& norm, ofTexture& hov, ofTexture& fpressed, ofTexture& fclicked, ofTexture& fclickedHovered, ofTexture& fclickedPressed, ofTrueTypeFont& f, std::string t);//initialize button with position and textures and text
    HoverButton(ofVec2f loc, ofTexture& norm, ofTexture& hov, ofTexture& fpressed, ofTexture& fclicked, ofTexture& fclickedHovered, ofTexture& fclickedPressed);//initialize button with position and textures without text

    void addPosition(ofVec2f p);
    void setPosition(ofVec2f);
    ofVec2f getPosition();

    void setButtonTextString(std::string);
    std::string getButtonTextString();


    void update(ofVec2f& mousePos, bool& clicked, bool& pressed);
    void draw();
    void update();
    void update(ofVec2f&, bool&);


    void setClicked(bool b); // set the clicked value manually
    int getEventDataInt();//return 0-3 (0 = nothing, 1 = hovered, 2 = pressed, 3 = clicked, 4 = clicked and hovered, 5 = pressed and hovered) value
    bool getEventDataBool();

private:
    ofTexture* normal; //pointer to default texture
    ofTexture* hovered; // pointer to hovered texture
    ofTexture* pressed; // pointer to pressed texture
    ofTexture* clicked; //pointer to texture used on mouse click
    ofTexture* clickedHovered;// pointer to clicked and hovered texture
    ofTexture* clickedPressed;// pointer to clicked and pressed texture

    ofTrueTypeFont* font; //pointer to font for button text
    std::string text;//text to draw

    ofVec2f position;//position of the buttons center
    ofVec2f textureTLPos;//location of current top left corner of the texture
    ofVec2f textureBRPos;//location of current bottom right corner of the Texture
    bool nowClicked;//true if the button is currently in its clicked state
    bool nowHovered;// true if button is hovered
    bool nowPressed;// true if button is pressed
    bool nowPressedOff; // true if the mouse is pressed and off of the button

    bool clickedComp[2];


};
