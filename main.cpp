#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "structures.h"
#include "define.h"
#include "functions.h"
#include "functions.cpp"

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
	initializeColors();

	// wy³¹czenie widocznoœci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);	

	SDL.charset = SDL_LoadBMP("./cs8x8.bmp");
	SDL.eti = SDL_LoadBMP("./eti.bmp");
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
	
	char text[128];
	g.t1 = SDL_GetTicks();

	basicSetting();

	while (!g.quit)
	{
		g.t2 = SDL_GetTicks();

		timeCounting();

		SDL_FillRect(SDL.screen, NULL, c.black); //because FillRect in second parameter has NULL this function fill in the color of the window (into black)
		
		DrawSurface(SDL.screen, SDL.eti, p.xCord, p.yCord);
		// info text
		DrawRectangle(SDL.screen, X, Y, SCREEN_WIDTH, 70, c.white, c.black);
		sprintf(text, "King Donkey");
		DrawString(SDL.screen, SDL.screen->w / 2 - strlen(text) * 8 / 2, 8, text, SDL.charset);
		sprintf(text, "Time from beginning: %.1lf s", g.gameTime); //"...1lf s, % .0lf klatek / s", worldTime, fps);
		DrawString(SDL.screen, SDL.screen->w / 2 - strlen(text) * 8 / 2, 25, text, SDL.charset);
		sprintf(text, "Esc - quit, n - new game ");
		DrawString(SDL.screen, SDL.screen->w / 2 - strlen(text) * 8 / 2, 40, text, SDL.charset);
		sprintf(text, "\30 - move up, \31 - move down, \32 - move left, \33 - move right");
		DrawString(SDL.screen, SDL.screen->w / 2 - strlen(text) * 8 / 2, 55, text, SDL.charset);
		sprintf(text, "Author: Tomasz Kruczalak 198049");
		DrawString(SDL.screen, X, END_OF_SCREEN_HEIGHT, text, SDL.charset);

		//game info
		DrawRectangle(SDL.screen, X, 70, 120, 36, c.white, c.black);
		sprintf(text, "Score: %.6d", p.score);
		DrawString(SDL.screen, TEN_ROW, 75, text, SDL.charset);
		sprintf(text, "Lives: %d", p.lives);
		DrawString(SDL.screen, TEN_ROW, 90, text, SDL.charset);

		//draw line
		DrawLine(SDL.screen, X, GROUND_HEIGHT, SCREEN_WIDTH, 1, 0, c.white);

		SDL_UpdateTexture(SDL.scrtex, NULL, SDL.screen->pixels, SDL.screen->pitch);
		//  	  SDL_RenderClear(renderer);
		SDL_RenderCopy(SDL.renderer, SDL.scrtex, NULL, NULL);
		SDL_RenderPresent(SDL.renderer);

		// obs³uga zdarzeñ (o ile jakieœ zasz³y) / handling of events (if there were any)
		while (SDL_PollEvent(&SDL.event))
		{
			switch (SDL.event.type)
			{
			case SDL_KEYDOWN:
				if (SDL.event.key.keysym.sym == SDLK_ESCAPE) //if Esc pressed then g.quit=1  so that ending the loop
					g.quit = 1;
				else if (SDL.event.key.keysym.sym == SDLK_n)
					basicSetting();
				else if (SDL.event.key.keysym.sym == SDLK_p)
					addPoints();
				else if (SDL.event.key.keysym.sym == SDLK_l)
					loseLive();
				else if (SDL.event.key.keysym.sym == SDLK_LEFT)
					p.xCord -= 1;
				else if (SDL.event.key.keysym.sym == SDLK_RIGHT)
					p.xCord += 1;
				else if (SDL.event.key.keysym.sym == SDLK_UP)
					p.yCord -= 1;
				else if (SDL.event.key.keysym.sym == SDLK_DOWN)
					p.yCord += 1;
				break;
			case SDL_QUIT: //X button in right up corner
				g.quit = 1;
				break;
			}
		}
	}

	freeSpace();
	SDL_Quit();
	return 0;
}
