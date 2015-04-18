#include "GameMap.h"
#include <sstream>
#include "../XML/src/ofxXmlSettings.h"
#include "simplexnoise.h"



int GameMap::xwfunc(int x)
{
    return fabs(fabs(x-(mapSize.x-1))-(mapSize.x-1));
}
int GameMap::ywfunc(int x)
{
    return fabs(fabs(x-(mapSize.y-1))-(mapSize.y-1));
}
double maximize(double a, double b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int roundforint(double i)
{
    if (i < 0)
    {
        return (i - .5);
    }
    else if (i > 0)
    {
        return (i + .5);
    }
    else
    {
        return 0;
    }

}



GameMap::GameMap()
{
    numCities = 20;
}

void GameMap::generateMap()
{
    mapTextureNames("C:\\OpenFrameworks\\apps\\FinalGame\\OGPC_GAME\\bin\\data\\tiles");
    genMapTwo();
    objectFile.addValue("numObjectTypes", 2);
    genCities();
    genBand();

}

std::vector<int> GameMap::genMap(int sizeX, int sizeY, int seeds)
{

    mapSize = ofVec2i(sizeX, sizeY);
    int highalt = 9;
    GenTile mapArray[mapSize.x][mapSize.y];

    for (int i = 0; i < mapSize.x; i ++)
    {
        for (int j = 0; j < mapSize.y; j ++)
        {
             mapArray[i][j].aset = false;
             mapArray[i][j].altitude = -5;

        }
    }


//    seednum = maximize(sqrt((mapSize.x + mapSize.y)/2) + ofRandom(0,3) - 1, 1);
    seednum = seeds;
    ofVec2i seed;

    ofVec2i focus(seed.x, seed.y);


    bool done = false;
    int percentmountain = 80;
    ofVec2i rangeSpread(6, 10);
    ofVec2i lastSeed;

    int highnum;
    bool donecheck;
    ofVec2i pluspattern;
    ofVec2i petal;
    int rando;
    //std::vector<ofVec2i> seedVec;
    for (int i = 0; i < seednum; i++)
    {
        rando = ofRandom (0, 99); //  random int to determine if mountain should continue a range
        if (rando > percentmountain or i == 0) // if its the first time, it cant be near a mountain
        {
            seed = ofVec2i(ofRandom(0, mapSize.x), ofRandom(0, mapSize.y));
            //seedVec.push_back(seed);
            lastSeed = seed;
            mapArray[seed.x][seed.y].setAltitude(highalt);
        }
        else
        {


            ofVec2i spread = ofVec2i(ofRandom(rangeSpread.x, rangeSpread.y), ofRandom(rangeSpread.x, rangeSpread.y));
            ofVec2i anchor = lastSeed;
            anchor = ofVec2i(anchor.x+spread.x, anchor.y+spread.y);

            if(anchor.x > mapSize.x || anchor.y < mapSize.y)    //if the point is off the map make a new random one inside the map
            {
                anchor = seed = ofVec2i(ofRandom(0, mapSize.x), ofRandom(0, mapSize.y));
            }

            mapArray[anchor.x][anchor.y].setAltitude(highalt);
            lastSeed = anchor;

        }

    }




    while (done == false) // if all the tiles aren't filled, continue
    {

        donecheck = true; // reset donecheck
        highnum = -1;  // highjnum starts below zero to find the next highest altitude
        for (int i = 0; i < mapSize.x; i++) // check the entire map
        {
            for (int j = 0; j < mapSize.y; j++)
            {

                if (mapArray[i][j].aset == true and mapArray[i][j].altitude > highnum) // if the tile is set and the altitude is greater than the highest altitude so far...
                {

                    if (        mapArray[xwfunc(i-1)][ywfunc(j)].aset == false // if not all of the surrounding tiles are set...
                                or mapArray[xwfunc(i+1)][ywfunc(j)].aset == false
                                or mapArray[xwfunc(i)][ywfunc(j-1)].aset == false
                                or mapArray[xwfunc(i)][ywfunc(j+1)].aset == false
                        )
                    {


                        highnum = mapArray[i][j].altitude; // the altitude becomes the highest altitude
                        focus = ofVec2i(i,j); // swap the focus to this tile
                    }
                }
                else if (mapArray[i][j].aset == false) // if a tile is unset...
                {

                    donecheck = false; // we will go through the while loop again
                }
            }
        }

        rando = ofRandom(0,99); // for probability...
        for (int i = 0; i < 4; i ++) // go through the flower pattern
        {
            pluspattern.x = roundforint(cos(i * 3.14159265 / 2)); // trig to find next "petal"
            pluspattern.y = roundforint(sin(i * 3.14159265 / 2));
            petal = ofVec2i(xwfunc(focus.x + pluspattern.x), ywfunc(focus.y + pluspattern.y)); // set the petal position


            if (mapArray[petal.x][petal.y].aset == false) // if the petal is unset
            {
                if (rando >= 0 and rando < 40) // 40 %
                {
                    mapArray[petal.x][petal.y].setAltitude(mapArray[focus.x][focus.y].altitude - 1); // the petal is one less than the stem
                }
                else if (rando >= 40 and rando < 60) // 20 %
                {
                    mapArray[petal.x][petal.y].setAltitude(mapArray[focus.x][focus.y].altitude - 2); // the petal is two less than the stem
                }
                else if (rando >= 60 and rando < 100) // 40 %
                {
                    mapArray[petal.x][petal.y].setAltitude(mapArray[focus.x][focus.y].altitude); // the petal is the same as the stem
                }
            }

        }
        if (donecheck == true) // if the donecheck has stayed true (i.e., all of the tiles are set...
        {

            done = true; // this exits the while loop
        }


    }
    std::vector<int> mapHeights;
    for (int i = 0; i < mapSize.x; i++)
    {
        for (int j = 0; j < mapSize.y; j++)
        {

            mapTiles.push_back(mapArray[i][j]);                     //push tile into 1d array
            mapHeights.push_back(mapArray[i][j].altitude);

        }

    }
    return mapHeights;
    //saveMap(mapSize, mapHeights);



}

void GameMap::genMapTwo()
{
  /*this*/  mapSize = ofVec2i(50, 50);        //size of the map in tiles
 /*this*/   int numSeeds = 10;                  //number of mountains to generate in genMap()
    int last = 1;                       //last height used(for noise z seed)
    float noiseWeight = 1;              //value to multiply noise vector by before averaging
    float seedWeight = 1;               //value to multiply seed vector by before averaging
    int waterThresh = 2;                //first level that is not a water tile
    int minLakeSize = 60;               //minimum amount of connected water tiles
    int mountainHeightMultiplier = 2;   //value to increase height of mountains
    int heightNorm = 9;                 //normalization factor for height


    std::vector <int> noiseAlts;        //holds perlin random altitudes
    for(int yy = 0; yy < mapSize.y; yy++)
    {
        for(int xx = 0; xx < mapSize.x; xx++)
        {
            float noise = scaled_octave_noise_3d(4, .5, .05, 0, 9, xx, yy, last); //get perlin for square

            noise = trunc(noise);               //truncate decimals
            last = noise;                       //set z coord for next loop
            noiseAlts.push_back((int)noise);    //add height to array

        }

    }

    float avg = 0;
    std::vector<int> seedAlts = genMap(mapSize.x, mapSize.y, numSeeds);     //make a new vector with mountain point from genMap()
    for(int ii = 0; ii < seedAlts.size(); ii++)
    {
        seedAlts[ii] *= mountainHeightMultiplier;//*(heightNorm/(textureStrings.size()-1));                                //simple averaging based on weights
        avg = seedAlts[ii]*seedWeight;
        avg += noiseAlts[ii]*noiseWeight;
        avg/=noiseWeight+seedWeight;
        avg = trunc(avg);
        if(avg > textureStrings.size()-1)                                     //make sure the height is not bigger than the number of textures
        {
            avg = textureStrings.size()-1;                                    //if it is, set the height to the highest texture

        }
        altitudes.push_back(avg);
    }

    for(int ii = 1; ii < altitudes.size(); ii++)                //check all of the tiles
    {
        if(altitudes[ii] < waterThresh)             //if its a water tile
        {
            drought(false, waterThresh, minLakeSize, ii, 31); //check to make sure there are at least >>minLakeSize<< tiles around it
        }
    }
    saveMap(ofVec2i(mapSize.x, mapSize.y), altitudes);


}

void GameMap::drought(bool diag, int& threshold, int& minSize, int start, int desired)
{
    fillAlts = altitudes;   //reset spare altitude vector
    numWater = 0;           //reset the number of water tiles
    if(!diag)               //call the 4 way fill
    {
        floodFill(threshold, desired, start);   //fill all water tiles in that section with other values
    }


    if(numWater < minSize)          //if the water needs to be replaced
    {
        for(int ii = 0; ii < fillAlts.size(); ii++)
        {
            if(fillAlts[ii] == desired)
            {
                altitudes[ii] = threshold;      //set the tile to not be water
            }
        }
    }

}

void GameMap::floodFill(int threshold, int desired, int indice)
{
    if(fillAlts[indice] < threshold)        //basic flood fill algorithm with counter implemented look it up
    {
        fillAlts[indice] = desired;
        numWater++;
        floodFill(threshold, desired, indice+1);
        floodFill(threshold, desired, indice-1);
        floodFill(threshold, desired, indice+mapSize.x);
        floodFill(threshold, desired, indice-mapSize.x);
    }
    //        std::vector<int> q;
//    q.push_back(indice);
//    int siz = 0;
//    bool emp = false;
//    while(emp == false)        //basic flood fill algorithm with counter implemented look it up
//    {
//        int currentIndice = q[q.size()-1];
//        q.pop_back();
//        fillAlts[currentIndice] = desired;
//        numWater++;
//        if(altitudes[indice+1] < threshold)
//        {
//            fillAlts[indice+1] = desired;
//            q.push_back(indice+1);
//        }
//        if(altitudes[indice-1] < threshold)
//        {
//            fillAlts[indice-1] = desired;
//            q.push_back(indice-1);
//        }
//        if(altitudes[indice+mapSize.x] < threshold)
//        {
//            fillAlts[indice+mapSize.x] = desired;
//            q.push_back(indice+mapSize.x);
//        }
//        if(altitudes[indice-mapSize.x] < threshold)
//        {
//            fillAlts[indice-mapSize.x] = desired;
//            q.push_back(indice-mapSize.x);
//        }
//        emp = q.empty();
//        siz = q.size();
//
//    }

}
void GameMap::saveMap(ofVec2i mapSize, std::vector<int> heights)
{

    ofxXmlSettings tileSave;
    tileSave.addValue("mapSizeX", mapSize.x);
    tileSave.addValue("mapSizeY", mapSize.y);
    tileSave.addValue("tileSizeX", 32);
    tileSave.addValue("tileSizeY", 32);
    tileSave.addTag("tileArray");
    tileSave.pushTag("tileArray");

    int numSame = 1;
    int currentH = 0;
    int nextH = 0;
    int pushedTagCount = 0;

    for(int bb = 0; bb < heights.size(); bb++)//cycle through all of the tags
    {
        currentH = heights[bb];
        nextH = heights[bb+1];
        if(currentH == nextH)
        {
            numSame++;
        }
        else
        {
            tileSave.addTag("tile");
            tileSave.pushTag("tile", pushedTagCount);
            pushedTagCount++;

            tileSave.addValue("texture", textureStrings[currentH]);
            tileSave.addValue("numSame", numSame);

            tileSave.popTag();

            numSame = 1;

        }

    }

    tileSave.popTag();

    tileSave.addValue("pushedTileCount", pushedTagCount);

    tileSave.saveFile("tiles.xml");
}

void GameMap::mapTextureNames(std::string folder)
{
    std::vector<std::string> names;

    std::string specPath = folder + "\\*.*";
    folder += "\\";

    WIN32_FIND_DATA fd;                                     //declare variable to hold file data
    HANDLE hFind = FindFirstFile(specPath.c_str(), &fd);    //find first file and store data
    if(hFind != INVALID_HANDLE_VALUE) {                     //if that data is not corrupt
        do {
            // read all (real) files in current folder
            // , delete '!' read other 2 default folder . and ..
            if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
                names.push_back(fd.cFileName);
            }
        }while(FindNextFile(hFind, &fd));                   //find the next file

        FindClose(hFind);

    }
    //at this point "names" vector has all file names in directory

    for(int indice = 0; indice < names.size(); indice++)
    {
        int dotLoc = names[indice].size(); //location of '.' in string
        std::string extension = "";  //parsed file extension
        std::string notExtension = ""; //just the name
        std::string prefix = "";
        prefix[0] = names[indice][0];
        int prefixInt;
        stringstream ss;
        ss << prefix;
        ss >> prefixInt;
        for(int ii = 0; ii<names[indice].size(); ii++)
        {
            if(names[indice][ii] == '.')    //if the character is a period
            {
                dotLoc = ii;                //store that indice
            }
            else if(ii > dotLoc)            //if the indice is after the period
            {
                extension+= names[indice][ii];   //store the character
            }
            else if(ii < dotLoc)
            {
                notExtension+= names[indice][ii];
            }
        }

        std::string fullPath  = folder+names[indice];
        if(extension == "jpg" ||       //Checking for all texture file extensions
            extension == "jpeg" ||
            extension == "png" ||
            extension == "bmp")
        {

            textureStrings.push_back(notExtension);  //if so load texture from that path
            //std::cout << textureMap[prefixInt] << " SWAG1" << std::endl;

        }


    }
}

