#include "TextBox.h"

TextBox::TextBox(std::string str, ofVec2f posi, ofTrueTypeFont& f)
{
    text = str;
    position = posi;
    font = &f;
}

TextBox::TextBox()
{
}

void TextBox::update()
{
}

void TextBox::draw()
{
   if(font != NULL)
    {
        //center the text
        font->drawString(text, position.x - font->stringWidth(text)/2, position.y + font->stringHeight(text)/2 );
    }
}
void TextBox::setText(std::string str)
{
    text = str;
}

void TextBox::setPosition(ofVec2f posi)
{
    position = posi;
}
void TextBox::addPosition(ofVec2f dpos)
{
    position.x += dpos.x;
    position.y += dpos.y;
}
void TextBox::setFont(ofTrueTypeFont& f)
{
    font = &f;
}

int TextBox::getWidth()
{
    return font->stringWidth(text);
}

int TextBox::getHeight()
{
    return font->stringHeight(text);
}
