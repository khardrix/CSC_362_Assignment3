#include "chutes.h"


// Used to output the current game board, including player 1's and player 2's
	// positions to a disk file on a single line.
void output(char* board, char* player1, char* player2, FILE* outputFP) {
	
	int i = 0;

	while (board[i] != '\0') {

		if (i == *player1) {
			board[i] = '1';
		}
		else if (i == *player2) {
			board[i] = '2';
		}
		
		putc(board[i], outputFP);
		
		i++;
	}
	putc('\n', outputFP);
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