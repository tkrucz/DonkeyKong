#pragma once
#define USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "Define.h"
#include "Structures.h"
#include "GeneralFunctions.h"
#include "PlayerFunctions.h"
#include "SDLFunctions.h"

extern "C" {
#include"../SDL2-2.0.10/include/SDL.h"
#include"../SDL2-2.0.10/include/SDL_main.h"
}

void drawGround(SDLConst* SDL, Color* colors);

void platformColor(Stage* stage, Color* colors);

void createPlatforms(Stage* stage);

void drawPlatforms(Stage* stage, SDLConst* SDL, Color* colors);

void createLadders(Stage* stage);

void drawLadders(Stage* stage, SDLConst* SDL, Color* colors);

void createTrophies(Stage* stage);

void drawTrophies(Stage* stage, SDLConst* SDL);

void createPlatforms2(Stage* stage);

void createTrophies2(Stage* stage);

void createPlatforms3(Stage* stage);

void createTrophies3(Stage* stage);

void createLives(Stage* stage);

void drawLives(Stage* stage, SDLConst* SDL);

void drawPlatformsFromFile(Stage* stage, SDLConst* SDL, Color* colors);

void drawLaddersFromFile(Stage* stage, SDLConst* SDL, Color* colors);

void drawBarrelsFromFile(Stage* stage, SDLConst* SDL, Color* colors);

void drawTrohpiesFromFile(Stage* stage, SDLConst* SDL, Color* colors);


void drawGround(SDLConst* SDL, Color* colors)
{
	DrawLine(SDL->screen, ZERO_COLUMN, GROUND_HEIGHT, SCREEN_WIDTH, 1, 0, colors->white);
}

void platformColor(Stage* stage, Color* colors)
{
	if (stage->stageSpecifier == STAGE1)
	{
		colors->platformColor = colors->pink;
		stage->platformColor.platformColor = colors->platformColor;
	}
	else if (stage->stageSpecifier == STAGE2)
	{
		colors->platformColor = colors->indygo;
		stage->platformColor.platformColor = colors->platformColor;
	}
	else if (stage->stageSpecifier == STAGE3)
	{
		colors->platformColor = colors->lime;
		stage->platformColor.platformColor = colors->platformColor;
	}
	else if (stage->stageSpecifier == STAGE4)
	{
		colors->platformColor = colors->white;
		stage->platformColor.platformColor = colors->platformColor;
	}
}

void createPlatforms(Stage* stage)
{
	//platformsParameters{ X cordinate, Y cordinate, length }
	int platformsParameters[NUMBER_OF_PLATFORMS][THREE] = {
		{ PLATFORM1_I_X_CORD, PLATFORM_I_HEIGHT, PLATFORM1_VI_LENGTH}, { PLATFORM1_II_X_CORD, PLATFORM_I_HEIGHT, PLATFORM1_II_LENGTH },
		{ PLATFORM1_III_X_CORD, PLATFORM_II_HEIGHT, PLATFORM1_II_LENGTH }, { PLATFORM1_IV_X_CORD, PLATFORM_II_HEIGHT, PLATFORM1_VI_LENGTH },
		{ PLATFORM1_V_X_CORD, PLATFORM_III_HEIGHT, PLATFORM1_III_LENGTH }, { PLATFORM1_VI_X_CORD, PLATFORM_III_HEIGHT, PLATFORM1_I_LENGTH },
		{ PLATFORM1_VII_X_CORD, PLATFORM_III_HEIGHT, PLATFORM1_IV_LENGTH }, { PLATFORM1_VIII_X_CORD, PLATFORM_IV_HEIGHT, PLATFORM1_IV_LENGTH },
		{ PLATFORM1_IX_X_CORD, PLATFORM_IV_HEIGHT, PLATFORM1_V_LENGTH }, { PLATFORM1_X_X_CORD, PLATFORM_V_HEIGHT, PLATFORM1_II_LENGTH }
	};

	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		stage->platforms[i].upperCorner.x = platformsParameters[i][0];
		stage->platforms[i].upperCorner.y = platformsParameters[i][1];
		stage->platforms[i].length = platformsParameters[i][2];
	}
}

void drawPlatforms(Stage* stage, SDLConst* SDL, Color* colors)
{
	platformColor(stage, colors);
	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
		DrawRectangle(SDL->screen, stage->platforms[i].upperCorner.x, stage->platforms[i].upperCorner.y, stage->platforms[i].length, stage->platforms[i].width, colors->black, stage->platformColor.platformColor);
}

void createLadders(Stage* stage)
{
	//laddersParameters {X cordinate, Y cordinate, ladder height}
	int laddersParameters[NUMBER_OF_LADDERS][THREE] = {
		{ LADDER_I_X_CORD, PLATFORM_V_HEIGHT, LADDER_I_HEIGHT }, { LADDER_II_X_CORD, PLATFORM_IV_HEIGHT, LADDER_HEIGHT },
		{ LADDER_III_X_CORD, PLATFORM_III_HEIGHT, LADDER_HEIGHT}, { LADDER_IV_X_CORD, PLATFORM_II_HEIGHT, LADDER_HEIGHT },
		{ LADDER_V_X_CORD, PLATFORM_I_HEIGHT, LADDER_V_HEIGHT }
	};

	for (int i = 0; i < NUMBER_OF_LADDERS; i++)
	{
		stage->ladders[i].upperCorner.x = laddersParameters[i][0];
		stage->ladders[i].upperCorner.y = laddersParameters[i][1];
		stage->ladders[i].height = laddersParameters[i][2];
	}
}

