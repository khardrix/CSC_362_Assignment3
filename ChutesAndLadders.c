#include "chutes.h"


/*****************************************************************************************************************************************
 *****************************************************************************************************************************************
 *****    Class: CSC-362-001             Semester: Fall 2019             Professor: Richard Fox             Student: Ryan Huffman    *****
 *****-------------------------------------------------------------------------------------------------------------------------------*****
 *****                                         Programming Assignment #3: Chutes and Ladders                                         *****
 *****_______________________________________________________________________________________________________________________________*****
 *****                                  This program is a version of the game "Chutes and Ladders"                                   *****
 *****                                                                                                                               *****
 *****                                    The characters of the board have the following meaning:                                    *****  
 ***** ‘ ’: a normal square, a player who lands here does not move again in this turn (unless the other player is on the same square)*****
 *****                     ‘B’: move backward to the nearest preceding haven, stop at 0 if no more havens exist                      *****  
 *****                            ‘F’: move forward to the next haven, stay here if no more havens exist                             *****
 *****                            ‘H’: a haven which a player might move to when landing on a ‘B’ or ‘F’;                            *****
 *****                                once moved to because of a ‘B’ or ‘F’, change the ‘H’ to a ‘*’                                 *****
 *****   (do not change the ‘H’ if the player lands on this square normally, that is, without reaching here because of ‘B’ or ‘F’)   *****
 *****                    ‘a’ – ‘m’: a chute, move backward (see below), change this to ‘-’ after the play moves                     *****
 *****                    ‘o’ – ‘z’: a ladder, move forward (see below), change this to ‘-’ after the play moves                     *****
 *****                                                       ‘n’ – is not used                                                       *****
 *****-------------------------------------------------------------------------------------------------------------------------------*****                                                                                
 *****                       Each player takes a turn rolling a single six-sided die and moving along the board and                  *****  
 *****                         depending on what they land on (as explained above), they may end up moving more.                     *****
 *****       The player who's turn it is may end up moving yet again if they land on the same square as the other player and         *****
 *****                   there is a "collision." In this case (unless the players are on the very first square),                     *****
 *****                                       the moving player is forced back one square.                                            *****
 *****                                                                                                                               *****
 *****                 The players take turns until at least one player reaches or exceeds the end of the game board.                *****
 *****              At this point, the players' indices are compared and the player with the greatest index wins the game.           *****
 *****                                                                                                                               *****
 *****                  Each player's individual turns and the result of that turn are output to the terminal.                       *****
 *****        After each round (player 1 and player 2 have taken a turn), the altered array (including where the players are)        *****
 *****                  is output on a single line to the output file as specified by the FILE pointer variable.                     *****
 *****************************************************************************************************************************************
 *****************************************************************************************************************************************/


int main() {

	/* ------------------------------------------------ VARIABLE DECLARATIONS ------------------------------------------------- */
	// Character Array that represents the Chutes and Ladders game board with the player caused changes and player positions
	char board[100] = "  mHk nH l B He Flq p H  hByHlho H B  jr HFB ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB ";

	// Character pointer variables that represent player 1 and player 2 and 
		// initialize both players to start on the first square on the board
	char* player1 = &board[0];
	char* player2 = &board[0]; 

	// FILE pointer to the output file
	FILE* outputFP;

	// Character pointer variable to store the name of the output file
	char* outputFileName = "testOutputFile.txt";

	// int variables to store the player indexes to test for the winner after at least one player reaches the end of the board
	int player1Index;
	int player2Index;
	/* -------------------------------------------- END OF VARIABLE DECLARATIONS ---------------------------------------------- */

	// Used to seed the rand() function 
		// to make sure all calls to the rollDice(){...} function return a truly random number from 1 - 6
	srand(time(0)); 

	// Open the output file or create the file if it does not already exist and
		// then set the FILE pointer to "write mode" to write output to that file
	outputFP = fopen(outputFileName, "w");

	// while loop that will execute until the game is over 
		// (when at least one player gets to or exceeds the end of the board)
	while (player1 <= board + (SIZE - 1) && player2 <= board + (SIZE - 1)) {
		
		player1 = move(player1, player2, 1, board, SIZE); // player 1’s turn
		player2 = move(player2, player1, 2, board, SIZE); // player 2’s turn
		
		// Output both players current position on the board and the altered game board after each round
		output(board, player1, player2, outputFP);
	}

	player1Index = (int)(player1 - board); // player 1's index after the game ends
	player2Index = (int)(player2 - board); // player 2's index after the game ends

	// Print to the terminal the indices of player 1 and player 2 after the end of the game
	printf("PLAYER 1 INDEX = %d \n", player1Index);
	printf("PLAYER 2 INDEX = %d \n\n", player2Index);

	// if statement to check if player 1 won (player 1's index was greater than player 2's at the end of the game)
	if (player1Index > player2Index) {
		// Print to the terminal that player 1 won
		printf("PLAYER 1 WINS! \n\n");
	}
	// else if statement to check if player 2 won (player 2's index was greater than player 1's at the end of the game)
	else if (player1Index < player2Index) {
		// Print to the terminal that player 2 won
		printf("PLAYER 2 WINS! \n\n");
	}
	// else statement that executes if player 1 and player 2 tied
	else {
		// Print to the terminal that player 1 and player 2 tied
		printf("THERE WAS A TIE! \n\n");
	}

	
	// Close the output file with the FILE pointer
	fclose(outputFP);


	// return 0 (zero) to indicate the program finished with no errors
	return 0;
}