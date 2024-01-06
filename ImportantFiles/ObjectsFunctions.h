#pragma once
#define USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "define.h"
#include "structures.h"
#include "GameStructure.h"
#include "GameStageFunctions.h"
#include "GeneralFunctions.h"
#include "PlayerFunctions.h"
#include "Score.h"
#include "SDLFunctions.h"

extern "C" {
#include"../SDL2-2.0.10/include/SDL.h"
#include"../SDL2-2.0.10/include/SDL_main.h"
}

int loadBMPs(SDLConst* SDL);

void initializeColors(SDLConst* SDL, Color* colors);

void createBarrels(Barrel* barrels);

void drawBarrels(SDLConst* SDL, Barrel* barrels);

void initializeGameObjects(StageSpecifier* stageSpecifier, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies);

void barrelsApproximateOnPlatform(Platform* platforms, Barrel* barrels);

void areBarrelsOnGround(Barrel* barrels);

void whereAreBarrels(Platform* platforms, Barrel* barrels);

void barrelBowling(Barrel* barrels, GameInfo* gameInfo);

void barrelFalling(Barrel* barrels, GameInfo* gameInfo);

void barrelMovement(Barrel* barrels, GameInfo* gameInfo);

void collision(SDLConst* SDL, GameInfo* gameInfo, PlayerInfo* playerInfo, Barrel* barrels);

void whereAreObjects(PlayerInfo* playerInfo, Score* score, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies);

void moveObjects(SDLConst* SDL, GameInfo* gameInfo, PlayerInfo* playerInfo, Barrel* barrels);


int loadBMPs(SDLConst* SDL)
{
	SDL->charset = SDL_LoadBMP("./BMP/cs8x8.bmp");
	SDL->player = SDL_LoadBMP("./BMP/mario.bmp");
	SDL->barrel = SDL_LoadBMP("./BMP/barrels.bmp");
	SDL->trophy = SDL_LoadBMP("./BMP/trophy.bmp");
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

void createBarrels(Barrel* barrels)
{
	//barrelsParameters{ X cordinate, Y cordinate, fallDown flag, onPlatform flag, onGround flag }
	int barrelsParameters[NUMBER_OF_BARRELS][5] = {
		{BARRELS_SPAWN_POINT_X,BARRELS_SPAWN_POINT_Y,false,true,false},
		{BARRELS_SPAWN_POINT_X + 50,BARRELS_SPAWN_POINT_Y,true,false,false},
		{BARRELS_SPAWN_POINT_X + 220,BARRELS_SPAWN_POINT_Y,true,false,false},
		{BARRELS_SPAWN_POINT_X + 300,BARRELS_SPAWN_POINT_Y,true,false,false},
		{BARRELS_SPAWN_POINT_X - 160,BARRELS_SPAWN_POINT_Y,true,false,false},
		{BARRELS_SPAWN_POINT_X - 200,BARRELS_SPAWN_POINT_Y,true,false,false},
		{BARRELS_SPAWN_POINT_X - 120,BARRELS_SPAWN_POINT_Y,true,false,false},
		{BARRELS_SPAWN_POINT_X + 380,PLATFORM_V_HEIGHT,false,false,false}
	};

	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		barrels[i].lowerRightCoordinates.x = barrelsParameters[i][0];
		barrels[i].lowerRightCoordinates.y = barrelsParameters[i][1];
		barrels[i].fallDown = barrelsParameters[i][2];
		barrels[i].onPlatform = barrelsParameters[i][3];
		barrels[i].onGround = barrelsParameters[i][4];
		barrels[i].animation = { ZERO, ZERO, barrels[i].realSize[0], barrels[i].realSize[1] };
	}
}

void drawBarrels(SDLConst* SDL, Barrel* barrels)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
		DrawSurface(SDL->screen, SDL->barrel, barrels[i].lowerRightCoordinates.x, barrels[i].lowerRightCoordinates.y, &barrels[i].animation);
}

void initializeGameObjects(StageSpecifier* stageSpecifier, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies)
{
	if (*stageSpecifier == STAGE1)
	{
		createPlatforms(platforms);
		createLadders(ladders);
		createBarrels(barrels);
		createTrophies(trophies);
	}
	else if (*stageSpecifier == STAGE2)
	{
		createPlatforms2(platforms);
		createLadders2(ladders);
		createBarrels(barrels);
		createTrophies2(trophies);
	}
	else if (*stageSpecifier == STAGE3)
	{
		createPlatforms3(platforms);
		createLadders3(ladders);
		createBarrels(barrels);
		createTrophies3(trophies);
	}
}