void drawLadders(Stage* stage, SDLConst* SDL, Color* colors)
{
	for (int i = 0; i < NUMBER_OF_LADDERS; i++)
		DrawRectangle(SDL->screen, stage->ladders[i].upperCorner.x, stage->ladders[i].upperCorner.y, stage->ladders[i].width, stage->ladders[i].height, colors->black, colors->grey);
}

void createTrophies(Stage* stage)
{
	int trophiesParameters[NUMBER_OF_TROPHIES][TWO] = {
		{ TROPHIES1_I_SPAWN_POINT_X, PLATFORM_I_HEIGHT - TROPHIES_DIFFERENCE_IN_Y },
		{ TROPHIES1_II_SPAWN_POINT_X, PLATFORM_II_HEIGHT - TROPHIES_DIFFERENCE_IN_Y },
		{ TROPHIES1_III_SPAWN_POINT_X, PLATFORM_IV_HEIGHT - TROPHIES_DIFFERENCE_IN_Y }
	};

	for (int i = 0; i < NUMBER_OF_TROPHIES; i++)
	{
		stage->trophies[i].lowerCoordinates.x = trophiesParameters[i][0];
		stage->trophies[i].lowerCoordinates.y = trophiesParameters[i][1];
		stage->trophies[i].animation = { 0, 0, TROPHIES_REAL_SIZE, TROPHIES_REAL_SIZE };
	}
}

void drawTrophies(Stage* stage, SDLConst* SDL)
{
	for (int i = 0; i < NUMBER_OF_TROPHIES; i++)
		DrawSurface(SDL->screen, SDL->trophy, stage->trophies[i].lowerCoordinates.x, stage->trophies[i].lowerCoordinates.y, &stage->trophies[i].animation);
}

void createPlatforms2(Stage* stage)
{
	//platformsParameters{ X cordinate, Y cordinate, length }
	int platformsParameters[NUMBER_OF_PLATFORMS][THREE] = {
		{ PLATFORM2_I_X_CORD, PLATFORM_I_HEIGHT, PLATFORM2_VI_LENGTH }, { PLATFORM2_II_X_CORD, PLATFORM_I_HEIGHT, PLATFORM2_I_LENGTH },
		{ PLATFORM2_III_X_CORD, PLATFORM_II_HEIGHT, PLATFORM2_II_LENGTH }, { PLATFORM2_IV_X_CORD, PLATFORM_II_HEIGHT, PLATFORM2_V_LENGTH },
		{ PLATFORM2_V_X_CORD, PLATFORM_III_HEIGHT, PLATFORM2_III_LENGTH }, { PLATFORM2_VI_X_CORD, PLATFORM_III_HEIGHT, PLATFORM2_V_LENGTH },
		{ PLATFORM2_VII_X_CORD, PLATFORM_IV_HEIGHT, PLATFORM2_III_LENGTH }, { PLATFORM2_VIII_X_CORD, PLATFORM_IV_HEIGHT, PLATFORM2_I_LENGTH },
		{ PLATFORM2_IX_X_CORD, PLATFORM_IV_HEIGHT, PLATFORM2_IV_LENGTH }, { PLATFORM2_X_X_CORD, PLATFORM_V_HEIGHT, PLATFORM2_III_LENGTH }
	};

	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		stage->platforms[i].upperCorner.x = platformsParameters[i][0];
		stage->platforms[i].upperCorner.y = platformsParameters[i][1];
		stage->platforms[i].length = platformsParameters[i][2];
	}
}

void createTrophies2(Stage* stage)
{
	int trophiesParameters[NUMBER_OF_TROPHIES][TWO] = {
		{ TROPHIES2_I_SPAWN_POINT_X, PLATFORM_I_HEIGHT - TROPHIES_DIFFERENCE_IN_Y },
		{ TROPHIES2_II_SPAWN_POINT_X, PLATFORM_II_HEIGHT - TROPHIES_DIFFERENCE_IN_Y },
		{ TROPHIES2_III_SPAWN_POINT_X, PLATFORM_IV_HEIGHT - TROPHIES_DIFFERENCE_IN_Y }
	};

	for (int i = 0; i < NUMBER_OF_TROPHIES; i++)
	{
		stage->trophies[i].lowerCoordinates.x = trophiesParameters[i][0];
		stage->trophies[i].lowerCoordinates.y = trophiesParameters[i][1];
		stage->trophies[i].animation = { 0, 0, TROPHIES_REAL_SIZE, TROPHIES_REAL_SIZE };
	}
}

