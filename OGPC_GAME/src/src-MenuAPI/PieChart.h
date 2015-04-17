#pragma once
#include "MenuEntity.h"

class PieChart : public MenuEntity
{
public:
    PieChart();
    PieChart(double tot, double dep, double radi, ofVec2f posi, ofColor c1, ofColor c2);

    void setVariables(double dub, double tot);
    void update();
    void draw();
    void setRadius(double radi);
    void setPosition(ofVec2f posi);
    void addPosition(ofVec2f dpos);
    void setColor(int i, ofColor col);
    void setColor(ofColor cola, ofColor colb);

    void update(ofVec2f&, bool&, bool&)
    {

    }
    bool getEventDataBool()
    {

    }
    int getEventDataInt()
    {

    }

private:

    double total;
    double depVar;
    double rati;
    ofColor colors[2];
    double rad;
    int resolution;
    ofVec2f pos;
    int endingindeces[2];
    vector<ofVec2f> vertecies;
    ofPath arc;

};
