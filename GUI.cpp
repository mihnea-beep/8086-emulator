#include "GUI.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
using namespace std;

void GUI::setPos(int x, int y)
{
    this->x = x;
    this->y = y;
    GUIrc.x = x;
    GUIrc.y = y;
}

GUI::GUI()
{

}

GUI::~GUI()
{

}

int GUI::getX()
{
   return x;

}

int GUI::getY()
{
   return y;
}

void GUI::setDim(int w, int h)
{
    this->w = w;
    this->h = h;
    GUIrc.w = w;
    GUIrc.h = h;
}

int GUI::getW()
{
    return w;
}

int GUI::getH()
{
    return h;
}

void GUI::setMsg(string msgtext, SDL_Renderer* render)
{
    BoxText.setColor(getColor().r, getColor().g, getColor().b);
    BoxText.setText(msgtext.c_str(), "IBM_PS.ttf", 24, render);
   // BoxText.display(getX(), getY(), getW(), getH(), render);

}

void GUI::displayMsg(SDL_Renderer* render)
{
    BoxText.display(getX(), getY(), getW(), getH(), render);
}

void GUI::display(SDL_Renderer* render)
{
    SDL_SetRenderDrawColor(render, GUIcolor.r, GUIcolor.g, GUIcolor.b, 0);
    SDL_RenderDrawRect(render, &GUIrc);
}

void GUI::setColor(int r, int g, int b)
{
    GUIcolor = {(unsigned char)r, (unsigned char)g, (unsigned char)b};
}

SDL_Color GUI::getColor()
{
    return GUIcolor;
}

void GUI::Free()
{
	BoxText.Free();
}
