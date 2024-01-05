#pragma once
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "structures.h"
#include "define.h"
#include "ObjectsFunctions.h"
#include "PlayerFunctions.h"
#include "SDLFunctions.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

void createWindow(GameInfo* gameInfo);

void printInfo(GameInfo* gameInfo, PlayerInfo* playerInfo, Color* colors);

void drawScene(Color* colors, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies);

void displayWindow(GameInfo* gameInfo, PlayerInfo* playerInfo, Color* colors, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies);

void refreshWindow();

void printGameInfo(GameInfo* gameInfo, Color* colors);

void printPlayerInfo(GameInfo* gameInfo, PlayerInfo* playerInfo, Color* colors);

void defaultSettings(GameInfo* gameInfo, PlayerInfo* playerInfo); //set up the game at the beginning

void newGameSettings(GameInfo* gameInfo, PlayerInfo* playerInfo, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies); //set up settings after pressing "n"

void loadStageSettings(GameInfo* gameInfo, PlayerInfo* playerInfo); //NOT USED

void timeCounting(GameInfo* gameInfo); //counting the game time

void readKeys(GameInfo* gameInfo, PlayerInfo* playerInfo, Score* score, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies); //read key input

void SDLSpace(); //freeing all surfaces

void quit(GameInfo* gameInfo);


void createWindow(GameInfo* gameInfo) // Create a window with specified size. Also create renderer for this window, renderer meaning a thing actually showing/drawing/rendering stuff
{
	gameInfo->err = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&SDL.window, &SDL.renderer);
	if (gameInfo->err != 0)
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

void printInfo(GameInfo* gameInfo, PlayerInfo* playerInfo, Color* colors)
{
	printGameInfo(gameInfo,colors);
	printPlayerInfo(gameInfo, playerInfo, colors);
}

void drawScene(Color* colors, Platform* platforms, Ladder* ladders, Barrel* barrels,Trophy* trophies)
{
	drawGround(colors);
	drawPlatforms(colors, platforms);
	drawLadders(colors, ladders);
	drawTrophies(trophies);
	drawBarrels(barrels);
} 

void displayWindow(GameInfo* gameInfo, PlayerInfo* playerInfo, Color* colors, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies)
{
	SDL_FillRect(SDL.screen, ZERO, colors->black); //because FillRect in second parameter has NULL this function fill in the color of the window (into black)
	drawScene(colors, platforms, ladders, barrels,trophies);
	printInfo(gameInfo, playerInfo,colors);
	DrawSurface(SDL.screen, SDL.player, Mario.lowerCoordinates.x + PLAYER_DIFFERENCE_IN_X, Mario.lowerCoordinates.y + PLAYER_DIFFERENCE_IN_Y, &Mario.animation); //draws the player
}

void refreshWindow()
{
	SDL_UpdateTexture(SDL.scrtex, ZERO, SDL.screen->pixels, SDL.screen->pitch);
	SDL_RenderCopy(SDL.renderer, SDL.scrtex, ZERO, ZERO);
	SDL_RenderPresent(SDL.renderer);
}

void printGameInfo(GameInfo* gameInfo, Color* colors)
{
	DrawRectangle(SDL.screen, ZERO_COLUMN, FIRST_ROW, SCREEN_WIDTH, TABLE_HEIGHT, colors->white, colors->black);
	sprintf(gameInfo->text, "King Donkey");
	DrawString(SDL.screen, SDL.screen->w / 2 - strlen(gameInfo->text) * 8 / 2, TITLE_ROW, gameInfo->text, SDL.charset);
	sprintf(gameInfo->text, "Time from beginning: %.1lf s", gameInfo->gameTime);
	DrawString(SDL.screen, SDL.screen->w / 2 - strlen(gameInfo->text) * 8 / 2, TIME_ROW, gameInfo->text, SDL.charset);
	sprintf(gameInfo->text, "Esc - quit, n - new game ");
	DrawString(SDL.screen, SDL.screen->w / 2 - strlen(gameInfo->text) * 8 / 2, OPTIONS_ROW, gameInfo->text, SDL.charset);
	sprintf(gameInfo->text, "\30 - move up \31 - move down \32 - move left \33 - move right SPACE - jump");
	DrawString(SDL.screen, SDL.screen->w / 2 - strlen(gameInfo->text) * 8 / 2, KEYS_ROW, gameInfo->text, SDL.charset);
	sprintf(gameInfo->text, "Author: Tomasz Kruczalak 198049");
	DrawString(SDL.screen, ZERO_COLUMN, AUTHOR_INFO_ROW, gameInfo->text, SDL.charset);
}

