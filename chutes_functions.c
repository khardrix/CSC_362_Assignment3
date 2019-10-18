#include "chutes.h"


// Used to output the current game board, including player 1's and player 2's
	// positions to a disk file on a single line.
void output(char board[], char* player1, char* player2, FILE* outputFP) {

	// while loop to iterate, char-by-char, through the char array that serves as the game board
	while (*board != '\0') {
		// if statement that checks if player1 is located at this position
		if (board == player1) {
			putc('1', outputFP);
		}
		else if (board == player2) {
			putc('2', outputFP);
		}

		putc(*board, outputFP);

		board++;
	}

	putc('\n', outputFP);
}

// Used when a player lands on a 'B' or 'F'. This function searches for the
	// the nearest haven (denoted as a 'H'), with the direction
	// depending on what the player landed on. This function changes the board
	// and returns where the player is to move to the move(...){...} function.
char* findHaven(char board[], char* player, char direction) {
	int squaresToMove = 0;

	if (direction == 'B') {

	}
}


// This function was added by me to detect collisions among players.
	// If this function returns a "0" (zero), that means there is zero distance
	// between the players, meaning there was a collision. If this function
	// returns any int other than "0" (zero), then there was some distance
	// between the players and there was no collision. This function acts like a
	// boolean method does in Java
int collision(char* p1, char* p2) {

	return ((int)p1 - (int)p2);
}


// This function was added by me to simulate rolling a six-sided die.
	// This function returns the int value result of "rolling the die"
int rollDice() {

	return (rand() % 6) + 1;
}