#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "ImportantFiles/Define.h"
#include "ImportantFiles/Structures.h"
#include "ImportantFiles/GeneralFunctions.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#ifdef __cplusplus
extern "C"
#endif

int main(int argc, char** argv) {
	SDLConst SDL;
	Color colors;
	Score score;
	ShowText showText;
	Animator animator;
	
	Stage stage;
	StageSpecifier specifier;
	
	specifier = stage.stageSpecifier;
	
	SDL_ShowCursor(SDL_DISABLE);

	createWindow(&stage, &SDL);
	initializeColors(&SDL, &colors);
	loadBMPs(&SDL);
	defaultSettings(&stage, &SDL);
	initializeGameObjects(&stage, &animator);

	stage.gameInfo.t1 = SDL_GetTicks();

	while (!stage.gameInfo.quit)
	{
		stage.gameInfo.t2 = SDL_GetTicks();
		timeCounting(&stage);

		refreshWindow(&SDL);
		displayWindow(&stage, &SDL, &colors, &animator, &score);
		
		readKeys(&stage, &SDL, &score, &animator);

		gravityApply(&stage);
		whereAreObjects(&stage, &SDL, &score, &showText);
		moveObjects(&stage, &SDL, &animator);
	}
	return 0;
}


/*
* NOWA SCENA (PUSTE OKNO)
* 1. czytanie klawiszy, np: klawisz p -> platforma 
* 1a. (przypadek wyj¹tkowy) potrzebujemy d³ugoœci platformy, czyli wyœwietlamy jakiœ tekst -> wprowadŸ d³ugosc.
* Ograniczamy ja np do max 1000
* 2. SDL_GetMouseState (&twojX, &twojY), SDL Draw platforma w tym miejscu
* 3. Sprawdzamy czy nie przekroczylismy rozmiaru tablicy 
* 3a. (przypadek wyj¹tkowy) jezeli przekroczylismy, to alokujemy nowa tablice o rozmiarze 2*(porzedni rozmiar), np 40
* i przepisujemy zawartosc poprzedniej tablicy
* 4. Dodajemy do tablicy platform wczesniej zaalokowanej dynamicznie, np o rozmiarze 20
* 5. wroc to podpunktu 1
*/

/*
* 
* 
* void DrawCreatorWindow() {
* ......
* }
* 
* 
* void HandleCreatorEvents() {
*	Platform platforms = malloc(sizeof * platforms * (PLATFORMS_STARTUP_SIZE + 1)); 
*	int platformCounter = 0;
*	int maxPlatformsNumber = PLATFORMS_STARTUP_SIZE;
*	.........
* 
*	while (SDL_PollEvent(&SDL->event))
	{
		int keyPressed = SDL->event.key.keysym.sym;
		switch (SDL->event.type)
		{
		case SDL_KEYDOWN:
			if (keyPressed == SDLK_ESCAPE)
				quit();
			else if (keyPressed == SDLK_p)

			// maybe calosc do funkcji handlePlatform(...)
				platformSize = readSize(); 
				SDL_GetMouseState (&twojX, &twojY);

				// checkArray(...)
				if(platformSize < maxPlatformsNumber) {
					platforms[platformsCounter] = Platform (.....tworzenie obiektu);
				}
				else {
					reallocTheArray(platfroms, maxPlatformsNumber);
				}

				platformCounter++;
			.....
			break;
		case SDL_QUIT: 
			quit();
			break;
		}
	}

	
* }
* 
* 
* void SaveCreatorToFile(......) {
* 
*	....
* }
* 
* void Creator(...) {
*	
*	DrawCreatorWindow();
*	HandleCreatorEvents();
*	SaveCreatorToFile();
*
* }
* 
* 
* void LoadCreatorLevel(...) 
* 
* 
* //////////////////////////////////////////////////////////////
* TEKSTOWO
* 
* 
* void LoadTheFile() {
*	Platform platforms = malloc(sizeof * platforms * (PLATFORMS_STARTUP_SIZE + 1));
*	int platformCounter = 0;
*	int maxPlatformsNumber = PLATFORMS_STARTUP_SIZE;
* 
*	const char * filename = "costam";
*	FILE* file = fopen(filename);
* 
*	char tmp = '\0';
* 
*	while (tmp != '*') {
*	
*		tmp = getchar();
* 
*		switch(tmp) {
*		
*			case '#':
*				3. Sprawdzamy czy nie przekroczylismy rozmiaru tablicy 
*				3a. (przypadek wyj¹tkowy) jezeli przekroczylismy, to alokujemy nowa tablice o rozmiarze 2*(porzedni rozmiar), np 40
*				i przepisujemy zawartosc poprzedniej tablicy
*				4. Dodajemy do tablicy platform wczesniej zaalokowanej dynamicznie, np o rozmiarze 20
*		
*		}
*		
*	}
* 
*	fclose(file);
* }
* 
* 
*/