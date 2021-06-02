#include "Button.h"

Button::Button(/* args */)
{
}
void Button::setButton(string text, string font, uint16_t size, SDL_Renderer* renderer, string mode, int wrapLength){
    Message::setText(text, font, size, renderer, mode, wrapLength);
}
Button::~Button()
{
}