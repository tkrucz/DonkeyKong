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

void initializeGameObjects(Platform* platforms, Ladder* ladders);

void drawScene(Platform* platforms, Ladder* ladders);

void displayWindow(Platform* platforms, Ladder* ladders);

void refreshWindow();

void printGameInfo();

void printPlayerInfo();

void drawGround();

void basicSettings();

void initializePlayer();

void initializeBarrels();

void initializeColors();

void playerWalk(); //move player in X axis by the current speedX

void playerClimb(); //move player in Y axis by the current speedY

void approximateOnGround(); //check if player is near the ground

void approximateOnPlatform(Platform* platforms); //check if player is near the platform

void hitBottomOfThePlatform(Platform* platforms); //check if player hit the platform

void graivityApply(Platform* platforms); //check if Mario is jumping||falling down, then change his position by the current speedY 

void playerJump(); //give the speedY value -JumpingSpeed

void checkIfPlayerIsJumping();

void playerMovement();

void addPoints(); //for test

void jumpOverBarrel();//not used

void getTrophy();//not used

void endTheStage();//not used

void addScore(); //not used

void loseLive(); //for test

void timeCounting(); //counting the game time

void createPlatforms(Platform* platforms);

void drawPlatforms(Platform* platforms);

void createLadders(Ladder* ladders);

void drawLadders(Ladder* ladders);

void playerOnLadderBeg();

void playerNotOnLadderBeg();

void playerOnLadderEnd();

void playerNotOnLadderEnd();

void playerOnLadder();

void playerNotOnLadder();

void playerOnPlatform();

void playerNotOnPlatform();

void playerFallingDown();

void playerNotFallingDown();

void playerJumping();

void playerNotJumping();

void playerOnGround();

void isPlayerOnLadder(Ladder* ladders);

void isPlayerOnPlatform(Platform* platforms);

void isPlayerOnGround();

void whereIsPLayer(Platform* platforms, Ladder* ladders);

void areBarrelsOnGround(); //TO DO

void areBarrelsOnPlatform(Platform* platforms); //TO DO

void whereAreBarrels(Platform* platforms); //TO DO

void whereAreObjects(Platform* platforms, Ladder* ladders);

void barrelBowling(); //TO DO

void barrelFallDown(); //TO DO

void barrelMovement();

void collision(); //TO CHANGE

void moveObjects();

void readKeys(); //read key input

void SDLSpace(); //freeing all surfaces

void quit();

/*Functions definitions
===================================================================
*/

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
	drawGround();
	drawPlatforms(platforms);
	drawLadders(ladders);
}

void displayWindow(Platform* platforms, Ladder* ladders)
{
	SDL_FillRect(SDL.screen, NULL, colors.black); //because FillRect in second parameter has NULL this function fill in the color of the window (into black)
	drawScene(platforms, ladders);
	drawInfo();
	DrawSurface(SDL.screen, SDL.player, Mario.lowerXCorner + PLAYER_DIFFERENCE_IN_X, Mario.lowerYCorner + PLAYER_DIFFERENCE_IN_Y, &Mario.animation); //draws the player
	DrawSurface(SDL.screen, SDL.barrels, barrel.lowerXCorner + BARRELS_DIFFERENCE_IN_X, barrel.lowerYCorner + BARRELS_DIFFERENCE_IN_Y, &barrel.animation);
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
	sprintf(gameInfo.text, "LeftLowerXCorner: %.0f", Mario.lowerXCorner);
	DrawString(SDL.screen, TEN_ROW, 150, gameInfo.text, SDL.charset);
	sprintf(gameInfo.text, "LeftLowerYCorner: %.0f", Mario.lowerYCorner);
	DrawString(SDL.screen, TEN_ROW, 170, gameInfo.text, SDL.charset);
	sprintf(gameInfo.text, "LeftLowerXCorner: %d", barrel.lowerXCorner);
	DrawString(SDL.screen, TEN_ROW, 190, gameInfo.text, SDL.charset);
	sprintf(gameInfo.text, "LeftLowerYCorner: %.4f", barrel.lowerYCorner);
	DrawString(SDL.screen, TEN_ROW, 210, gameInfo.text, SDL.charset);
}

void drawGround()
{
	DrawLine(SDL.screen, ZERO_COLUMN, GROUND_HEIGHT, SCREEN_WIDTH, 1, 0, colors.white);
}

void basicSettings()
{
	playerInfo.score = PLAYER_START_POINTS;
	playerInfo.lives = PLAYER_LIVES;
	gameInfo.quit = false;
	gameInfo.gameTime = NULL;
	initializePlayer();
	initializeBarrels();
}

