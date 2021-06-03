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
  Button msg[10]; // 5 buttons
  bool assemblePressed = false;
  bool exitPressed = false;
  bool editPressed = false;
  bool executePressed = false;
  bool stepPressed = false; // next
  bool prevPressed = false; 
  bool formatPressed = false;
  bool decimalFormat = false;
  bool runPressed = false;
  bool finishPressed = false;
  Assembler assembler;
  CPU cpu;
  int i = 0;

  int stepIndex = 0;
  Button regs[30];


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
  virtual void launchProgram();

  virtual ~Scene();
};
