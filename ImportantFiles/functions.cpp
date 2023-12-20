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

void createWindow() // Create a window with specified size. Also create renderer for this window, renderer meaning a thing actually showing/drawing/rendering stuff
{
	gameInfo.err = SDL_CreateWindowAndRenderer(ScreenWidth, ScreenHeight, 0,
		&SDL.window, &SDL.renderer);
	if (gameInfo.err != 0)
	{
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(SDL.renderer, ScreenWidth, ScreenHeight);
	SDL_SetRenderDrawColor(SDL.renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(SDL.window, "Tomasz Kruczalak 198049");

	SDL.screen = SDL_CreateRGBSurface(0, ScreenWidth, ScreenHeight, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	SDL.scrtex = SDL_CreateTexture(SDL.renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		ScreenWidth, ScreenHeight);
}

void printWindow()
{
	SDL_FillRect(SDL.screen, NULL, colors.black); //because FillRect in second parameter has NULL this function fill in the color of the window (into black)
	DrawSurface(SDL.screen, SDL.eti, Mario.upperXCorner, Mario.upperYCorner); //draws the player(eti)
	printGameInfo();
	printPlayerInfo();
	printGround();
	createPlatforms();
	createLadders();
}

void printGameInfo()
{
	DrawRectangle(SDL.screen, ZeroColumn, FirstRow, ScreenWidth, 70, colors.white, colors.black);
	sprintf(gameInfo.text, "King Donkey");
	DrawString(SDL.screen, SDL.screen->w / 2 - strlen(gameInfo.text) * 8 / 2, 8, gameInfo.text, SDL.charset);
	sprintf(gameInfo.text, "Time from beginning: %.1lf s", gameInfo.gameTime);
	DrawString(SDL.screen, SDL.screen->w / 2 - strlen(gameInfo.text) * 8 / 2, 25, gameInfo.text, SDL.charset);
	sprintf(gameInfo.text, "Esc - quit, n - new game ");
	DrawString(SDL.screen, SDL.screen->w / 2 - strlen(gameInfo.text) * 8 / 2, 40, gameInfo.text, SDL.charset);
	sprintf(gameInfo.text, "\30 - move up, \31 - move down, \32 - move left, \33 - move right");
	DrawString(SDL.screen, SDL.screen->w / 2 - strlen(gameInfo.text) * 8 / 2, 55, gameInfo.text, SDL.charset);
	sprintf(gameInfo.text, "Author: Tomasz Kruczalak 198049");
	DrawString(SDL.screen, ZeroColumn, AuhtorInfoRow, gameInfo.text, SDL.charset);
}

void printPlayerInfo()
{
	DrawRectangle(SDL.screen, ZeroColumn, 70, 120, 36, colors.white, colors.black);
	sprintf(gameInfo.text, "Score: %.6d", playerInfo.score);
	DrawString(SDL.screen, TenRow, 75, gameInfo.text, SDL.charset);
	sprintf(gameInfo.text, "Lives: %d", playerInfo.lives);
	DrawString(SDL.screen, TenRow, 90, gameInfo.text, SDL.charset);
}

/*My functions
======================================================================================================*/

void printGround()
{
	DrawLine(SDL.screen, ZeroColumn, GroundHeight, ScreenWidth, 1, 0, colors.white);
}

void basicSetting()
{
	playerInfo.score = 0;
	playerInfo.lives = 3;
	gameInfo.quit = 0;
	gameInfo.gameTime = 0;
	Mario.upperXCorner = PlayerStartXCoordinate;
	Mario.upperYCorner = PlayerStartYCoordinate;
}

void createColor()
{
	colors.black = SDL_MapRGB(SDL.screen->format, 0x00, 0x00, 0x00);
	colors.white = SDL_MapRGB(SDL.screen->format, 255, 255, 255);
	colors.blue = SDL_MapRGB(SDL.screen->format, 0x11, 0x11, 0xCC);
	colors.green = SDL_MapRGB(SDL.screen->format, 0x00, 0xFF, 0x00);
	colors.red = SDL_MapRGB(SDL.screen->format, 0xFF, 0x00, 0x00);
	colors.pink = SDL_MapRGB(SDL.screen->format, 214, 136, 150);
	colors.indygo = SDL_MapRGB(SDL.screen->format, 85, 120, 200);
	colors.lime = SDL_MapRGB(SDL.screen->format, 152, 190, 100);
	colors.grey = SDL_MapRGB(SDL.screen->format, 160, 160, 160);
}

void playerWalking()
{
	if (SDL.event.key.keysym.sym == SDLK_LEFT)
		Mario.upperXCorner -= WalkingSpeed;
	else if (SDL.event.key.keysym.sym == SDLK_RIGHT)
		Mario.upperXCorner += WalkingSpeed;
}

void playerClimbing()
{
	if (SDL.event.key.keysym.sym == SDLK_UP)
		Mario.upperYCorner -= ClimbingSpeed;
	else if (SDL.event.key.keysym.sym == SDLK_DOWN)
		Mario.upperYCorner += ClimbingSpeed;
}

void playerJumping()
{
	if (SDL.event.key.keysym.sym == SDLK_SPACE)
	{
		
	}
}

void playerMove()
{
	playerWalking();
	playerClimbing();
}

void addPoints()
{
	playerInfo.score += 10;
}

void jumpOverBarrel()
{
	playerInfo.score += score.jumpOverBarrel;
}

void endTheStage()
{
	playerInfo.score += score.endTheStage;
}

void getTrophy()
{
	playerInfo.score += score.getTrophy;
}

void addScore()
{
	jumpOverBarrel();
	getTrophy();
	endTheStage();
}

void loseLive()
{
	playerInfo.lives -= 1;
	if (playerInfo.lives == 0)
	{
		gameInfo.quit = 1;
	}
}

void timeCounting() //counting the game time
{
	gameInfo.deltaTime = (gameInfo.t2 - gameInfo.t1) * 0.001;
	gameInfo.t1 = gameInfo.t2;
	gameInfo.gameTime += gameInfo.deltaTime;
}

void createPlatforms()
{
	Platform platorm1 = { 60,Platform_I_Height,350 };
	DrawRectangle(SDL.screen, platorm1.x, platorm1.y, platorm1.l, platorm1.w, colors.black, colors.pink);
	Platform platorm2 = {520,Platform_I_Height,160 };
	DrawRectangle(SDL.screen, platorm2.x, platorm2.y, platorm2.l, platorm2.w, colors.black, colors.pink);
	Platform platorm3 = { 440,Platform_II_Height,160 };
	DrawRectangle(SDL.screen, platorm3.x, platorm3.y, platorm3.l, platorm3.w, colors.black, colors.pink);
	Platform platorm4 = { 40,Platform_II_Height,350 };
	DrawRectangle(SDL.screen, platorm4.x, platorm4.y, platorm4.l, platorm4.w, colors.black, colors.pink);
	Platform platorm5 = { 480,Platform_III_Height,200 };
	DrawRectangle(SDL.screen, platorm5.x, platorm5.y, platorm5.l, platorm5.w, colors.black, colors.pink);
	Platform platorm6 = { 340,Platform_III_Height,80 };
	DrawRectangle(SDL.screen, platorm6.x, platorm6.y, platorm6.l, platorm6.w, colors.black, colors.pink);
	Platform platorm7 = { 60,Platform_III_Height,240 };
	DrawRectangle(SDL.screen, platorm7.x, platorm7.y, platorm7.l, platorm7.w, colors.black, colors.pink);
	Platform platorm8 = { 100,Platform_IV_Height,240 };
	DrawRectangle(SDL.screen, platorm8.x, platorm8.y, platorm8.l, platorm8.w, colors.black, colors.pink);
	Platform platorm9 = { 470,Platform_IV_Height,240 };
	DrawRectangle(SDL.screen, platorm9.x, platorm9.y, platorm9.l, platorm9.w, colors.black, colors.pink);
	Platform platorm10 = { 280,Platform_V_Height,160 };
	DrawRectangle(SDL.screen, platorm10.x, platorm10.y, platorm10.l, platorm10.w, colors.black, colors.pink);

}

void createLadders()
{
	Ladder ladder1 = {365,Platform_V_Height};
	DrawRectangle(SDL.screen, ladder1.x, ladder1.y, ladder1.w, 160, colors.black, colors.grey);
	Ladder ladder2 = { 600,Platform_IV_Height };
	DrawRectangle(SDL.screen, ladder2.x, ladder2.y, ladder2.w, ladder2.h, colors.black, colors.grey);
	Ladder ladder3 = { 150,Platform_III_Height };
	DrawRectangle(SDL.screen, ladder3.x, ladder3.y, ladder3.w, ladder3.h, colors.black, colors.grey);
	Ladder ladder4 = { 550,Platform_II_Height };
	DrawRectangle(SDL.screen, ladder4.x, ladder4.y, ladder4.w, ladder4.h, colors.black, colors.grey);
	Ladder ladder5 = { 110,Platform_I_Height };
	DrawRectangle(SDL.screen, ladder5.x, ladder5.y, ladder5.w, 60, colors.black, colors.grey);
}


bool playerOnLadder() //flaga-na razie nie korzystam
{
	return true;
}

bool playerOnPlatform() //flaga-na razie nie korzystam
{
	return true;
}

bool playerOnGround() //flaga-na razie nie korzystam
{
	return true;
}

void whereIsPLayer() //na razie nie korzystam
{
	int leftUpperCorner[2] = { Mario.upperXCorner,Mario.upperYCorner };
	int rightLowerCorner[2] = { Mario.upperXCorner + PlayerWidth,Mario.upperYCorner + PlayerHeight };
	if (rightLowerCorner[1] == GroundHeight)
		playerOnGround();
	else if (leftUpperCorner[0] == 110 && leftUpperCorner[1] == Platform_I_Height + 60)
		playerOnLadder();
	else if (rightLowerCorner[1] == Platform_I_Height)
		playerOnPlatform();
}

void freeSpace() 	//freeing all surfaces
{
	SDL_FreeSurface(SDL.charset);
	SDL_FreeSurface(SDL.screen);
	SDL_DestroyTexture(SDL.scrtex);
	SDL_DestroyRenderer(SDL.renderer);
	SDL_DestroyWindow(SDL.window);
}