#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "ImportantFiles/define.h"
#include "ImportantFiles/structures.h"
#include"ImportantFiles/functions.h"

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
	Platform platforms[NUMBER_OF_PLATFORMS];
	Ladder ladders[NUMBER_OF_LADDERS];
	Barrel barrels[NUMBER_OF_BARRELS];
	Trophy trophies[NUMBER_OF_TROPHIES];
	PlayerInfo playerInfo;
	GameInfo gameInfo;
	Color colors;
	Score score;

	//stageSpecifier specifier;
	//specifier = handleSpecifier();
	//Stage tmp = whichStage(specifier, game);
	SDL_ShowCursor(SDL_DISABLE);

	createWindow(&SDL, &gameInfo);
	initializeColors(&SDL, &colors);
	loadBMPs(&SDL);
	defaultSettings(&gameInfo, &playerInfo);
	initializeGameObjects(platforms, ladders, barrels,trophies);

	gameInfo.t1 = SDL_GetTicks();

	while (!gameInfo.quit)
	{
		gameInfo.t2 = SDL_GetTicks();
		timeCounting(&gameInfo);

		refreshWindow(&SDL);
		displayWindow(&SDL, &gameInfo, &playerInfo, &colors, platforms, ladders, barrels, trophies);

		readKeys(&SDL, &gameInfo, &playerInfo, &score, platforms, ladders, barrels, trophies);

		gravityApply(&gameInfo, platforms, barrels);
		whereAreObjects(&playerInfo, &score, platforms, ladders, barrels, trophies);
		moveObjects(&SDL, &gameInfo, &playerInfo, barrels);
	}
	return 0;
}

/*enum stageSpecifier {
	STAGE1,
	STAGE2
};

// przyjmuje feedback od przyciskow w menu albo gry
stageSpecifier handleSpecifier() {
}

Stage whichStage(stageSpecifier* specifier, Game game) {

	switch (specifier) {
	case STAGE1:
		return game.stage1;
	}
}

void animations(Player* player, Barell* barells) {
	playerAnimation(player)
	barrelsAnimations(barells);
}

void playerAnimation(Player * player) {
	player->animator.actualAnimation++;
	player->animator.spirtesArray[player->animator.actualAnimation]
	(display spritesArray[actualAnimation)
}
*/
