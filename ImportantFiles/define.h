#pragma once
//REMEMBER: GET RID OF MAGIC NUMBERS !!!
//+ 1

#define SCREEN_WIDTH	720
#define SCREEN_HEIGHT	520
#define SECONDS_BETWEEN_REFRESH 0.5
#define REFRESH_RATE 1/SECONDS_BETWEEN_REFRESH

#define ZERO_COLUMN 0 
#define FIRST_ROW 1
#define TEN_ROW 10
#define AUTHOR_INFO_ROW SCREEN_HEIGHT - 12
#define GROUND_HEIGHT SCREEN_HEIGHT - 20

#define NULL 0
#define HALF 0.5
#define ONE 1

#define PLAYER_START_X_COORDINATE 310 
#define PLAYER_START_Y_COORDINATE 500
#define PLAYER_DIFFERENCE_IN_X 144
#define PLAYER_DIFFERENCE_IN_Y 50

#define PLAYER_WIDTH 37 
#define PLAYER_HEIGHT 34
#define PLAYER_REAL_SIZE 16

#define PLAYER_LIVES 3
#define PLAYER_START_POINTS 0

#define DEAFULT_PLAYER_SPRITE_I (PLAYER_WIDTH * 4) //DEAFULT_PLAYER_SPRITE_I describes from which column take a graphic 
#define DEAFULT_PLAYER_SPRITE_II (PLAYER_HEIGHT * 0) //DEAFULT_PLAYER_SPRITE_II describes from which row take a graphic 
#define MARIO_BMP_DISTANCE 10 //const which allows to show whole Mario graphic from the chosen row and column

#define NUMBER_OF_PLATFORMS 10
#define PLATFORM_WIDTH 20
#define PLATFORM_I_HEIGHT 440
#define PLATFORM_II_HEIGHT 360
#define PLATFORM_III_HEIGHT 280
#define PLATFORM_IV_HEIGHT 200
#define PLATFORM_V_HEIGHT 120

#define NUMBER_OF_LADDERS 5
#define LADDER_WIDTH 18
#define LADDER_HEIGHT 80

#define NUMBER_OF_BARRELS 8
#define BARRELS_SPAWN_POINT_X 280
#define BARRELS_DIFFERENCE_IN_X 16
#define BARRELS_SPAWN_POINT_Y 120
#define BARRELS_DIFFERENCE_IN_Y 5
#define BARRELS_REAL_SIZE 20

#define GRAVITY_SPEED 0.004
#define JUMPING_SPEED 0.8
#define ELASTIC_COLISION_CONST -0.4 

#define NULL_SPEED 0
#define WALKING_SPEED 0.15
#define CLIMBING_SPEED 0.1
