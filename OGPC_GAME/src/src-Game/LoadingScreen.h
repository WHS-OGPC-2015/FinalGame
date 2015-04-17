#pragma once
#include "ofMain.h"


class rectObject
{
public:
    rectObject(ofVec2f location, int w, int h)
    {
        position = location;
        width = w;
        height = h;
    }

    void draw()
    {
        ofRect(position.x, position.y, width, height);
    }

    int width, height;
    ofVec2f position;

};

class Chain
{
public:
    Chain(int s, ofVec2f start, int w, int ml)
    {
        screenSize = ofVec2f(ofGetWindowWidth(), ofGetWindowHeight());
        width = w;
        speed = s;
        pos = start;
        maxLength = ml;
    }
    void draw()
    {
        ofSetColor(ofColor(176, 136, 31));
        for(int ii = 0; ii < segs.size(); ii++)
        {
            segs[ii].draw();
        }
    }
    bool update()
    {
        if(first)
        {
            randLength = ofRandom(maxLength);
            direction = ofRandom(1, 5);
            if(!segs.empty())
            {
                pos.x += segs[segs.size()-1].width;
                pos.y += segs[segs.size()-1].height;
                if(pos.x >= screenSize.x || pos.x <= 0 || pos.y >= screenSize.y || pos.y <= 0)
                {
                    pos = ofVec2f(ofRandom(screenSize.x), ofRandom(screenSize.y));
                }
            }
            if(direction == 1 || direction == 2)
            {
                rectObject temp(pos, 0, width);
                segs.push_back(temp);
            }
            else if(direction == 3 || direction == 4)
            {
                rectObject temp(pos, width, 0);
                segs.push_back(temp);
            }
            first = false;


        }
        if(abs(segs[segs.size()-1].height) < randLength && abs(segs[segs.size()-1].width) < randLength)
        {
            if(direction == 1)
            {
                segs[segs.size()-1].width += speed;
            }
            else if(direction == 2)
            {
                segs[segs.size()-1].width -= speed;
            }
            else if(direction == 3)
            {
                segs[segs.size()-1].height += speed;
            }
            else if(direction == 4)
            {
                segs[segs.size()-1].height -= speed;
            }

        }
        else
        {
            first = true;
        }

        if(segs.size() > 20)
        {
            segs.erase(segs.begin());
        }


    }
private:

    std::vector<rectObject> segs;
    ofVec2f screenSize;
    int width;
    int direction;         //1 = right 2 = left 3 = down 4= up;
    int randLength;
    int it;     //current iteration
    int maxIt;  //maxinum number of iterations
    bool first;
    int speed;
    ofVec2f pos;
    int maxLength;
};

 class LoadingScreen
 {
 public:
    LoadingScreen(int s, ofVec2f start, int w, int num, int maxLength)
    {
        for(int ii = 0; ii < num; ii++)
        {
            Chain tmp(s, ofVec2f(ofRandom(600), ofRandom(600)), w, maxLength);
            chains.push_back(tmp);
        }
    }

    void update()
    {
        for(int bb = 0; bb < chains.size(); bb++)
        {
            chains[bb].update();
        }

    }

    void draw()
    {
        for(int bb = 0; bb< chains.size(); bb++)
        {
            chains[bb].draw();
        }

    }
 private:
    std::vector<Chain> chains;
};


