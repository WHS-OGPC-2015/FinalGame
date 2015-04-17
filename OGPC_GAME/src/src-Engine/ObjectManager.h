#pragma once
#include "ofMain.h"
#include "../XML/src/ofxXmlSettings.h"
#include "ObjectVector.h"
#include "TileManager.h"
#include "ResourceManager.h"
#include "City.h"
#include "CityMenu.h"
#include "Band.h"
#include "BandMenu.h"
#include "UtilMenus.h"
class ObjectManager
{

public:
    ObjectManager(std::string, ofVec2f, TileManager*, ResourceManager*);
    ~ObjectManager();


    template<class T>
    bool addObjectType(std::string name, int startNum)    //add a new type of object to the array
    {
        if(objectArrayNames.find(name) == objectArrayNames.end())
        {
            oVectorAbstract* tmp = new oVector<T>;
            objects.push_back(tmp);
            objectArrayNames[name] = objects.size()-1;
            T tmpObject;
            for(int ii = 0; ii < startNum; ii++)
            {
                addObjectToType<T>(tmpObject, name);
            }
            return true;
        }
        return false;
    }

    template<class C>//C is child class
    oVector<C>* getPointerToChildByName(std::string name)
    {
        oVector<C>* tmpChild = (oVector<C>*) (objects[objectArrayNames[name]]);    //cast parent as child
        return tmpChild;
    }

    template<class C>//C is child class
    oVector<C>* getPointerToChildByIndice(int i)
    {
        oVector<C>* tmpChild = (oVector<C>*) (objects[i]);    //cast parent as child
        return tmpChild;
    }

    template<class oT>
    void addObjectToType(oT object, std::string type)    //add an object of specific type to its array
    {
        oVector<oT>* S = getPointerToChildByName<oT>(type);
        S->addObject(object);
    }
    //auto getObjectTypePointer(std::string type) -> decltype(objects[objectArrayNames[type]]);           //get pointer to an oVector



    void saveToFile(std::string);
    void loadFromFile(std::string filePath);    //load all objects from file
    void updateAll(ofVec2f& mousePos, bool& clicked, bool& pressed);                           //update all objects
    void drawAll();
    void updateNoTranslate(ofVec2f& mousePos, bool& clicked, bool& pressed);                             //draw all objects
    void drawNoTranslate();
    void mainThreadFunction();
private:
    std::vector<oVectorAbstract*> objects;   //array of objects which will hold their own objects
    std::map<std::string, int> objectArrayNames;

    TileManager* tiles;         //local reference to tile manager
    ResourceManager* recMan;    //local reference to resources
    MenuManager* objectMenus;   //manager for popups and stuff

    std::string fileString;

    bool turn;

};