void printPlayerInfo(GameInfo* gameInfo, PlayerInfo* playerInfo, Color* colors)
{
	DrawRectangle(SDL.screen, ZERO_COLUMN, SEVENTY_ROW, ONE_HUNDRED_TWENTY, THIRTY_FIVE, colors->white, colors->black);
	sprintf(gameInfo->text, "Score: %.6d", playerInfo->score);
	DrawString(SDL.screen, TEN_COLUMN, SEVENTY_FIVE_ROW, gameInfo->text, SDL.charset);
	sprintf(gameInfo->text, "Lives: %d", playerInfo->lives);
	DrawString(SDL.screen, TEN_COLUMN, NINETY_ROW, gameInfo->text, SDL.charset);
	sprintf(gameInfo->text, "Trophies:");
	DrawString(SDL.screen, FIVE_HUNDRED_COLUMN, AUTHOR_INFO_ROW, gameInfo->text, SDL.charset);
	sprintf(gameInfo->text, "LeftLowerXCorner: %.0f", Mario.lowerCoordinates.x);
	DrawString(SDL.screen, TEN_COLUMN, ONE_HUNDRED_FIFTHY_COLUMN, gameInfo->text, SDL.charset);
	sprintf(gameInfo->text, "LeftLowerYCorner: %.0f", Mario.lowerCoordinates.y);
	DrawString(SDL.screen, TEN_COLUMN, ONE_HUNDRED_SEVENTY_COLUMN, gameInfo->text, SDL.charset);
}

void defaultSettings(GameInfo* gameInfo, PlayerInfo* playerInfo)
{
	gameInfo->quit = false;
	gameInfo->gameTime = ZERO;
	playerInfo->score = PLAYER_DEFAULT_POINTS;
	playerInfo->lives = PLAYER_DEFAULT_LIVES;
	initializePlayer();
}

void newGameSettings(GameInfo* gameInfo, PlayerInfo* playerInfo, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies)
{
	defaultSettings(gameInfo, playerInfo);
	initializeGameObjects(platforms, ladders, barrels, trophies);
}

void loadStageSettings(GameInfo* gameInfo, PlayerInfo* playerInfo)
{
	gameInfo->quit = false;
	playerInfo->score = playerInfo->score;
	playerInfo->lives = playerInfo->lives;
	initializePlayer();
}

void timeCounting(GameInfo* gameInfo)
{
	gameInfo->deltaTime = (gameInfo->t2 - gameInfo->t1) * MILI;
	gameInfo->t1 = gameInfo->t2;
	gameInfo->gameTime += gameInfo->deltaTime;
}

// TODO przejrzystosc kodu
void readKeys(GameInfo* gameInfo, PlayerInfo* playerInfo, Score* score, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies)
{
	while (SDL_PollEvent(&SDL.event))
	{
		int keyPressed = SDL.event.key.keysym.sym;
		switch (SDL.event.type)
		{
		case SDL_KEYDOWN:
			if (keyPressed == SDLK_ESCAPE)
				quit(gameInfo);
			else if (keyPressed == SDLK_n)
				newGameSettings(gameInfo, playerInfo, platforms, ladders, barrels, trophies);
			else if (keyPressed == SDLK_RIGHT)
				playerWalkRight();
			else if (keyPressed == SDLK_LEFT)
				playerWalkLeft();
			else if (keyPressed == SDLK_DOWN)
				playerClimbDown();
			else if (keyPressed == SDLK_UP)
				playerClimbUp();
			else if (keyPressed == SDLK_SPACE)
				checkIfPlayerIsJumping();
			break;
		case SDL_KEYUP:
			playerNotWalking();
			if (keyPressed == SDLK_DOWN || keyPressed == SDLK_UP)
				playerNotClimbing();
			break;		
		case SDL_QUIT: //X button in right up corner
			quit(gameInfo);
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
	SDL_FreeSurface(SDL.trophy);
	SDL_DestroyTexture(SDL.scrtex);
	SDL_DestroyRenderer(SDL.renderer);
	SDL_DestroyWindow(SDL.window);
}

void quit(GameInfo* gameInfo)
{
	gameInfo->quit = true;
	SDLSpace();
	SDL_Quit();
}
