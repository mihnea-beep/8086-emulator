#include "Scene.h"
#include "GUI.h"
#include "Button.h"
#include <stdio.h>
#include <sys/wait.h> // for wait()
#include <unistd.h>   // for fork()
#include <thread>
#include "emu/Assembler.h"
#include "emu/CPU.h"
#include <bitset>

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

  regs[1].setX(500);
  regs[1].setY(100);
  regs[1].setColor(0, 0, 0);
  regs[1].setButton("BX: ", "IBM_PS.ttf", 20, Renderer);

  regs[2].setX(500);
  regs[2].setY(150);
  regs[2].setColor(0, 0, 0);
  regs[2].setButton("CX: ", "IBM_PS.ttf", 20, Renderer);

  regs[3].setX(500);
  regs[3].setY(200);
  regs[3].setColor(0, 0, 0);
  regs[3].setButton("DX: ", "IBM_PS.ttf", 20, Renderer);

  regs[4].setX(500);
  regs[4].setY(250);
  regs[4].setColor(0, 0, 0);
  regs[4].setButton("IP: ", "IBM_PS.ttf", 20, Renderer);
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
      if (prevPressed)
      {
        cout << "Prev" << endl;
        cout << "stepIndex: " << stepIndex << endl;
        if (stepIndex >= 1)
          stepIndex--;
        stepPressed = false;
      }
      if (formatPressed)
      {
        cout << "Changed format" << endl;
        decimalFormat = !decimalFormat;
        formatPressed = false;
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

  if(assembler.getErr())
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Assembly error", "Assembly error\nCheck your code!", NULL);
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
  msg[5].setColor(0, 0, 0);
  msg[6].setColor(0, 0, 0);
  msg[7].setColor(0, 0, 0);

  assemblePressed = false;
  exitPressed = false;
  editPressed = false;
  executePressed = false;
  stepPressed = false;
  prevPressed = false;
  formatPressed = false;

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

  if ((mx >= msg[5].getX()) && (mx <= (msg[5].getX() + msg[5].getW())))
    if ((my >= msg[5].getY()) && (my <= (msg[5].getY() + msg[5].getH())))
    {
      msg[5].setColor(255, 0, 0);
      prevPressed = true;
    }

  if ((mx >= msg[7].getX()) && (mx <= (msg[7].getX() + msg[7].getW())))
    if ((my >= msg[7].getY()) && (my <= (msg[7].getY() + msg[7].getH())))
    {
      msg[7].setColor(255, 0, 0);
      formatPressed = true;
    }
  // CPU
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

  msg[5].setButton("Prev", "IBM_PS.ttf", 35, Renderer, "blended");
  msg[5].display(352, 310, 150, 50, Renderer, "blended");

  // registers values

  stringstream axStream;
  stringstream bxStream;
  stringstream cxStream;
  stringstream dxStream;
  stringstream ipStream;


  if (decimalFormat)
  {
    axStream.str("");
    axStream << cpu.get_eax().at(stepIndex);

    bxStream.str("");
    bxStream << cpu.get_ebx().at(stepIndex);

    cxStream.str("");
    cxStream << cpu.get_ecx().at(stepIndex);

    dxStream.str("");
    dxStream << cpu.get_edx().at(stepIndex);

    ipStream.str("");
    ipStream << cpu.get_eip().at(stepIndex);

    cout << "decimal";
  }
  else // hex
  {
    axStream.str("");
    axStream << "0x" << setfill('0') << setw(4) << right << std::hex << cpu.get_eax().at(stepIndex);

    bxStream.str("");
    bxStream << "0x" << setfill('0') << setw(4) << right << std::hex << cpu.get_ebx().at(stepIndex);

    cxStream.str("");
    cxStream << "0x" << setfill('0') << setw(4) << right << std::hex << cpu.get_ecx().at(stepIndex);

    dxStream.str("");
    dxStream << "0x" << setfill('0') << setw(4) << right << std::hex << cpu.get_edx().at(stepIndex);

    ipStream.str("");
    ipStream << "0x" << setfill('0') << setw(4) << right << std::hex << cpu.get_eip().at(stepIndex);

    cout << "hex";
  }

  // bxStream << bitset<8>(cpu.get_ebx().at(stepIndex));

  regs[0].setButton("AX: " + axStream.str(), "IBM_PS.ttf", 35, Renderer);
  regs[0].display(regs[0].getX(), regs[0].getY(), 150, 50, Renderer, "blended");

  regs[1].setButton("BX: " + bxStream.str(), "IBM_PS.ttf", 35, Renderer);
  regs[1].display(regs[1].getX(), regs[1].getY(), 150, 50, Renderer, "blended");

  regs[2].setButton("CX: " + cxStream.str(), "IBM_PS.ttf", 35, Renderer);
  regs[2].display(regs[2].getX(), regs[2].getY(), 150, 50, Renderer, "blended");

  regs[3].setButton("DX: " + dxStream.str(), "IBM_PS.ttf", 35, Renderer);
  regs[3].display(regs[3].getX(), regs[3].getY(), 150, 50, Renderer, "blended");

  regs[4].setButton("IP: " + ipStream.str(), "IBM_PS.ttf", 35, Renderer);
  regs[4].display(regs[4].getX(), regs[4].getY(), 150, 50, Renderer, "blended");

  // step index
  msg[6].setButton("Step index: " + to_string(stepIndex), "IBM_PS.ttf", 25, Renderer, "blended");
  msg[6].display(322, 410, 150, 30, Renderer, "blended");

  // change format

  msg[7].setButton("Format", "IBM_PS.ttf", 25, Renderer, "blended");
  msg[7].display(322, 510, 150, 30, Renderer, "blended");

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
