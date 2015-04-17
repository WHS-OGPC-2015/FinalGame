#pragma once
#include "MenuEntity.h"

class MenuBackground : public MenuEntity
{
public:

	MenuBackground(ofVec2f loc, ofTexture& textu);//constrctor
	MenuBackground(ofVec2f loc, ofTexture& textu, bool fit);//constrctor

	void update();
	void update(ofVec2f& mousePos, bool& clicked, bool& pressed);
    void setPosition(ofVec2f loc);
    void addPosition(ofVec2f dpos);
	void draw();

	bool getEventDataBool();
	int getEventDataInt();

private:
	ofTexture *backTexture;
	ofVec2f position;
	bool fitToWindow; //if true, fit the texture to fill the window, otherwise, draw at normal size

};
