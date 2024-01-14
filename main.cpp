#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "ImportantFiles/Define.h"
#include "ImportantFiles/Structures.h"
#include "ImportantFiles/GeneralFunctions.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

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

	SDL_ShowCursor(SDL_DISABLE);

	createWindow(&stage, &SDL);
	initializeColors(&SDL, &colors);
	validation(&SDL);
	defaultSettings(&stage, &SDL);
	initializeGameObjects(&stage, &SDL, &animator, &colors);

	stage.gameInfo.t1 = SDL_GetTicks();

	while (!stage.gameInfo.quit)
	{
		stage.gameInfo.t2 = SDL_GetTicks();
		timeCounting(&stage);

		refreshWindow(&SDL);
		displayWindow(&stage, &SDL, &animator, &colors, &score);
		
		readKeys(&stage, &SDL, &animator, &colors, &score);

		gravityApply(&stage);
		whereAreObjects(&stage, &SDL, &score, &showText);
		moveObjects(&stage, &SDL, &animator);
	}
	return 0;
}