void createPlatforms3(Stage* stage)
{
	//platformsParameters{ X cordinate, Y cordinate, length }
	int platformsParameters[NUMBER_OF_PLATFORMS][THREE] = {
		{ PLATFORM3_I_X_CORD, PLATFORM_I_HEIGHT, PLATFORM3_V_LENGTH }, { PLATFORM3_II_X_CORD, PLATFORM_I_HEIGHT, PLATFORM3_III_LENGTH },
		{ PLATFORM3_III_X_CORD, PLATFORM_II_HEIGHT, PLATFORM3_I_LENGTH },{ PLATFORM3_IV_X_CORD, PLATFORM_II_HEIGHT, PLATFORM3_VII_LENGTH },
		{ PLATFORM3_V_X_CORD, PLATFORM_II_HEIGHT, PLATFORM3_II_LENGTH }, { PLATFORM3_VI_X_CORD, PLATFORM_III_HEIGHT, PLATFORM3_VI_LENGTH },
		{ PLATFORM3_VII_X_CORD, PLATFORM_III_HEIGHT, PLATFORM3_IV_LENGTH },{ PLATFORM3_VIII_X_CORD, PLATFORM_IV_HEIGHT, PLATFORM3_IV_LENGTH },
		{ PLATFORM3_IX_X_CORD, PLATFORM_IV_HEIGHT, PLATFORM3_V_LENGTH },{ PLATFORM3_X_X_CORD, PLATFORM_V_HEIGHT, PLATFORM3_III_LENGTH }
	};

	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		stage->platforms[i].upperCorner.x = platformsParameters[i][0];
		stage->platforms[i].upperCorner.y = platformsParameters[i][1];
		stage->platforms[i].length = platformsParameters[i][2];
	}
}

void createTrophies3(Stage* stage)
{
	int trophiesParameters[NUMBER_OF_TROPHIES][TWO] = {
		{ TROPHIES3_I_SPAWN_POINT_X, PLATFORM_II_HEIGHT - TROPHIES_DIFFERENCE_IN_Y },
		{ TROPHIES3_II_SPAWN_POINT_X, PLATFORM_II_HEIGHT - TROPHIES_DIFFERENCE_IN_Y },
		{ TROPHIES3_III_SPAWN_POINT_X, PLATFORM_IV_HEIGHT - TROPHIES_DIFFERENCE_IN_Y }
	};

	for (int i = 0; i < NUMBER_OF_TROPHIES; i++)
	{
		stage->trophies[i].lowerCoordinates.x = trophiesParameters[i][0];
		stage->trophies[i].lowerCoordinates.y = trophiesParameters[i][1];
		stage->trophies[i].animation = { 0, 0, TROPHIES_REAL_SIZE, TROPHIES_REAL_SIZE };
	}
}

void createLives(Stage* stage)
{
	for (int i = 0; i < stage->playerInfo.lives; i++)
	{
		stage->lives[i].lowerCoordinates.x = LIVES_SPAWN_POINT_X + (LIVES_REAL_SIZE * i);
		stage->lives[i].lowerCoordinates.y = HUNDRED_ROW + THREE;
		stage->lives[i].animation = { 0, 0, stage->lives[i].realSize[0], stage->lives[i].realSize[1] };
	}
}

void  drawLives(Stage* stage, SDLConst* SDL)
{
	for (int i = 0; i < PLAYER_DEFAULT_LIVES; i++)
		DrawSurface(SDL->screen, SDL->lives, stage->lives[i].lowerCoordinates.x, stage->lives[i].lowerCoordinates.y, &stage->lives[i].animation);
}

void drawPlatformsFromFile(Stage* stage, SDLConst* SDL, Color* colors)
{
	platformColor(stage, colors);
	for (int i = 0; i < stage->numberOfPlatformsInFile; i++)
		DrawRectangle(SDL->screen, stage->platforms[i].upperCorner.x, stage->platforms[i].upperCorner.y, stage->platforms[i].length, stage->platforms[i].width, colors->black, stage->platformColor.platformColor);
}

void drawLaddersFromFile(Stage* stage, SDLConst* SDL, Color* colors)
{
	for (int i = 0; i < stage->numberOfLaddersInFile; i++)
		DrawRectangle(SDL->screen, stage->ladders[i].upperCorner.x, stage->ladders[i].upperCorner.y, stage->ladders[i].width, stage->ladders[i].height, colors->black, colors->grey);
}

void drawBarrelsFromFile(Stage* stage, SDLConst* SDL, Color* colors)
{
	for (int i = 0; i < stage->numberOfBarrelsInFile; i++)
	{
		DrawSurface(SDL->screen, SDL->barrel, stage->barrels[i].lowerRightCoordinates.x, stage->barrels[i].lowerRightCoordinates.y, &stage->barrels[i].animation);
	}
}

void drawTrohpiesFromFile(Stage* stage, SDLConst* SDL, Color* colors)
{
	for (int i = 0; i < stage->numberOfTrohpiesInFile; i++)
	{
		
		DrawSurface(SDL->screen, SDL->trophy, stage->trophies[i].lowerCoordinates.x, stage->trophies[i].lowerCoordinates.y, &stage->trophies[i].animation);
	}
}
