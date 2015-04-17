//#include "EnemyBand.h"
//
//
//int EnemyBand::convertTo1dindex(ofVec2i v)
//{
//    return (v.y * fabs(extremeTiles[1].x - extremeTiles[0].x) + v.x); // converts an ofVec2i to an int based on the amount of tiles in the map
//}
//
//EnemyBand::EnemyBand()
//{
//    textureName = "";
//    movable = true;
//}
//
//EnemyBand::EnemyBand(std::string str)
//{
//    textureName = str;
//    movable = true;
//}
////---------------------------------------------------
//void EnemyBand::update()
//{
//
//}
//
//void EnemyBand::turnlyUpdate(vector<Band> bands)
//{
//    bool found;
//    int siz = bands.size();
//    int discipleNum = 0;
//    int followIndex = -1;
//    ofVec2i coords = ofVec2i(-1, -1);
//    for (int i = 0; i < siz; i++)
//    {
//        if (bands[i].getIncognito() == false)
//        {
//            if (bands[i].getDiscipleNum() > discipleNum)
//            {
//                discipleNum = bands[i].getDiscipleNum();
//                coords = bands[i].getCoords();
//                followIndex = i;
//                found = true;
//            }
//        }
//    }
//
//
//    if (found == true)
//    {
//        double rise = (boundTileCoords.y - coords.y);
//        double run =  (boundTileCoords.x - coords.x);
//        if (rise + run != 0)
//        {
//            double nrise = (rise * movement)/(rise + run);
//            double nrun = (run * movement)/(rise + run);
//            if (nrise > nrun)
//            {
//                newCoord = ofVec2i(nrise, nrun + .5);
//            }
//            else
//            {
//                newCoord = ofVec2i(nrise + .5, nrun);
//            }
//        }
//        else
//        {
//            newCoord = boundTileCoords;
//        }
//    }
//
//
//}
//
//void EnemyBand::draw()
//{
//
//}
//
//
////---------------------------------------------------
//void EnemyBand::setTexture(ResourceManager* res)
//{
//    enemyTexture = &res->getTexture(TexNam);
//}
//
//void EnemyBand::setTile(Tile til, int inde)
//{
//    boundTile = &til;
//    boundTileIndex = inde;
//}
//
//void EnemyBand::setExtremeTiles(ofVec2i v1, ofVec2i v2)
//{
//    extremeTiles[0] = v1;
//    extremeTiles[1] = v2;
//    int temp = fabs(extremeTiles[1].x - extremeTiles[0].x);
//    boundTileCoords = ofVec2i(boundTileIndex % temp, boundTileIndex / temp);
//}
//
//int EnemyBand::getIndex();
//{
//    return boundTileIndex;
//}
//
//
//void EnemyBand::saveObjectData(ofxXmlSettings& file)
//{
//    file.addValue("movable", movable);
//    file.addValue("textureName", textureName);
//    file.addValue("boundTileIndex", boundTileIndex);
//
//    file.addValue("boundTileCoordsx", boundTileCoords.x);
//    file.addValue("boundTileCoordsy", boundTileCoords.y);
//
//    file.addValue("extremeTile0x", extremeTiles[0].x);
//    file.addValue("extremeTile0y", extremeTiles[0].y);
//    file.addValue("extremeTile1x", extremeTiles[1].x);
//    file.addValue("extremeTile1y", extremeTiles[1].y);
//}
//
//void EnemyBand::loadObjectData(ofxXmlSettings& file)
//{
//    movable = file.getValue("movable", 0);
//    textureName = file.getValue("textureName", "");
//    boundTileIndex = file.getValue("boundTileIndex", 0);
//    boundTileCoords.x = file.getValue("boundTileCoordsx", 0);
//    boundTileCoords.y = file.getValue("boundTileCoordsy", 0);
//
//    extremeTiles[0].x = file.getValue("extremeTile0x", 0);
//    extremeTiles[0].y = file.getValue("extremeTile0y", 0);
//    extremeTiles[1].x = file.getValue("extremeTile1x", 0);
//    extremeTiles[1].y = file.getValue("extremeTile1y", 0);
//}
