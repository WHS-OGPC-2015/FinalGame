#include "City.h"
#include <sstream>

int turnsToInt(double d)
{
    int i = d;
    return i;
}

City::City()
{
   // cityName = randomname(); // set name to a random combination of prefixes and suffixes
    maxdif = 5;  // set the maximum difficulty for ALL cities
    accelmax = 50; // same in each city
    difficulty = 0;     // set the difficulty for a city
    thresholds[0] = .05;     // below this percentage of believers in an entered city, the believers will increase
    thresholds[1] = .5 + difficulty; // above this percentage in an entered city, the converted will increase
    thresholds[2] = .95;  // above this percentage in an entered city, the converted will decline
//    velmin = -(thresholds[1]-thresholds[0]) * accelmax; //integral from bottom th to middle th of the acceleration, / (-2) -- the C of the integral
//    velmax = (thresholds[2]-thresholds[1]) * accelmax;
    extremeaccel[0] = 10;
    extremeaccel[1] = -10;
//    threshnums[0] = 0;
    drawMenu = false;
    selected = false;
    hovered = false;
    strength = 20;
    bandAccel = 0;
}

City::City(int dif, double fpopulation, std::string fcityName, int iTileIndex, std::string TN, std::string HTN)
{
    TileIndex = iTileIndex;
    population = fpopulation; // default population
    converted = 2000; // you don't have any influence
    cityName = fcityName;
    textureName = TN;
    textureHoverName = HTN;
    occupied = 0;
    entered = false;
    velocity = 0;
    accel = 0;
   // cityName = randomname(); // set name to a random combination of prefixes and suffixes
    maxdif = 5;  // set the maximum difficulty for ALL cities
    accelmax = 50; // same in each city
    difficulty = dif;     // set the difficulty for a city (1-5?)
    thresholds[0] = .05;     // below this percentage of believers in an entered city, the believers will increase
    thresholds[1] = .5 + difficulty; // above this percentage in an entered city, the converted will increase
    thresholds[2] = .95;  // above this percentage in an entered city, the converted will decline
//    velmin = -(thresholds[1]-thresholds[0]) * accelmax; //integral from bottom th to middle th of the acceleration, / (-2) -- the C of the integral
//    velmax = (thresholds[2]-thresholds[1]) * accelmax;
    extremeaccel[0] = 10;
    extremeaccel[1] = -10;
//    threshnums[0] = 0;
    drawMenu = false;
    selected = false;
    hovered = false;
    strength = 25;
    bandAccel = 0;
}

void City::setTile(Tile* T)
{
    boundTile = T;
    boundTile->switchCityoc();
}

int City::getTileIndex()
{
    return TileIndex;
}

void City::setTexture(ofTexture& Text, bool hover)
{
    if(hover)
    {
        cityHoverTexture = &Text;
    }
    else
    {
        cityTexture = &Text;
    }

}

std::string City::getTextureName(bool hover)
{
    if(hover)
    {
        return textureHoverName;
    }
    return textureName;
}

int City::getClickedData(ofVec2f& mousePos, bool& clicked, bool& pressed)
 {
    if (mousePos.x < TLpos.x || mousePos.x > BRpos.x ||
        mousePos.y < TLpos.y || mousePos.y > BRpos.y)
    {
        return 0;
        // its ouside
    }
    else
    {
        if (clicked == true)
        {
            return 3;
        }
        else if (pressed == true)
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }


 }

void City::update(ofVec2f& mousePos, bool& clicked, bool& pressed)
{
    TLpos = ofVec2f(boundTile->getLocation().x, boundTile->getLocation().y);
    BRpos = ofVec2f(boundTile->getLocation().x + cityTexture->getWidth(), boundTile->getLocation().y + cityTexture->getHeight());
    occupied = boundTile->getBandoc();
    if (occupied > 0 and entered == false)
    {
        entered = true;
    }

    clickedData = getClickedData(mousePos, clicked, pressed);
    if(clickedData == 3 and mousePos.y < 724)
    {
        if (selected == true)
        {
            selected = false;
        }
        else
        {
            selected = true;
        }

    }
    else if (clicked == true and mousePos.y < 724)
    {
        selected = false;
    }

    if (clickedData == 1 or clickedData == 2)
    {
        hovered = true;
    }

    if (selected == true)
    {
        cityMenu->setActive();
        fillMenu();
        hovered = false;
    }

    if (hovered == true)
    {
        cityMenu->setActive();
        fillMenu();
    }

    if (clickedData == 0)
    {
        hovered = false;
    }


}


