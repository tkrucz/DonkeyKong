#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "ImportantFiles/define.h"
#include"ImportantFiles/functions.h"
#include "ImportantFiles/structures.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
// main
#ifdef __cplusplus
extern "C"
#endif

//TODO main to mainGameLoop()
int main(int argc, char** argv) {
	Platform platforms[NUMBER_OF_PLATFORMS];
	Ladder ladders[NUMBERS_OF_LADDERS];

	SDL_ShowCursor(SDL_DISABLE);

	createWindow();
	createColors();
	loadBMPs();
	basicSetting();
	initializeGameObjects(platforms, ladders);

	gameInfo.t1 = SDL_GetTicks();

	while (!gameInfo.quit)
	{
		gameInfo.t2 = SDL_GetTicks();
		timeCounting();

		displayWindow(platforms, ladders);
		refreshWindow();

		graivityApply();
		whereIsPLayer(platforms, ladders);

		readKeys();
	}

	SDLSpace();
	SDL_Quit();
	return 0;
}