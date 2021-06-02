#include "Scene.h"
#include "GUI.h"
#include "Button.h"
#include <stdio.h>
#include <sys/wait.h> // for wait()
#include <unistd.h> // for fork()
#include <thread>
Scene::Scene()
{

}

void Scene::loadRes(SDL_Renderer* Renderer)
{
  
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

}

void Scene::Init(SDL_Renderer* Renderer)
{
    loadRes(Renderer);
}


void Scene::checkInput()
{

  SDL_Event ev;

  while(SDL_PollEvent(&ev))
      {
          if(ev.type == SDL_QUIT)
             {
                 cout<<"'exit'!";
                 scene_running = false;
                //  break;
             }

            if(ev.type == SDL_KEYDOWN)
            {
              switch(ev.key.keysym.sym)
              {
                case SDLK_ESCAPE:

                cout<<"'escape'!";

                scene_running = false;

                break;

                default:
                break;

              }
            }
            if(ev.type == SDL_MOUSEBUTTONUP){ // TODO: thread ?
              if(assemblePressed){
                system("echo \"Assembling ... \"");
                system("cd unicorn \n ./run_assembler.sh");
                assemblePressed = false;
                //setRunning(false);
                // system("./run.sh \n ^C");
              }
              if(exitPressed){
                cout << "Exiting ...";
                setRunning(false);
              }
              if(editPressed){
                cout << "Editing ...";
                thread threadEdit = thread(editFile);
                threadEdit.detach();
                
              }
              if(executePressed){
                cout << "Launching CPU ...";
                thread threadLaunch = thread(launchCPU);
                threadLaunch.detach();
              }
            }
          }

}

void Scene::launchCPU(){
  system("cd unicorn \n ./run_CPU.sh");
}

void Scene::editFile(){
  system("gedit unicorn/asm_code.asm");
}

void Scene::update()
{
  int mx, my;
  SDL_GetMouseState(&mx, &my);
  msg[0].setColor(0, 0, 0);
  msg[1].setColor(0, 0, 0);
  msg[2].setColor(0, 0, 0);
  msg[3].setColor(0, 0, 0);


  assemblePressed = false;
  exitPressed = false;
  editPressed = false;
  executePressed = false;

  if( (mx >= msg[0].getX()) && (mx <= (msg[0].getX() + msg[0].getW())) )
    if( (my >= msg[0].getY()) && (my <= (msg[0].getY() + msg[0].getH())) )
      {
        msg[0].setColor(255, 0, 0);
        assemblePressed = true;
      }
  if( (mx >= msg[1].getX()) && (mx <= (msg[1].getX() + msg[1].getW())) )
    if( (my >= msg[1].getY()) && (my <= (msg[1].getY() + msg[1].getH())) )
      {
        msg[1].setColor(255, 0, 0);
        exitPressed = true;
      }
  if( (mx >= msg[2].getX()) && (mx <= (msg[2].getX() + msg[2].getW())) )
    if( (my >= msg[2].getY()) && (my <= (msg[2].getY() + msg[2].getH())) )
      {
        msg[2].setColor(255, 0, 0);
        editPressed = true;
      }

  if( (mx >= msg[3].getX()) && (mx <= (msg[3].getX() + msg[3].getW())) )
    if( (my >= msg[3].getY()) && (my <= (msg[3].getY() + msg[3].getH())) )
      {
        msg[3].setColor(255, 0, 0);
        executePressed = true;
      }
      // CPU

}

void Scene::render(SDL_Renderer* Renderer)
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
  msg[3].display(152, 210, 150, 50, Renderer,  "blended");
  SDL_RenderPresent(Renderer);

}

void Scene::loop(SDL_Renderer* Renderer)
{
  while(scene_running)
  {
    SDL_Delay(33);
    checkInput();
    update();
    render(Renderer);
  }

}

void Scene::loadScene(SDL_Renderer* Renderer)
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