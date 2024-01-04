#pragma once
#define USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "structures.h"
#include "define.h"
#include "SDLFunctions.h"

extern "C" {
#include"../SDL2-2.0.10/include/SDL.h"
#include"../SDL2-2.0.10/include/SDL_main.h"
}

void initializeColors(Color* colors);


void createPlatforms(Platform* platforms);

void drawPlatforms(Color* colors, Platform* platforms);


void createLadders(Ladder* ladders);

void drawLadders(Color* colors, Ladder* ladders);


void createBarrels(Barrel* barrels);

void drawBarrels(Barrel* barrels);


void createTrophies(Trophy* trophies);

void drawTrophies(Trophy* trophies);


void initializeGameObjects(Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies);


void barrelsApproximateOnPlatform(Platform* platforms, Barrel* barrels);

void areBarrelsOnGround(Barrel* barrels);

void whereAreBarrels(Platform* platforms, Barrel* barrels);


void barrelBowling(Barrel* barrels, GameInfo* gameInfo);

void barrelFalling(Barrel* barrels, GameInfo* gameInfo);

void barrelMovement(Barrel* barrels, GameInfo* gameInfo);


void initializeColors(Color* colors)
{
	colors->black = SDL_MapRGB(SDL.screen->format, 0x00, 0x00, 0x00);
	colors->white = SDL_MapRGB(SDL.screen->format, 255, 255, 255);
	colors->blue = SDL_MapRGB(SDL.screen->format, 0x11, 0x11, 0xCC);
	colors->green = SDL_MapRGB(SDL.screen->format, 0x00, 0xFF, 0x00);
	colors->red = SDL_MapRGB(SDL.screen->format, 0xFF, 0x00, 0x00);
	colors->pink = SDL_MapRGB(SDL.screen->format, 214, 136, 150);
	colors->indygo = SDL_MapRGB(SDL.screen->format, 85, 120, 200);
	colors->lime = SDL_MapRGB(SDL.screen->format, 152, 190, 100);
	colors->grey = SDL_MapRGB(SDL.screen->format, 160, 160, 160);
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
		platforms[i].upperXCorner = platformsParameters[i][0];
		platforms[i].upperYCorner = platformsParameters[i][1];
		platforms[i].length = platformsParameters[i][2];
	}
}

void drawPlatforms(Color* colors, Platform* platforms) {

	for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
		DrawRectangle(SDL.screen, platforms[i].upperXCorner, platforms[i].upperYCorner, platforms[i].length, platforms[i].width, colors->black, colors->pink);

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

void drawLadders(Color* colors, Ladder* ladders)
{
	for (int i = 0; i < NUMBER_OF_LADDERS; i++)
		DrawRectangle(SDL.screen, ladders[i].upperXCorner, ladders[i].upperYCorner, ladders[i].width, ladders[i].height, colors->black, colors->grey);
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
		barrels[i].lowerXCorner = barrelsParameters[i][0];
		barrels[i].lowerYCorner = barrelsParameters[i][1];
		barrels[i].fallDown = barrelsParameters[i][2];
		barrels[i].onPlatform = barrelsParameters[i][3];
		barrels[i].onGround = barrelsParameters[i][4];
		barrels[i].animation = { ZERO, ZERO, barrels[i].realSize[0], barrels[i].realSize[1] };
	}
}

void drawBarrels(Barrel* barrels)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
		DrawSurface(SDL.screen, SDL.barrel, barrels[i].lowerXCorner, barrels[i].lowerYCorner, &barrels[i].animation);
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
		trophies[i].lowerXCorner = trophiesParameters[i][0];
		trophies[i].lowerYCorner = trophiesParameters[i][1];
		trophies[i].animation = { ZERO, ZERO, 20, 20 };
	}
}

void drawTrophies(Trophy* trophies)
{
	for (int i = 0; i < NUMBER_OF_TROPHIES; i++)
		DrawSurface(SDL.screen, SDL.trophy, trophies[i].lowerXCorner, trophies[i].lowerYCorner, &trophies[i].animation);
}

void initializeGameObjects(Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies)
{
	createPlatforms(platforms);
	createLadders(ladders);
	createBarrels(barrels);
	createTrophies(trophies);
}

void barrelsApproximateOnPlatform(Platform* platforms, Barrel* barrels)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		barrels[i].onPlatform = false;
		for (int j = 0; j < NUMBER_OF_PLATFORMS; j++)
		{
			if (barrels[i].lowerYCorner + barrels[i].fallingSpeed + BARRELS_DIFFERENCE_IN_Y >= platforms[j].upperYCorner &&
				barrels[i].lowerYCorner - barrels[i].realSize[1] <= platforms[j].upperYCorner + platforms[j].width &&
				platforms[j].upperXCorner <= barrels[i].lowerXCorner &&
				barrels[i].lowerXCorner - barrels[i].realSize[0] <= platforms[j].upperXCorner + platforms[j].length)
			{
				barrels[i].lowerYCorner = platforms[j].upperYCorner + BARRELS_DIFFERENCE_IN_Y;
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
		if (barrels[i].lowerYCorner + barrels[i].fallingSpeed >= GROUND_HEIGHT)
			barrels[i].onGround = true;
		else
			barrels[i].onGround = false;

		if (barrels[i].onGround)
		{
			if (barrels[i].lowerXCorner < SCREEN_WIDTH / 2)
				barrels[i].speedX = barrels[i].bowlingSpeed;
			if (barrels[i].lowerXCorner < SCREEN_WIDTH)
				barrels[i].speedX = -barrels[i].bowlingSpeed;
			barrels[i].lowerYCorner = BARRELS_SPAWN_POINT_Y;
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
			barrels[i].lowerXCorner += barrels[i].speedX * gameInfo->deltaTime;
		if (barrels[i].lowerXCorner >= SCREEN_WIDTH)
			barrels[i].speedX = -barrels[i].bowlingSpeed;
	}
}

void barrelFalling(Barrel* barrels, GameInfo* gameInfo)
{
	for (int i = 0; i < NUMBER_OF_BARRELS; i++)
	{
		if (!barrels[i].onPlatform && !barrels[i].onGround)
			barrels[i].fallDown = true;
		if (barrels[i].fallDown)
			barrels[i].lowerYCorner += barrels[i].fallingSpeed * gameInfo->deltaTime;
	}
}

void barrelMovement(Barrel* barrels, GameInfo* gameInfo)
{
	barrelBowling(barrels, gameInfo);
	barrelFalling(barrels, gameInfo);
}