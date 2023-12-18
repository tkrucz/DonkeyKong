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
	double worldTime, deltaTime;
	int quit;
	int err;
}g;

struct Score 
{
	int jumpOverBarrel = 500;
	int getTrophy = 1000;
	int endTheStage = 10000;
}s;

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
	g.worldTime = 0;
}

void playerMove() //Zrobiæ jakoœ
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

void timeCounting()
{
	g.deltaTime = (g.t2 - g.t1) * 0.001;
	g.t1 = g.t2;
	g.worldTime += g.deltaTime;
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
// main
#ifdef __cplusplus
extern "C"
#endif

int main(int argc, char** argv) {		
	SDL_Event event;
	SDL_Surface* screen, * charset;
	SDL_Surface* eti;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;

	// Create a window with specified size
	// Also create renderer for this window, renderer meaning a thing actually showing/drawing/rendering stuff

	g.err = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&window, &renderer);
	if (g.err != 0)
	{
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Tomasz Kruczalak 198049");

	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);

	// wy³¹czenie widocznoœci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);	

	charset = SDL_LoadBMP("./cs8x8.bmp");
	eti = SDL_LoadBMP("./eti.bmp");
	if (charset == NULL)
	{
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}	
	
	char text[128];
	int black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int white = SDL_MapRGB(screen->format, 255, 255, 255);
	int green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int blue = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	int purple = SDL_MapRGB(screen->format, 154, 169, 217);

	g.t1 = SDL_GetTicks();

	basicSetting();

	while (!g.quit)
	{
		g.t2 = SDL_GetTicks();

		timeCounting();

		SDL_FillRect(screen, NULL, black); //because FillRect in second parameter has NULL this function fill in the color of the window (into black)
		
		DrawSurface(screen, eti, p.xCord, p.yCord);
		// info text
		DrawRectangle(screen, X, Y, SCREEN_WIDTH, 70, white, black);
		sprintf(text, "King Donkey");
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 8, text, charset);
		sprintf(text, "Time from beginning: %.1lf s", g.worldTime); //"...1lf s, % .0lf klatek / s", worldTime, fps);
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 25, text, charset);
		sprintf(text, "Esc - quit, n - new game ");
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 40, text, charset);
		sprintf(text, "\30 - move up, \31 - move down, \32 - move left, \33 - move right");
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 55, text, charset);
		sprintf(text, "Author: Tomasz Kruczalak 198049");
		DrawString(screen, X, END_OF_SCREEN_HEIGHT, text, charset);

		//game info
		DrawRectangle(screen, X, 70, 120, 36, white, black);
		sprintf(text, "Score: %.6d", p.score);
		DrawString(screen, TEN_ROW, 75, text, charset);
		sprintf(text, "Lives: %d", p.lives);
		DrawString(screen, TEN_ROW, 90, text, charset);

		//draw line
		DrawLine(screen, X, GROUND_HEIGHT, SCREEN_WIDTH, 1, 0, white);

		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		//  	  SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);

		// obs³uga zdarzeñ (o ile jakieœ zasz³y) / handling of events (if there were any)
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) //if Esc pressed then g.quit=1  so that ending the loop
					g.quit = 1;
				else if (event.key.keysym.sym == SDLK_n)
					basicSetting();
				else if (event.key.keysym.sym == SDLK_p)
					addPoints();
				else if (event.key.keysym.sym == SDLK_l)
					loseLive();
				else if (event.key.keysym.sym == SDLK_LEFT)
					p.xCord -= 1;
				else if (event.key.keysym.sym == SDLK_RIGHT)
					p.xCord += 1;
				else if (event.key.keysym.sym == SDLK_UP)
					p.yCord -= 1;
				else if (event.key.keysym.sym == SDLK_DOWN)
					p.yCord += 1;
				break;
			case SDL_QUIT: //X button in right up corner
				g.quit = 1;
				break;
			}
		}
	}

	// zwolnienie powierzchni / freeing all surfaces
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}
