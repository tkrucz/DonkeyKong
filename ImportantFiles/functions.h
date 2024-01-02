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

void drawInfo(PlayerInfo* playerInfo);

void initializeGameObjects(Platform* platforms, Ladder* ladders, Barrel* barrels);

void drawScene(Platform* platforms, Ladder* ladders, Barrel* barrels);

void displayWindow(PlayerInfo* playerInfo, Platform* platforms, Ladder* ladders, Barrel* barrels);

void refreshWindow();

void printGameInfo();

void printPlayerInfo(PlayerInfo* playerInfo);

void drawGround();

void basicSettings(PlayerInfo* playerInfo);

void initializePlayer();

void initializeColors();

void playerWalk(); //move player in X axis by the current speedX

void playerClimb(); //move player in Y axis by the current speedY

void approximateOnGround(); //check if player is near the ground

void approximateOnPlatform(Platform* platforms); //check if player is near the platform, while falling down

void hitBottomOfThePlatform(Platform* platforms); //check if player hit the bottom of platform

void hitSidesOfThePlatform(Platform* platforms); //check if player hit the sides of platform

void gravityApply(Platform* platforms, PlayerInfo* playerInfo); //check if player is jumping||falling down, then change his position by the current speedY 

void playerJump(); //give the speedY value -JumpingSpeed

void checkIfPlayerIsJumping();

void playerMovement();

void addPoints(PlayerInfo* playerInfo, Score* punkty); //for test

void jumpOverBarrel(PlayerInfo* playerInfo, Score* punkty);//not used

void getTrophy(PlayerInfo* playerInfo, Score* punkty);//not used

void endTheStage(PlayerInfo* playerInfo, Score* punkty);//not used

void addScore(PlayerInfo* playerInfo, Score* punkty); //not used

void loseLive(PlayerInfo* playerInfo); 

void timeCounting(); //counting the game time

void createPlatforms(Platform* platforms);

void drawPlatforms(Platform* platforms);

void createLadders(Ladder* ladders);

void drawLadders(Ladder* ladders);

void createBarrels(Barrel* barrels); 

void drawBarrels(Barrel* barrels); 

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

void isPlayerOutsideTheBorders(); //check if player isn't outside of the screen borders

void isPlayerOnLadder(Ladder* ladders);

void isPlayerOnPlatform(Platform* platforms);

void isPlayerOnGround();

void whereIsPLayer(Platform* platforms, Ladder* ladders);

void areBarrelsOnGround(Barrel* barrels); //CHANGE?

void areBarrelsOnPlatform(Platform* platforms, Barrel* barrels); //CHANGE!!!

void whereAreBarrels(Platform* platforms, Barrel* barrels);

void whereAreObjects(Platform* platforms, Ladder* ladders, Barrel* barrels);

void barrelBowling(Barrel* barrels); //CHANGE?

void barrelFalling(Barrel* barrels); //CHANGE?

void barrelMovement(Barrel* barrels);

void collision(PlayerInfo* playerInfo); //CHANGE

void moveObjects(Barrel* barrels);

void readKeys(PlayerInfo* playerInfo, Score* punkty); //read key input

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

void drawInfo(PlayerInfo* playerInfo) {
	printGameInfo();
	printPlayerInfo(playerInfo);
}

void initializeGameObjects(Platform* platforms, Ladder* ladders, Barrel* barrels) {
	createPlatforms(platforms);
	createLadders(ladders);
	createBarrels(barrels);
}

void drawScene(Platform* platforms, Ladder* ladders, Barrel* barrels) {
	drawGround();
	drawPlatforms(platforms);
	drawLadders(ladders);
	drawBarrels(barrels);
}

