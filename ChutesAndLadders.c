#include "chutes.h"


/*****************************************************************************************************************************************
 *****************************************************************************************************************************************
 *****    Class: CSC-362-001             Semester: Fall 2019             Professor: Richard Fox             Student: Ryan Huffman    *****
 *****-------------------------------------------------------------------------------------------------------------------------------*****
 *****                                         Programming Assignment #3: Chutes and Ladders                                         *****
 *****_______________________________________________________________________________________________________________________________*****
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
 *****                                                                                                                               *****
 *****************************************************************************************************************************************
 *****************************************************************************************************************************************/


int main() {

	/* ------------------------------------------------ VARIABLE DECLARATIONS ------------------------------------------------- */
	// Character Array that represents the Chutes and Ladders game board with the player caused changes and player positions
	char board[100] = "  mHk nH l B He Flq p H  hByHlho H B  jr HFB ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB ";
	/* Alternate game board
	char board[100] = "  mHk  H l B He Flq p H  hByHlho H B  jr HFB ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB "; 
	*/

	// Character Array that stores a copy of the original game board
	char gameBoard[100] = "  mHk nH l B He Flq p H  hByHlho H B  jr HFB ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB ";

	// Character pointer variables that represent player 1 and player 2 and 
		// initialize both players to start on the first square on the board
	char* player1 = &board[0];
	char* player2 = &board[0]; 

	// FILE pointer to the output file
	FILE* outputFP;

	// Character pointer variable to store the name of the output file
	char* outputFileName = "testOutputFile.txt";

	// int variable to simulate a boolean variable to tell whether the game has ended (0 = false, any int other than 0 = true)
	int isGameOver = 0;



	// TEST VARIABLE
	// int i = 0;
	/* -------------------------------------------- END OF VARIABLE DECLARATIONS ---------------------------------------------- */

	// Used to seed the rand() function 
		// to make sure all calls to the rollDice(){...} function return a truly random number from 1 - 6
	srand(time(0)); 

	// Open the output file or create the file if it does not already exist and
		// then set the FILE pointer to "write mode" to write output to that file
	outputFP = fopen(outputFileName, "w");




//////////////////////////////////////////// BEGINNING TESTING CODE: DELETE BEFORE TURN IN /////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	/////////////////////// BEGINNING: HOW TO MOVE THE POINTER THROUGH THE BOARD! ///////////////////////////////
	player1 += 3;
	player2 += 7;
	// printf("player 1 = %c \nplayer 2 = %c \n", *player1, *player2);
	output(board, &player1, &player2, outputFP);

	
	////////////////////////// END: HOW TO MOVE THE POINTER THROUGH THE BOARD! //////////////////////////////////
	// fprintf(outputFP, "player 1 = %c \nplayer 2 = %c \n", *player1, *player2);
	player1 += 10;
	player2 += 20;
	// printf("player 1 = %c \nplayer 2 = %c \n", *player1, *player2);
	output(board, &player1, &player2, outputFP);
	// fprintf(outputFP, "player 1 = %c \nplayer 2 = %c \n", *player1, *player2);


	////////////////////////////// THIS FOR LOOP WORKS & IS FOR THE output(...){...} FUNCTION ///////////////////////////////////////
	/*
	for (int i = 0; i < SIZE; i++) {
		putc(board[i], outputFP);
	}
	*/
	////////////////////////////// THIS ABOVE FOR LOOP WORKS & IS FOR THE output(...){...} FUNCTION /////////////////////////////////
	

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// END OF TESTING CODE: DELETE BEFORE TURN IN //////////////////////////////////////////
	output(board, player1, player2, outputFP);

	// while loop that will execute until the game is over
	while (isGameOver == 0) {
		isGameOver = isGameOver + 1;
	}


	// Close the output file with the FILE pointer
	fclose(outputFP);

	// return 0 (zero) to indicate the program finished with no errors
	return 0;
}