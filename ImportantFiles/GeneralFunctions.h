#pragma once
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "Define.h"
#include "Structures.h"
#include "MenuFunctions.h"
#include "ObjectsFunctions.h"
#include "PlayerFunctions.h"
#include "SDLFunctions.h"

extern "C" {
#include"../SDL2-2.0.10/include/SDL.h"
#include"../SDL2-2.0.10/include/SDL_main.h"
}

void createWindow(Stage* stage, SDLConst* SDL);

void drawScene(Stage* stage, SDLConst* SDL, Animator* animator, Color* colors); //draws objects (without player)

void displayGame(Stage* stage, SDLConst* SDL, Animator* animator, Color* colors);

void displayWindow(Stage* stage, SDLConst* SDL, Animator* animator, Color* colors, Score* score);

void refreshWindow(SDLConst* SDL);

void printGameInfo(Stage* stage, SDLConst* SDL, Color* colors); 

void printPlayerInfo(Stage* stage, SDLConst* SDL, Color* colors);

void printInfo(Stage* stage, SDLConst* SDL, Color* colors); //print GameInfo+ print PlayerInfo

void defaultSettings(Stage* stage, SDLConst* SDL); //set up the game at the beginning

void newGameSettings(Stage* stage, SDLConst* SDL, Animator* animator, Color* colors); //set up new game

void loadStageSettings(Stage* stage, SDLConst* SDL, Animator* animator, Color* colors, Score* score); //set up next level

void timeCounting(Stage* stage); //counting the game time

void timeTransformation(Stage* stage);

void readKeys(Stage* stage,SDLConst* SDL, Animator* animator, Color* colors, Score* score); //read key input

void playerKeyHandle(Stage* stage, SDLConst* SDL, Animator* animator, Color* colors, Score* score); //read player key input

void firstStageSpecify(Stage* stage);

void secondStageSpecify(Stage* stage);

void thirdStageSpecify(Stage* stage);

void stageSpecifierKeyHandle(Stage* stage, SDLConst* SDL, Animator* animator, Color* colors, Score* score); //read key input to change stages

void SDLFree(SDLConst* SDL); //freeing all surfaces

void quit(Stage* stage, SDLConst* SDL);


void createWindow(Stage* stage, SDLConst* SDL)
{
	stage->gameInfo.err = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&SDL->window, &SDL->renderer);
	if (stage->gameInfo.err != NULL)
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

void drawScene(Stage* stage, SDLConst* SDL, Animator* animator, Color* colors)
{
	drawGround(SDL, colors);
	drawLives(stage, SDL);
	drawPlatforms(stage, SDL, colors);
	drawLadders(stage, SDL, colors);
	drawTrophies(stage, SDL);
	drawBarrels(stage, SDL);
} 

void displayGame(Stage* stage, SDLConst* SDL, Animator* animator, Color* colors)
{
	drawScene(stage, SDL, animator, colors);
	printInfo(stage,SDL,colors);
	drawPlayer(stage, SDL);
}

void displayWindow(Stage* stage, SDLConst* SDL, Animator* animator, Color* colors, Score* score)
{
	SDL_FillRect(SDL->screen, 0, colors->black);
	if (stage->menu.showMenu)
		displayMainMenu(stage, SDL, colors, animator, score);
	else if (stage->menu.showBarrelMenu)
		displayHittedByBarrelMenu(stage, SDL);
	else if (stage->menu.showFinishMenu)
		finishGameMenu(stage, SDL, score);
	else
		displayGame(stage, SDL, animator, colors);
}

void refreshWindow(SDLConst* SDL)
{
	SDL_UpdateTexture(SDL->scrtex, 0, SDL->screen->pixels, SDL->screen->pitch);
	SDL_RenderCopy(SDL->renderer, SDL->scrtex, 0, 0);
	SDL_RenderPresent(SDL->renderer);
}

void printGameInfo(Stage* stage, SDLConst* SDL, Color* colors)
{
	DrawRectangle(SDL->screen, ZERO_COLUMN, FIRST_ROW, SCREEN_WIDTH, GAME_TABLE_HEIGHT, colors->white, colors->black);
	sprintf(stage->gameInfo.text, "King Donkey");
	DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->gameInfo.text) * EIGHT / TWO, TITLE_ROW, stage->gameInfo.text, SDL->charset);
	sprintf(stage->gameInfo.text, "Implemented requirements: mandatory, A, B, C, D, E, F, G ");
	DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->gameInfo.text) * EIGHT / TWO, REQUIREMENTS_ROW, stage->gameInfo.text, SDL->charset);
	sprintf(stage->gameInfo.text, "Time from beginning: %.1lf s", stage->gameInfo.gameTime);
	DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->gameInfo.text) * EIGHT / TWO, TIME_ROW, stage->gameInfo.text, SDL->charset);
	sprintf(stage->gameInfo.text, "Esc - quit, N - new game ");
	DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->gameInfo.text) * EIGHT / TWO, OPTIONS_ROW, stage->gameInfo.text, SDL->charset);
	sprintf(stage->gameInfo.text, "\30 - move up \31 - move down \32 - move left \33 - move right SPACE - jump");
	DrawString(SDL->screen, SDL->screen->w / TWO - strlen(stage->gameInfo.text) * EIGHT / TWO, KEYS_ROW, stage->gameInfo.text, SDL->charset);
	sprintf(stage->gameInfo.text, "Author: Tomasz Kruczalak 198049");
	DrawString(SDL->screen, ZERO_COLUMN, AUTHOR_INFO_ROW, stage->gameInfo.text, SDL->charset);
}

