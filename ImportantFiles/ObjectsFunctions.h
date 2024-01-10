#pragma once
#define USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "Define.h"
#include "Structures.h"
#include "GameStructure.h"
#include "GameStageFunctions.h"
#include "GeneralFunctions.h"
#include "PlayerFunctions.h"
#include "Score.h"
#include "Animations.h"
#include "SDLFunctions.h"

extern "C" {
#include"../SDL2-2.0.10/include/SDL.h"
#include"../SDL2-2.0.10/include/SDL_main.h"
}

int loadBMPs(SDLConst* SDL);

void initializeColors(SDLConst* SDL, Color* colors);

void createBarrels(Stage* stage);

void drawBarrels(Stage* stage, SDLConst* SDL);

void initializeGameObjects(Stage* stage, Animator* animator);

void barrelsApproximateOnPlatform(Stage* stage);

void areBarrelsOnGround(Stage* stage);

void whereAreBarrels(Stage* stage);

void barrelBowling(Stage* stage);

void barrelFalling(Stage* stage);

void barrelMovement(Stage* stage);

void collision(Stage* stage, SDLConst* SDL);

void whereAreObjects(Stage* stage, SDLConst* SDL, Score* score, ShowText* showText);

void moveObjects(Stage* stage, SDLConst* SDL, Animator* animator);

void createLives(Stage* stage);

int loadBMPs(SDLConst* SDL)
{
	SDL->charset = SDL_LoadBMP("./BMP/cs8x8.bmp");
	SDL->player = SDL_LoadBMP("./BMP/mario.bmp");
	SDL->barrel = SDL_LoadBMP("./BMP/barrels.bmp");
	SDL->trophy = SDL_LoadBMP("./BMP/trophy.bmp");
	SDL->lives = SDL_LoadBMP("./BMP/HP.bmp");
	if (SDL->charset == ZERO)
	{
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(SDL->screen);
		SDL_DestroyTexture(SDL->scrtex);
		SDL_DestroyWindow(SDL->window);
		SDL_DestroyRenderer(SDL->renderer);
		SDL_Quit();
		return 1;
	}
}

void initializeColors(SDLConst* SDL, Color* colors)
{
	colors->black = SDL_MapRGB(SDL->screen->format, 0x00, 0x00, 0x00);
	colors->white = SDL_MapRGB(SDL->screen->format, 255, 255, 255);
	colors->pink = SDL_MapRGB(SDL->screen->format, 214, 136, 150);
	colors->indygo = SDL_MapRGB(SDL->screen->format, 85, 120, 200);
	colors->lime = SDL_MapRGB(SDL->screen->format, 152, 190, 100);
	colors->grey = SDL_MapRGB(SDL->screen->format, 160, 160, 160);
}

void createBarrels(Stage* stage)
{
	//barrelsParameters{ X cordinate, Y cordinate, fallDown flag, onPlatform flag, onGround flag }
	int barrelsParameters[NUMBER_OF_BARRELS][5] = {
		{ BARRELS_I_SPAWN_POINT_X, BARRELS_SPAWN_POINT_Y, true, false, false },
		{ BARRELS_II_SPAWN_POINT_X, BARRELS_SPAWN_POINT_Y, true, false, false },
		{ BARRELS_III_SPAWN_POINT_X , BARRELS_SPAWN_POINT_Y, true, false, false },
		{ BARRELS_IV_SPAWN_POINT_X , BARRELS_SPAWN_POINT_Y, true, false, false },
		{ BARRELS_V_SPAWN_POINT_X , BARRELS_SPAWN_POINT_Y, true, false, false },
		{ BARRELS_VI_SPAWN_POINT_X , BARRELS_SPAWN_POINT_Y, true, false, false },
		{ BARRELS_VII_SPAWN_POINT_X , BARRELS_SPAWN_POINT_Y, true, false, false },
		{ BARRELS_VIII_SPAWN_POINT_X , BARRELS_SPAWN_POINT_Y, true, false, false }
	};

	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		stage->barrels[i].lowerRightCoordinates.x = barrelsParameters[i][0];
		stage->barrels[i].lowerRightCoordinates.y = barrelsParameters[i][1];
		stage->barrels[i].fallDown = barrelsParameters[i][2];
		stage->barrels[i].onPlatform = barrelsParameters[i][3];
		stage->barrels[i].onGround = barrelsParameters[i][4];
	}
}

void drawBarrels(Stage* stage, SDLConst* SDL)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
		DrawSurface(SDL->screen, SDL->barrel, stage->barrels[i].lowerRightCoordinates.x, stage->barrels[i].lowerRightCoordinates.y, &stage->barrels[i].animation);
}