void initializePlayer()
{
	Mario.lowerXCorner = PLAYER_START_X_COORDINATE;
	Mario.lowerYCorner = PLAYER_START_Y_COORDINATE;
	//TODO comments
	Mario.animation = { DEAFULT_PLAYER_SPRITE_I + MARIO_BMP_DISTANCE, DEAFULT_PLAYER_SPRITE_II ,Mario.realSize[0],Mario.realSize[1] };
	Mario.speedX = NULL_SPEED;
	Mario.speedY = NULL_SPEED;
	playerOnPlatform();
}

void initializeBarrels()
{
	barrel.animation = { NULL,NULL,barrel.realSize[0],barrel.realSize[1] };
	barrel.lowerXCorner = BARRELS_SPAWN_POINT_X;
	barrel.lowerYCorner = BARRELS_SPAWN_POINT_Y;
}

void initializeColors()
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

void playerWalk()
{
	Mario.lowerXCorner += Mario.speedX;
}

void playerClimb()
{
	if (Mario.begLadder && Mario.speedY >= 0)
		Mario.speedY = NULL_SPEED;
	Mario.lowerYCorner += Mario.speedY;
}

void approximateOnGround()
{
	if (Mario.lowerYCorner + Mario.speedY + GRAVITY_SPEED >= GROUND_HEIGHT)
	{
		Mario.lowerYCorner = GROUND_HEIGHT;
		playerNotFallingDown();
		playerNotJumping();
	}
}

void approximateOnPlatform(Platform* platforms)
{
	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		if (Mario.speedY >= 0 && Mario.lowerYCorner + Mario.speedY + GRAVITY_SPEED <= platforms[i].y)
		{
			Mario.lowerYCorner = platforms[i].y;
			Mario.speedY = NULL_SPEED;
			playerNotFallingDown();
			playerNotJumping();
		}		
	}
}

void hitBottomOfThePlatform(Platform* platforms) //check if player doesn't hit the bottom of the platform
{
	int upperYCorner = Mario.lowerYCorner - Mario.realSize[1]; //"-" beacuse y increases in down direction
	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		if (upperYCorner <= platforms[i].y + platforms[i].w && upperYCorner >= platforms[i].y)
			if (platforms[i].x <= Mario.lowerXCorner + Mario.realSize[0] && Mario.lowerXCorner <= platforms[i].x + platforms[i].l)
			{
				double elasticColision = ELASTIC_COLISION_CONST * (Mario.speedY + GRAVITY_SPEED);
				Mario.speedY = elasticColision; //dodać elastic colision do sturktury skok kiedyś?
			}
	}
}

//TODO KONIECZNIE WSZYSTKIE STRUKTURY/ZMIENNE NIE MOGA BYC GLOBALNE !!!!!! ////////////////////////////////////////////////////////////////
void graivityApply(Platform* platforms)
{
	collision();
	if (Mario.isJumping || Mario.fallDown)
	{
 		Mario.speedY += GRAVITY_SPEED;
		Mario.lowerYCorner += Mario.speedY; 
		approximateOnGround();
		hitBottomOfThePlatform(platforms);
		approximateOnPlatform(platforms);
	}
}

void playerJump()
{
	playerJumping();
	Mario.speedY = -JUMPING_SPEED;
}

void checkIfPlayerIsJumping() //no "double" jump or inifinity jump
{
	if (Mario.isJumping == true)
		return;
	else
		playerJump();
}

