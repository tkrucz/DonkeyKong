#pragma once
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "structures.h"
#include "define.h"
#include "SDLFunctions.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

void createWindow();

void drawInfo();

void drawScene(Platform* platforms);

void displayWindow(Platform* platforms);

void refreshWindow();

void printGameInfo();

void printPlayerInfo();

void printGround();

void basicSetting();

void playerSettings();

void createColors();

void playerWalking();

void playerClimbing();

void graivityApply(); //checks if Mario is jumping, change his position while jumping

void playerJumping();

void playerMove();

void addPoints(); //function needed only right for test

void jumpOverBarrel();

void endTheStage();

void getTrophy();

void addScore();

void loseLive();

void timeCounting(); //counting the game time

void createPlatforms(Platform* platforms);

void drawPlatforms(Platform* platforms);

void createLadders();

void playerOnLadder(); 

void playerOnPlatform(); 

void playerNoWhere();

void whereIsPLayer(Platform* platforms); 

void SDLSpace();

//Functions definitions

void createWindow() // Create a window with specified size. Also create renderer for this window, renderer meaning a thing actually showing/drawing/rendering stuff
{
	gameInfo.err = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&SDL.window, &SDL.renderer);
	if (gameInfo.err != 0)
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

void drawInfo() {
	printGameInfo();
	printPlayerInfo();
}

//TODO createLadders
void initializeGameObjects(Platform* platforms) {
	createPlatforms(platforms);
}

void drawScene(Platform* platforms) {
	printGround();
	drawPlatforms(platforms);
	createLadders();
}

void displayWindow(Platform* platforms)
{
	SDL_FillRect(SDL.screen, NULL, colors.black); //because FillRect in second parameter has NULL this function fill in the color of the window (into black)
	drawScene(platforms);
	drawInfo();
	DrawSurface(SDL.screen, SDL.player, Mario.upperXCorner + DIFFERENCE_IN_X, Mario.upperYCorner + DIFFERENCE_IN_Y, &Mario.size); //draws the player 
}

void refreshWindow()
{
	SDL_UpdateTexture(SDL.scrtex, NULL, SDL.screen->pixels, SDL.screen->pitch);
	SDL_RenderCopy(SDL.renderer, SDL.scrtex, NULL, NULL);
	SDL_RenderPresent(SDL.renderer);
}

void printGameInfo()
{
	DrawRectangle(SDL.screen, ZERO_COLUMN, FIRST_ROW, SCREEN_WIDTH, 70, colors.white, colors.black);
	sprintf(gameInfo.text, "King Donkey");
	DrawString(SDL.screen, SDL.screen->w / 2 - strlen(gameInfo.text) * 8 / 2, 8, gameInfo.text, SDL.charset);
	sprintf(gameInfo.text, "Time from beginning: %.1lf s", gameInfo.gameTime);
	DrawString(SDL.screen, SDL.screen->w / 2 - strlen(gameInfo.text) * 8 / 2, 25, gameInfo.text, SDL.charset);
	sprintf(gameInfo.text, "Esc - quit, n - new game ");
	DrawString(SDL.screen, SDL.screen->w / 2 - strlen(gameInfo.text) * 8 / 2, 40, gameInfo.text, SDL.charset);
	sprintf(gameInfo.text, "\30 - move up, \31 - move down, \32 - move left, \33 - move right");
	DrawString(SDL.screen, SDL.screen->w / 2 - strlen(gameInfo.text) * 8 / 2, 55, gameInfo.text, SDL.charset);
	sprintf(gameInfo.text, "Author: Tomasz Kruczalak 198049");
	DrawString(SDL.screen, ZERO_COLUMN, AUTHOR_INFO_ROW, gameInfo.text, SDL.charset);
}