void GameMap::genCities()
{
        std::string type = "City";
        objectFile.addTag("type");
        objectFile.pushTag("type", 0);
        objectFile.addValue("name", "City");
        objectFile.addValue("numOf", numCities);
        for(int ii = 0; ii < numCities; ii++)
        {
            objectFile.addTag("object");
            objectFile.pushTag("object", ii);
            int proposedIndex = ofRandom(altitudes.size());
//            while(altitudes[proposedIndex] < 2 || altitudes[proposedIndex] > 5)
//            {
//                proposedIndex = ofRandom(altitudes.size());
//            }
            std::cout << proposedIndex << std::endl;
            City tmp(3, ofRandom(5000, 30000), randomName(), proposedIndex, "City", "CityHover");
            tmp.saveObjectData(objectFile);

            objectFile.popTag();


        }
        objectFile.popTag();

}


std::string GameMap::randomName()
{
    std::vector <std::string> prefixes;
    std::vector <std::string> suffixes;
    std::string line;
    bool recordpf = true;

    std::ifstream TownNames("../bin/data/CityNames.txt");
    if(TownNames.is_open())
    {
        while(getline(TownNames, line))
        {
            if (line == "---Prefixes---")
            {
                recordpf = 1;
            }
            else if (recordpf)
            {
                prefixes.push_back(line);
            }
            if (line == "---Suffixes---")
            {
                recordpf = false;
            }
            else if (!recordpf)
            {
                suffixes.push_back(line);
            }
        }
        TownNames.close();
    }
    int preRand = ofRandom(prefixes.size()-1);
    int sufRand = ofRandom(suffixes.size()-1);
    std::string preString = prefixes[preRand];
    std::string sufString = suffixes[sufRand];
    std::string retstr = preString + sufString;
    return  retstr;
}

