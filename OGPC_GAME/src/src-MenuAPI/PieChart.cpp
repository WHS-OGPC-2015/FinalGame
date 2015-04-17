#include "PieChart.h"
#define pi 3.14159265359

PieChart::PieChart()
{
    arc.setCircleResolution(360);
    arc.arc(pos.x, pos.y, rad, rad, pi/2, pi/2+(rati*2*pi));
    requiresMouseData = false;
}

PieChart::PieChart(double tot, double dep, double radi, ofVec2f posi, ofColor c1, ofColor c2)
{
    requiresMouseData = false;
    depVar = dep;
    total = tot;
    rati = (depVar/total);
    rad = radi;
    pos = posi;
    colors[0] = c1;
    colors[1] = c2;
    arc.setCircleResolution(360);
    arc.arc(pos.x, pos.y, rad, rad, pi/2*(180/pi), (pi/2+(rati*2*pi))*(180/pi));
    std::cout << rati << std::endl;
}


void PieChart::setVariables(double dub, double tot)
{
    depVar = dub;
    total = tot;
    //std::cout << depVar << " " << tot << std::endl;
}

void PieChart::update()
{
    rati = depVar/total;
    arc.clear();
    arc.setFillColor(colors[0]);
    arc.arc(pos.x, pos.y, rad, rad, ofRadToDeg(pi/2), ofRadToDeg(pi/2+(rati*2*pi)));
}

void PieChart::draw()
{
    ofSetColor(colors[1]);
    ofCircle(pos.x, pos.y, rad);
    arc.draw();
    ofSetColor(ofColor::white);



}

void PieChart::setRadius(double radi)
{
    double tempr = radi/rad;
    rad = radi;
}

void PieChart::setPosition(ofVec2f posi)
{
    pos = posi;

}

void PieChart::addPosition(ofVec2f dpos)
{
    pos.x += dpos.x;
    pos.y += dpos.y;
}

void PieChart::setColor(int i, ofColor col)
{
    if (i == 0 or i == 1)
    {
        colors[i] = col;
    }
}

void PieChart::setColor(ofColor cola, ofColor colb)
{
    colors[0] = cola;
    colors[1] = colb;
}