void displayWindow(PlayerInfo* playerInfo, Platform* platforms, Ladder* ladders, Barrel* barrels)
{
	SDL_FillRect(SDL.screen, ZERO, colors.black); //because FillRect in second parameter has NULL this function fill in the color of the window (into black)
	drawScene(platforms, ladders, barrels);
	drawInfo(playerInfo);
	DrawSurface(SDL.screen, SDL.player, Mario.lowerXCorner + PLAYER_DIFFERENCE_IN_X, Mario.lowerYCorner + PLAYER_DIFFERENCE_IN_Y, &Mario.animation); //draws the player
}

void refreshWindow()
{
	SDL_UpdateTexture(SDL.scrtex, ZERO, SDL.screen->pixels, SDL.screen->pitch);
	SDL_RenderCopy(SDL.renderer, SDL.scrtex, ZERO, ZERO);
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

void printPlayerInfo(PlayerInfo* playerInfo)
{
	DrawRectangle(SDL.screen, ZERO_COLUMN, 70, 120, 36, colors.white, colors.black);
	sprintf(gameInfo.text, "Score: %.6d", playerInfo->score);
	DrawString(SDL.screen, TEN_ROW, 75, gameInfo.text, SDL.charset);
	sprintf(gameInfo.text, "Lives: %d", playerInfo->lives);
	DrawString(SDL.screen, TEN_ROW, 90, gameInfo.text, SDL.charset);
	sprintf(gameInfo.text, "LeftLowerXCorner: %.0f", Mario.lowerXCorner);
	DrawString(SDL.screen, TEN_ROW, 150, gameInfo.text, SDL.charset);
	sprintf(gameInfo.text, "LeftLowerYCorner: %.0f", Mario.lowerYCorner);
	DrawString(SDL.screen, TEN_ROW, 170, gameInfo.text, SDL.charset);
	sprintf(gameInfo.text, "LeftLowerXCorner: %.0f", barrel.lowerXCorner);
}

void drawGround()
{
	DrawLine(SDL.screen, ZERO_COLUMN, GROUND_HEIGHT, SCREEN_WIDTH, 1, 0, colors.white);
}

void basicSettings(PlayerInfo* playerInfo)
{
	playerInfo->score = PLAYER_START_POINTS;
	playerInfo->lives = PLAYER_LIVES;
	gameInfo.quit = false;
	gameInfo.gameTime = ZERO;
	initializePlayer();
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
		if (Mario.speedY > 0 && Mario.lowerYCorner > platforms[i].upperYCorner &&
			Mario.lowerYCorner < platforms[i].upperYCorner + platforms[i].width &&
			Mario.lowerXCorner<platforms[i].upperXCorner + platforms[i].length &&
			Mario.lowerXCorner + Mario.realSize[0]>platforms[i].upperXCorner)
		{
			Mario.lowerYCorner = platforms[i].upperYCorner;
			Mario.speedY = NULL_SPEED;
			playerNotFallingDown();
			playerNotJumping();
		}		
	}
}

void hitBottomOfThePlatform(Platform* platforms) //check if player doesn't hit the bottom of the platform
{
	double upperYCorner = Mario.lowerYCorner - Mario.realSize[1]; //"-" beacuse y increases in down direction
	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		if (upperYCorner <= platforms[i].upperYCorner + platforms[i].width && upperYCorner > platforms[i].upperYCorner)
			if (platforms[i].upperXCorner <= Mario.lowerXCorner + Mario.realSize[0] && Mario.lowerXCorner <= platforms[i].upperXCorner + platforms[i].length)
			{
				double elasticColision = ELASTIC_COLISION_CONST * (Mario.speedY + GRAVITY_SPEED);
				Mario.speedY = elasticColision; //dodać elastic colision do sturktury skok kiedyś?
			}
	}
}

