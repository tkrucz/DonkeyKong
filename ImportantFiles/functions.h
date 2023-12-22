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

void drawScene(Platform* platforms, Ladder* ladders);

void displayWindow(Platform* platforms, Ladder* ladders);

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

void playerFallDown();

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

void createLadders(Ladder* ladders);

void drawLadders(Ladder* ladders);

void playerOnLadder();

void playerOnPlatform();

void playerNoWhere();

void isPlayerOnLadder(Ladder* ladders);

void isPlayerOnPlatform(Platform* platforms);

void whereIsPLayer(Platform* platforms, Ladder* ladders);

void SDLSpace();

void readKeys();

void quit();

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

void initializeGameObjects(Platform* platforms, Ladder* ladders) {
	createPlatforms(platforms);
	createLadders(ladders);
}

void drawScene(Platform* platforms, Ladder* ladders) {
	printGround();
	drawPlatforms(platforms);
	drawLadders(ladders);
}

void displayWindow(Platform* platforms, Ladder* ladders)
{
	SDL_FillRect(SDL.screen, NULL, colors.black); //because FillRect in second parameter has NULL this function fill in the color of the window (into black)
	drawScene(platforms, ladders);
	drawInfo();
	DrawSurface(SDL.screen, SDL.player, Mario.lowerXCorner + DIFFERENCE_IN_X, Mario.lowerYCorner + DIFFERENCE_IN_Y, &Mario.animation); //draws the player 
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
	sprintf(gameInfo.text, "LeftLowerXCorner: %d", Mario.lowerXCorner);
	DrawString(SDL.screen, TEN_ROW, 150, gameInfo.text, SDL.charset);
	sprintf(gameInfo.text, "LeftLowerYCorner: %d", Mario.lowerYCorner);
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
	Mario.lowerXCorner = PLAYER_START_X_COORDINATE;
	Mario.lowerYCorner = PLAYER_START_Y_COORDINATE;
	//TODO comments
	Mario.animation = { DEAFULT_PLAYER_SPRITE_I + MARIO_BMP_DISTANCE, DEAFULT_PLAYER_SPRITE_II ,Mario.realSize[0],Mario.realSize[1] };
	Mario.speedX = WALKING_SPEED;
	Mario.speedY = 0;
	playerOnPlatform();
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
		Mario.lowerXCorner -= Mario.speedX;
	else if (SDL.event.key.keysym.sym == SDLK_RIGHT)
		Mario.lowerXCorner += Mario.speedX;
}

void playerClimbing()
{
	if (SDL.event.key.keysym.sym == SDLK_UP)
		Mario.lowerYCorner -= CLIMBING_SPEED;
	else if (SDL.event.key.keysym.sym == SDLK_DOWN)
		Mario.lowerYCorner += CLIMBING_SPEED;
}

void graivityApply()
{
	if (Mario.isJumping || Mario.fallDown)
	{
		Mario.speedY += GRAVITY_SPEED;
		Mario.lowerYCorner += Mario.speedY;
		if (Mario.onPlatform || Mario.lowerYCorner == GROUND_HEIGHT)
		{
			Mario.isJumping = false;
			Mario.fallDown = false;
			Mario.speedY = 0;
		}
	}
}

void playerJumping()
{
	Mario.onPlatform = false;
	Mario.onLadder = false;
	Mario.isJumping = true;
	Mario.speedY = -JUMPING_SPEED;	
}

void playerFallDown()
{
	graivityApply();
}

