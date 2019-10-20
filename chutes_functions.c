#include "chutes.h"


// Used to output the current game board, including player 1's and player 2's
	// positions to a disk file on a single line.
void output(char board[], char *player1, char *player2, FILE *outputFP) {

	// while loop to iterate, char-by-char, through the passed in char array parameter, board (that serves as the game board)
	while (*board != '\0') {
		// if statement that checks if the passed in char pointer parameter, player1, is located at this position in the
			// passed in char array parameter, board
		if (board == player1) {
			// Output a '1' to the outfile specified by the passed in FILE pointer parameter, outputFP
			putc('1', outputFP);
			// increment the position inside the passed in char array parameter, board
			board++;
		}
		// else if statement that checks if the passed in char pointer parameter, player2, is located at this position in the
			// passed in char array parameter, board
		else if (board == player2) {
			// Output a '2' to the outfile specified by the passed in FILE pointer parameter, outputFP
			putc('2', outputFP);
			// increment the position inside the passed in char array parameter, board
			board++;
		}

		// output to the file specified by the passed in FILE pointer parameter, outputFP, the char at the 
			// current position inside the passed in char array parameter, board
		putc(*board, outputFP);

		// increment the position inside the passed in char array parameter, board
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
	/*
	move – This function receives both player pointers, the board, the player number (1 or
   2) and the size of the board. Output the player number. Randomly generate a move
   from 1-6. Move the player by that amount and determine if the player has landed on a
   chute/ladder or ‘B’/’F’, if so, call the appropriate function (see below); if not or if the
   player has moved because of it, see if the player has landed on the other player
   (p1==p2) and if so, move this player back 1 additional square indicating a collision
   occurred. Output the amount the player moved and where the player is now (the current
   location is p1 – board or p2 - board). NOTE: All output from this function goes to the
   console window using printf. main will call move twice, once for each player, using
   notation like this: 
        p1 = move(p1, p2, 1, board, SIZE); // player 1’s turn 
        p2 = move(p2, p1, 2, board, SIZE); // player 2’s turn 
   SIZE is a constant, passed as a parameter. It is needed before printing *p1 or *p2
   because you do not want to print *p1 or *p2 if p1/p2 >= board+SIZE (may cause an
   error). NOTE: as this function returns the new location of p1/p2, it is a char * (it returns
   a char pointer).
	*/

	int index;
	int index2;
	int distance;
	int distanceBetweenPlayers;
	char *originalPlayerPosition; 
	char* charPointingAt;

	distance = rollDice();
	

	if (movingPlayer >= board) {
		if((movingPlayer + distance) < (board + size)) {
			movingPlayer = movingPlayer + distance;
			originalPlayerPosition = movingPlayer;
			distanceBetweenPlayers = collision(movingPlayer, waitingPlayer);

			if (*movingPlayer == 'B') {
				index = (int)(movingPlayer - board);
				printf("Player %d rolled %d and moved to square %d which is a \'B\' so is moving back and lands at ", playerNumber, distance, index);
				movingPlayer = findHaven(board, movingPlayer, 'B');
				index = (int)(movingPlayer - board);
				printf("%d", index);

				distanceBetweenPlayers = collision(movingPlayer, waitingPlayer);

				if (distanceBetweenPlayers == 0) {
					if (movingPlayer != board) {
						movingPlayer = movingPlayer - 1;
						index = (int)(movingPlayer - board);
						printf("  -- Collision! %d is moving back 1 square to %d \n\n", playerNumber, index);
					}
				}
				else {
					printf("\n\n");
				}
			}
			else if (*movingPlayer == 'F') {
				movingPlayer = findHaven(board, movingPlayer, 'F');

				if (originalPlayerPosition != movingPlayer) {
					index = (int)(originalPlayerPosition - board);
					printf("Player %d rolled %d and moved to square %d which is a \'F\' so is moving forward and lands at ", playerNumber, distance, index);
					index = (int)(movingPlayer - board);
					printf("%d", index);

					distanceBetweenPlayers = collision(movingPlayer, waitingPlayer);

					if (distanceBetweenPlayers == 0) {
						if (movingPlayer != board) {
							movingPlayer = movingPlayer - 1;
							index = (int)(movingPlayer - board);
							printf("  -- Collision! %d is moving back 1 square to %d \n\n", playerNumber, index);
						}
					}
					else {
						printf("\n\n");
					}
				}
				else {
					index = (int)(movingPlayer - board);
					printf("Player %d rolled %d and moved to square %d which is a \'F\', but there is no \'H\'s after square %d, so the player does not move any further forward \n\n", playerNumber, distance, index, index);
				}
			}
			else if (*movingPlayer == ' ') {
				if (distanceBetweenPlayers != 0) {
					index = (int)(movingPlayer - board);
					printf("Player %d rolled %d and moved to square %d \n\n", playerNumber, distance, index);
				}
				else {
					index = (int)(movingPlayer - board);
					printf("Player %d rolled %d and moved to square %d", playerNumber, distance, index);
					movingPlayer = movingPlayer - 1;
					index = (int)(movingPlayer - board);
					printf("  -- Collision! %d is moving back 1 square to %d \n\n", playerNumber, index);
				}
			}
			else {
				if (*movingPlayer >= 'a' && *movingPlayer <= 'm') {
					originalPlayerPosition = movingPlayer;
					index2 = (int)(originalPlayerPosition - board);
					movingPlayer = chuteLadder(movingPlayer, board);
					index = (int)(movingPlayer - board);
					*originalPlayerPosition = '-';

					printf("Player %d rolled %d and moved to square %d which is a chute and is moving back to square %d", playerNumber, distance, index2, index);

					distanceBetweenPlayers = collision(movingPlayer, waitingPlayer);

					if (distanceBetweenPlayers == 0) {
						if (movingPlayer != board) {
							movingPlayer = movingPlayer - 1;
							index = (int)(movingPlayer - board);
							printf("  -- Collision! %d is moving back 1 square to %d \n\n", playerNumber, index);
						}
						else {
							printf("\n\n");
						}
					}
					else {
						printf("\n\n");
					}
				}
				else if (*movingPlayer >= 'o' && *movingPlayer <= 'z') {
					originalPlayerPosition = movingPlayer;
					index2 = (int)(originalPlayerPosition - board);
					movingPlayer = chuteLadder(movingPlayer, board);
					index = (int)(movingPlayer - board);
					*originalPlayerPosition = '-';

					printf("Player %d rolled %d and moved to square %d which is a ladder and is moving forward to square %d", playerNumber, distance, index2, index);

					distanceBetweenPlayers = collision(movingPlayer, waitingPlayer);

					if (distanceBetweenPlayers == 0) {
						if (movingPlayer != board) {
							movingPlayer = movingPlayer - 1;
							index = (int)(movingPlayer - board);
							printf("  -- Collision! %d is moving back 1 square to %d \n\n", playerNumber, index);
						}
						else {
							printf("\n\n");
						}
					}
					else {
						printf("\n\n");
					}
				}
			} 
		}
		else {
			movingPlayer += distance;
			printf("Player %d has reached the end of the game board! \n\n", playerNumber);
		}
	}

	return movingPlayer;
}

// Used when a player lands on a 'B' or 'F'. This function searches for the
	// the nearest haven (denoted as a 'H'), with the direction
	// depending on what the player landed on. This function changes the board
	// and returns where the player is to move to the move(...){...} function.
char* findHaven(char board[], char* player, char direction) {
	
	// This char pointer is used to store the original position of the passed in parameter char pointer variable, player
	char *originalPlayerPosition = player;

	if (direction == 'B') {
		while (player > board) {
			if (*player == 'H') {
				*player = '*';
				return player;
			}
			player--;
		}
		return player;
	}
	else {
		while (player < board + SIZE) {
			if (*player == 'H') {
				*player = '*';
				return player;
			}
			player++;
		}
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

	char *pointerCopy;
	int moveAmount;

	pointerCopy = player;

	if (*player != 'n') {
		moveAmount = (int)(*player - 'n');

		if (moveAmount < 0) {
			if (player + moveAmount >= board) {
				player += moveAmount;
				*pointerCopy = '-';
				return player;
			}
			else {
				player = &board[0];
				*pointerCopy = '-';
				return player;
			}
		}
		else {
			player += moveAmount;
			*pointerCopy = '-';
		}
	}

	return player;
}


// This function was added by me to detect collisions among players.
	// If this function returns a "0" (zero), that means there is zero distance
	// between the players, meaning there was a collision. If this function
	// returns any int other than "0" (zero), then there was some distance
	// between the players and there was no collision. This function acts like a
	// boolean method does in Java
int collision(char *p1, char *p2) {

	// return the int difference between the positions of the passed in char pointer parameters, p1 and p2.
		// If this function returns a "0" (zero), player1 and player2 are on the same square on the game board
	return ((int)p1 - (int)p2);
}


// This function was added by me to simulate rolling a six-sided die.
	// This function returns the int value result of "rolling the die"
int rollDice() {

	// return a random int between the numbers 1 and 6 to simulate the rolling of a single six-sided die
	return (rand() % 6) + 1;
}