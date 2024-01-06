#pragma once
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "define.h"
#include "structures.h"
#include "GameStructure.h"
#include "ObjectsFunctions.h"
#include "PlayerFunctions.h"
#include "SDLFunctions.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

void createWindow(SDLConst* SDL, GameInfo* gameInfo);

void printInfo(SDLConst* SDL, GameInfo* gameInfo, PlayerInfo* playerInfo, Color* colors);

void drawScene(Stage* stage, StageSpecifier* stageSpecifier, SDLConst* SDL, Color* colors, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies);

void displayWindow(Stage* stage, StageSpecifier* stageSpecifier, SDLConst* SDL, GameInfo* gameInfo, PlayerInfo* playerInfo,
Color* colors, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies);

void refreshWindow(SDLConst* SDL);

void printGameInfo(SDLConst* SDL, GameInfo* gameInfo, Color* colors);

void printPlayerInfo(SDLConst* SDL, GameInfo* gameInfo, PlayerInfo* playerInfo, Color* colors);

void defaultSettings(GameInfo* gameInfo, PlayerInfo* playerInfo); //set up the game at the beginning

void newGameSettings(StageSpecifier* stageSpecifier, GameInfo* gameInfo, PlayerInfo* playerInfo,
Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies); //set up settings after pressing "n"

void loadStageSettings(StageSpecifier* stageSpecifier, GameInfo* gameInfo, PlayerInfo* playerInfo,
Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies); //NOT USED

void timeCounting(GameInfo* gameInfo); //counting the game time

void readKeys(Stage* stage, StageSpecifier* stageSpecifier, SDLConst* SDL, GameInfo* gameInfo, PlayerInfo* playerInfo,
Score* score, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies); //read key input

void playerKeyHandle(Stage* stage, StageSpecifier* stageSpecifier, SDLConst* SDL, GameInfo* gameInfo, PlayerInfo* playerInfo,
	Score* score, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies);

void SDLSpace(SDLConst* SDL); //freeing all surfaces

void quit(SDLConst* SDL, GameInfo* gameInfo);

void firstStageSpecify(Stage* stage);

void secondStageSpecify(Stage* stage);

void thirdStageSpecify(Stage* stage);

void handleSpecifier(Stage* stage, StageSpecifier* stageSpecifier, SDLConst* SDL, GameInfo* gameInfo, PlayerInfo* playerInfo,
Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies);

Stage whichStage(Stage* stage, Game* game);

