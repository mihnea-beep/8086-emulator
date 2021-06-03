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

  regs[5].setX(500);
  regs[5].setY(650);
  regs[5].setColor(0, 0, 0);
  regs[5].setButton("EFLAGS: ", "IBM_PS.ttf", 20, Renderer);

  regs[6].setX(400);
  regs[6].setY(550);
  regs[6].setColor(0, 0, 0);
  regs[6].setButton("CF: ", "IBM_PS.ttf", 20, Renderer);

  regs[7].setX(490);
  regs[7].setY(550);
  regs[7].setColor(0, 0, 0);
  regs[7].setButton("PF: ", "IBM_PS.ttf", 20, Renderer);

  regs[8].setX(580);
  regs[8].setY(550);
  regs[8].setColor(0, 0, 0);
  regs[8].setButton("AF: ", "IBM_PS.ttf", 20, Renderer);

  regs[9].setX(670);
  regs[9].setY(550);
  regs[9].setColor(0, 0, 0);
  regs[9].setButton("ZF: ", "IBM_PS.ttf", 20, Renderer);

  regs[10].setX(760);
  regs[10].setY(550);
  regs[10].setColor(0, 0, 0);
  regs[10].setButton("ZF: ", "IBM_PS.ttf", 20, Renderer);

  regs[11].setX(850);
  regs[11].setY(550);
  regs[11].setColor(0, 0, 0);
  regs[11].setButton("ZF: ", "IBM_PS.ttf", 20, Renderer);

  regs[12].setX(940);
  regs[12].setY(550);
  regs[12].setColor(0, 0, 0);
  regs[12].setButton("ZF: ", "IBM_PS.ttf", 20, Renderer);

  regs[13].setX(1030);
  regs[13].setY(550);
  regs[13].setColor(0, 0, 0);
  regs[13].setButton("ZF: ", "IBM_PS.ttf", 20, Renderer);

  regs[14].setX(1120);
  regs[14].setY(550);
  regs[14].setColor(0, 0, 0);
  regs[14].setButton("ZF: ", "IBM_PS.ttf", 20, Renderer);

  regs[15].setX(regs[0].getX() + 200);
  regs[15].setY(regs[0].getY());
  regs[15].setColor(0, 0, 0);
  regs[15].setButton("SP: ", "IBM_PS.ttf", 20, Renderer);

  regs[16].setX(regs[1].getX() + 200);
  regs[16].setY(regs[1].getY());
  regs[16].setColor(0, 0, 0);
  regs[16].setButton("BP: ", "IBM_PS.ttf", 20, Renderer);

  regs[17].setX(regs[2].getX() + 200);
  regs[17].setY(regs[2].getY());
  regs[17].setColor(0, 0, 0);
  regs[17].setButton("SI: ", "IBM_PS.ttf", 20, Renderer);

  regs[18].setX(regs[3].getX() + 200);
  regs[18].setY(regs[3].getY());
  regs[18].setColor(0, 0, 0);
  regs[18].setButton("DI: ", "IBM_PS.ttf", 20, Renderer);

  regs[19].setX(regs[15].getX() + 200);
  regs[19].setY(regs[15].getY());
  regs[19].setColor(0, 0, 0);
  regs[19].setButton("CS: ", "IBM_PS.ttf", 20, Renderer);

  regs[20].setX(regs[16].getX() + 200);
  regs[20].setY(regs[16].getY());
  regs[20].setColor(0, 0, 0);
  regs[20].setButton("DS: ", "IBM_PS.ttf", 20, Renderer);

  regs[21].setX(regs[17].getX() + 200);
  regs[21].setY(regs[17].getY());
  regs[21].setColor(0, 0, 0);
  regs[21].setButton("SS: ", "IBM_PS.ttf", 20, Renderer);

  regs[22].setX(regs[18].getX() + 200);
  regs[22].setY(regs[18].getY());
  regs[22].setColor(0, 0, 0);
  regs[22].setButton("ES: ", "IBM_PS.ttf", 20, Renderer);
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

  if (assembler.getErr())
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
  stringstream efStream;

  stringstream spStream;
  stringstream bpStream;
  stringstream siStream;
  stringstream diStream;

  stringstream csStream;
  stringstream dsStream;
  stringstream ssStream;
  stringstream esStream;

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

    efStream.str("");
    efStream << cpu.get_eflags().at(stepIndex);

    spStream.str("");
    spStream << cpu.get_sp().at(stepIndex);

    bpStream.str("");
    bpStream << cpu.get_bp().at(stepIndex);

    siStream.str("");
    siStream << cpu.get_si().at(stepIndex);

    diStream.str("");
    diStream << cpu.get_di().at(stepIndex);

    csStream.str("");
    csStream << cpu.get_cs().at(stepIndex);
    
    dsStream.str("");
    dsStream << cpu.get_ds().at(stepIndex);

    ssStream.str("");
    ssStream << cpu.get_ss().at(stepIndex);

    esStream.str("");
    esStream << cpu.get_es().at(stepIndex);
    // cout << "decimal";
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

    efStream.str("");
    efStream << "0x" << setfill('0') << setw(4) << right << std::hex << stoi(cpu.get_eflags().at(stepIndex));

    spStream.str("");
    spStream << "0x" << setfill('0') << setw(4) << right << std::hex << cpu.get_sp().at(stepIndex);

    bpStream.str("");
    bpStream << "0x" << setfill('0') << setw(4) << right << std::hex << cpu.get_bp().at(stepIndex);

    siStream.str("");
    siStream << "0x" << setfill('0') << setw(4) << right << std::hex << cpu.get_si().at(stepIndex);

    diStream.str("");
    diStream << "0x" << setfill('0') << setw(4) << right << std::hex << cpu.get_di().at(stepIndex);

    csStream.str("");
    csStream << "0x" << setfill('0') << setw(4) << right << std::hex << cpu.get_cs().at(stepIndex);

    dsStream.str("");
    dsStream << "0x" << setfill('0') << setw(4) << right << std::hex << cpu.get_ds().at(stepIndex);

    ssStream.str("");
    ssStream << "0x" << setfill('0') << setw(4) << right << std::hex << cpu.get_ss().at(stepIndex);

    esStream.str("");
    esStream << "0x" << setfill('0') << setw(4) << right << std::hex << cpu.get_es().at(stepIndex);

    // cout << "hex";
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

  regs[5].setButton("EFLAGS: " + efStream.str(), "IBM_PS.ttf", 35, Renderer);
  regs[5].display(regs[5].getX(), regs[5].getY(), 150, 50, Renderer, "blended");

  regs[6].setButton("CF: " + cpu.get_eflags().at(stepIndex).substr(11, 1), "IBM_PS.ttf", 35, Renderer);
  regs[6].display(regs[6].getX(), regs[6].getY(), 150, 50, Renderer, "blended");

  regs[7].setButton("PF: " + cpu.get_eflags().at(stepIndex).substr(9, 1), "IBM_PS.ttf", 35, Renderer);
  regs[7].display(regs[7].getX(), regs[7].getY(), 150, 50, Renderer, "blended");

  regs[8].setButton("AF: " + cpu.get_eflags().at(stepIndex).substr(7, 1), "IBM_PS.ttf", 35, Renderer);
  regs[8].display(regs[8].getX(), regs[8].getY(), 150, 50, Renderer, "blended");

  regs[9].setButton("ZF: " + cpu.get_eflags().at(stepIndex).substr(5, 1), "IBM_PS.ttf", 35, Renderer);
  regs[9].display(regs[9].getX(), regs[9].getY(), 150, 50, Renderer, "blended");

  regs[10].setButton("SF: " + cpu.get_eflags().at(stepIndex).substr(4, 1), "IBM_PS.ttf", 35, Renderer);
  regs[10].display(regs[10].getX(), regs[10].getY(), 150, 50, Renderer, "blended");

  regs[11].setButton("TF: " + cpu.get_eflags().at(stepIndex).substr(3, 1), "IBM_PS.ttf", 35, Renderer);
  regs[11].display(regs[11].getX(), regs[11].getY(), 150, 50, Renderer, "blended");

  regs[12].setButton("IF: " + cpu.get_eflags().at(stepIndex).substr(2, 1), "IBM_PS.ttf", 35, Renderer);
  regs[12].display(regs[12].getX(), regs[12].getY(), 150, 50, Renderer, "blended");

  regs[13].setButton("DF: " + cpu.get_eflags().at(stepIndex).substr(1, 1), "IBM_PS.ttf", 35, Renderer);
  regs[13].display(regs[13].getX(), regs[13].getY(), 150, 50, Renderer, "blended");

  regs[14].setButton("OF: " + cpu.get_eflags().at(stepIndex).substr(0, 1), "IBM_PS.ttf", 35, Renderer);
  regs[14].display(regs[14].getX(), regs[14].getY(), 150, 50, Renderer, "blended");

  regs[15].setButton("SP: " + spStream.str(), "IBM_PS.ttf", 35, Renderer);
  regs[15].display(regs[15].getX(), regs[15].getY(), 150, 50, Renderer, "blended");

  regs[16].setButton("BP: " + bpStream.str(), "IBM_PS.ttf", 35, Renderer);
  regs[16].display(regs[16].getX(), regs[16].getY(), 150, 50, Renderer, "blended");

  regs[17].setButton("SI: " + siStream.str(), "IBM_PS.ttf", 35, Renderer);
  regs[17].display(regs[17].getX(), regs[17].getY(), 150, 50, Renderer, "blended");

  regs[18].setButton("DI: " + diStream.str(), "IBM_PS.ttf", 35, Renderer);
  regs[18].display(regs[18].getX(), regs[18].getY(), 150, 50, Renderer, "blended");

  // segment regs

  regs[19].setButton("CS: " + csStream.str(), "IBM_PS.ttf", 35, Renderer);
  regs[19].display(regs[19].getX(), regs[19].getY(), 150, 50, Renderer, "blended");

  regs[20].setButton("DS: " + dsStream.str(), "IBM_PS.ttf", 35, Renderer);
  regs[20].display(regs[20].getX(), regs[20].getY(), 150, 50, Renderer, "blended");

  regs[21].setButton("SS: " + ssStream.str(), "IBM_PS.ttf", 35, Renderer);
  regs[21].display(regs[21].getX(), regs[21].getY(), 150, 50, Renderer, "blended");

  regs[22].setButton("ES: " + esStream.str(), "IBM_PS.ttf", 35, Renderer);
  regs[22].display(regs[22].getX(), regs[22].getY(), 150, 50, Renderer, "blended");

  // step index
  msg[6].setButton("Step index: " + to_string(stepIndex), "IBM_PS.ttf", 25, Renderer, "blended");
  msg[6].display(322, 410, 150, 30, Renderer, "blended");

  // change format

  msg[7].setButton("Format", "IBM_PS.ttf", 25, Renderer, "blended");
  msg[7].display(322, 480, 150, 30, Renderer, "blended");

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
