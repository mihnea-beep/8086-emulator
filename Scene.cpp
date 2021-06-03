#include "Scene.h"
#include "GUI.h"
#include "Button.h"
#include <stdio.h>
#include <sys/wait.h> // for wait()
#include <unistd.h>   // for fork()
#include <thread>
#include "emu/Assembler.h"
#include "emu/CPU.h"

Scene::Scene()
{
}

void Scene::loadRes(SDL_Renderer *Renderer)
{

  // menu buttons
  msg[0].setX(260);
  msg[0].setY(50);

  msg[0].setColor(0, 0, 0);
  msg[0].setButton("Assemble", "IBM_PS.ttf", 20, Renderer);

  msg[1].setX(260);
  msg[1].setY(300);
  msg[1].setColor(0, 0, 0);
  msg[1].setButton("Exit", "IBM_PS.ttf", 20, Renderer);

  msg[2].setX(260);
  msg[2].setY(150);
  msg[2].setColor(0, 0, 0);
  msg[2].setButton("Edit", "IBM_PS.ttf", 20, Renderer);

  msg[3].setX(260);
  msg[3].setY(250);
  msg[3].setColor(0, 0, 0);
  msg[3].setButton("Execute", "IBM_PS.ttf", 20, Renderer);

  // register values
  regs[0].setX(500);
  regs[0].setY(50);
  regs[0].setColor(0, 0, 0);
  regs[0].setButton("AX: ", "IBM_PS.ttf", 20, Renderer);
}

void Scene::Init(SDL_Renderer *Renderer)
{
  loadRes(Renderer);
}

void Scene::checkInput()
{

  SDL_Event ev;

  while (SDL_PollEvent(&ev))
  {
    if (ev.type == SDL_QUIT)
    {
      cout << "'exit'!";
      scene_running = false;
      //  break;
    }

    if (ev.type == SDL_KEYDOWN)
    {
      switch (ev.key.keysym.sym)
      {
      case SDLK_ESCAPE:

        cout << "'escape'!";

        scene_running = false;

        break;

      default:
        break;
      }
    }
    if (ev.type == SDL_MOUSEBUTTONUP)
    { // TODO: thread ?
      if (assemblePressed)
      {
        // TODO: functionality
        system("echo \"Assembling ... \"");
        system("cd unicorn \n ./run_assembler.sh");
        assemblePressed = false;
        //setRunning(false);
        // system("./run.sh \n ^C");
      }
      if (exitPressed)
      {
        cout << "Exiting ...";
        setRunning(false);
      }
      if (editPressed)
      {
        cout << "Editing ...";
        thread threadEdit = thread(editFile);
        threadEdit.detach();
      }
      if (executePressed)
      {
        stepIndex = 0;
        cout << "Launching CPU ...";
        startCPU();
        // thread threadLaunch = thread(launchCPU);
        // threadLaunch.detach();
      }
      if (stepPressed)
      {
        cout << "Next" << endl;
        cout << "stepIndex: " << stepIndex << endl;

        if (stepIndex < cpu.get_instructionsCnt() - 1)
          stepIndex++;
        stepPressed = false;
        // if (stepIndex < cpu.get_instructionsCnt())
        //   stepIndex++;
        // else
        //   stepIndex = 0;
        // stepPressed = false;
        // thread threadLaunch = thread(launchCPU);
        // threadLaunch.detach();
      }
    }
  }
}

void Scene::launchCPU()
{

  // system("cd unicorn \n ./run_CPU.sh");

  // cpu.set_data();
  // cpu.open();
  // cpu.map();
  // cpu.write();

  // cpu.wx_regs();
  // cpu.rx_regs();

  // cpu.emulate();
  // cpu.close();
}

void Scene::startCPU()
{

  assembler.open();
  assembler.load("emu_data/asm_code.asm"); // "asm_code.asm" - default input file
  assembler.store("emu_data/machine_code.txt");

  cpu.set_data();
  cpu.open();
  cpu.map();
  cpu.write();

  cpu.wx_regs();
  cpu.rx_regs();

  cpu.emulate();
  assembler.close();

  cpu.close();
}

