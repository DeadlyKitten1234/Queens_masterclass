#include "SDL.h"
#include "World.h"
#include <ctime>

#undef main

World world;
/*  TODO:
	Make the AI work
*/
int main(int argc, char* argv[]) {
	srand(time(0));

	world.init();
	while (1) {
		world.update();
		if (world.exit()) {
			break;
		}
		world.draw();
		SDL_Delay(20);
	}

	return 0;
}