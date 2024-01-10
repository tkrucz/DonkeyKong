#pragma once
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "Define.h"
#include "Structures.h"
#include "GeneralFunctions.h"
#include "SDLFunctions.h"

extern "C" {
#include"../SDL2-2.0.10/include/SDL.h"
#include"../SDL2-2.0.10/include/SDL_main.h"
}

void displayMenu(Stage* stage, SDLConst* SDL, Color* colors);

void readMenuKeys(Stage* stage, SDLConst* SDL, Color* colors);

void writeName(Stage* stage, SDLConst* SDL);

void quit(Stage* stage, SDLConst* SDL);


void displayMenu(Stage* stage, SDLConst* SDL, Color* colors)
{
	if (stage->menu.showMenu)
	{
		sprintf(stage->menu.text, "KING DONKEY");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 50, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "START NEW GAME - N");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 100, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "ENTER YOUR NAME - W");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 120, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "CHOOSE STAGE");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 140, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "CHECK PLAYER SCORE");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 160, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "EXIT THE GAME - ESC");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 180, stage->menu.text, SDL->charset);
		readMenuKeys(stage, SDL, colors);
	}
}

void readMenuKeys(Stage* stage, SDLConst* SDL, Color* colors)
{
	if (stage->menu.showMenu)
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
					stage->menu.showMenu = false;
				else if (keyPressed == SDLK_w)
					writeName(stage, SDL);
				//	else if (keyPressed == SDLK_s)
						//chooseStage();
				//	else if (keyPressed == SDLK_p)
						//checkPlayersScore();
				break;
			case SDL_QUIT: //X button in right up corner
				quit(stage, SDL);
				break;
			}
		}
	}
}

void writeName(Stage* stage, SDLConst* SDL)
{
	while (SDL_PollEvent(&SDL->event))
	{
		int keyPressed = SDL->event.key.keysym.sym;
		switch (SDL->event.type)
		{
		case SDL_KEYDOWN:
			//else if (keyPressed == SDLK_BACKSPACE)
			*stage->menu.text += (char)(keyPressed);
			break;
		case SDL_KEYUP:
		{
			sprintf(stage->menu.text, "ENTERED NAME: %s", stage->menu.text);
			DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 200, stage->menu.text, SDL->charset);
			break;
		}
		}
	}
}