void barrelsApproximateOnPlatform(Platform* platforms, Barrel* barrels)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		barrels[i].onPlatform = false;
		for (int j = 0; j < NUMBER_OF_PLATFORMS; j++)
		{
			if (barrels[i].lowerRightCoordinates.y + barrels[i].speed.speedY + BARRELS_DIFFERENCE_IN_Y >= platforms[j].upperCorner.y &&
				barrels[i].lowerRightCoordinates.y - barrels[i].realSize[1] <= platforms[j].upperCorner.y + platforms[j].width &&
				platforms[j].upperCorner.x <= barrels[i].lowerRightCoordinates.x &&
				barrels[i].lowerRightCoordinates.x - barrels[i].realSize[0] <= platforms[j].upperCorner.x + platforms[j].length)
			{
				barrels[i].lowerRightCoordinates.y = platforms[j].upperCorner.y + BARRELS_DIFFERENCE_IN_Y;
				barrels[i].onPlatform = true;
				break;
			}
		}
	}
}

void areBarrelsOnGround(Barrel* barrels)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		if (barrels[i].lowerRightCoordinates.y + barrels[i].speed.speedY >= GROUND_HEIGHT)
			barrels[i].onGround = true;
		else
			barrels[i].onGround = false;

		if (barrels[i].onGround)
		{
			if (barrels[i].lowerRightCoordinates.x < SCREEN_WIDTH / 2)
				barrels[i].speed.speedX = BARRELS_BOWLING_SPEED;
			if (barrels[i].lowerRightCoordinates.x < SCREEN_WIDTH)
				barrels[i].speed.speedX = -BARRELS_BOWLING_SPEED;
			barrels[i].lowerRightCoordinates.y = BARRELS_SPAWN_POINT_Y;
		}
	}
}

void whereAreBarrels(Platform* platforms, Barrel* barrels)
{
	barrelsApproximateOnPlatform(platforms, barrels);
	areBarrelsOnGround(barrels);
}

void barrelBowling(Barrel* barrels, GameInfo* gameInfo)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		if (barrels[i].onPlatform)
			barrels[i].lowerRightCoordinates.x += barrels[i].speed.speedX * gameInfo->deltaTime;
		if (barrels[i].lowerRightCoordinates.x >= SCREEN_WIDTH)
			barrels[i].speed.speedX = -BARRELS_BOWLING_SPEED; //change the speed "direction"
	}
}

void barrelFalling(Barrel* barrels, GameInfo* gameInfo)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		if (!barrels[i].onPlatform && !barrels[i].onGround)
			barrels[i].fallDown = true;
		if (barrels[i].fallDown)
			barrels[i].lowerRightCoordinates.y += barrels[i].speed.speedY * gameInfo->deltaTime;
	}
}

void barrelMovement(Barrel* barrels, GameInfo* gameInfo)
{
	barrelBowling(barrels, gameInfo);
	barrelFalling(barrels, gameInfo);
}

void collision(SDLConst* SDL, GameInfo* gameInfo, PlayerInfo* playerInfo, Barrel* barrels)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		if (barrels[i].lowerRightCoordinates.y + BARRELS_DIFFERENCE_IN_Y >= Mario.lowerCoordinates.y - Mario.realSize[1] &&
			barrels[i].lowerRightCoordinates.y - BARRELS_HITBOX_SIZE <= Mario.lowerCoordinates.y &&
			barrels[i].lowerRightCoordinates.x <= Mario.lowerCoordinates.x + Mario.realSize[0] &&
			barrels[i].lowerRightCoordinates.x + BARRELS_HITBOX_SIZE >= Mario.lowerCoordinates.x)
		{
			loseLive(SDL, gameInfo, playerInfo);
			barrels[i].lowerRightCoordinates.y = BARRELS_SPAWN_POINT_Y;
			break;
		}
	}
}

void whereAreObjects(PlayerInfo* playerInfo, Score* score, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies)
{
	whereIsPLayer(platforms, ladders);
	whereAreBarrels(platforms, barrels);
	deltaScore(playerInfo, score, barrels, trophies);
}

void moveObjects(SDLConst* SDL, GameInfo* gameInfo, PlayerInfo* playerInfo, Barrel* barrels)
{
	playerMovement(gameInfo);
	barrelMovement(barrels, gameInfo);
	collision(SDL, gameInfo, playerInfo, barrels);
}