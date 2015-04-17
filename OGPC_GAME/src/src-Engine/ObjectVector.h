#pragma once
#include "ofMain.h"
#include "../XML/src/ofxXmlSettings.h"
struct oVectorAbstract
{
public:
    virtual void updateAll(ofVec2f& mousePos, bool& clicked, bool& pressed) = 0;
    virtual void drawAll() = 0;
    virtual void turnlyUpdateAll() = 0;
};



template<class T> class oVector : public oVectorAbstract
{
public:
    oVector()
    {

    }

    void loadObjectData(ofxXmlSettings& file, int numType)//create objects and if necessary tell them to load themselves
    {
        for(int ii = 0; ii < numType; ii++)
        {
            file.pushTag("object", ii);
            vec[ii].loadObjectData(file);
            file.popTag();
        }
    }
    void loadOneObject(ofxXmlSettings& file, int which)
    {
        T tmp;
        vec[which].loadObjectdata(file);
    }

    T* getObject(int index)
    {
        return &vec[index];
    }

    void saveObjectData(ofxXmlSettings& file)
    {
        for(int ii = 0; ii < vec.size(); ii++)
        {
            file.addTag("object");
            file.pushTag("object", ii);
            vec[ii].saveObjectData(file);
            file.popTag();
        }
    }
    void setVector(std::vector<T> s)
    {
        vec = s;
    }
    std::vector<T> getVector()
    {
        return vec;
    }

    void updateAll(ofVec2f& mousePos, bool& clicked, bool& pressed)
    {
        for(int ii = 0; ii < vec.size(); ii++)
        {
            vec[ii].update(mousePos, clicked, pressed);
        }
    }

    void turnlyUpdateAll()
    {
        for(int ii = 0; ii < vec.size(); ii++)
        {
            vec[ii].turnlyUpdate();
        }
    }

    void drawAll()
    {
        for(int ii = 0; ii < vec.size(); ii++)
        {
            vec[ii].draw();
        }
    }

    void addObject(T object)//add an object of type to the array
    {
        vec.push_back(object);
    }
private:
    std::vector<T> vec;
};
