#include "chutes.h"


// Used to output the current game board, including player 1's and player 2's
	// positions to a disk file on a single line.
void output(char board[], char *player1, char *player2, FILE *outputFP) {

	// while loop to iterate, char-by-char, through the game board
	while (*board != '\0') {
		// if statement that checks if player 1 is located at the current position on the board
		if (board == player1) {
			// Output a '1' to the outfile specified by the passed in FILE pointer parameter, outputFP
			putc('1', outputFP);
		}
		// else if statement that checks if player 2 is located at the current position on the board
		else if (board == player2) {
			// Output a '2' to the outfile specified by the passed in FILE pointer parameter, outputFP
			putc('2', outputFP);
		}
		else {

			// output to the file specified by the passed in FILE pointer parameter, outputFP, the char at the 
				// current position on the game board
			putc(*board, outputFP);
		}

		// increment the index position of the game board
		board++;
	}

	// insert a new line character into the file specified by the passed in FILE pointer parameter, outputFP, so that
		// the next call to this function will be on a new line
	putc('\n', outputFP);
}


// Used to move the players around the board. Other functions are called from
	// called from this function to detect chutes and ladders and collisions.
	// This functions outputs to the console window via printf
	// the amount the player moved and the current position of the player.
		// This function performs some error prevention and
		// returns a char pointer