void City::turnlyUpdate()
{
    percentconverted = converted / population;
   // std::cout << entered << std::endl;

    if (entered == true)
    {

//        threshnums[1] = threshnums[0];
        if (percentconverted <= thresholds[0])
        {
           accel = extremeaccel[0];
//           threshnums[0] = 0;
        }
        else if (percentconverted >= thresholds[2])
        {
            accel = extremeaccel[1];
//            threshnums[0] = 3;
        }
        //now stuff?
        else
        {

            if (percentconverted < thresholds[1])
            {
//                threshnums[0] = 1;

                accel  = (percentconverted - thresholds[0])*((accelmax)/(thresholds[1] - thresholds[0])) - accelmax;
                //std::cout << accel << std::endl;
                //std::cout << bandAccel << std::endl;
               //this is a point-slope formula
            }
            else
            {
//                threshnums[0] = 2;
                accel  = (percentconverted - thresholds[2])*((accelmax)/(thresholds[1] - thresholds[2])) - accelmax;
                // this is, too
            }
        }
        if (percentconverted < thresholds[2])
        {
            if (occupied > 0 and boundTile->getIncog() == false)
            {
                bandAccel = occupied * strength;
            }
            else
            {
                bandAccel = 0;
            }
        }

        velocity += accel + bandAccel;
        converted += velocity;


        if(converted < 0)
        {
            converted = 0;
        }
        if (converted > population)
        {
            converted = population;
        }
    }
   // std::cout << converted << std::endl;

}

void City::draw()
{
    if(selected == true or hovered == true)
    {
        cityHoverTexture->draw(boundTile->getLocation());
    }
    else
    {
        cityTexture->draw(boundTile->getLocation());
    }

}

void City::fillMenu()
{
    TextBox* cName = cityMenu->getPointerToChildByName<TextBox>("CityName");
    cName->setText(cityName);
//
    TextBox* disNumber = cityMenu->getPointerToChildByName<TextBox>("DiscipleNumber");
    ostringstream convert;
    convert << occupied;
    disNumber->setText(convert.str());
//
    TextBox* difNumber = cityMenu->getPointerToChildByName<TextBox>("Difficulty");
    ostringstream converta;
    converta << difficulty;
    difNumber->setText(converta.str());
//
    PieChart*  pChart = cityMenu->getPointerToChildByName<PieChart>("BelieverPie");
    pChart->setVariables(converted, population);
    //std::cout << "fuc," << std::endl;

}

void City::setMenu(Menu* CM)
{
    cityMenu = CM;
}

double City::getPercentConverted()
{
    return percentconverted;
}

void City::saveObjectData(ofxXmlSettings& file)
{
    //std::cout << cityName << std::endl;
    file.addValue("cityTexture", textureName);
    file.addValue("cityHoverTexture", textureHoverName);
    file.addValue("cityName", cityName);
    file.addValue("tileIndex", TileIndex);
    file.addValue("population", population);
    file.addValue("converted", converted);
    file.addValue("velocity", velocity);
   // file.addValue("velmin", velmin);
   // file.addValue("velmax", velmax);
    file.addValue("accel", accel);
 //   file.addValue("TLposx", TLpos.x);
  //  file.addValue("TLposy", TLpos.y);
  //  file.addValue("BRposx", BRpos.x);
   // file.addValue("BRposy", BRpos.y);
   // file.addValue("threshold0", thresholds[0]);
    //file.addValue("threshold1", thresholds[1]);
    //file.addValue("threshold2", thresholds[2]);
    file.addValue("difficulty", difficulty);
    file.addValue("occupied", occupied);
    file.addValue("entered", entered);


}

void City::loadObjectData(ofxXmlSettings& file)
{
    //TileIndex = boundTile;
    textureName = file.getValue("cityTexture", "");
    textureHoverName = file.getValue("cityHoverTexture", "");
    cityName = file.getValue("cityName", "");
    TileIndex = file.getValue("tileIndex", 0);
    population = file.getValue("population", 0.0);
    converted = file.getValue("converted", 0.0);
    velocity = file.getValue("velocity", 0.0);
  //  velmin = file.getValue("velmin", 0.0);
   // velmax = file.getValue("velmax", 0.0);
    accel = file.getValue("accel", 0.0);
    //ofVec2f TLpos = ofVec2f(file.getValue("TLposx", 0.0), file.getValue("TLposy", 0.0));
   // ofVec2f BRpos = ofVec2f(file.getValue("BRposx", 0.0), file.getValue("BRposy", 0.0));
   // thresholds[0] = file.getValue("threshold0", 0.0);
    //thresholds[1] = file.getValue("threshold1", 0.0);
   // thresholds[2] = file.getValue("threshold2", 0.0);
    difficulty = file.getValue("difficulty", 0);
    occupied = file.getValue("occupied", 0);
    entered = file.getValue("entered", 0 /*hopefully works for bool?*/);
}