void playerMovement()
{
	if (Mario.onPlatform || Mario.isJumping || Mario.fallDown)
		playerWalk();
	if (Mario.onLadder)
		playerClimb();
	if (Mario.begLadder || Mario.endLadder)
	{
		playerWalk();
		playerClimb();
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

void getTrophy()
{
	playerInfo.score += score.getTrophy;
}

void endTheStage()
{
	playerInfo.score += score.endTheStage;
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
	if (playerInfo.lives == NULL)
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

	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
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
	for (int i = 0; i < NUMBERS_OF_LADDERS; i++)
		DrawRectangle(SDL.screen, ladders[i].x, ladders[i].y, ladders[i].w, ladders[i].h, colors.black, colors.grey);
}


void playerOnLadderBeg()
{
	Mario.begLadder = true;
}

void playerNotOnLadderBeg()
{
	Mario.begLadder = false;
}

void playerOnLadderEnd()
{
	Mario.endLadder = true;
}

void playerNotOnLadderEnd()
{
	Mario.endLadder = false;
}

void playerOnLadder()
{
	Mario.onLadder = true;
}

void playerNotOnLadder()
{
	Mario.onLadder = false;
}

void playerOnPlatform()
{
	Mario.onPlatform = true;
}

void playerNotOnPlatform()
{
	Mario.onPlatform = false;
}

void playerFallingDown()
{
	Mario.fallDown = true;
}

void playerNotFallingDown()
{
	Mario.fallDown = false;
}

void playerJumping()
{
	Mario.isJumping = true;
}

void playerNotJumping()
{
	Mario.isJumping = false;
}

void playerOnGround()
{
	Mario.onPlatform = true;
}

void isPlayerOnLadder(Ladder* ladders)
{
	int leftLowerCorner[2] = { Mario.lowerXCorner, Mario.lowerYCorner };
	for (int i = 0; i < NUMBERS_OF_LADDERS; i++)
	{
		if (ladders[i].x <= Mario.lowerXCorner && Mario.lowerXCorner <= ladders[i].x + ladders[i].w) //x increses in right direciton
		{
			//is Mario at the beginning of ladder?
			if (leftLowerCorner[1] == ladders[i].y + ladders[i].h)
			{
				playerOnLadderBeg();
				playerNotOnLadderEnd();
				playerOnLadder();
				return;
			}
			//is Mario at the end of ladder?
			else if (leftLowerCorner[1] == ladders[i].y)
			{
				playerOnLadderEnd();
				playerNotOnLadderBeg();
				playerOnLadder();
				return;
			}
			//is Mario in the "middle" of ladder?
			else if (ladders[i].y < leftLowerCorner[1] && leftLowerCorner[1] < ladders[i].y + ladders[i].h)//y increases in down direction 
			{
				playerOnLadder();
				playerNotOnLadderEnd();
				playerNotOnLadderBeg();
				return;
			}
		}
	}
	playerNotOnLadderEnd();
	playerNotOnLadderBeg();
	playerNotOnLadder();
}

void isPlayerOnPlatform(Platform* platforms)
{
	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		// is Mario on platform height?
		if (Mario.lowerYCorner == platforms[i].y)
			// how far from edges?
			if (platforms[i].x <= Mario.lowerXCorner + +Mario.realSize[0] && Mario.lowerXCorner <= platforms[i].x + platforms[i].l)
			{
				playerOnPlatform();
				return;
			}
	}
	playerNotOnPlatform();
}

void isPlayerOnGround() //przez to Mario na drugim poziome platform spada znowu do I poziomu
{
	if (!Mario.onPlatform && !Mario.onLadder && Mario.lowerYCorner != GROUND_HEIGHT)
		playerFallingDown();
	if (Mario.lowerYCorner == GROUND_HEIGHT)
	{
		playerOnGround();
		playerNotFallingDown();
	}
}

void whereIsPLayer(Platform* platforms, Ladder* ladders)
{
	isPlayerOnLadder(ladders);
	isPlayerOnPlatform(platforms);
	isPlayerOnGround();	
}

void areBarrelsOnGround()
{
	if (barrel.lowerYCorner + barrel.fallingSpeed >= GROUND_HEIGHT)
		barrel.lowerYCorner = BARRELS_SPAWN_POINT_Y;
}

void areBarrelsOnPlatform(Platform* platforms)
{

}

void whereAreBarrels(Platform* platforms)
{
	areBarrelsOnGround();
}

void whereAreObjects(Platform* platforms, Ladder* ladders)
{
	whereIsPLayer(platforms, ladders);
	whereAreBarrels(platforms);
}

void barrelBowling()
{

}

void barrelFallDown()
{
	barrel.lowerYCorner += barrel.fallingSpeed;
}

void barrelMovement()
{
	barrelBowling();
	barrelFallDown();
}

void collision()//should add something like "one barrel can substract only one life", so I have to start numerate them
{
	if (barrel.lowerXCorner == Mario.lowerXCorner && barrel.lowerYCorner + 0.1 >= Mario.lowerYCorner && barrel.lowerYCorner - 0.1 <= Mario.lowerYCorner)
	{
		loseLive();
	}
}

void moveObjects()
{
	playerMovement();
	barrelMovement();
}


void readKeys()
{
	while (SDL_PollEvent(&SDL.event))
	{
		int keyPressed = SDL.event.key.keysym.sym;
		switch (SDL.event.type)
		{
		case SDL_KEYDOWN:
			if (keyPressed == SDLK_ESCAPE)
				quit();
			else if (keyPressed == SDLK_n)
				basicSettings();
			else if (keyPressed == SDLK_p)
				addPoints();
			else if (keyPressed == SDLK_l)
				loseLive();
			else if (keyPressed == SDLK_RIGHT)
				Mario.speedX = WALKING_SPEED;
			else if (keyPressed == SDLK_LEFT)
				Mario.speedX = -WALKING_SPEED;
			else if ( keyPressed == SDLK_DOWN)
				Mario.speedY = CLIMBING_SPEED;
			else if (keyPressed == SDLK_UP)
				Mario.speedY = -CLIMBING_SPEED;
			else if (keyPressed == SDLK_SPACE)
				checkIfPlayerIsJumping(); 
			break;
		case SDL_KEYUP:
			Mario.speedX = 0;
			if(keyPressed==SDLK_DOWN || keyPressed==SDLK_UP)
				Mario.speedY = 0;
			break;		
		case SDL_QUIT: //X button in right up corner
			quit();
			break;
		}
	}
}

void SDLSpace()
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
	SDLSpace();
	SDL_Quit();
}