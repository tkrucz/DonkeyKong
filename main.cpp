#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

//REMEMBER: GET RID OF MAGIC NUMBERS !!!

#define SCREEN_WIDTH	720
#define SCREEN_HEIGHT	520
#define SECONDS_BETWEEN_REFRESH 0.5
#define REFRESH_RATE 1/SECONDS_BETWEEN_REFRESH

#define X 0
#define Y 1
#define playerX 300
#define playerY 400
#define TEN_ROW 10
#define END_OF_SCREEN_HEIGHT SCREEN_HEIGHT - 12
#define GROUND_HEIGHT SCREEN_HEIGHT - 20

struct PlayerInfo
{
	int score;
	int lives;
	int xCord, yCord;//coordinates
}p;

struct GameInfo
{
	int t1, t2;
	double gameTime, deltaTime;
	int quit;
	int err;
}g;

struct Score 
{
	int jumpOverBarrel = 500;
	int getTrophy = 1000;
	int endTheStage = 10000;
}s;

struct SDLConst
{
	SDL_Event event;
	SDL_Surface* screen, * charset;
	SDL_Surface* eti;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;
}SDL;

struct Colors
{
	int black;
	int white;
	int green;
	int red;
	int blue;
	int purple;
}c;

// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset)
{
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text)
	{
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	}
}

// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
// "sprite" meaning an asset/image or a part of it
void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y)
{
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
}

// draw a single pixel
void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color)
{
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
}



// draw vertical or horizontal line
// vertical (when dx = 0, dy = 1), horizontal (when dx = 1, dy = 0)
void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color)
{
	for (int i = 0; i < l; i++)
	{
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	}
}

// draw a rectangle of size l and k (l-length, k-width)
void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor)
{
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
	{
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
	}
}

//My functions

void basicSetting()
{
	p.score = 0;
	p.lives = 3;
	p.xCord = playerX;
	p.yCord = playerY;
	g.quit = 0;
	g.gameTime = 0;
}

void createWindow() // Create a window with specified size. Also create renderer for this window, renderer meaning a thing actually showing/drawing/rendering stuff
{
	g.err = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&SDL.window, &SDL.renderer);
	if (g.err != 0)
	{
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());	
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(SDL.renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(SDL.renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(SDL.window, "Tomasz Kruczalak 198049");

	SDL.screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	SDL.scrtex = SDL_CreateTexture(SDL.renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);
}

void initializeColors()
{
	c.black = SDL_MapRGB(SDL.screen->format, 0x00, 0x00, 0x00);
	c.white = SDL_MapRGB(SDL.screen->format, 255, 255, 255);
	c.blue = SDL_MapRGB(SDL.screen->format, 0x11, 0x11, 0xCC);
	c.green = SDL_MapRGB(SDL.screen->format, 0x00, 0xFF, 0x00);
	c.purple = SDL_MapRGB(SDL.screen->format, 154, 169, 217);
	c.red = SDL_MapRGB(SDL.screen->format, 0xFF, 0x00, 0x00);
}

void playerMove() //Zrobić jakoś
{
	
}

void addPoints()
{
	p.score += 10;
}

void jumpOverBarrel()
{
	p.score += s.jumpOverBarrel;
}

void endTheStage()
{
	p.score += s.endTheStage;
}

void getTrophy()
{
	p.score += s.getTrophy;
}

void addScore()
{
	jumpOverBarrel();
	getTrophy();
	endTheStage();
}

void loseLive()
{
	p.lives -= 1;
	if (p.lives == 0)
	{
		g.quit = 1;
	}
}

void timeCounting() //counting the game time
{
	g.deltaTime = (g.t2 - g.t1) * 0.001;
	g.t1 = g.t2;
	g.gameTime += g.deltaTime;
}

bool playerOnLadder() //na razie nie korzystam
{
	return true;
}

bool playerOnPlatform() //na razie nie korzystam
{
	return true;
}

void whereIsPLayer() //na razie nie korzystam
{

}

void freeSpace() 	//freeing all surfaces
{
	SDL_FreeSurface(SDL.charset);
	SDL_FreeSurface(SDL.screen);
	SDL_DestroyTexture(SDL.scrtex);
	SDL_DestroyRenderer(SDL.renderer);
	SDL_DestroyWindow(SDL.window);
}
// main
#ifdef __cplusplus
extern "C"
#endif

int main(int argc, char** argv) {	

	createWindow();
	initializeColors();

	// wyłączenie widoczności kursora myszy
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

		// obsługa zdarzeń (o ile jakieś zaszły) / handling of events (if there were any)
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
