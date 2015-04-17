#pragma once

#include "ofMain.h"
#include "src-Engine/EngineInclude.h"
#include "src-Game/GameMap.h"
#include "MainMenu.h"
#include "src-Game/LoadingScreen.h"
#include "src-Game/PauseMenu.h"

class LoadingThread : public ofThread
{
public:
    LoadingThread(Engine* e, GameMap* m, ResourceManager* r) : E(e), M(m), R(r) {}

    void threadedFunction()
    {
        ofSeedRandom();
        if(isThreadRunning())
        {
            M->generateMap();
            E->setup("tiles.xml", "game.xml", "objects.xml", viewPos, R);
            Sleep(1000);
            stopThread();
        }
    }

    void start()
    {
        startThread();
    }
    void update(ofVec2f v)
    {
        viewPos = v;
    }
private:
    Engine* E;
    GameMap* M;
    ofVec2f viewPos;
    ResourceManager* R;

};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofVec2f mousePos, lastMousePos, dif, adjustedMousePos;
		ofVec2f viewPos;
		ofVec2f mapDim, tileDim;

        bool pressed;//true if mouse button has been pressed down
        bool clicked;//true if mouse button has been pushed down then released
        bool dragging;//true if mouse button is pressed and is being moved
        int currentState;
        bool first;

        Engine* gameEngine;
        GameMap* mapGenerator;
        MainMenu* startingMenu;
        LoadingThread* loader;
        LoadingScreen* loading;
        ResourceManager* resources;
        PauseMenu* pause;
        ofSoundPlayer mainSound;

        enum GameStates{MAINMENU, LOADING, GAME};




};