void Scene::editFile()
{
  // TODO: parameter
  system("gedit emu_data/asm_code.asm");
  // system("ls");
}

void Scene::update()
{
  int mx, my;
  SDL_GetMouseState(&mx, &my);
  msg[0].setColor(0, 0, 0);
  msg[1].setColor(0, 0, 0);
  msg[2].setColor(0, 0, 0);
  msg[3].setColor(0, 0, 0);
  msg[4].setColor(0, 0, 0);

  assemblePressed = false;
  exitPressed = false;
  editPressed = false;
  executePressed = false;
  stepPressed = false;

  if ((mx >= msg[0].getX()) && (mx <= (msg[0].getX() + msg[0].getW())))
    if ((my >= msg[0].getY()) && (my <= (msg[0].getY() + msg[0].getH())))
    {
      msg[0].setColor(255, 0, 0);
      assemblePressed = true;
    }
  if ((mx >= msg[1].getX()) && (mx <= (msg[1].getX() + msg[1].getW())))
    if ((my >= msg[1].getY()) && (my <= (msg[1].getY() + msg[1].getH())))
    {
      msg[1].setColor(255, 0, 0);
      exitPressed = true;
    }
  if ((mx >= msg[2].getX()) && (mx <= (msg[2].getX() + msg[2].getW())))
    if ((my >= msg[2].getY()) && (my <= (msg[2].getY() + msg[2].getH())))
    {
      msg[2].setColor(255, 0, 0);
      editPressed = true;
    }

  if ((mx >= msg[3].getX()) && (mx <= (msg[3].getX() + msg[3].getW())))
    if ((my >= msg[3].getY()) && (my <= (msg[3].getY() + msg[3].getH())))
    {
      msg[3].setColor(255, 0, 0);
      executePressed = true;
    }

  if ((mx >= msg[4].getX()) && (mx <= (msg[4].getX() + msg[4].getW())))
    if ((my >= msg[4].getY()) && (my <= (msg[4].getY() + msg[4].getH())))
    {
      msg[4].setColor(255, 0, 0);
      stepPressed = true;
    }
  // CPU

  // step by step execution

  if (stepPressed)
  {
  }
}

void Scene::render(SDL_Renderer *Renderer)
{
  SDL_SetRenderDrawColor(Renderer, 200, 200, 200, 230);
  SDL_RenderClear(Renderer);

  msg[0].setButton(" Assemble ", "IBM_PS.ttf", 35, Renderer, "blended");
  msg[0].display(150, 50, 150, 50, Renderer, "blended");

  msg[1].setButton("  Exit  ", "IBM_PS.ttf", 35, Renderer, "blended");
  msg[1].display(180, 290, 150, 50, Renderer, "blended");

  msg[2].setButton("  Edit  ", "IBM_PS.ttf", 35, Renderer, "blended");
  msg[2].display(180, 130, 150, 50, Renderer, "blended");

  msg[3].setButton("  Execute  ", "IBM_PS.ttf", 35, Renderer, "blended");
  msg[3].display(152, 210, 150, 50, Renderer, "blended");

  // step button

  msg[4].setButton("Next", "IBM_PS.ttf", 35, Renderer, "blended");
  msg[4].display(352, 210, 150, 50, Renderer, "blended");

  // registers values
  regs[0].setButton("AX: " + to_string(cpu.get_eax().at(stepIndex)), "IBM_PS.ttf", 35, Renderer);
  regs[0].display(regs[0].getX(), regs[0].getY(), 150, 50, Renderer, "blended");

  SDL_RenderPresent(Renderer);
}

void Scene::loop(SDL_Renderer *Renderer)
{
  while (scene_running)
  {
    SDL_Delay(33);
    checkInput();
    update();
    render(Renderer);
  }
}

void Scene::loadScene(SDL_Renderer *Renderer)
{

  loadRes(Renderer);
  loop(Renderer);
}

Scene::~Scene()
{
}

bool Scene::getRunning()
{
  return scene_running;
}

void Scene::setRunning(bool x)
{
  scene_running = x;
}

void Scene::free()
{
}
