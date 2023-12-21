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

	createWindow();
	createColors();

	SDL_ShowCursor(SDL_DISABLE);

	loadBMPs();

	gameInfo.t1 = SDL_GetTicks();
	basicSetting();



	while (!gameInfo.quit)
	{
		Platform platforms[NUMBER_OF_PLATFORMS];
		Ladder ladders[NUMBERS_OF_LADDERS];
		gameInfo.t2 = SDL_GetTicks();

		timeCounting();
		initializeGameObjects(platforms,ladders);
		displayWindow(platforms,ladders);
		refreshWindow();		

		graivityApply();
		whereIsPLayer(platforms);

		// TODO 48 -> 69 readKeys() 
		// obs³uga zdarzeñ (o ile jakieœ zasz³y) / handling of events (if there were any)
		while (SDL_PollEvent(&SDL.event))
		{
			switch (SDL.event.type)
			{
			case SDL_KEYDOWN:				
				if (SDL.event.key.keysym.sym == SDLK_ESCAPE) //if Esc pressed then g.quit=1  so that ending the loop
					gameInfo.quit = true;
				else if (SDL.event.key.keysym.sym == SDLK_n)
					basicSetting();
				else if (SDL.event.key.keysym.sym == SDLK_p)
					addPoints();
				else if (SDL.event.key.keysym.sym == SDLK_l)
					loseLive();
				else if (Mario.onPlatform || Mario.onLadder)
					playerMove();		
				break;		
			case SDL_QUIT: //X button in right up corner
				gameInfo.quit = true;
				break;
			}
		}
	}

	SDLSpace();
	SDL_Quit();
	return 0;
}
