#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "ImportantFiles/define.h"
#include"ImportantFiles/functions.h"
#include "ImportantFiles/functions.cpp"
#include "ImportantFiles/structures.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
// main
#ifdef __cplusplus
extern "C"
#endif

int main(int argc, char** argv) {	

	createWindow();
	createColor();

	// wy≥πczenie widocznoúci kursora myszy
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
		gameInfo.t2 = SDL_GetTicks();

		timeCounting();
		printWindow();

		SDL_UpdateTexture(SDL.scrtex, NULL, SDL.screen->pixels, SDL.screen->pitch);
		//  	  SDL_RenderClear(renderer);
		SDL_RenderCopy(SDL.renderer, SDL.scrtex, NULL, NULL);
		SDL_RenderPresent(SDL.renderer);

		graivityApply();

		// obs≥uga zdarzeÒ (o ile jakieú zasz≥y) / handling of events (if there were any)
		while (SDL_PollEvent(&SDL.event))
		{
			switch (SDL.event.type)
			{
			case SDL_KEYDOWN:
				whereIsPLayer(); //èLE YUP?
				if (SDL.event.key.keysym.sym == SDLK_ESCAPE) //if Esc pressed then g.quit=1  so that ending the loop
					gameInfo.quit = 1;
				else if (SDL.event.key.keysym.sym == SDLK_n)
					basicSetting();
				else if (SDL.event.key.keysym.sym == SDLK_p)
					addPoints();
				else if (SDL.event.key.keysym.sym == SDLK_l)
					loseLive();
				else if ((playerOnGround() || playerOnPlatform()) && (SDL.event.key.keysym.sym == SDLK_LEFT || SDL.event.key.keysym.sym == SDLK_RIGHT))
					playerWalking();
				else if (playerOnLadder() && (SDL.event.key.keysym.sym == SDLK_UP || SDL.event.key.keysym.sym == SDLK_DOWN))
					playerClimbing();
				else if (SDL.event.key.keysym.sym == SDLK_SPACE)
				{
					Mario.isJumping = true;
					playerJumping();
				}
				break;		
			case SDL_QUIT: //X button in right up corner
				gameInfo.quit = 1;
				break;
			}
		}
	}

	freeSpace();
	SDL_Quit();
	return 0;
}