char* move(char *movingPlayer, char *waitingPlayer, int playerNumber, char board[], int size) {
	// int variable declarations for the index of the player who's turn it is (index, index2), 
		// the amount they rolled with the dice (moveAmount) and
		// the number of squares between the player who's turn it is and the other player (distanceBetweenPlayers)
	int index, index2, moveAmount, distanceBetweenPlayers;
	// char pointer variable declaration to store the player who's turn it is position after they move the number of
		// squares specified by their dice roll
	char *playerPositionAfterRoll;

	// set the number of squares to move the moving player by getting the resulting int from the rollDice(){...} function
	moveAmount = rollDice();

	// if statement that checks if the player moves the number of squares specified by their dice roll will put them
		// before the beginning of the game board 
		// (THIS SHOULD NEVER EXECUTE - only used to correct if something goes wrong and set the player at the first square on the game board)
	if ((movingPlayer + moveAmount) < board) {
		// set the moving player's position to the first square on the board
		movingPlayer = board;

		// return the moving player's position to the calling function (int main(){...})
		return movingPlayer;
	}
	// else statement that executes if the player is still on the game board after the player moves
	else {
		// if statement that checks if the moving player has reached or exceeded the end of the game board (winning condition)
		if ((movingPlayer + moveAmount) >= (board + size)) {
			// get the index of the moving player
			index = (int)(movingPlayer - board);
			// print to the terminal what square the player was on, how much they rolled with the die and what square they landed on
			printf("Player %d was at square %d and rolled a %d and landed on square ", playerNumber, index, moveAmount);
			// move the player the amount of squares specified by their dice roll
			movingPlayer += moveAmount;
			// get the new index of the moving player after they moved the number of squares specified by their dice roll
			index = (int)(movingPlayer - board);
			// print to the terminal the square number the player ended up landing on and move to the next line
			printf("%d \n", index);
			// print to the terminal that the moving player (and their number) has reached the end of the game board and 
				// move the cursor in the terminal down two lines
			printf("Player %d has reached the end of the game board! \n\n", playerNumber);

			// return the moving player's position to the calling function (int main(){...})
			return movingPlayer;
		}
		// else statement that executes if the moving player has not reached the end of the game board yet
		else {
			// move the moving player's position the number of squares specified by their dice roll
			movingPlayer += moveAmount;
			// store a copy of the moving player's position after their dice roll and initial move (in case they land on a 'F'
				// and there isn't any Havens after their current position, so they end up not moving forward any extra squares)
			playerPositionAfterRoll = movingPlayer;

			// if statement that checks if moving player landed on a square labeled with a 'B'
			if (*movingPlayer == 'B') {
				// get the index of the moving player
				index = (int)(movingPlayer - board);
				// print to the terminal which player is the moving player, what number they rolled with their die roll,
					// that they landed on a 'B'and they are moving back 
				printf("Player %d rolled %d and moved to square %d which is a \'B\' so is moving back and lands at ", playerNumber, moveAmount, index);

				// get the resulting square the moving player is to move to after landing on a 'B' by calling the findHaven(...){...} function
				movingPlayer = findHaven(board, movingPlayer);

				// get the new index of the moving player
				index = (int)(movingPlayer - board);

				// print to the terminal the index of the square the moving player landed on
				printf("%d", index);

				// get the number of squares between the two players by calling the collision(...){...} function
				distanceBetweenPlayers = collision(movingPlayer, waitingPlayer);

				// if statement that checks if the players are on the same square (there was a "collision")
				if (distanceBetweenPlayers == 0) {
					// if statement to check if the moving player can move back one square and still be on the game board
					if (movingPlayer > board) {
						// move the moving player back one square
						movingPlayer = movingPlayer - 1;
						// get the index of the moving player
						index = (int)(movingPlayer - board);
						// print to the terminal that there was a "collision" between the two players, which player is moving back and
							// to which square they are moving back to and then set the cursor in the terminal down two lines
						printf("  -- Collision! %d is moving back 1 square to %d \n\n", playerNumber, index);

						// return the moving player's position to the calling function (int main(){...})
						return movingPlayer;
					}
					// else statement that executes if the moving player can't move back one square (they are on the first square)
					else {
						// move the cursor in the terminal down two lines
						printf("\n\n");

						// return the moving player's position to the calling function (int main(){...})
						return movingPlayer;
					}
				}
				// else statement that executes if the two players are not on the same square
				else {
					// move the cursor in the terminal down two lines
					printf("\n\n");

					// return the moving player's position to the calling function (int main(){...})
					return movingPlayer;
				}
			}
			// else if statement that executes if the moving player landed on a square labeled with a 'F'
			else if (*movingPlayer == 'F') {
				// store a copy of the moving player's position after their dice roll and initial move 
					// (in case there isn't any Havens after their current position, so they end up not moving forward any extra squares)
				playerPositionAfterRoll = movingPlayer;

				// get the resulting square the moving player is to move to after landing on a 'F' by calling the findHaven(...){...} function
				movingPlayer = findHaven(board, movingPlayer);

				// if statement that checks if the player ended up not moving forward at all after landing on a 'F' 
					// (there were no Havens after the 'F' they landed on)
				if (movingPlayer == playerPositionAfterRoll) {
					// get the index of the moving player
					index = (int)(movingPlayer - board);
					// print to the terminal which player's turn it was, the result of their dice roll, that they landed on a 'F' and
						// that there were no Havens after that 'F' so the moving player is not moving any farther forward
					printf("Player %d rolled %d and moved to square %d which is a \'F\', but there is no \'H\'s after square %d, so the player does not move any farther forward \n\n", playerNumber, moveAmount, index, index);

					// return the moving player's position to the calling function (int main(){...})
					return movingPlayer;
				}
				// else statement that executes if the moving player ended up moving forward to the nearest Haven after the 'F' they landed on
				else {
					// get the index of the moving player (after just their dice roll)
					index = (int)(playerPositionAfterRoll - board);
					// print to the terminal which player's turn it is, the result of their dice roll, which square index they landed on,
						// that that square was a 'F' and that they will be moving farther foward to another square 
						// (nearest Haven after the 'F')
					printf("Player %d rolled %d and moved to square %d which is a \'F\' so is moving forward and lands at ", playerNumber, moveAmount, index);
					// get the index of the moving player (after being moved by the findHaven(...){...} function)
					index = (int)(movingPlayer - board);
					// print to the terminal the square index the moving player landed on after the findHaven(...){...} function moved them
					printf("%d", index);

					// get the number of squares between the two players
					distanceBetweenPlayers = collision(movingPlayer, waitingPlayer);

					// if statement that checks if both players are on the same square (there was a "collision")
					if (distanceBetweenPlayers == 0) {
						// if statement that checks if the moving player can move back one square and still be on the game board
						if (movingPlayer > board) {
							// move the moving player back one square
							movingPlayer = movingPlayer - 1;
							// get the index of the moving player
							index = (int)(movingPlayer - board);
							// print to the terminal that there was a collision, whose turn it was and the square index they are moving back to
							printf("  -- Collision! %d is moving back 1 square to %d \n\n", playerNumber, index);

							// return the moving player's position to the calling function (int main(){...})
							return movingPlayer;
						}
						// else statement that executes if the moving player can't move back one square (they are on the first square)
						else {
							// move the cursor in the terminal down two lines
							printf("\n\n");

							// return the moving player's position to the calling function (int main(){...})
							return movingPlayer;
						}
					}
					// else statement that executes if the players did not end up on the same square
					else {
						// move the cursor in the terminal down two lines
						printf("\n\n");

						// return the moving player's position to the calling function (int main(){...})
						return movingPlayer;
					}
				}
			}
			// else if statement that checks if the square the moving player landed on was labeled with a lowercase letter
				// from 'a' to 'm'
			else if (((*movingPlayer >= 'a') && (*movingPlayer <= 'm'))) {
				// get a copy of the moving player's square index after their dice roll and subsequent move
				playerPositionAfterRoll = movingPlayer;
				// get the index of the moving player after their dice roll move
				index2 = (int)(playerPositionAfterRoll - board);
				// set the square index of the moving player to the result of the chuteLadder(...){...} function
				movingPlayer = chuteLadder(movingPlayer, board);
				// get the index of the moving player after the chuteLadder(...){...} function
				index = (int)(movingPlayer - board);
				// change the character at the index that the player moved to after their dice roll to a hyphen ("-")
				*playerPositionAfterRoll = '-';

				// print to the terminal which player's turn it is, the result of their dice roll, 
					// which square they moved to after their dice roll, that the player landed on a "chute",
					// that they are moving backwards and to which square index they are moving back to
				printf("Player %d rolled %d and moved to square %d which is a chute and is moving back to square %d", playerNumber, moveAmount, index2, index);

				// get the number of squares between the two players by calling the collision(...){...} function
				distanceBetweenPlayers = collision(movingPlayer, waitingPlayer);

				// if statement that checks if both players ended up on the same square
				if (distanceBetweenPlayers == 0) {
					// if statement that checks if the moving player can move back one square and still be on the game board
					if (movingPlayer > board) {
						// move the moving player back one square
						movingPlayer = movingPlayer - 1;
						// get the index of the moving player
						index = (int)(movingPlayer - board);
						// print to the terminal that there was a collision, whose turn it was and the square index they are moving back to
						printf("  -- Collision! %d is moving back 1 square to %d \n\n", playerNumber, index);

						// return the moving player's position to the calling function (int main(){...})
						return movingPlayer;
					}
					// else statement that executes if the moving player can't move back one square (they are on the first square)
					else {
						// move the cursor in the terminal down two lines
						printf("\n\n");

						// return the moving player's position to the calling function (int main(){...})
						return movingPlayer;
					}
				}
				// else statement that executes if the players did not end up on the same square
				else {
					// move the cursor in the terminal down two lines
					printf("\n\n");

					// return the moving player's position to the calling function (int main(){...})
					return movingPlayer;
				}
			}
			// else if statement that checks if the moving player landed on a square labeled with a lowercase letter in the range from
				// 'o' to 'z'
			else if (((*movingPlayer >= 'o') && (*movingPlayer <= 'z'))) {
				// copy the moving player's index after their dice roll and initial move
				playerPositionAfterRoll = movingPlayer;
				// get the index of the moving player after their dice roll and initial move
				index2 = (int)(playerPositionAfterRoll - board);
				// set the index of the moving player to the result of the chuteLadder(...){...} function
				movingPlayer = chuteLadder(movingPlayer, board);
				// get the index of the moving player after the chuteLadder(...){...} function
				index = (int)(movingPlayer - board);
				// change the character at the index that the player moved to after their dice roll to a hyphen ("-")
				*playerPositionAfterRoll = '-';

				// print to the terminal which player's turn it is, the result of their dice roll, 
					// which square index they moved to after their dice roll move, that they landed on a ladder and are moving forward and
					// which square index they are landing on
				printf("Player %d rolled %d and moved to square %d which is a ladder and is moving forward to square %d", playerNumber, moveAmount, index2, index);

				// get the number of squares between the two players
				distanceBetweenPlayers = collision(movingPlayer, waitingPlayer);

				// if statement that checks if the two players ended up on the same square (there was a "collision")
				if (distanceBetweenPlayers == 0) {
					// if statement that checks if the moving player can move back one square and still be on the game board
					if (movingPlayer != board) {
						// move the moving player back one square
						movingPlayer = movingPlayer - 1;
						// get the index of the moving player
						index = (int)(movingPlayer - board);
						// print to the terminal that there was a collision, whose turn it was and the square index they are moving back to
						printf("  -- Collision! %d is moving back 1 square to %d \n\n", playerNumber, index);

						// return the moving player's position to the calling function (int main(){...})
						return movingPlayer;
					}
					// else statement that executes if the moving player can't move back one square (they are on the first square)
					else {
						// move the cursor in the terminal down two lines
						printf("\n\n");

						// return the moving player's position to the calling function (int main(){...})
						return movingPlayer;
					}
				}
				// else statement that executes if the players did not end up on the same square
				else {
					// move the cursor in the terminal down two lines
					printf("\n\n");

					// return the moving player's position to the calling function (int main(){...})
					return movingPlayer;
				}
			}
			// else statement that executes if the player lands on a square labeled with anything not already tested for
				// (examples: ' ', 'n', '-', '*')
			else {
				// get the number of squares between the two players
				distanceBetweenPlayers = collision(movingPlayer, waitingPlayer);

				// if statement that checks if the two players landed on the same square (there was a "collision")
				if (distanceBetweenPlayers == 0) {
					// get the index of the moving player
					index = (int)(movingPlayer - board);
					// print to the terminal which player's turn it is, the result of their dice roll and which square index they moved to
					printf("Player %d rolled %d and moved to square %d", playerNumber, moveAmount, index);

					// if statement that checks if the moving player can move back one square and still be on the game board
					if (movingPlayer != board) {
						// move the moving player back one square
						movingPlayer = movingPlayer - 1;
						// get the index of the moving player
						index = (int)(movingPlayer - board);
						// print to the terminal that there was a collision, whose turn it was and the square index they are moving back to
						printf("  -- Collision! %d is moving back 1 square to %d \n\n", playerNumber, index);

						// return the moving player's position to the calling function (int main(){...})
						return movingPlayer;
					}
					// else statement that executes if the moving player can't move back one square (they are on the first square)
					else {
						// move the cursor in the terminal down two lines
						printf("\n\n");

						// return the moving player's position to the calling function (int main(){...})
						return movingPlayer;
					}
				}
				// else statement that executes if the two players did not land on the same square
				else {
					// get the index of the moving player
					index = (int)(movingPlayer - board);
					// print to the terminal which player's turn it is, the result of their dice roll and which square index they moved to
					printf("Player %d rolled %d and moved to square %d \n\n", playerNumber, moveAmount, index);

					// return the moving player's position to the calling function (int main(){...})
					return movingPlayer;
				}
			}
		}
	}
}



