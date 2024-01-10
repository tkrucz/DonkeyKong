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

void displayMainMenu(Stage* stage, SDLConst* SDL, Color* colors, Animator* animator, Score* score);

void displayNamePart(Stage* stage, SDLConst* SDL);

void displayStagePart(Stage* stage, SDLConst* SDL);

void readMainMenuKeys(Stage* stage, SDLConst* SDL, Color* colors, Animator* animator, Score* score);

void displayHittedByBarrelMenu(Stage* stage, SDLConst* SDL);

void readBarrelMenuKeys(Stage* stage, SDLConst* SDL);

void emptyName(Stage* stage, SDLConst* SDL);

void writeName(Stage* stage, SDLConst* SDL);

void chooseStage(Stage* stage, SDLConst* SDL, Color* colors, Animator* animator, Score* score);

void stageSpecifierKeyHandle(Stage* stage, SDLConst* SDL, Animator* animator, Score* score);

void defaultMessage(Stage* stage, SDLConst* SDL);

void setMessage(Stage* stage, SDLConst* SDL);

void saveGame(Stage* stage);

void quit(Stage* stage, SDLConst* SDL);


void displayMainMenu(Stage* stage, SDLConst* SDL, Color* colors, Animator* animator, Score* score)
{
	if (stage->menu.showMenu)
	{
		defaultMessage(stage, SDL);
		sprintf(stage->menu.text, "KING DONKEY");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 50, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "START NEW GAME - N");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 100, stage->menu.text, SDL->charset);
		displayNamePart(stage, SDL);
		displayStagePart(stage, SDL);		
		sprintf(stage->menu.text, "CHECK PLAYER SCORE - P");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 160, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "EXIT THE GAME - ESC");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 180, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "%s", stage->menu.message);
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 260, stage->menu.text, SDL->charset);
		readMainMenuKeys(stage, SDL, colors, animator, score);
	}
}

void displayNamePart(Stage* stage, SDLConst* SDL)
{
	if (!stage->menu.nameConfirmed)
	{
		sprintf(stage->menu.text, "ENTER YOUR NAME - W");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 120, stage->menu.text, SDL->charset);
	}
	else
	{
		sprintf(stage->menu.text, "ENTERED NAME: %s", stage->player.name);
		DrawString(SDL->screen, NAME_COLUMN, 120, stage->menu.text, SDL->charset);
	}
	if (stage->menu.nameEnter)
	{
		sprintf(stage->menu.text, "ENTERED NAME (press ENTER to confirm) : %s", stage->player.name);
		DrawString(SDL->screen, WRITING_NAME_COLUMN, 220, stage->menu.text, SDL->charset);
	}
}

void displayStagePart(Stage* stage, SDLConst* SDL)
{
	sprintf(stage->menu.text, "CHOOSE STAGE - L");
	DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 140, stage->menu.text, SDL->charset);
	if (stage->stageSpecifier == STAGE1 || stage->stageSpecifier == STAGE2 || stage->stageSpecifier == STAGE3)
	{
		sprintf(stage->menu.text, "CHOOSEN STAGE: %d", stage->stageSpecifier + 1);
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 140, stage->menu.text, SDL->charset);
	}
	if (stage->menu.stageChoose)
	{
		sprintf(stage->menu.text, "CHOOSE STAGE FROM: 1, 2, 3");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 240, stage->menu.text, SDL->charset);
	}
}

void readMainMenuKeys(Stage* stage, SDLConst* SDL, Color* colors, Animator* animator, Score* score)
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
					if (stage->stageSpecifier == STAGE1 || stage->stageSpecifier == STAGE2 || stage->stageSpecifier == STAGE3)
						stage->menu.showMenu = false;
					else
					{
						stage->menu.noneStage = true;
						stage->menu.defaultMessage = false;
						break;
					}
				else if (keyPressed == SDLK_w)
				{
					stage->menu.nameEnter = true;
					stage->menu.defaultMessage = true;
				}
				else if (keyPressed == SDLK_l)
				{
					stage->menu.stageChoose = true;
					stage->menu.defaultMessage = true;
				}
				break;
			case SDL_QUIT: //X button in right up corner
				quit(stage, SDL);
				break;
			}
			if (stage->menu.nameEnter)
				writeName(stage, SDL);
			else if (stage->menu.stageChoose)
				chooseStage(stage, SDL, colors, animator, score);
		}
}

void displayHittedByBarrelMenu(Stage* stage, SDLConst* SDL)
{
	if (stage->menu.showBarrelMenu)
	{
		sprintf(stage->menu.text, "Player score : %.6d", stage->playerInfo.score);
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 200, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "You are hitted by barrel (fcking noob)");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 220, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "You want to continue?");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 240, stage->menu.text, SDL->charset);
		sprintf(stage->menu.text, "YES - Y , NO (quit the game) - Esc, NO (save score) - S");
		DrawString(SDL->screen, SDL->screen->w / 2 - strlen(stage->menu.text) * EIGHT / TWO, 250, stage->menu.text, SDL->charset);
		readBarrelMenuKeys(stage, SDL);
	}
}