void printPlayerInfo()
{
	DrawRectangle(SDL.screen, ZERO_COLUMN, 70, 120, 36, colors.white, colors.black);
	sprintf(gameInfo.text, "Score: %.6d", playerInfo.score);
	DrawString(SDL.screen, TEN_ROW, 75, gameInfo.text, SDL.charset);
	sprintf(gameInfo.text, "Lives: %d", playerInfo.lives);
	DrawString(SDL.screen, TEN_ROW, 90, gameInfo.text, SDL.charset);
	sprintf(gameInfo.text, "LeftUpperXCorner: %d", Mario.upperXCorner);
	DrawString(SDL.screen, TEN_ROW, 150, gameInfo.text, SDL.charset);
	sprintf(gameInfo.text, "LeftUpperYCorner: %d", Mario.upperYCorner);
	DrawString(SDL.screen, TEN_ROW, 170, gameInfo.text, SDL.charset);
}

/*My functions
======================================================================================================*/

void printGround()
{
	DrawLine(SDL.screen, ZERO_COLUMN, GROUND_HEIGHT, SCREEN_WIDTH, 1, 0, colors.white);
}

void basicSetting()
{
	playerInfo.score = PLAYER_START_POINTS;
	playerInfo.lives = PLAYER_LIVES;
	gameInfo.quit = false;
	gameInfo.gameTime = 0;
	playerSettings();
}

void playerSettings()
{
	Mario.upperXCorner = PLAYER_START_X_COORDINATE;
	Mario.upperYCorner = PLAYER_START_Y_COORDINATE;
	//TODO comments
	Mario.size = { DEAFULT_PLAYER_SPRITE_I + MARIO_BMP_DISTANCE, DEAFULT_PLAYER_SPRITE_II ,Mario.realSize[0],Mario.realSize[1] };
	Mario.speedX = WALKING_SPEED;
	Mario.speedY = 0;
	Mario.isJumping = false;
	Mario.onLadder = false;
	Mario.onPlatform = true;
}

void createColors()
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
		Mario.upperXCorner -= Mario.speedX;
	else if (SDL.event.key.keysym.sym == SDLK_RIGHT)
		Mario.upperXCorner += Mario.speedX;
}

void playerClimbing()
{
	if (SDL.event.key.keysym.sym == SDLK_UP)
		Mario.upperYCorner -= CLIMBING_SPEED;
	else if (SDL.event.key.keysym.sym == SDLK_DOWN)
		Mario.upperYCorner += CLIMBING_SPEED;
}

void graivityApply()
{
	if (Mario.isJumping || Mario.fallDown)
	{
		Mario.speedY += GRAVITY_SPEED;
		Mario.upperYCorner += Mario.speedY;
		if (Mario.onPlatform)
		{
			Mario.isJumping = false;
			Mario.fallDown = false;
			Mario.speedY = 0;
		}
	}
}

void playerJumping()
{
	Mario.speedY = -JUMPING_SPEED;
}

void playerMove()
{
	if (Mario.onPlatform)
		playerWalking();
	if (Mario.onLadder)
		playerClimbing();
	if (SDL.event.key.keysym.sym == SDLK_SPACE)
	{
		Mario.onPlatform = false;
		Mario.isJumping = true;
		playerJumping();
	}
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
		gameInfo.quit = true;
	}
}

void timeCounting()
{
	gameInfo.deltaTime = (gameInfo.t2 - gameInfo.t1) * 0.001;
	gameInfo.t1 = gameInfo.t2;
	gameInfo.gameTime += gameInfo.deltaTime;
}

void createPlatforms(Platform* platforms)
{
	int platformsParameters[NUMBER_OF_PLATFORMS][3] = {
		{60,PLATFROM_I_HEIGHT,350}, {520,PLATFROM_I_HEIGHT,160},
		{440,PLATFROM_II_HEIGHT,160}, { 40,PLATFROM_II_HEIGHT,350 },
		{ 480,PLATFROM_III_HEIGHT,200 }, { 340,PLATFROM_III_HEIGHT,80 },
		{ 60,PLATFROM_III_HEIGHT,240 }, { 100,PLATFORM_IV_HEIGHT,240 },
		{ 470,PLATFORM_IV_HEIGHT,240 }, { 280,PLATFORM_V_HEIGHT,160 }
	};

	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++) {
		platforms[i].x = platformsParameters[i][0];
		platforms[i].y = platformsParameters[i][1];
		platforms[i].l = platformsParameters[i][2];
	}
}