void hitSidesOfThePlatform(Platform* platforms)
{
	double upperYCorner = Mario.lowerYCorner - Mario.realSize[1];
	double LeftCorner = Mario.lowerXCorner;
	double RightCorner = Mario.lowerXCorner + Mario.realSize[0];
	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		if (LeftCorner <= platforms[i].upperXCorner + platforms[i].length && LeftCorner >= platforms[i].upperXCorner + platforms[i].length - ONE)
			if (upperYCorner <= platforms[i].upperYCorner + platforms[i].width && upperYCorner > platforms[i].upperYCorner)
			{
				Mario.lowerXCorner = platforms[i].upperXCorner + platforms[i].length;
				return;
			}
		if (RightCorner >= platforms[i].upperXCorner && RightCorner <= platforms[i].upperXCorner + ONE)
			if (upperYCorner <= platforms[i].upperYCorner + platforms[i].width && upperYCorner > platforms[i].upperYCorner)
				Mario.lowerXCorner = platforms[i].upperXCorner - Mario.realSize[0];
	}
}

//TODO KONIECZNIE WSZYSTKIE STRUKTURY/ZMIENNE NIE MOGA BYC GLOBALNE !!!!!! ////////////////////////////////////////////////////////////////
void gravityApply(Platform* platforms, PlayerInfo* playerInfo)
{
	collision(playerInfo);
	if (Mario.isJumping || Mario.fallDown)
	{
		Mario.speedY += GRAVITY_SPEED;
		Mario.lowerYCorner += Mario.speedY;
		approximateOnGround();
		hitBottomOfThePlatform(platforms);
		hitSidesOfThePlatform(platforms);
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

void addPoints(PlayerInfo* playerInfo, Score* punkty)
{
	playerInfo->score += punkty->score;
}

void jumpOverBarrel(PlayerInfo* playerInfo, Score* punkty)
{
	playerInfo->score += punkty->jumpOverBarrel;
}

void getTrophy(PlayerInfo* playerInfo, Score* punkty)
{
	playerInfo->score += punkty->getTrophy;
}

void endTheStage(PlayerInfo* playerInfo, Score* punkty)
{
	playerInfo->score += punkty->endTheStage;
}

void addScore(PlayerInfo* playerInfo, Score* punkty)
{
	jumpOverBarrel(playerInfo,punkty);
	getTrophy(playerInfo, punkty);
	endTheStage(playerInfo, punkty);
}

void loseLive(PlayerInfo* playerInfo)
{
	playerInfo->lives -= 1;
	if (playerInfo->lives == ZERO)
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
	//platformsParameters{ X cordinate, Y cordinate, length }
	int platformsParameters[NUMBER_OF_PLATFORMS][3] = {
		{60,PLATFORM_I_HEIGHT,350}, {520,PLATFORM_I_HEIGHT,160},
		{440,PLATFORM_II_HEIGHT,160}, { 40,PLATFORM_II_HEIGHT,350 },
		{ 480,PLATFORM_III_HEIGHT,200 }, { 340,PLATFORM_III_HEIGHT,80 },
		{ 60,PLATFORM_III_HEIGHT,240 }, { 100,PLATFORM_IV_HEIGHT,240 },
		{ 470,PLATFORM_IV_HEIGHT,240 }, { 280,PLATFORM_V_HEIGHT,160 }
	};

	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		platforms[i].upperXCorner = platformsParameters[i][0];
		platforms[i].upperYCorner = platformsParameters[i][1];
		platforms[i].length = platformsParameters[i][2];
	}
}

void drawPlatforms(Platform* platforms) {

	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
		DrawRectangle(SDL.screen, platforms[i].upperXCorner, platforms[i].upperYCorner, platforms[i].length, platforms[i].width, colors.black, colors.pink);

}

void createLadders(Ladder* ladders)
{
	//laddersParameters {X cordinate, Y cordinate, ladder height}
	int laddersParameters[NUMBER_OF_LADDERS][3] = {
		{365,PLATFORM_V_HEIGHT,160}, {600,PLATFORM_IV_HEIGHT,LADDER_HEIGHT},
		{150,PLATFORM_III_HEIGHT,LADDER_HEIGHT}, {550,PLATFORM_II_HEIGHT,LADDER_HEIGHT},
		{110,PLATFORM_I_HEIGHT,60}
	};

	for (int i = 0; i < NUMBER_OF_LADDERS; i++)
	{
		ladders[i].upperXCorner = laddersParameters[i][0];
		ladders[i].upperYCorner = laddersParameters[i][1];
		ladders[i].height = laddersParameters[i][2];
	}
}

void drawLadders(Ladder* ladders)
{
	for (int i = 0; i < NUMBER_OF_LADDERS; i++)
		DrawRectangle(SDL.screen, ladders[i].upperXCorner, ladders[i].upperYCorner, ladders[i].width, ladders[i].height, colors.black, colors.grey);
}

void createBarrels(Barrel* barrels)
{
	//barrelsParameters{ X cordinate, Y cordinate, fallDown flag, onPlatform flag, onGround flag }
	int barrelsParameters[NUMBER_OF_BARRELS][5] = {
		{100,PLATFORM_I_HEIGHT,false,true,false},
		{BARRELS_SPAWN_POINT_X + 100,BARRELS_SPAWN_POINT_Y,true,false,false},
		{BARRELS_SPAWN_POINT_X + 150,BARRELS_SPAWN_POINT_Y,true,false,false},
		{BARRELS_SPAWN_POINT_X + 200,BARRELS_SPAWN_POINT_Y,true,false,false},
		{BARRELS_SPAWN_POINT_X + 250,BARRELS_SPAWN_POINT_Y,true,false,false},
		{BARRELS_SPAWN_POINT_X + 300,BARRELS_SPAWN_POINT_Y,true,false,false},
		{BARRELS_SPAWN_POINT_X + 350,BARRELS_SPAWN_POINT_Y,true,false,false},
		{BARRELS_SPAWN_POINT_X + BARRELS_DIFFERENCE_IN_X,PLATFORM_V_HEIGHT,false,true,false}
	};

	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		barrels[i].lowerXCorner = barrelsParameters[i][0];
		barrels[i].lowerYCorner = barrelsParameters[i][1];
		barrels[i].fallDown = barrelsParameters[i][2];
		barrels[i].onPlatform = barrelsParameters[i][3];
		barrels[i].onGround = barrelsParameters[i][4];
		barrels[i].animation = { ZERO, ZERO, barrel.realSize[0], barrel.realSize[1] };
	}
}

