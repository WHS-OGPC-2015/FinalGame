#pragma once
#include "ofMain.h"
#include <windows.h>
#include <stdio.h>

class ResourceManager
{
public:
    ResourceManager();
    void loadFilesFromDirectory(std::string);


    void addTexture(std::string, std::string);
    ofTexture& getTextureReference(std::string);
    ofTexture getTexture(std::string);

    void addFont(std::string, std::string, int);
    ofTrueTypeFont& getFontReference(std::string);
    ofTrueTypeFont getFont(std::string);

    void addSound(std::string, std::string, bool stream=false);        //add sound to vector
    ofSoundPlayer& getSoundReference(std::string);  //returns REFERECE to sound
    ofSoundPlayer getSound(std::string);            //returns COPY of sound
   std::vector<ofTexture> textures;
private:
             //holds real copy of textures
    std::map<std::string, int> textureNames;    //holds names mapped to textures

    std::vector<ofTrueTypeFont> fonts;          //same but with fonts
    std::map<std::string, int> fontNames;

    std::vector<ofSoundPlayer> sounds;
    std::map<std::string, int> soundNames;


};
