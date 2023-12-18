#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "structures.h"
#include "define.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

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

void printWindow()
{
	SDL_FillRect(SDL.screen, NULL, c.black); //because FillRect in second parameter has NULL this function fill in the color of the window (into black)

	DrawSurface(SDL.screen, SDL.eti, p.xCord, p.yCord);
	// info text
	DrawRectangle(SDL.screen, X, Y, SCREEN_WIDTH, 70, c.white, c.black);
	sprintf(g.text, "King Donkey");
	DrawString(SDL.screen, SDL.screen->w / 2 - strlen(g.text) * 8 / 2, 8, g.text, SDL.charset);
	sprintf(g.text, "Time from beginning: %.1lf s", g.gameTime); //"...1lf s, % .0lf klatek / s", worldTime, fps);
	DrawString(SDL.screen, SDL.screen->w / 2 - strlen(g.text) * 8 / 2, 25, g.text, SDL.charset);
	sprintf(g.text, "Esc - quit, n - new game ");
	DrawString(SDL.screen, SDL.screen->w / 2 - strlen(g.text) * 8 / 2, 40, g.text, SDL.charset);
	sprintf(g.text, "\30 - move up, \31 - move down, \32 - move left, \33 - move right");
	DrawString(SDL.screen, SDL.screen->w / 2 - strlen(g.text) * 8 / 2, 55, g.text, SDL.charset);
	sprintf(g.text, "Author: Tomasz Kruczalak 198049");
	DrawString(SDL.screen, X, END_OF_SCREEN_HEIGHT, g.text, SDL.charset);

	//game info
	DrawRectangle(SDL.screen, X, 70, 120, 36, c.white, c.black);
	sprintf(g.text, "Score: %.6d", p.score);
	DrawString(SDL.screen, TEN_ROW, 75, g.text, SDL.charset);
	sprintf(g.text, "Lives: %d", p.lives);
	DrawString(SDL.screen, TEN_ROW, 90, g.text, SDL.charset);

	//draw gorund
	DrawLine(SDL.screen, X, GROUND_HEIGHT, SCREEN_WIDTH, 1, 0, c.white);
}

void createColor()
{
	c.black = SDL_MapRGB(SDL.screen->format, 0x00, 0x00, 0x00);
	c.white = SDL_MapRGB(SDL.screen->format, 255, 255, 255);
	c.blue = SDL_MapRGB(SDL.screen->format, 0x11, 0x11, 0xCC);
	c.green = SDL_MapRGB(SDL.screen->format, 0x00, 0xFF, 0x00);	
	c.red = SDL_MapRGB(SDL.screen->format, 0xFF, 0x00, 0x00);
}

void playerWalking()
{
	if(SDL.event.key.keysym.sym == SDLK_LEFT)
		p.xCord -= WalkingSpeed;
	else if(SDL.event.key.keysym.sym == SDLK_RIGHT)
	p.xCord += WalkingSpeed;
}

void playerClimbing()
{
	if (SDL.event.key.keysym.sym == SDLK_UP)
		p.yCord -= ClimbingSpeed;
	else if (SDL.event.key.keysym.sym == SDLK_DOWN)
	p.yCord += ClimbingSpeed;
}

void playerJumping()  
{
	if (SDL.event.key.keysym.sym == SDLK_SPACE)
	{
		j.beginning = SDL_GetTicks();
		j.duration = j.beginning;
		while(p.yCord<GROUND_HEIGHT)
		{
			p.yCord -= j.velocity - (j.g*j.duration);		
		}
	}		
}

void playerMove() 
{
	playerWalking();
	playerClimbing();
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

bool playerOnLadder() //flaga-na razie nie korzystam
{
	return true;
}

bool playerOnPlatform() //flaga-na razie nie korzystam
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