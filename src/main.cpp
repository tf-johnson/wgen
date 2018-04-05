#include <iostream>

#include "display.h"

int main(int argc, char **argv) {
    bool running = true;
    Display* display = new Display("Hello World!", 800, 600);
    
    while(running) {
      
      display->Clear();
      
      
      display->Swap();
      
      SDL_Event e;
      while(SDL_PollEvent(&e)) {
	if(e.type == SDL_QUIT) {
	  running = false;
	}
      }
    }
    
    delete display;
    
    return 0;
}
