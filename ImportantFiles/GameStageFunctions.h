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

void createPlatforms(Platform* platforms);

void drawPlatforms(Stage* stage, StageSpecifier* stageSpecifier, SDLConst* SDL, Color* colors, Platform* platforms);

void platformColor(Stage* stage, StageSpecifier* stageSpecifier, Color* colors);

void createLadders(Ladder* ladders);

void drawLadders(SDLConst* SDL, Color* colors, Ladder* ladders);

void createTrophies(Trophy* trophies);

void drawTrophies(SDLConst* SDL, Trophy* trophies);

void createPlatforms2(Platform* platforms);

void createLadders2(Ladder* ladders);

void createTrophies2(Trophy* trophies);

void createPlatforms3(Platform* platforms);

void createLadders3(Ladder* ladders);

void createTrophies3(Trophy* trophies);


void drawGround(SDLConst* SDL, Color* colors)
{
	DrawLine(SDL->screen, ZERO_COLUMN, GROUND_HEIGHT, SCREEN_WIDTH, 1, 0, colors->white);
}

void createPlatforms(Platform* platforms)
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
		platforms[i].upperCorner.x = platformsParameters[i][0];
		platforms[i].upperCorner.y = platformsParameters[i][1];
		platforms[i].length = platformsParameters[i][2];
	}
}

void drawPlatforms(Stage* stage, StageSpecifier* stageSpecifier, SDLConst* SDL, Color* colors, Platform* platforms)
{
	platformColor(stage, stageSpecifier, colors);
	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
		DrawRectangle(SDL->screen, platforms[i].upperCorner.x, platforms[i].upperCorner.y, platforms[i].length, platforms[i].width, colors->black, stage->platformColor.platformColor);
}

void platformColor(Stage* stage, StageSpecifier* stageSpecifier, Color* colors)
{
	if (*stageSpecifier == STAGE1)
	{
		colors->platformColor = colors->pink;
		stage->platformColor.platformColor = colors->platformColor;
	}
	else if (*stageSpecifier == STAGE2)
	{
		colors->platformColor = colors->indygo;
		stage->platformColor.platformColor = colors->platformColor;
	}
	else if (*stageSpecifier == STAGE3)
	{
		colors->platformColor = colors->lime;
		stage->platformColor.platformColor = colors->platformColor;
	}
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
		ladders[i].upperCorner.x = laddersParameters[i][0];
		ladders[i].upperCorner.y = laddersParameters[i][1];
		ladders[i].height = laddersParameters[i][2];
	}
}

void drawLadders(SDLConst* SDL, Color* colors, Ladder* ladders)
{
	for (int i = 0; i < NUMBER_OF_LADDERS; i++)
		DrawRectangle(SDL->screen, ladders[i].upperCorner.x, ladders[i].upperCorner.y, ladders[i].width, ladders[i].height, colors->black, colors->grey);
}

void createTrophies(Trophy* trophies)
{
	int trophiesParameters[NUMBER_OF_TROPHIES][2] = {
		{TROPHIES_I_SPAWN_POINT_X,PLATFORM_I_HEIGHT - TROPHIES_DIFFERENCE_IN_Y},
		{TROPHIES_II_SPAWN_POINT_X,PLATFORM_II_HEIGHT - TROPHIES_DIFFERENCE_IN_Y},
		{TROPHIES_III_SPAWN_POINT_X,PLATFORM_IV_HEIGHT - TROPHIES_DIFFERENCE_IN_Y}
	};

	for (int i = 0; i < NUMBER_OF_TROPHIES; i++)
	{
		trophies[i].lowerCoordinates.x = trophiesParameters[i][0];
		trophies[i].lowerCoordinates.y = trophiesParameters[i][1];
		trophies[i].animation = { ZERO, ZERO, 20, 20 };
	}
}

void drawTrophies(SDLConst* SDL, Trophy* trophies)
{
	for (int i = 0; i < NUMBER_OF_TROPHIES; i++)
		DrawSurface(SDL->screen, SDL->trophy, trophies[i].lowerCoordinates.x, trophies[i].lowerCoordinates.y, &trophies[i].animation);
}

