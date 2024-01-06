#pragma once
#define USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "define.h"
#include "structures.h"
#include "GameStructure.h"
#include "GeneralFunctions.h"
#include "PlayerFunctions.h"
#include "SDLFunctions.h"

extern "C" {
#include"../SDL2-2.0.10/include/SDL.h"
#include"../SDL2-2.0.10/include/SDL_main.h"
}

void drawGround(SDLConst* SDL, Color* colors);

void createPlatforms(Stage* stage);

void drawPlatforms(Stage* stage, SDLConst* SDL, Color* colors);

void platformColor(Stage* stage, Color* colors);

void createLadders(Stage* stage);

void drawLadders(Stage* stage, SDLConst* SDL, Color* colors);

void createTrophies(Stage* stage);

void drawTrophies(Stage* stage, SDLConst* SDL);

void createPlatforms2(Stage* stage);

void createLadders2(Stage* stage);

void createTrophies2(Stage* stage);

void createPlatforms3(Stage* stage);

void createLadders3(Stage* stage);

void createTrophies3(Stage* stage);


void drawGround(SDLConst* SDL, Color* colors)
{
	DrawLine(SDL->screen, ZERO_COLUMN, GROUND_HEIGHT, SCREEN_WIDTH, 1, 0, colors->white);
}

