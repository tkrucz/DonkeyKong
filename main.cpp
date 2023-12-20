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

//TODO main do mainGameLoop()
int main(int argc, char** argv) {	

	createWindow();
	createColor();

	//TODO 28-39 loadBMPS() 
	SDL_ShowCursor(SDL_DISABLE);	

	SDL.charset = SDL_LoadBMP("./BMP/cs8x8.bmp");
	SDL.player = SDL_LoadBMP("./BMP/mario.bmp");
	if (SDL.charset == NULL)
	{
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(SDL.screen);
		SDL_DestroyTexture(SDL.scrtex);
		SDL_DestroyWindow(SDL.window);
		SDL_DestroyRenderer(SDL.renderer);
		SDL_Quit();
		return 1;
	}

	gameInfo.t1 = SDL_GetTicks();
	basicSetting();



	while (!gameInfo.quit)
	{
		Platform platforms[NUMBER_OF_PLATFORMS];
		gameInfo.t2 = SDL_GetTicks();

		timeCounting();
		initializeGameObjects(platforms);
		displayWindow(platforms);
		refreshWindow();		

		graivityApply();
		whereIsPLayer(platforms);

		// TODO 57 -> 78 readKeys() 
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