void drawBarrels(Barrel* barrels)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
		DrawSurface(SDL.screen, SDL.barrel, barrels[i].lowerXCorner, barrels[i].lowerYCorner, &barrels[i].animation);
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

void isPlayerOutsideTheBorders()
{
	if (Mario.lowerXCorner <= ZERO)
		Mario.lowerXCorner = ZERO;
	if (Mario.lowerXCorner + Mario.realSize[0] >= SCREEN_WIDTH)
		Mario.lowerXCorner = SCREEN_WIDTH - Mario.realSize[0];
}

void isPlayerOnLadder(Ladder* ladders)
{
	int leftLowerCorner[2] = { Mario.lowerXCorner, Mario.lowerYCorner };
	for (int i = 0; i < NUMBER_OF_LADDERS; i++)
	{
		if (ladders[i].upperXCorner <= Mario.lowerXCorner && Mario.lowerXCorner <= ladders[i].upperXCorner + ladders[i].width) //x increses in right direciton
		{
			//is Mario at the beginning of ladder?
			if (leftLowerCorner[1] == ladders[i].upperYCorner + ladders[i].height)
			{
				playerOnLadderBeg();
				playerNotOnLadderEnd();
				playerOnLadder();
				return;
			}
			//is Mario at the end of ladder?
			else if (leftLowerCorner[1] == ladders[i].upperYCorner)
			{
				playerOnLadderEnd();
				playerNotOnLadderBeg();
				playerOnLadder();
				return;
			}
			//is Mario in the "middle" of ladder?
			else if (ladders[i].upperYCorner < leftLowerCorner[1] && leftLowerCorner[1] < ladders[i].upperYCorner + ladders[i].height)//y increases in down direction 
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
		if (Mario.lowerYCorner == platforms[i].upperYCorner)
			// how far from edges?
			if (platforms[i].upperXCorner <= Mario.lowerXCorner + Mario.realSize[0] && Mario.lowerXCorner <= platforms[i].upperXCorner + platforms[i].length)
			{
				playerOnPlatform();
				return;
			}
	}
	playerNotOnPlatform();
}

void isPlayerOnGround()
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
	isPlayerOutsideTheBorders();
	isPlayerOnLadder(ladders);
	isPlayerOnPlatform(platforms);
	isPlayerOnGround();	
}

