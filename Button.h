#pragma once
#include <iostream>
#include "Message.h"
using namespace std;

class Button: public Message
{
private:
    SDL_Rect rc;
public:
    Button(/* args */);
    void setButton(string, string, uint16_t, SDL_Renderer*, string mode = "", int wLen = 640);
    ~Button();
};


