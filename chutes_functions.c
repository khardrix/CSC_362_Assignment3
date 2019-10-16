#include "chutes.h"


// This function was added by me to detect collisions among players.
	// If this function returns a "0" (zero), that means there is zero distance
	// between the players, meaning there was a collision. If this function
	// returns any int other than "0" (zero), then there was some distance
	// between the players and there was no collision. This function acts like a
	// boolean method does in Java
int collision(char* p1, char* p2) {
	int p1Position = (int)p1;
	int p2Position = (int)p2;

	return (p1Position - p2Position);
}


// This function was added by me to simulate rolling a six-sided die.
	// This function returns the int value result of "rolling the die"
int rollDice() {

	return (rand() % 6) + 1;
}