void areBarrelsOnGround(Barrel* barrels)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		if (barrels[i].lowerYCorner + barrels[i].fallingSpeed >= GROUND_HEIGHT)
			barrels[i].onGround = true;
		else 
			barrels[i].onGround = false;

		if (barrels[i].onGround)
			barrels[i].lowerYCorner = BARRELS_SPAWN_POINT_Y;
	}
}

void areBarrelsOnPlatform(Platform* platforms, Barrel* barrels)
{
		for (int i = 0; i < NUMBER_OF_BARRELS; i++)
		{
			for (int j = 0; j < NUMBER_OF_PLATFORMS; j++)
			{
				if (barrels[i].lowerYCorner + barrels[i].fallingSpeed >= platforms[j].upperYCorner)				
					barrels[i].lowerYCorner = platforms[j].upperYCorner+BARRELS_DIFFERENCE_IN_Y;				
				
				if (platforms[j].upperXCorner <= barrels[i].lowerXCorner + barrels[i].realSize[0] && barrels[i].lowerXCorner - barrels[i].realSize[0] <= platforms[j].upperXCorner + platforms[j].length)
				{
					barrels[i].onPlatform = true;
					barrels[i].fallDown = false;
					return;
				}
				else
				{
					barrels[i].onPlatform = false;
					barrels[i].fallDown = true;
					return;
				}
			}
		}
}

void whereAreBarrels(Platform* platforms, Barrel* barrels)
{
	areBarrelsOnPlatform(platforms,barrels);
	areBarrelsOnGround(barrels);
}

void whereAreObjects(Platform* platforms, Ladder* ladders,Barrel* barrels)
{
	whereIsPLayer(platforms, ladders);
	whereAreBarrels(platforms, barrels);
}

void barrelBowling(Barrel* barrels)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		if (barrels[i].onPlatform)
			barrels[i].lowerXCorner += barrel.bowlingSpeed;
	}
}

void barrelFalling(Barrel* barrels)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		if (!barrels[i].onPlatform && !barrels[i].onGround)
			barrels[i].fallDown = true;
		if (barrels[i].fallDown)
			barrels[i].lowerYCorner += barrel.fallingSpeed;
	}
}

void barrelMovement(Barrel* barrels)
{
	barrelBowling(barrels);
	barrelFalling(barrels);
}

void collision(PlayerInfo* playerInfo)//should add something like "one barrel can substract only one life", so I have to start numerate them
{
	if (barrel.lowerXCorner == Mario.lowerXCorner && barrel.lowerYCorner + 0.1 >= Mario.lowerYCorner && barrel.lowerYCorner - 0.1 <= Mario.lowerYCorner)
	{
		loseLive(playerInfo);
	}
}

void moveObjects(Barrel* barrels)
{
	playerMovement();
	barrelMovement(barrels);
}


void readKeys(PlayerInfo* playerInfo, Score* punkty)
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
				basicSettings(playerInfo);
			else if (keyPressed == SDLK_p) //usunąć
				addPoints(playerInfo,punkty);
			else if (keyPressed == SDLK_l) //usunąć
				loseLive(playerInfo);
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
	SDL_FreeSurface(SDL.player);
	SDL_FreeSurface(SDL.barrel);
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
