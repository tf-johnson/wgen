#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "display.h"
#include "world.h"

int main(int argc, char **argv) {

    bool running = true;
    Display* display = new Display("Hello World!", 800, 600);

    TTile* ttile = new TTile({0,0}, 16, 1024);

    while(running) {
	
	display->Clear();
	
	
	display->Swap();
	
	SDL_Event e;
	while(SDL_PollEvent(&e)) {
	    if(e.type == SDL_QUIT) {
		running = false;
	    }
	    if(e.type == SDL_KEYDOWN) {
		if(e.key.keysym.sym == SDLK_ESCAPE)
		    running = false;
	    }
	}
    }


    return 0;
}