void initializeGameObjects(Stage* stage, Animator* animator)
{
	createLives(stage);
	if (stage->stageSpecifier == STAGE1)
	{
		createPlatforms(stage);
		createLadders(stage);
		createBarrels(stage);
		createTrophies(stage);
	}
	else if (stage->stageSpecifier == STAGE2)
	{
		createPlatforms2(stage);
		createLadders2(stage);
		createBarrels(stage);
		createTrophies2(stage);
	}
	else if (stage->stageSpecifier == STAGE3)
	{
		createPlatforms3(stage);
		createLadders3(stage);
		createBarrels(stage);
		createTrophies3(stage);
	}
}

void barrelsApproximateOnPlatform(Stage* stage)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		stage->barrels[i].onPlatform = false;
		for (int j = 0; j < NUMBER_OF_PLATFORMS; j++)
		{
			if (stage->barrels[i].lowerRightCoordinates.y + stage->barrels[i].speed.speedY + BARRELS_DIFFERENCE_IN_Y >= stage->platforms[j].upperCorner.y &&
				stage->barrels[i].lowerRightCoordinates.y - stage->barrels[i].realSize[1] <= stage->platforms[j].upperCorner.y + stage->platforms[j].width &&
				stage->platforms[j].upperCorner.x <= stage->barrels[i].lowerRightCoordinates.x &&
				stage->barrels[i].lowerRightCoordinates.x - stage->barrels[i].realSize[0] <= stage->platforms[j].upperCorner.x + stage->platforms[j].length)
			{
				stage->barrels[i].lowerRightCoordinates.y = stage->platforms[j].upperCorner.y + BARRELS_DIFFERENCE_IN_Y;
				stage->barrels[i].onPlatform = true;
				break;
			}
		}
	}
}

void areBarrelsOnGround(Stage* stage)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		if (stage->barrels[i].lowerRightCoordinates.y + stage->barrels[i].speed.speedY >= GROUND_HEIGHT)
			stage->barrels[i].onGround = true;
		else
			stage->barrels[i].onGround = false;

		if (stage->barrels[i].onGround)
		{
			if (stage->barrels[i].lowerRightCoordinates.x < SCREEN_WIDTH / 2)
				stage->barrels[i].speed.speedX = BARRELS_BOWLING_SPEED;
			if (stage->barrels[i].lowerRightCoordinates.x < SCREEN_WIDTH)
				stage->barrels[i].speed.speedX = -BARRELS_BOWLING_SPEED;
			stage->barrels[i].lowerRightCoordinates.y = BARRELS_SPAWN_POINT_Y;
		}
	}
}

void whereAreBarrels(Stage* stage)
{
	barrelsApproximateOnPlatform(stage);
	areBarrelsOnGround(stage);
}

void barrelBowling(Stage* stage)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		if (stage->barrels[i].onPlatform)
			stage->barrels[i].lowerRightCoordinates.x += stage->barrels[i].speed.speedX * stage->gameInfo.deltaTime;
		if (stage->barrels[i].lowerRightCoordinates.x >= SCREEN_WIDTH)
			stage->barrels[i].speed.speedX = -BARRELS_BOWLING_SPEED; //change the speed "direction"
	}
}

void barrelFalling(Stage* stage)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		if (!stage->barrels[i].onPlatform && !stage->barrels[i].onGround)
			stage->barrels[i].fallDown = true;
		if (stage->barrels[i].fallDown)
			stage->barrels[i].lowerRightCoordinates.y += stage->barrels[i].speed.speedY * stage->gameInfo.deltaTime;
	}
}

void barrelMovement(Stage* stage)
{
	barrelBowling(stage);
	barrelFalling(stage);
}

void collision(Stage* stage, SDLConst* SDL)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		if (stage->barrels[i].lowerRightCoordinates.y + BARRELS_DIFFERENCE_IN_Y >= stage->player.lowerCoordinates.y - stage->player.realSize[1] &&
			stage->barrels[i].lowerRightCoordinates.y - BARRELS_HITBOX_SIZE <= stage->player.lowerCoordinates.y &&
			stage->barrels[i].lowerRightCoordinates.x <= stage->player.lowerCoordinates.x + stage->player.realSize[0] &&
			stage->barrels[i].lowerRightCoordinates.x + BARRELS_HITBOX_SIZE >= stage->player.lowerCoordinates.x)
		{
			stage->menu.showBarrelMenu = true;
			loseLive(stage, SDL);
			stage->barrels[i].lowerRightCoordinates.y = BARRELS_SPAWN_POINT_Y;
			initializePlayer(stage);
			break;
		}
	}
}

void whereAreObjects(Stage* stage, SDLConst* SDL, Score* score, ShowText* showText)
{
	whereIsPLayer(stage);
	whereAreBarrels(stage);
	deltaScore(stage, SDL, score, showText);	
}

void moveObjects(Stage* stage, SDLConst* SDL, Animator* animator)
{
	if (!stage->menu.showMenu && !stage->menu.showBarrelMenu)
	{
		playerMovement(stage);
		barrelMovement(stage);
		collision(stage, SDL);
		checkAnimaitons(stage, animator);
	}
}