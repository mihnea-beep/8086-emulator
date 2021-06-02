
#include "Message.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

using namespace std;

Message::Message()
{

}

Message::Message(SDL_Renderer* renderer, string text)
{

}

void Message::setText(string text)
{
    messageText = text;
}

string Message::getText()
{
    return messageText;
}

TTF_Font* Message::getFont()
{
    return msg_font;
}

void Message::setText(string text, string font, uint16_t size, SDL_Renderer* renderer, string mode, int wrapLength)
{
    //msg_color = {0, 0, 100};

    if(msg_font != NULL)
        TTF_CloseFont(msg_font);
    msg_font = NULL;

   fontSize = size;

    msg_font = TTF_OpenFont(font.c_str(), size);

    if(msg_font == NULL)
        cout << "LOADING ERROR - font " << TTF_GetError() << endl;

	if(msg_texture != NULL)
		SDL_DestroyTexture(msg_texture);

    msg_texture = NULL;

    if(mode == "blended")
        msg_surface = TTF_RenderText_Blended_Wrapped(msg_font, text.c_str(), msg_color, wrapLength); 
    else
        msg_surface = TTF_RenderText_Solid(msg_font, text.c_str(), msg_color);

    msg_texture = SDL_CreateTextureFromSurface(renderer, msg_surface);

    if(msg_surface == NULL)
        cout << msg_surface << endl;

    SDL_FreeSurface(msg_surface);

    messageText = text;
}

void Message::setColor(int r, int g, int b)
{
    msg_color = {(unsigned char)r, (unsigned char)g, (unsigned char)b};
}

void Message::clearText()
{
    setText("");
}

void Message::Free()
{
    if(msg_texture != NULL)
        SDL_DestroyTexture(msg_texture);

    msg_texture = NULL;

    if(msg_font != NULL)
        TTF_CloseFont(getFont());
    
    msg_font = NULL;
}

void Message::setX(int x)
{
    msgRc.x = x;
}
void Message::setY(int y)
{
    msgRc.y = y;
}
int Message::getY()
{
    return msgRc.y;
}
int Message::getX()
{
    return msgRc.x;
}

int Message::getH(){
    return msgRc.h;
}

int Message::getW(){
    return msgRc.w;
}

void Message::setVisible(bool visible)
{
    isVisible = visible;
}

bool Message::getVisible()
{
    return isVisible;
}

void Message::display(int x, int y, int w, int h, SDL_Renderer* renderer, string mode)
{
    msgRc.x = x;
    msgRc.y = y;

     if(mode == "blended")
    {
        int width, height;
        TTF_SizeText(msg_font, messageText.c_str(), &width, &height);

        SDL_QueryTexture(getTexture(), NULL, NULL, &width, &height);

            msgRc.h = height;

        msgRc.w = width;

    }
    else
    {
        msgRc.w = w;
        msgRc.h = h;
    }
        SDL_SetRenderDrawColor(renderer, msg_color.r, msg_color.g, msg_color.b, 0);

        SDL_RenderCopy(renderer, msg_texture, NULL, &msgRc);
        SDL_RenderDrawRect(renderer, &msgRc);
    
}

SDL_Texture* Message::getTexture()
{
    return msg_texture;
}

Message::~Message()
{
    Free();
}
