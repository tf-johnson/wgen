#include "display.h"

Display::Display(const std::string& title, int width, int height)
{
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "\e[31m" << "Error: Could not initialize SDL." << "\e[0m" << std::endl;
    std::cout << "\e[31m" << "Aborting program - Failed to initialize SDL." << "\e[0m" << std::endl;
  } else {
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
  
    window = SDL_CreateWindow("WGen Display", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    if(window == NULL) {
      std::cerr << "\e[31m" << "Error: Could not create a window." << "\e[0m" << std::endl;
      std::cout << "\e[31m" << "Aborting program - Failed to create SDL Window." << "\e[0m" << std::endl;
    } else {
      context = SDL_GL_CreateContext(window);
      if(context == NULL) {
	std::cerr << "\e[31m" << "Error: Could not give window a GL Context." << "\e[0m" << std::endl;
	std::cout << "\e[31m" << "Aborting program - Failed to give window a gl context." << "\e[0m" << std::endl;
      } else {
	GLenum glewRes = glewInit();
	if(glewRes != GLEW_OK) {
	  std::cerr << "\e[31m" << "Error: Could not initialize GLEW." << "\e[0m" << std::endl;
	  std::cout << "\e[31m" << "Aborting program - Failed to initialize GLEW." << "\e[0m" << std::endl;
	} else {
	  std::cout  << "\e[32m" << "Display '" << title << "' created." << "\e[0m" << std::endl;
	  Clear();
	}
      }
    }
  }
}

Display::~Display()
{
  if(context) SDL_GL_DeleteContext(context);
  if(window) SDL_DestroyWindow(window);
  SDL_Quit();
}

void Display::Clear(float r, float g, float b, float a)
{
  float col[4] = {r, g, b, a};
  Clear(col);
}

void Display::Clear(float* rgba)
{
  glClearColor(rgba[0], rgba[1], rgba[2], rgba[3]);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::Clear()
{
  Clear(&color[0]);
}

float* Display::getColor()
{
  return &color[0];
}

void Display::setColor(float r, float g, float b, float a)
{
  color[0] = r;
  color[1] = g;
  color[2] = b;
  color[3] = a;
}

void Display::setColor(float* rgba)
{
  
  color[0] = rgba[0];
  color[1] = rgba[1];
  color[2] = rgba[2];
  color[3] = rgba[3];
}

void Display::Swap()
{
  SDL_GL_SwapWindow(window);
}
