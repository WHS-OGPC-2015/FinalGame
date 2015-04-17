#pragma once
#include "ofMain.h"
#include "MenuEntity.h"
class Menu
{
public:
    Menu(ofVec2f loc);
    void setLocation(ofVec2f loc);//set center location of menu
    ofVec2f getLocation();

    void addEntity(MenuEntity&, std::string name);//add Entity by reference with name
    MenuEntity* getEntityPointer(int);//get pointer to MenuEntity by its indice
    MenuEntity* getEntityPointer(std::string);//get pointer to MenuEntity by its name

    template<class C>//C is child class
    C* getPointerToChildByName(std::string name)
    {
        C* tmpChild = (C *) &*(entities[entityNames[name]]);
        return tmpChild;
    }



    void update(ofVec2f& mousePos, bool& clicked, bool& pressed);
    void draw();

    void setActive();//set menu to be drawn
    void setInactive();//set menu to not be drawn
    bool isActive();//returns value of active



private:
    ofVec2f location;//center location
    std::vector <MenuEntity*> entities;//array of menu objects to be displayed
    std::map <std::string, int> entityNames;//names mapped to entities in map
    bool active;//menu is active by default

};