void printPlayerInfo(Stage* stage, SDLConst* SDL, Color* colors)
{
	DrawRectangle(SDL->screen, ZERO_COLUMN, EIGHTY_ROW, ONE_HUNDRED_TWENTY, THIRTY_FIVE, colors->white, colors->black);
	sprintf(stage->gameInfo.text, "Score: %.6d", stage->playerInfo.score);
	DrawString(SDL->screen, TEN_COLUMN, EIGHTY_FIVE_ROW, stage->gameInfo.text, SDL->charset);
	sprintf(stage->gameInfo.text, "Lives: ");
	DrawString(SDL->screen, TEN_COLUMN, HUNDRED_ROW, stage->gameInfo.text, SDL->charset);
	drawLives(stage, SDL);
	sprintf(stage->gameInfo.text, "Trophies:");
	DrawString(SDL->screen, FIVE_HUNDRED_COLUMN, AUTHOR_INFO_ROW, stage->gameInfo.text, SDL->charset);
}

void printInfo(Stage* stage, SDLConst* SDL, Color* colors)
{
	printGameInfo(stage, SDL, colors);
	printPlayerInfo(stage, SDL, colors);
}

void defaultSettings(Stage* stage, SDLConst* SDL)
{
	emptyName(stage, SDL);
	stage->gameInfo.quit = false;
	stage->gameInfo.gameTime = 0;
	stage->playerInfo.score = PLAYER_DEFAULT_POINTS;
	stage->playerInfo.lives = PLAYER_DEFAULT_LIVES;
	initializePlayer(stage);
}

void newGameSettings(Stage* stage, SDLConst* SDL, Animator* animator, Color* colors)
{
	defaultSettings(stage, SDL);
	initializeGameObjects(stage, SDL, animator, colors);
}

void loadStageSettings(Stage* stage, SDLConst* SDL, Animator* animator, Color* colors, Score* score)
{
	stage->gameInfo.quit = false;
	score->endTheStage = END_THE_STAGE_POINTS;
	initializePlayer(stage);
	initializeGameObjects(stage, SDL, animator, colors);
}

void timeCounting(Stage* stage)
{
	if (stage->menu.showMenu || stage->menu.showBarrelMenu || stage->menu.showFinishMenu)
	{
		timeTransformation(stage);
	}	
	else
	{
		timeTransformation(stage);
		stage->gameInfo.gameTime += stage->gameInfo.deltaTime;
	} 
}

void timeTransformation(Stage* stage)
{
	stage->gameInfo.deltaTime = (stage->gameInfo.t2 - stage->gameInfo.t1) * MILI;
	stage->gameInfo.t1 = stage->gameInfo.t2;
}

void readKeys(Stage* stage, SDLConst* SDL, Animator* animator, Color* colors, Score* score)
{
	if (!stage->menu.showMenu)
	{
		while (SDL_PollEvent(&SDL->event))
		{
			int keyPressed = SDL->event.key.keysym.sym;
			switch (SDL->event.type)
			{
			case SDL_KEYDOWN:
				if (keyPressed == SDLK_ESCAPE)
					quit(stage, SDL);
				else if (keyPressed == SDLK_n)
					newGameSettings(stage, SDL, animator,colors);
				break;
			case SDL_QUIT: 
				quit(stage, SDL);
				break;
			}
			playerKeyHandle(stage, SDL, animator, colors, score);
		}
	}
}

void playerKeyHandle(Stage* stage, SDLConst* SDL, Animator* animator, Color* colors, Score* score)
{
	int keyPressed = SDL->event.key.keysym.sym;
	switch (SDL->event.type)
	{
	case SDL_KEYDOWN:
		if (keyPressed == SDLK_RIGHT)
			playerWalkRight(stage);
		else if (keyPressed == SDLK_LEFT)
			playerWalkLeft(stage);
		else if (keyPressed == SDLK_DOWN)
			playerClimbDown(stage);
		else if (keyPressed == SDLK_UP)
			playerClimbUp(stage);
		else if (keyPressed == SDLK_SPACE)
			checkIfPlayerIsJumping(stage);
		else if (keyPressed == SDLK_1)
			stageSpecifierKeyHandle(stage, SDL, animator, colors, score);
		else if (keyPressed == SDLK_2)
			stageSpecifierKeyHandle(stage, SDL, animator, colors, score);
		else if (keyPressed == SDLK_3)
			stageSpecifierKeyHandle(stage, SDL, animator, colors, score);
		break;
	case SDL_KEYUP:
		playerNotWalking(stage);
		playerNotClimbing(stage);
		break;
	}
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

void stageSpecifierKeyHandle(Stage* stage, SDLConst* SDL, Animator* animator, Color* colors, Score* score)
{
	if (stage->menu.showMenu || stage->player.lowerCoordinates.y == PLATFORM_V_HEIGHT)
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
		loadStageSettings(stage, SDL, animator, colors, score);
	}
}

void SDLFree(SDLConst* SDL)
{
	SDL_FreeSurface(SDL->charset);
	SDL_FreeSurface(SDL->screen);
	SDL_FreeSurface(SDL->player);
	SDL_FreeSurface(SDL->barrel);
	SDL_FreeSurface(SDL->trophy);
	SDL_FreeSurface(SDL->lives);
	SDL_DestroyTexture(SDL->scrtex);
	SDL_DestroyRenderer(SDL->renderer);
	SDL_DestroyWindow(SDL->window);
}

void quit(Stage* stage, SDLConst* SDL)
{
	stage->gameInfo.quit = true;
	SDLFree(SDL);
	SDL_Quit();
}