void createPlatforms2(Platform* platforms)
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
		platforms[i].upperCorner.x = platformsParameters[i][0];
		platforms[i].upperCorner.y = platformsParameters[i][1];
		platforms[i].length = platformsParameters[i][2];
	}
}

void createLadders2(Ladder* ladders)
{
	//laddersParameters {X cordinate, Y cordinate, ladder height}
	int laddersParameters[NUMBER_OF_LADDERS][3] = {
		{340,PLATFORM_V_HEIGHT,160}, {600,PLATFORM_IV_HEIGHT,LADDER_HEIGHT},
		{150,PLATFORM_III_HEIGHT,LADDER_HEIGHT}, {550,PLATFORM_II_HEIGHT,LADDER_HEIGHT},
		{110,PLATFORM_I_HEIGHT,60}
	};

	for (int i = 0; i < NUMBER_OF_LADDERS; i++)
	{
		ladders[i].upperCorner.x = laddersParameters[i][0];
		ladders[i].upperCorner.y = laddersParameters[i][1];
		ladders[i].height = laddersParameters[i][2];
	}
}

void createTrophies2(Trophy* trophies)
{
	int trophiesParameters[NUMBER_OF_TROPHIES][2] = {
		{670,PLATFORM_I_HEIGHT - TROPHIES_DIFFERENCE_IN_Y},
		{70,PLATFORM_II_HEIGHT - TROPHIES_DIFFERENCE_IN_Y},
		{400,PLATFORM_IV_HEIGHT - TROPHIES_DIFFERENCE_IN_Y}
	};

	for (int i = 0; i < NUMBER_OF_TROPHIES; i++)
	{
		trophies[i].lowerCoordinates.x = trophiesParameters[i][0];
		trophies[i].lowerCoordinates.y = trophiesParameters[i][1];
		trophies[i].animation = { ZERO, ZERO, 20, 20 };
	}
}

void createPlatforms3(Platform* platforms)
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
		platforms[i].upperCorner.x = platformsParameters[i][0];
		platforms[i].upperCorner.y = platformsParameters[i][1];
		platforms[i].length = platformsParameters[i][2];
	}
}

void createLadders3(Ladder* ladders)
{
	//laddersParameters {X cordinate, Y cordinate, ladder height}
	int laddersParameters[NUMBER_OF_LADDERS][3] = {
		{365,PLATFORM_V_HEIGHT,160}, {600,PLATFORM_IV_HEIGHT,LADDER_HEIGHT},
		{150,PLATFORM_III_HEIGHT,LADDER_HEIGHT}, {550,PLATFORM_II_HEIGHT,LADDER_HEIGHT},
		{110,PLATFORM_I_HEIGHT,60}
	};

	for (int i = 0; i < NUMBER_OF_LADDERS; i++)
	{
		ladders[i].upperCorner.x = laddersParameters[i][0];
		ladders[i].upperCorner.y = laddersParameters[i][1];
		ladders[i].height = laddersParameters[i][2];
	}
}

void createTrophies3(Trophy* trophies)
{
	int trophiesParameters[NUMBER_OF_TROPHIES][2] = {
		{675,PLATFORM_II_HEIGHT - TROPHIES_DIFFERENCE_IN_Y},
		{TROPHIES_II_SPAWN_POINT_X,PLATFORM_II_HEIGHT - TROPHIES_DIFFERENCE_IN_Y},
		{TROPHIES_III_SPAWN_POINT_X,PLATFORM_IV_HEIGHT - TROPHIES_DIFFERENCE_IN_Y}
	};

	for (int i = 0; i < NUMBER_OF_TROPHIES; i++)
	{
		trophies[i].lowerCoordinates.x = trophiesParameters[i][0];
		trophies[i].lowerCoordinates.y = trophiesParameters[i][1];
		trophies[i].animation = { ZERO, ZERO, 20, 20 };
	}
}