void createWindow(SDLConst* SDL, GameInfo* gameInfo) // Create a window with specified size.
{
	gameInfo->err = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&SDL->window, &SDL->renderer);
	if (gameInfo->err != 0)
	{
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(SDL->renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(SDL->renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(SDL->window, "Tomasz Kruczalak 198049");

	SDL->screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	SDL->scrtex = SDL_CreateTexture(SDL->renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);
}

void printInfo(SDLConst* SDL, GameInfo* gameInfo, PlayerInfo* playerInfo, Color* colors)
{
	printGameInfo(SDL, gameInfo, colors);
	printPlayerInfo(SDL, gameInfo, playerInfo, colors);
}

void drawScene(Stage* stage, StageSpecifier* stageSpecifier, SDLConst* SDL, Color* colors, Platform* platforms, Ladder* ladders, Barrel* barrels,Trophy* trophies)
{
	drawGround(SDL, colors);
	drawPlatforms(stage, stageSpecifier, SDL, colors, platforms);
	drawLadders(SDL, colors, ladders);
	drawTrophies(SDL, trophies);
	drawBarrels(SDL, barrels);

} 

void displayWindow(Stage* stage, StageSpecifier* stageSpecifier,SDLConst* SDL, GameInfo* gameInfo, PlayerInfo* playerInfo,
	Color* colors, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies)
{
	SDL_FillRect(SDL->screen, ZERO, colors->black); //because FillRect in second parameter has NULL this function fill in the color of the window (into black)
	drawScene(stage, &stage->stageSpecifier, SDL, colors, platforms, ladders, barrels, trophies);
	printInfo(SDL, gameInfo, playerInfo, colors);
	DrawSurface(SDL->screen, SDL->player, Mario.lowerCoordinates.x + PLAYER_DIFFERENCE_IN_X, Mario.lowerCoordinates.y + PLAYER_DIFFERENCE_IN_Y, &Mario.animation); //draws the player
}

void refreshWindow(SDLConst* SDL)
{
	SDL_UpdateTexture(SDL->scrtex, ZERO, SDL->screen->pixels, SDL->screen->pitch);
	SDL_RenderCopy(SDL->renderer, SDL->scrtex, ZERO, ZERO);
	SDL_RenderPresent(SDL->renderer);
}

void printGameInfo(SDLConst* SDL, GameInfo* gameInfo, Color* colors)
{
	DrawRectangle(SDL->screen, ZERO_COLUMN, FIRST_ROW, SCREEN_WIDTH, TABLE_HEIGHT, colors->white, colors->black);
	sprintf(gameInfo->text, "King Donkey");
	DrawString(SDL->screen, SDL->screen->w / 2 - strlen(gameInfo->text) * 8 / 2, TITLE_ROW, gameInfo->text, SDL->charset);
	sprintf(gameInfo->text, "Implemented requirements: mandatory, A, B, C, F ");
	DrawString(SDL->screen, SDL->screen->w / 2 - strlen(gameInfo->text) * 8 / 2, REQUIREMENTS_ROW, gameInfo->text, SDL->charset);
	sprintf(gameInfo->text, "Time from beginning: %.1lf s", gameInfo->gameTime);
	DrawString(SDL->screen, SDL->screen->w / 2 - strlen(gameInfo->text) * 8 / 2, TIME_ROW, gameInfo->text, SDL->charset);
	sprintf(gameInfo->text, "Esc - quit, n - new game ");
	DrawString(SDL->screen, SDL->screen->w / 2 - strlen(gameInfo->text) * 8 / 2, OPTIONS_ROW, gameInfo->text, SDL->charset);
	sprintf(gameInfo->text, "\30 - move up \31 - move down \32 - move left \33 - move right SPACE - jump");
	DrawString(SDL->screen, SDL->screen->w / 2 - strlen(gameInfo->text) * 8 / 2, KEYS_ROW, gameInfo->text, SDL->charset);
	sprintf(gameInfo->text, "Author: Tomasz Kruczalak 198049");
	DrawString(SDL->screen, ZERO_COLUMN, AUTHOR_INFO_ROW, gameInfo->text, SDL->charset);
}

void printPlayerInfo(SDLConst* SDL, GameInfo* gameInfo, PlayerInfo* playerInfo, Color* colors)
{
	DrawRectangle(SDL->screen, ZERO_COLUMN, EIGHTY_ROW, ONE_HUNDRED_TWENTY, THIRTY_FIVE, colors->white, colors->black);
	sprintf(gameInfo->text, "Score: %.6d", playerInfo->score);
	DrawString(SDL->screen, TEN_COLUMN, EIGHTY_FIVE_ROW, gameInfo->text, SDL->charset);
	sprintf(gameInfo->text, "Lives: %d", playerInfo->lives);
	DrawString(SDL->screen, TEN_COLUMN, HUNDRED_ROW, gameInfo->text, SDL->charset);
	sprintf(gameInfo->text, "Trophies:");
	DrawString(SDL->screen, FIVE_HUNDRED_COLUMN, AUTHOR_INFO_ROW, gameInfo->text, SDL->charset);
	sprintf(gameInfo->text, "LeftLowerXCorner: %.0f", Mario.lowerCoordinates.x);
	DrawString(SDL->screen, TEN_COLUMN, ONE_HUNDRED_FIFTHY_COLUMN, gameInfo->text, SDL->charset);
	sprintf(gameInfo->text, "LeftLowerYCorner: %.0f", Mario.lowerCoordinates.y);
	DrawString(SDL->screen, TEN_COLUMN, ONE_HUNDRED_SEVENTY_COLUMN, gameInfo->text, SDL->charset);
}

void defaultSettings(GameInfo* gameInfo, PlayerInfo* playerInfo)
{
	gameInfo->quit = false;
	gameInfo->gameTime = ZERO;
	playerInfo->score = PLAYER_DEFAULT_POINTS;
	playerInfo->lives = PLAYER_DEFAULT_LIVES;
	initializePlayer();
}

void newGameSettings(StageSpecifier* stageSpecifier, GameInfo* gameInfo, PlayerInfo* playerInfo,
	Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies)
{
	defaultSettings(gameInfo, playerInfo);
	initializeGameObjects(stageSpecifier, platforms, ladders, barrels, trophies);
}

void loadStageSettings(StageSpecifier* stageSpecifier, GameInfo* gameInfo, PlayerInfo* playerInfo,
	Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies)
{
	gameInfo->quit = false;
	playerInfo->score = playerInfo->score;
	playerInfo->lives = playerInfo->lives;
	initializePlayer();
	initializeGameObjects(stageSpecifier, platforms, ladders, barrels, trophies);
}

void timeCounting(GameInfo* gameInfo)
{
	gameInfo->deltaTime = (gameInfo->t2 - gameInfo->t1) * MILI;
	gameInfo->t1 = gameInfo->t2;
	gameInfo->gameTime += gameInfo->deltaTime;
}

// TODO przejrzystosc kodu
void readKeys(Stage* stage, StageSpecifier* stageSpecifier, SDLConst* SDL, GameInfo* gameInfo, PlayerInfo* playerInfo,
	Score* score, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies)
{
	while (SDL_PollEvent(&SDL->event))
	{
		int keyPressed = SDL->event.key.keysym.sym;
		switch (SDL->event.type)
		{
		case SDL_KEYDOWN:
			if (keyPressed == SDLK_ESCAPE)
				quit(SDL, gameInfo);
			else if (keyPressed == SDLK_n)
				newGameSettings(stageSpecifier, gameInfo, playerInfo, platforms, ladders, barrels, trophies);
			break;	
		case SDL_QUIT: //X button in right up corner
			quit(SDL, gameInfo);
			break;
		}
		playerKeyHandle(stage,stageSpecifier,SDL,gameInfo,playerInfo,score,platforms,ladders,barrels,trophies);
	}
}

void playerKeyHandle(Stage* stage, StageSpecifier* stageSpecifier, SDLConst* SDL, GameInfo* gameInfo, PlayerInfo* playerInfo,
	Score* score, Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies)
{
	int keyPressed = SDL->event.key.keysym.sym;
	switch (SDL->event.type)
	{
	case SDL_KEYDOWN:
		if (keyPressed == SDLK_RIGHT)
			playerWalkRight();
		else if (keyPressed == SDLK_LEFT)
			playerWalkLeft();
		else if (keyPressed == SDLK_DOWN)
			playerClimbDown();
		else if (keyPressed == SDLK_UP)
			playerClimbUp();
		else if (keyPressed == SDLK_SPACE)
			checkIfPlayerIsJumping();
		else if (keyPressed == SDLK_1)
			handleSpecifier(stage, stageSpecifier, SDL, gameInfo, playerInfo, platforms, ladders, barrels, trophies);
		else if (keyPressed == SDLK_2)
			handleSpecifier(stage, stageSpecifier, SDL, gameInfo, playerInfo, platforms, ladders, barrels, trophies);
		else if (keyPressed == SDLK_3)
			handleSpecifier(stage, stageSpecifier, SDL, gameInfo, playerInfo, platforms, ladders, barrels, trophies);
		break;
	case SDL_KEYUP:
		playerNotWalking();
		playerNotClimbing();
		break;
	}
}

void SDLSpace(SDLConst* SDL)
{
	SDL_FreeSurface(SDL->charset);
	SDL_FreeSurface(SDL->screen);
	SDL_FreeSurface(SDL->player);
	SDL_FreeSurface(SDL->barrel);
	SDL_FreeSurface(SDL->trophy);
	SDL_DestroyTexture(SDL->scrtex);
	SDL_DestroyRenderer(SDL->renderer);
	SDL_DestroyWindow(SDL->window);
}

void quit(SDLConst* SDL, GameInfo* gameInfo)
{
	gameInfo->quit = true;
	SDLSpace(SDL);
	SDL_Quit();
}

void firstStageSpecify(Stage* stage)
{
	stage->stageSpecifier = STAGE1;

}

void secondStageSpecify(Stage* stage)
{
	stage->stageSpecifier = STAGE2;

}

void thirdStageSpecify(Stage* stage)
{
	stage->stageSpecifier = STAGE3;
}

void handleSpecifier(Stage* stage, StageSpecifier* stageSpecifier, SDLConst* SDL, GameInfo* gameInfo, PlayerInfo* playerInfo,
Platform* platforms, Ladder* ladders, Barrel* barrels, Trophy* trophies)
{
	if (Mario.lowerCoordinates.y == PLATFORM_V_HEIGHT)
	{
		int keyPressed = SDL->event.key.keysym.sym;
		switch (SDL->event.type)
		{
		case SDL_KEYDOWN:
			if (keyPressed == SDLK_1)
				firstStageSpecify(stage);
			else if (keyPressed == SDLK_2)
				secondStageSpecify(stage);
			else if (keyPressed == SDLK_3)
				thirdStageSpecify(stage);
			break;
		case SDL_KEYUP:
			break;
		}		
		loadStageSettings(&stage->stageSpecifier, gameInfo, playerInfo, platforms, ladders, barrels, trophies);
	}
}

Stage whichStage(Stage* stage, Game* game)
{
	switch (stage->stageSpecifier) {
	case STAGE1:
		return game->stage1;
	case STAGE2:
		return game->stage2;
	case STAGE3:
		return game->stage3;
	}
}