#include "ofApp.h"
#include "XML/src/ofxXmlSettings.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableAlphaBlending();
    viewPos = ofVec2f(0, 0);
    first = true;
    currentState = MAINMENU;
    ofSetFrameRate(60); //set framerate
    ofSeedRandom();
    mapDim = ofVec2f(100, 100);
    tileDim = ofVec2f(32, 32);
    mainSound.loadSound("MenuMusic.mp3");
}

//--------------------------------------------------------------
void ofApp::update(){

    if(currentState == MAINMENU)
    {
        if(first == true)
        {
            first = false;
            startingMenu = new MainMenu;
        }
        if(startingMenu->update(mousePos, clicked, pressed))
        {
            currentState = LOADING;
            first = true;
            delete startingMenu;
        }
    }
    else if(currentState == LOADING)
    {
        if(first == true)
        {
            resources = new ResourceManager;

          //  if(ofRandom(69) < 4.2)
          //  {
         //       resources->loadFilesFromDirectory("C:\\OpenFrameworks\\apps\\FinalGame\\OGPC_GAME\\bin\\data\\tiles\\memes");
           // }
          //  else
          //  {
                resources->loadFilesFromDirectory("C:\\OpenFrameworks\\apps\\FinalGame\\OGPC_GAME\\bin\\data\\tiles");
           // }

            resources->addTexture("City.png", "City");
            resources->addTexture("CityHover.png", "CityHover");
            resources->addTexture("CMBackground.png", "CMBackground");
            resources->addFont("monterey/MontereyFLF-Bold.ttf", "CMFont", 12);
            resources->loadFilesFromDirectory("C:\\OpenFrameworks\\apps\\FinalGame\\OGPC_GAME\\bin\\data\\BandTextures");
            resources->loadFilesFromDirectory("C:\\OpenFrameworks\\apps\\FinalGame\\OGPC_GAME\\bin\\data\\TurnMenuTextures");
            resources->addSound("MainMenu.mp3", "MainMusic", true);

            gameEngine = new Engine;
            mapGenerator = new GameMap;
            loader = new LoadingThread(gameEngine, mapGenerator, resources);
            loader->update(viewPos);
            loading = new LoadingScreen(ofRandom(5, 25), ofVec2f(512, 512), ofRandom(2, 20), ofRandom(1, 50), ofRandom(10, 250));
            //loading = new LoadingScreen(10, ofVec2f(512, 512), 10, 1, 100);
            pause = new PauseMenu();
            loader->start();

            first = false;
        }
        loading->update();
        if(!loader->isThreadRunning())
        {
            currentState = GAME;
        }
    }
    else if(currentState == GAME)
    {
        if(first == true)
        {
            //everything is allready loaded
            ofSoundSetVolume(.25f);
            //mainSound = resources->getSound("MainMusic");
            mainSound.setLoop(true);

            first = false;
        }

        else if(pause->isActive())
        {
            if(pause->update(mousePos, clicked, pressed) == 0)
            {
                currentState = MAINMENU;
            }
            dif = ofVec2f(0, 0);
        }

        else
        {
            loader->update(viewPos);
            if(!mainSound.getIsPlaying())
            {
                mainSound.play();
                mainSound.setVolume(.25f);
            }
            adjustedMousePos = mousePos - viewPos;
            gameEngine->update(adjustedMousePos, clicked, pressed);
            gameEngine->updateNoTranslate(mousePos, clicked, pressed);
            if(dragging)
            {
                dif = mousePos - lastMousePos;
                dif/=2; //scales the drag (2 would be half the distance the mouse was moved"
                viewPos+=dif;

                if(viewPos.x>0 || viewPos.x-ofGetWindowWidth() < (-1*mapDim.x*tileDim.x))
                {
                    viewPos.x-=dif.x;
                    dif.x = 0;
                }
                if(viewPos.y>0 || viewPos.y-ofGetWindowHeight()+150 < (-1*mapDim.y*tileDim.y))
                {
                    viewPos.y-=dif.y;
                    dif.y = 0;
                }
            }
            else
            {
                dif = ofVec2f(0, 0);
            }
        }
    }

    if(pressed != true)
    {
        clicked = false;
    }
    lastMousePos = mousePos;
    dragging = false;

}

//--------------------------------------------------------------
void ofApp::draw(){
    if(first != true)//only update once the object has been initialized
    {
        if(currentState == GAME)
        {
            ofSoundUpdate();
           // std::cout << mainSound.getIsPlaying() << ", " << mainSound.getVolume() << std::endl;
            ofSetColor(255, 255, 255);
            ofPopMatrix();
            ofTranslate(viewPos.x, viewPos.y);
            gameEngine->draw();
            ofPushMatrix();
            ofPopMatrix();
            ofTranslate(-viewPos.x, -viewPos.y);
            gameEngine->drawNoTranslate();
            if(pause->isActive())
            {
                pause->draw();
            }
            ofPushMatrix();

        }
        else if(currentState == MAINMENU)
        {
            startingMenu->draw();
        }
        else if(currentState == LOADING)
        {
            ofBackground(79, 67, 44);
            loading->draw();
            //ofCircle(400, 400, 200);
        }
    }





}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_F1)
    {
        pause->toggleActive();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
  mousePos.x = x;
  mousePos.y = y;
  dragging = false;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    dragging = true;
    mousePos.x = x;
    mousePos.y = y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    dragging = false;
    mousePos.x = x;
    mousePos.y = y;
    pressed = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if(pressed == true)
    {
        pressed = false;
        clicked = true;
    }
    dragging = false;
    mousePos.x = x;
    mousePos.y = y;
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

//void ofApp::exit()
//{
//    delete gameEngine;
//    delete mapGenerator;
//    delete startingMenu;
//    delete loader;
//}
