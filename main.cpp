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
	Ladder ladders[NUMBER_OF_LADDERS];
	Barrel barrels[NUMBER_OF_BARRELS];
	Trophy trophies[NUMBER_OF_TROPHIES];
	PlayerInfo playerInfo;
	GameInfo gameInfo;
	Color colors;
	Score score;

	SDL_ShowCursor(SDL_DISABLE);

	createWindow(&gameInfo);
	initializeColors(&colors);
	loadBMPs();
	basicSettings(&gameInfo, &playerInfo);
	initializeGameObjects(platforms, ladders, barrels,trophies);

	gameInfo.t1 = SDL_GetTicks();

	while (!gameInfo.quit)
	{
		gameInfo.t2 = SDL_GetTicks();
		timeCounting(&gameInfo);

		displayWindow(&gameInfo, &playerInfo, &colors, platforms, ladders, barrels,trophies);
		refreshWindow();

		readKeys(&gameInfo, &playerInfo, &score);

		gravityApply(&gameInfo, &playerInfo, &score, platforms, barrels, trophies);
		whereAreObjects(platforms, ladders, barrels);
		moveObjects(barrels);
	}
	return 0;
}