void createPlatforms(Stage* stage)
{
	//platformsParameters{ X cordinate, Y cordinate, length }
	int platformsParameters[NUMBER_OF_PLATFORMS][3] = {
		{60,PLATFORM_I_HEIGHT,350}, {520,PLATFORM_I_HEIGHT,160},
		{440,PLATFORM_II_HEIGHT,160}, { 40,PLATFORM_II_HEIGHT,350 },
		{ 480,PLATFORM_III_HEIGHT,200 }, { 340,PLATFORM_III_HEIGHT,80 },
		{ 60,PLATFORM_III_HEIGHT,240 }, { 100,PLATFORM_IV_HEIGHT,240 },
		{ 470,PLATFORM_IV_HEIGHT,245 }, { 280,PLATFORM_V_HEIGHT,160 }
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
}

void createLadders(Stage* stage)
{
	//laddersParameters {X cordinate, Y cordinate, ladder height}
	int laddersParameters[NUMBER_OF_LADDERS][3] = {
		{365,PLATFORM_V_HEIGHT,160}, {600,PLATFORM_IV_HEIGHT,LADDER_HEIGHT},
		{150,PLATFORM_III_HEIGHT,LADDER_HEIGHT}, {550,PLATFORM_II_HEIGHT,LADDER_HEIGHT},
		{110,PLATFORM_I_HEIGHT,60}
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
	int trophiesParameters[NUMBER_OF_TROPHIES][2] = {
		{TROPHIES_I_SPAWN_POINT_X,PLATFORM_I_HEIGHT - TROPHIES_DIFFERENCE_IN_Y},
		{TROPHIES_II_SPAWN_POINT_X,PLATFORM_II_HEIGHT - TROPHIES_DIFFERENCE_IN_Y},
		{TROPHIES_III_SPAWN_POINT_X,PLATFORM_IV_HEIGHT - TROPHIES_DIFFERENCE_IN_Y}
	};

	for (int i = 0; i < NUMBER_OF_TROPHIES; i++)
	{
		stage->trophies[i].lowerCoordinates.x = trophiesParameters[i][0];
		stage->trophies[i].lowerCoordinates.y = trophiesParameters[i][1];
		stage->trophies[i].animation = { ZERO, ZERO, 20, 20 };
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
	int platformsParameters[NUMBER_OF_PLATFORMS][3] = {
		{60,PLATFORM_I_HEIGHT,550}, {650,PLATFORM_I_HEIGHT,60},
		{440,PLATFORM_II_HEIGHT,160}, { 40,PLATFORM_II_HEIGHT,300 },
		{ 500,PLATFORM_III_HEIGHT,200 }, { 100,PLATFORM_III_HEIGHT,300 },
		{ 100,PLATFORM_IV_HEIGHT,200 }, { 380,PLATFORM_IV_HEIGHT,60 },
		{ 470,PLATFORM_IV_HEIGHT,240 },	{ 260,PLATFORM_V_HEIGHT,200 }
	};

	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		stage->platforms[i].upperCorner.x = platformsParameters[i][0];
		stage->platforms[i].upperCorner.y = platformsParameters[i][1];
		stage->platforms[i].length = platformsParameters[i][2];
	}
}

void createLadders2(Stage* stage)
{
	//laddersParameters {X cordinate, Y cordinate, ladder height}
	int laddersParameters[NUMBER_OF_LADDERS][3] = {
		{340,PLATFORM_V_HEIGHT,160}, {600,PLATFORM_IV_HEIGHT,LADDER_HEIGHT},
		{150,PLATFORM_III_HEIGHT,LADDER_HEIGHT}, {550,PLATFORM_II_HEIGHT,LADDER_HEIGHT},
		{110,PLATFORM_I_HEIGHT,60}
	};

	for (int i = 0; i < NUMBER_OF_LADDERS; i++)
	{
		stage->ladders[i].upperCorner.x = laddersParameters[i][0];
		stage->ladders[i].upperCorner.y = laddersParameters[i][1];
		stage->ladders[i].height = laddersParameters[i][2];
	}
}

void createTrophies2(Stage* stage)
{
	int trophiesParameters[NUMBER_OF_TROPHIES][2] = {
		{670,PLATFORM_I_HEIGHT - TROPHIES_DIFFERENCE_IN_Y},
		{70,PLATFORM_II_HEIGHT - TROPHIES_DIFFERENCE_IN_Y},
		{400,PLATFORM_IV_HEIGHT - TROPHIES_DIFFERENCE_IN_Y}
	};

	for (int i = 0; i < NUMBER_OF_TROPHIES; i++)
	{
		stage->trophies[i].lowerCoordinates.x = trophiesParameters[i][0];
		stage->trophies[i].lowerCoordinates.y = trophiesParameters[i][1];
		stage->trophies[i].animation = { ZERO, ZERO, 20, 20 };
	}
}

void createPlatforms3(Stage* stage)
{
	//platformsParameters{ X cordinate, Y cordinate, length }
	int platformsParameters[NUMBER_OF_PLATFORMS][3] = {
		{ 60,PLATFORM_I_HEIGHT,240 }, { 660, PLATFORM_II_HEIGHT,40 },
		{ 450,PLATFORM_I_HEIGHT,180 },{ 40,PLATFORM_II_HEIGHT,350 },
		{ 440,PLATFORM_II_HEIGHT,160 }, { 100,PLATFORM_III_HEIGHT,300 },
		{ 500,PLATFORM_III_HEIGHT,220 },{ 60,PLATFORM_IV_HEIGHT,220 },
		{ 420,PLATFORM_IV_HEIGHT,250 },	{ 260,PLATFORM_V_HEIGHT,200 }
	};

	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
	{
		stage->platforms[i].upperCorner.x = platformsParameters[i][0];
		stage->platforms[i].upperCorner.y = platformsParameters[i][1];
		stage->platforms[i].length = platformsParameters[i][2];
	}
}

void createLadders3(Stage* stage)
{
	//laddersParameters {X cordinate, Y cordinate, ladder height}
	int laddersParameters[NUMBER_OF_LADDERS][3] = {
		{365,PLATFORM_V_HEIGHT,160}, {600,PLATFORM_IV_HEIGHT,LADDER_HEIGHT},
		{150,PLATFORM_III_HEIGHT,LADDER_HEIGHT}, {550,PLATFORM_II_HEIGHT,LADDER_HEIGHT},
		{110,PLATFORM_I_HEIGHT,60}
	};

	for (int i = 0; i < NUMBER_OF_LADDERS; i++)
	{
		stage->ladders[i].upperCorner.x = laddersParameters[i][0];
		stage->ladders[i].upperCorner.y = laddersParameters[i][1];
		stage->ladders[i].height = laddersParameters[i][2];
	}
}

void createTrophies3(Stage* stage)
{
	int trophiesParameters[NUMBER_OF_TROPHIES][2] = {
		{675,PLATFORM_II_HEIGHT - TROPHIES_DIFFERENCE_IN_Y},
		{TROPHIES_II_SPAWN_POINT_X,PLATFORM_II_HEIGHT - TROPHIES_DIFFERENCE_IN_Y},
		{TROPHIES_III_SPAWN_POINT_X,PLATFORM_IV_HEIGHT - TROPHIES_DIFFERENCE_IN_Y}
	};

	for (int i = 0; i < NUMBER_OF_TROPHIES; i++)
	{
		stage->trophies[i].lowerCoordinates.x = trophiesParameters[i][0];
		stage->trophies[i].lowerCoordinates.y = trophiesParameters[i][1];
		stage->trophies[i].animation = { ZERO, ZERO, 20, 20 };
	}
}