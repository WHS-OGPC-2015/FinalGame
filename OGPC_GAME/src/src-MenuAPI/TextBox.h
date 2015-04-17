#pragma once
#include "MenuEntity.h"

class TextBox : public MenuEntity
{
public:
    TextBox(std::string str, ofVec2f posi, ofTrueTypeFont& f);
    TextBox();
    void update();
    void draw();

    void addPosition(ofVec2f dpos);
    void setText(std::string str);
    void setPosition(ofVec2f posi);
    void setFont(ofTrueTypeFont& f);
    int getHeight();
    int getWidth();

    //dont use these but they are virtual
    bool getEventDataBool()
    {

    }
    int getEventDataInt()
    {

    }
    void update(ofVec2f&, bool&, bool&)
    {

    }

private:
    std::string text;
    ofVec2f position;
    ofTrueTypeFont* font;

};
