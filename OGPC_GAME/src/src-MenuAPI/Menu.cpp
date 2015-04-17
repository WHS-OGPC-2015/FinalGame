#include "Menu.h"


Menu::Menu(ofVec2f loc)
{
    location = loc;
    active = true;//menu starts as active by default
}

void Menu::setLocation(ofVec2f loc)
{
    location = loc;
}

ofVec2f Menu::getLocation()
{
    return location;
}

void Menu::addEntity(MenuEntity& ent, std::string name)
{

    entities.push_back(&ent);
    entityNames[name]= entities.size()-1;
}


void Menu::update(ofVec2f& mousePos, bool& clicked, bool& pressed)
{
    for(int aa = 0; aa<entities.size(); aa++)//updates all of the menus entities
    {
        if(entities[aa]->requiresMouseData)//if the entity needs mouseinput call that update fxn
        {
            entities[aa]->update(mousePos, clicked, pressed);
        }
        else//otherwise call the other update
        {
            entities[aa]->update();
        }

    }
}
//should add vbo support here or in MenuManager on a permenu basis
void Menu::draw()
{
    for(int aa = 0; aa<entities.size(); aa++)
    {
        entities[aa]->draw();
    }
}

void Menu::setActive()
{
    active = true;
}

bool Menu::isActive()
{
    return active;
}

void Menu::setInactive()
{
    active = false;
}

MenuEntity* Menu::getEntityPointer(int indice)
{

    return entities[indice];
}

MenuEntity* Menu::getEntityPointer(std::string name)
{
    return entities[entityNames[name]];
}

//template<class C>