// Used when a player lands on a 'B' or 'F'. This function searches for the
	// the nearest haven (denoted as a 'H'), with the direction
	// depending on what the player landed on. This function changes the board
	// and returns where the player is to move to the move(...){...} function.
char* findHaven(char board[], char* player) {

	// This char pointer is used to store the original position of the player who's turn it is
	char* originalPlayerPosition = player;

	// if statement that checks if the square the player who's turn it is landed on a square labeled with a 'B'
	if (*player == 'B') {
		// while loop that executes while the player hasn't reached the beginning of the game board
		while (player > board) {
			// if statement that checks if the player has been moved onto a square labeled with a 'H'
			if (*player == 'H') {
				// change the square labeled with a 'H' that the player was moved onto to a "*"
				*player = '*';

				// return the player's position on the game board
				return player;
			}
			// move the player's position back one square
			player--;
		}
		// return the player's location on the game board
		return player;
	}
	// else statement that executes if the player did not land on a 'B' (the player landed on a 'F')
	else {
		// while loop that executes while the player hasn't moved passed the end of the game board
		while (player < board + SIZE) {
			// if statement that checks if the player has been moved onto a square labeled with a 'H'
			if (*player == 'H') {
				// change the square labeled with a 'H' that the player was moved onto to a "*"
				*player = '*';

				// return the player's position on the game board
				return player;
			}
			// move the player's position forward one square
			player++;
		}
		// return the original square the player was on if there wasn't any Havens ('H' squares) after the square they originally landed on
		return originalPlayerPosition;
	}
}

