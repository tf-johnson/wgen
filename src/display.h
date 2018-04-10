#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>

class Display
{
public:
  Display(const std::string& title, int width, int height);
  virtual ~Display();
  
  void Clear(); //uses Display::color
  void Clear(float* rgba);
  void Clear(float r, float g, float b, float a);
  
  float* getColor();
  void setColor(float* rgba);
  void setColor(float r, float g, float b, float a);

  void Swap();
private:
  SDL_Window* window;
  SDL_GLContext context;
  float color[4];
};

#endif