void readBarrelMenuKeys(Stage* stage, SDLConst* SDL)
{
	while (SDL_PollEvent(&SDL->event))
	{
		int keyPressed = SDL->event.key.keysym.sym;
		switch (SDL->event.type)
		{
		case SDL_KEYDOWN:
			if (keyPressed == SDLK_ESCAPE)
				quit(stage, SDL);
			else if (keyPressed == SDLK_y)
				stage->menu.showBarrelMenu = false;
			else if (keyPressed == SDLK_s)
				saveGame(stage);
			break;
		case SDL_QUIT: //X button in right up corner
			quit(stage, SDL);
			break;
		}		
	}
}

void emptyName(Stage* stage, SDLConst* SDL)
{
	for (int i = 0; i < 15; i++)
		stage->player.name[i] = ' ';
	stage->player.name[15] = '\0';
}

void writeName(Stage* stage, SDLConst* SDL)
{
	int keyPressed = SDL->event.key.keysym.sym;
	switch (SDL->event.type)
	{
	case SDL_KEYDOWN:
		if (keyPressed == SDLK_BACKSPACE)
		{
			stage->player.name[stage->menu.index] = '\0';
			stage->menu.index--;
		}
		else if (keyPressed == SDLK_RETURN)
		{
			stage->menu.nameEnter = false;
			stage->menu.nameConfirmed = true;
		}
		else if (keyPressed == SDLK_n)
		{
			stage->menu.showMenu = true;
			stage->player.name[stage->menu.index] = (char)(keyPressed);
			stage->menu.index++;
		}
		else if (keyPressed == SDLK_w)
		{
			stage->player.name[stage->menu.index] = (char)(keyPressed);
			stage->menu.index++;
		}
		else if (keyPressed == SDLK_l)
		{
			stage->menu.stageChoose = false;
			stage->player.name[stage->menu.index] = (char)(keyPressed);
			stage->menu.index++;
		}
		else
		{
			stage->player.name[stage->menu.index] = (char)(keyPressed);
			stage->menu.index++;
		}
	case SDL_KEYUP:
		break;
	}
}

void chooseStage(Stage* stage, SDLConst* SDL, Color* colors, Animator* animator, Score* score)
{
	int keyPressed = SDL->event.key.keysym.sym;
	switch (SDL->event.type)
	{
	case SDL_KEYDOWN:
		if (keyPressed == SDLK_1)
		{
			stageSpecifierKeyHandle(stage, SDL, animator, score);
			stage->menu.stageChoose = false;
			stage->menu.wrongStage = false;
			stage->menu.defaultMessage = true;
		}
		else if (keyPressed == SDLK_2)
		{
			stageSpecifierKeyHandle(stage, SDL, animator, score);
			stage->menu.stageChoose = false;
			stage->menu.wrongStage = false;
			stage->menu.defaultMessage = true;
		}
		else if (keyPressed == SDLK_3)
		{
			stageSpecifierKeyHandle(stage, SDL, animator, score);
			stage->menu.stageChoose = false;
			stage->menu.wrongStage = false;
			stage->menu.defaultMessage = true;
		}
		else if (keyPressed != SDLK_1 && keyPressed != SDLK_2 && keyPressed != SDLK_3)
		{
			stage->menu.wrongStage = true;
			stage->menu.defaultMessage = false;
		}
		break;	
	case SDL_KEYUP:
		break;
	}
}

void defaultMessage(Stage* stage, SDLConst* SDL)
{
	if (stage->menu.defaultMessage)
	{
		for (int i = 0; i < 39; i++)
		{
			stage->menu.message[i] = ' ';
		}
		stage->menu.message[39] = '\0';
	}
	else if (!stage->menu.defaultMessage)
		setMessage(stage, SDL);
}

//TO DO: set message kiedy wybierm opcj� kt�rej nie ma 
void setMessage(Stage* stage, SDLConst* SDL)
{
	if (stage->menu.wrongStage)
	{
		char message[] = "CHOOSE THE CORRECT STAGE";
		for (int i = 0; i < 25; i++)
			stage->menu.message[i] = message[i];
	}	
	else if (stage->menu.noneStage)
	{
		char message[] = "YOU CAN'T START A GAME WITHOUT STAGE";
		for (int i = 0; i < 37; i++)
			stage->menu.message[i] = message[i];
	}
}

void saveGame(Stage* stage)
{
	char filename[] = "Saves.txt";
	FILE* file = fopen(filename, "w");

	if (file != NULL) 
	{		
		fprintf(file, "Player Name: %s\n", stage->player.name);
		fprintf(file, "Score: %d\n", stage->playerInfo.score);
		fprintf(file, "Lives: %d\n", stage->playerInfo.lives);

		fclose(file);	
	}	
}