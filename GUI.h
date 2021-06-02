#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED
#include "Message.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
using namespace std;

class GUI
{
    string name;
    int x, y;			
    SDL_Rect GUIrc;
    int w, h;
    Message BoxText;
    SDL_Color GUIcolor;

public:

    GUI();

    void setName();
    void setPos(int x, int y);
    int getX();
    int getY();
    void setDim(int w, int h);
    void setMsg(string msgtext, SDL_Renderer* render);
    void display(SDL_Renderer* renderer);
    void displayMsg(SDL_Renderer* renderer);
    void setColor(int r, int g, int b);
    SDL_Color getColor();
    int getW();
    int getH();
    void Free();

    ~GUI();
};


#endif // GUI_H_INCLUDED