void GameMap::genBand()
{
    std::string type = "Band";
    objectFile.addTag("type");
    objectFile.pushTag("type", 1);
    objectFile.addValue("name", "Band");
    objectFile.addValue("numOf", 1);
    for(int ii = 0; ii < 5; ii++)
    {
        objectFile.addTag("object");
        objectFile.pushTag("object", ii);
        int proposedIndex = ofRandom(0, (mapSize.x*mapSize.y)-1);
//           while(altitudes[proposedIndex] < 2 || altitudes[proposedIndex] > 5)
//           {
//               proposedIndex = ofRandom(altitudes.size());
//           }
        std::string name[4] = {"BandNormal", "BandIncog", "BandIncarn", "BandIncarnIncog"};
        Band tmp(false, false, 10, 3, "", name, "selectTile", "bandOutline", proposedIndex);
        tmp.saveObjectData(objectFile);
        objectFile.popTag();
    }
    objectFile.popTag();
    objectFile.saveFile("objects.xml");
}

//void genEnemyBand()
//{
//        std::string type = "Band";
//    objectFile.addTag("type");
//    objectFile.pushTag("type", 1);
//    objectFile.addValue("name", "Band");
//    objectFile.addValue("numOf", 1);
//    for(int ii = 0; ii < 5; ii++)
//    {
//        objectFile.addTag("object");
//        objectFile.pushTag("object", ii);
//        int proposedIndex = ofRandom(0, (mapSize.x*mapSize.y)-1);
////           while(altitudes[proposedIndex] < 2 || altitudes[proposedIndex] > 5)
////           {
////               proposedIndex = ofRandom(altitudes.size());
////           }
//        std::string name[4] = {"BandNormal", "BandIncog", "BandIncarn", "BandIncarnIncog"};
//        Band tmp(false, false, 10, 3, "", name, "selectTile", proposedIndex);
//        tmp.saveObjectData(objectFile);
//        objectFile.popTag();
//    }
//    objectFile.popTag();
//    objectFile.saveFile("objects.xml");
//}


























