#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "ImportantFiles/Define.h"
#include "ImportantFiles/Structures.h"
#include "ImportantFiles/GameStructure.h"
#include "ImportantFiles/GeneralFunctions.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
// main
#ifdef __cplusplus
extern "C"
#endif

int main(int argc, char** argv) {
	SDLConst SDL;
	Color colors;
	Score score;
	ShowText showText;
	Animator animator;
	
	Stage stage;

	StageSpecifier specifier;
	Game game;

	specifier = stage.stageSpecifier;
	//stage = whichStage(&stage, &game);
	SDL_ShowCursor(SDL_DISABLE);

	createWindow(&stage, &SDL);
	initializeColors(&SDL, &colors);
	loadBMPs(&SDL);
	defaultSettings(&stage);
	initializeGameObjects(&stage, &animator);

	stage.gameInfo.t1 = SDL_GetTicks();

	while (!stage.gameInfo.quit)
	{
		stage.gameInfo.t2 = SDL_GetTicks();
		timeCounting(&stage);

		refreshWindow(&SDL);
		displayWindow(&stage, &SDL, &colors);
		
		readKeys(&stage, &SDL, &score, &animator);

		gravityApply(&stage);
		whereAreObjects(&stage, &SDL, &score, &showText);
		moveObjects(&stage, &SDL, &animator);
	}
	return 0;
}
