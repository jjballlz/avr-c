/***************************************
 *
 * File >>_> main.h
 *
 * Creation date >>_> 16.10-2019
 * Last modified >>_> Wed 16 Oct 2019 03:19:20 PM CEST
 *
 * Author >>_> gian.SANDRI
 *
 ***************************************/

#ifndef main_h
#define main_h

/*********************************
 *        SPI Pin defs
 *********************************/
#define _SS DDB2
#define _MOSI DDB3
#define _MISO DDB4
#define _SCK DDB5

#define _UP DDD5
#define _DOWN DDD6
#define _LEFT DDD7
#define _RIGHT DDD4
/********************************
 *          GAMESTATE
 ********************************/
typedef struct {
	uint8_t numberOfDots;
	uint8_t directon;
} GameState;

typedef struct {
	uint8_t x;
	uint8_t y;
} Food;

typedef struct {
	uint8_t x;
	uint8_t y;
} Snake;

GameState gameState;

Snake snake[128];

Food food;

#endif