// Used to dictate where the player is to move to when that player lands on
	// a chute (‘a’ – ‘m’: a chute, move backward) or
	// a ladder (‘o’ – ‘z’: a ladder, move forward)
		// and then change that square on the board to a ‘-’.
		// This function calculates how far the player is to move and then
		// return that forward or backward distance to the move(...){...}
		// function that calls this chuteLadder(...){...} function.
char* chuteLadder(char *player, char board[]) {
	
	// char pointer to store a copy of the player's original position 
	char *pointerCopy;
	// int variable to store the amount of the squares to move the player
	int moveAmount;

	// set the char pointer to the square index of the player
	pointerCopy = player;

	// if statement that checks if the player did not land on a square labeled with a 'n'
	if (*player != 'n') {
		// get the amount of squares to move the player on the game board
		moveAmount = (int)(*player - 'n');

		// if statement that checks if the player is to be moved backwards on the game board
		if (moveAmount < 0) {
			// if statement that checks if the player can move back that many squares and still be on the game board
			if (player + moveAmount >= board) {
				// move the player the calculated number of squares
				player += moveAmount;
				// set the square the player originally landed on to be labeled as a hyphen ("-")
				*pointerCopy = '-';

				// return the player's position on the game board
				return player;
			}
			// else statement that executes if the player cannot be moved back the calculated number of squares and still be on the game board
			else {
				// set the player's location to the first square on the board
				player = &board[0];
				// set the square the player originally landed on to be labeled as a hyphen ("-")
				*pointerCopy = '-';

				// return the player's position on the game board
				return player;
			}
		}
		// else statement that executes if the player is to be moved in a forward direction
		else {
			// move the player forward the calculated number of squares
			player += moveAmount;
			// set the square the player originally landed on to be labeled as a hyphen ("-")
			*pointerCopy = '-';
		}
	}

	// return the player's position on the game board
	return player;
}


// This function was added by me to detect collisions among players.
	// If this function returns a "0" (zero), that means there is zero distance
	// between the players, meaning there was a collision. If this function
	// returns any int other than "0" (zero), then there was some distance
	// between the players and there was no collision. This function acts like a
	// boolean method does in Java
int collision(char *p1, char *p2) {

	// return the int difference between the positions of the two players.
		// If this function returns a "0" (zero), player1 and player2 are on the same square on the game board
	return ((int)p1 - (int)p2);
}


// This function was added by me to simulate rolling a six-sided die.
	// This function returns the int value result of "rolling the die"
int rollDice() {

	// return a random int between the numbers 1 and 6 to simulate the rolling of a single six-sided die
	return (rand() % 6) + 1;
}