#pragma once
#include "ofMain.h"
#include "../src-MenuAPI/MenuInclude.h"
#include "ResourceManager.h"

void createCityMenu(MenuManager* man, ofVec2f pos, ResourceManager*);

void resetCityMenuPositions(Menu& citymenu, ofVec2f deltaPos);
