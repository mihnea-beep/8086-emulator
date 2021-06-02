#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "GUI.h"
#include "Button.h"
#include "emu/Assembler.h"
#include "emu/CPU.h"
using namespace std;

class Scene
{
  bool scene_running = false;

  GUI element;
  Button msg[4]; // 4 buttons
  bool assemblePressed = false;
  bool exitPressed = false;
  bool editPressed = false;
  bool executePressed = false;
  Assembler assembler;
  CPU cpu;


public:
  Scene();

  virtual void loadRes(SDL_Renderer *Renderer);
  virtual void Init(SDL_Renderer *Renderer);
  virtual void checkInput();
  virtual void update();
  virtual void render(SDL_Renderer *);
  virtual void loop(SDL_Renderer *Renderer);
  virtual void loadScene(SDL_Renderer *Renderer);

  virtual void setRunning(bool);
  virtual bool getRunning();

  virtual void free();
  static void editFile();
  static void launchCPU();

  virtual void startCPU();

  virtual ~Scene();
};
