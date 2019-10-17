#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* ---------------------------------------------- CONSTANT DECLARATIONS --------------------------------------------- */
#define SIZE 100
/* ------------------------------------------- END OF CONSTANT DECLARATIONS ----------------------------------------- */

/* ----------------------------------------------- FUNCTION PROTOTYPES ---------------------------------------------- */
// Used to output the current game board, including player 1's and player 2's
	// positions to a disk file on a single line.
void output(char [], char*, char*, FILE*);

// Used to move the players around the board. Other functions are called from
	// called from this function to detect chutes and ladders and collisions.
	// This functions outputs to the console window via printf
	// the amount the player moved and the current position of the player.
		// This function performs some error prevention and
		// returns a char pointer
char* move(char*, char*, int, char*, int);

// Used when a player lands on a 'B' or 'F'. This function searches for the
	// the nearest haven (denoted as a 'H'), with the direction
	// depending on what the player landed on. This function changes the board
	// and returns where the player is to move to the move(...){...} function.
char* findHaven(char*, char*, int);

// Used to dictate where the player is to move to when that player lands on
	// a chute (‘a’ – ‘m’: a chute, move backward) or
	// a ladder (‘o’ – ‘z’: a ladder, move forward)
		// and then change that square on the board to a ‘-’.
		// This function calculates how far the player is to move and then
		// return that forward or backward distance to the move(...){...}
		// function that calls this chuteLadder(...){...} function.
char* chuteLadder(char*, char*);

// This function was added by me to detect collisions among players and
	// return "0" (zero) if there was a collision amongst the players.
	// If this functions returns any other int, there was no collision.
	// This function receives two char pointers (one for each player position)
int collision(char*, char*);

// This function was added by me to simulate rolling a six-sided die.
	// This function returns the int value result of "rolling the die"
int rollDice();
/* -------------------------------------------- END OF FUNCTION PROTOTYPES ------------------------------------------ */