void playerMove()
{
	if (Mario.onPlatform)
		playerWalking();
	if (Mario.onLadder)
		playerClimbing();
	if (SDL.event.key.keysym.sym == SDLK_SPACE)
		playerJumping();
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
		quit();
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
		{60,PLATFORM_I_HEIGHT,350}, {520,PLATFORM_I_HEIGHT,160},
		{440,PLATFORM_II_HEIGHT,160}, { 40,PLATFORM_II_HEIGHT,350 },
		{ 480,PLATFORM_III_HEIGHT,200 }, { 340,PLATFORM_III_HEIGHT,80 },
		{ 60,PLATFORM_III_HEIGHT,240 }, { 100,PLATFORM_IV_HEIGHT,240 },
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

void createLadders(Ladder* ladders)
{
	int laddersParameters[NUMBERS_OF_LADDERS][3] = {
		{365,PLATFORM_V_HEIGHT,160}, {600,PLATFORM_IV_HEIGHT,LADDER_HEIGHT},
		{150,PLATFORM_III_HEIGHT,LADDER_HEIGHT}, {550,PLATFORM_II_HEIGHT,LADDER_HEIGHT},
		{110,PLATFORM_I_HEIGHT,60}
	};

	for (int i = 0; i < NUMBERS_OF_LADDERS; i++)
	{
		ladders[i].x = laddersParameters[i][0];
		ladders[i].y = laddersParameters[i][1];
		ladders[i].h = laddersParameters[i][2];
	}
}

void drawLadders(Ladder* ladders)
{
	for (int i = 0; i < NUMBERS_OF_LADDERS; i++) {
		DrawRectangle(SDL.screen, ladders[i].x, ladders[i].y, ladders[i].w, ladders[i].h, colors.black, colors.grey);
	}
}

void playerOnLadder()
{
	Mario.onLadder = true;
	Mario.onPlatform = false;
	Mario.fallDown = false;
}

void playerOnLadderEdge()
{
	Mario.onLadder = true;
	Mario.onPlatform = true;
	Mario.fallDown = false;
}

void playerOnPlatform()
{
	Mario.onLadder = false;
	Mario.onPlatform = true;
	Mario.fallDown = false;
}

void playerNoWhere()
{
	Mario.onLadder = false;
	Mario.onPlatform = false;
	Mario.fallDown = true;
}

void isPlayerOnLadder(Ladder* ladders)
{
	int leftLowerCorner[2] = { Mario.lowerXCorner, Mario.lowerYCorner };
	for (int i = 0; i < NUMBERS_OF_LADDERS; i++)
	{
		if (ladders[i].x <= leftLowerCorner[0] <= ladders[i].x + ladders[i].w) //x increses in right direciton
		{
			//is Mario at the beginning of ladder?
			if (leftLowerCorner[1] == ladders[i].y + ladders[i].h)
				playerOnLadderEdge();
			//is Mario in the "middle" of ladder?
			else if (ladders[i].y < leftLowerCorner[1] <= ladders[i].y + ladders[i].h) //y increases in down direction
				playerOnLadder();
		}
		else
		{
			playerNoWhere();
			if (leftLowerCorner[1] == GROUND_HEIGHT)
				playerOnPlatform();
		}
	}
}

void isPlayerOnPlatform(Platform* platforms)
{
	int leftLowerCorner[2] = { Mario.lowerXCorner, Mario.lowerYCorner }; //table containing player left lower corner cordinates
	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		// is Mario on platform?
		if (leftLowerCorner[1] == platforms[i].y) {
			// how far from left
			if (platforms[i].x <= leftLowerCorner[0])
				playerOnPlatform();
			//how far from right
			else if (platforms[i].x >= leftLowerCorner[0] + PLAYER_WIDTH)
				playerOnPlatform();
		}
		else
		{
			playerNoWhere();
			if (leftLowerCorner[1] == GROUND_HEIGHT)
				playerOnPlatform();
		}
	}
}

//Oversave whereisPLayer, doesn't change properly (all time "playerOnLadder")
void whereIsPLayer(Platform* platforms, Ladder* ladders)
{
	isPlayerOnPlatform(platforms);
	isPlayerOnLadder(ladders);

}

void readKeys()
{
	while (SDL_PollEvent(&SDL.event))
	{
		switch (SDL.event.type)
		{
		case SDL_KEYDOWN:
			if (SDL.event.key.keysym.sym == SDLK_ESCAPE)
				quit();
			else if (SDL.event.key.keysym.sym == SDLK_n)
				basicSetting();
			else if (SDL.event.key.keysym.sym == SDLK_p)
				addPoints();
			else if (SDL.event.key.keysym.sym == SDLK_l)
				loseLive();
			else if (SDL.event.key.keysym.sym == SDLK_LEFT || SDL.event.key.keysym.sym == SDLK_RIGHT)
				playerMove();
			else if (SDL.event.key.keysym.sym == SDLK_UP || SDL.event.key.keysym.sym == SDLK_DOWN)
				playerMove();
			else if (SDL.event.key.keysym.sym == SDLK_SPACE)
				playerMove();
			break;
		case SDL_QUIT: //X button in right up corner
			quit();
			break;
		}
	}
}

void SDLSpace() 	//freeing all surfaces
{
	SDL_FreeSurface(SDL.charset);
	SDL_FreeSurface(SDL.screen);
	SDL_DestroyTexture(SDL.scrtex);
	SDL_DestroyRenderer(SDL.renderer);
	SDL_DestroyWindow(SDL.window);
}

void quit()
{
	gameInfo.quit = true;
}