void drawPlatforms(Platform* platforms) {

	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
		DrawRectangle(SDL.screen, platforms[i].x, platforms[i].y, platforms[i].l, platforms[i].w, colors.black, colors.pink);

}

//TODO like platforms
void createLadders()
{
	Ladder ladder1 = { 365,PLATFORM_V_HEIGHT };
	DrawRectangle(SDL.screen, ladder1.x, ladder1.y, ladder1.w, 160, colors.black, colors.grey);
	Ladder ladder2 = { 600,PLATFORM_IV_HEIGHT };
	DrawRectangle(SDL.screen, ladder2.x, ladder2.y, ladder2.w, ladder2.h, colors.black, colors.grey);
	Ladder ladder3 = { 150,PLATFROM_III_HEIGHT };
	DrawRectangle(SDL.screen, ladder3.x, ladder3.y, ladder3.w, ladder3.h, colors.black, colors.grey);
	Ladder ladder4 = { 550,PLATFROM_II_HEIGHT };
	DrawRectangle(SDL.screen, ladder4.x, ladder4.y, ladder4.w, ladder4.h, colors.black, colors.grey);
	Ladder ladder5 = { 110,PLATFROM_I_HEIGHT };
	DrawRectangle(SDL.screen, ladder5.x, ladder5.y, ladder5.w, 60, colors.black, colors.grey);
}


void playerOnLadder()
{
	Mario.onLadder = true;
	Mario.onPlatform = false;
}

void playerOnLadderEdge()
{
	Mario.onLadder = true;
	Mario.onPlatform = true;
}

void playerOnPlatform()
{
	Mario.onPlatform = true;
	Mario.onLadder = false;
}

void playerNoWhere()
{
	Mario.onLadder = false;
	Mario.onPlatform = false;
	Mario.fallDown = true;
}

// TODO magic numbers, maybe use platforms array and ladders array
void whereIsPLayer(Platform* platforms)
{

	int leftUpperCorner[2] = { Mario.upperXCorner,Mario.upperYCorner - PLAYER_HEIGHT };
	if ((leftUpperCorner[0] == 110 || leftUpperCorner[0] == 115) && leftUpperCorner[1] == PLATFROM_I_HEIGHT + 60)
		playerOnLadderEdge();
	else if ((leftUpperCorner[0] == 110 || leftUpperCorner[0] == 115) && leftUpperCorner[1] == PLATFROM_I_HEIGHT + 58)
		playerOnLadder();
	else if (leftUpperCorner[1] == 500)
		playerOnPlatform();
	else if (leftUpperCorner[1] == PLATFROM_I_HEIGHT)
		playerOnPlatform();

	//loop for platforms
	/*for (int i = 0; i < PLATFORMS_COUNT; i++) {
		// is mario on platform?
		if (leftUpperCorner[1] == platforms[i].y) {
			// how far from left
			if (platforms[i].x <= leftUpperCorner[0])
				playerOnPlatform();
			else if (platforms[i].x >= leftUpperCorner[0] + PlayerWidth)
				playerOnPlatform();
		}
	}*/

	//loop for ladders
	// ............

}


void SDLSpace() 	//freeing all surfaces
{
	SDL_FreeSurface(SDL.charset);
	SDL_FreeSurface(SDL.screen);
	SDL_DestroyTexture(SDL.scrtex);
	SDL_DestroyRenderer(SDL.renderer);
	SDL_DestroyWindow(SDL.window);
}