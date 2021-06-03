#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Scene.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_CreateWindowAndRenderer(500, 380, SDL_WINDOW_RESIZABLE, &window, &renderer);
    SDL_SetWindowTitle(window, "Menu");

    SDL_SetWindowSize(window, 1280, 720);
    Scene a;
    a.Init(renderer);
    a.setRunning(true);
    a.loop(renderer);
    
    return 0;
}