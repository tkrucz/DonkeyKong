#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "ImportantFiles/define.h"
#include "ImportantFiles/structures.h"
#include "ImportantFiles/GameStructure.h"
#include "ImportantFiles/GeneralFunctions.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
// main
#ifdef __cplusplus
extern "C"
#endif

int main(int argc, char** argv) {
	SDLConst SDL;
	Color colors;
	Score score;
	ShowText showText;
	
	Stage stage;

	StageSpecifier specifier;
	Game game;

	specifier = stage.stageSpecifier;
	//stage = whichStage(&stage, &game);
	SDL_ShowCursor(SDL_DISABLE);

	createWindow(&SDL, &stage);
	initializeColors(&SDL, &colors);
	loadBMPs(&SDL);
	defaultSettings(&stage);
	initializeGameObjects(&stage);

	stage.gameInfo.t1 = SDL_GetTicks();

	while (!stage.gameInfo.quit)
	{
		stage.gameInfo.t2 = SDL_GetTicks();
		timeCounting(&stage);

		refreshWindow(&SDL);
		displayWindow(&stage, &SDL, &colors);

		readKeys(&stage, &SDL, &score);

		gravityApply(&stage);
		whereAreObjects(&stage, &SDL, &score, &showText);
		moveObjects(&stage, &SDL);
	}
	return 0;
}

/*
// przyjmuje feedback od przyciskow w menu albo gry
stageSpecifier handleSpecifier() {

}

Stage whichStage(stageSpecifier* specifier, Game game) {

	switch (specifier) {
	case STAGE1:
		return game.stage1;
	}
}

void animations(Player* player, Barrel* barrels) {
	playerAnimation(player)
	barrelsAnimations(barells);
}

void playerAnimation(Player* player) {
	player->animator.actualAnimation++;
	player->animator.spirtesArray[player->animator.actualAnimation]
	(display spritesArray[actualAnimation)
}
*/
