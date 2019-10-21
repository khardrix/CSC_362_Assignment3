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



	// TEST VARIABLES
	int testMove;
	int i;
	int count;
	int index;
	int distanceBetweenPlayers;
	int distanceToMove;

	int player1Index;
	int player2Index;

	char* testPointer;
	/* -------------------------------------------- END OF VARIABLE DECLARATIONS ---------------------------------------------- */

	// Used to seed the rand() function 
		// to make sure all calls to the rollDice(){...} function return a truly random number from 1 - 6
	srand(time(0)); 

	// Open the output file or create the file if it does not already exist and
		// then set the FILE pointer to "write mode" to write output to that file
	outputFP = fopen(outputFileName, "w");




//////////////////////////////////////////// BEGINNING TESTING CODE: DELETE BEFORE TURN IN /////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	/////////////////////// START OF TESTING HOW TO MOVE THE POINTER THROUGH THE BOARD //////////////////////////
	/*
	printf("Original board = %s \n", board);
	printf("if the following number is a 0 then there was a collision: %d \n", collision(player1, player2));
	player1 += 11;
	player2 += 7;
	printf("player 1 = %c \nplayer 2 = %c \n", *player1, *player2);
	output(board, player1, player2, outputFP);
	printf("board after first player1 and player 2 moves = %s \n", board);

	findHaven(board, player1, *player1);

	printf("if the following number is a 0 then there was a collision: %d \n", collision(player1, player2));
	player1 += 10;
	player2 += 20;
	printf("player 1 = %c \nplayer 2 = %c \n", *player1, *player2);
	output(board, player1, player2, outputFP);
	printf("board after second player1 and player 2 moves = %s \n", board);

	printf("if the following number is a 0 then there was a collision: %d \n", collision(player1, player2));
	player1 += 3;
	player2 += 6;
	printf("player 1 = %c \nplayer 2 = %c \n", *player1, *player2);
	output(board, player1, player2, outputFP);
	printf("board after third player1 and player 2 moves = %s \n", board);
	*/
	///////////////////////// END OF TESTING HOW TO MOVE THE POINTER THROUGH THE BOARD //////////////////////////




	//////////////////// START OF TESTING rollDice(){...} FUNCTION FOR move(...){...} FUNCTION //////////////////
	/*
	for (i = 1; i <= 20; i++) {
		testMove = rollDice();
		printf("Dice roll #%d was: %d \n", i, testMove);
	}
	*/
	///////////////////// END OF TESTING rollDice(){...} FUNCTION FOR move(...){...} FUNCTION ///////////////////




	/////////////////// START OF TESTING collition(){...} FUNCTION FOR move(...){...} FUNCTION //////////////////
	/*
	distanceBetweenPlayers = collision(player1, player2);
	// "0" (zero) squares when there is a collision (player1 and player2 are on the same square)
	printf("The distance between Player 1 ahd Player 2 is %d squares \n", distanceBetweenPlayers);

	player1 += 3;
	player2 += 4;
	distanceBetweenPlayers = collision(player1, player2);
	// Negative int when player2 is ahead on the board of player1
	printf("The distance between Player 1 ahd Player 2 is %d squares \n", distanceBetweenPlayers);

	player1 += 4;
	player2 += 3;
	distanceBetweenPlayers = collision(player1, player2);
	// "0" (zero) squares when there is a collision (player1 and player2 are on the same square)
	printf("The distance between Player 1 ahd Player 2 is %d squares \n", distanceBetweenPlayers);

	player1 += 4;
	player2 += 3;
	distanceBetweenPlayers = collision(player1, player2);
	// Positive int when player1 is ahead on the board of player2 
	printf("The distance between Player 1 ahd Player 2 is %d squares \n", distanceBetweenPlayers);
	*/
	//////////////////// END OF TESTING collition(){...} FUNCTION FOR move(...){...} FUNCTION ///////////////////




	///////// START OF TESTING HOW TO CHANGE A VALUE AT A POINTER INDEX INSIDE THE BOARD CHAR ARRAY /////////////
	/*
	player1 += 3;
	printf("player1 is pointing at %c \n", *player1);
	while (*player2 != '\0') {
		*player1 = '*';

		printf("%c", *player2);
		
		player2++;
	}
	*/
	////////// END OF TESTING HOW TO CHANGE A VALUE AT A POINTER INDEX INSIDE THE BOARD CHAR ARRAY //////////////




	//////////////////////////// START OF TESTING CREATING A COPY OF A char pointer /////////////////////////////
	/*
	player1 += 3;
	printf("player1 is pointing at %c \n", *player1);
	testPointer = player1;
	printf("testPointer is pointing at %c \n", *testPointer);

	testPointer++;
	printf("testPointer is pointing at %c \n", *testPointer);
	printf("player1 is pointing at %c \n", *player1);
	*/
	///////////////////////////// END OF TESTING CREATING A COPY OF A char pointer //////////////////////////////




	/////////////// START OF TESTING TO CALCULATE DISTANCE TO MOVE BECAUSE OF CHUTES AND LADDERS ////////////////
	/*
	player1 += 9;
	printf("player1 is pointing at %c \n", *player1);

	index = (int)(player1 - board);
	printf("player1 is at square#: %d \n", index);

	distanceToMove = (int)(*player1 - 'n');
	printf("player1 needs to move %d squares \n\n\n\n", distanceToMove);

	printf("AFTER player1 HAS BEEN MOVED \n");

	player1 += distanceToMove;
	printf("player1 is pointing at %c \n", *player1);

	index = (int)(player1 - board);
	printf("player1 is at square#: %d \n", index);



	printf("\n\n\n\nAFTER MOVING player1 AGAIN \n");
	player1 += 20;
	printf("player1 is pointing at %c \n", *player1);

	index = (int)(player1 - board);
	printf("player1 is at square#: %d \n", index);

	distanceToMove = (int)(*player1 - 'n');
	printf("player1 needs to move %d squares \n\n\n\n", distanceToMove);

	printf("AFTER player1 HAS BEEN MOVED \n");

	player1 += distanceToMove;
	printf("player1 is pointing at %c \n", *player1);

	index = (int)(player1 - board);
	printf("player1 is at square#: %d \n", index);
	*/
	//////////////// END OF TESTING TO CALCULATE DISTANCE TO MOVE BECAUSE OF CHUTES AND LADDERS /////////////////




	////////////// START OF TESTING move(...){...} FUNCTION, WHICH IS HOW EACH PLAYER TAKES A TURN //////////////
	/*
	printf("\n\n\n\n\n\n\n\nTHIS TESTING IS FOR THE move(...){...} function, which is basically how the game is played! \n\n");
	
	for (count = 1; count < 10; count++) {
		player1 = move(player1, player2, 1, board, SIZE);
	}
	*/
	/////////////// END OF TESTING move(...){...} FUNCTION, WHICH IS HOW EACH PLAYER TAKES A TURN ///////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// END OF TESTING CODE: DELETE BEFORE TURN IN //////////////////////////////////////////
	

	// while loop that will execute until the game is over
	while (player1 <= board + (SIZE - 1) && player2 <= board + (SIZE - 1)) {
		// TEMPORARILY COMMENTED OUT! MAKE SURE TO UNCOMMENT AND FINISH GAME IN ORDER TO TURN IN
		player1 = move(player1, player2, 1, board, SIZE); // player 1’s turn
		player2 = move(player2, player1, 2, board, SIZE); // player 2’s turn
		
		output(board, player1, player2, outputFP);
		
		isGameOver = isGameOver + 1;
	}

	player1Index = (int)(player1 - board);
	player2Index = (int)(player2 - board);

	printf("PLAYER 1 INDEX = %d \n", player1Index);
	printf("PLAYER 2 INDEX = %d \n\n", player2Index);

	if (player1Index > player2Index) {
		printf("PLAYER 1 WINS! \n\n");
	}
	else if (player1Index < player2Index) {
		printf("PLAYER 2 WINS! \n\n");
	}
	else {
		printf("THERE WAS A TIE! \n\n");
	}



	// Close the output file with the FILE pointer
	fclose(outputFP);

	// return 0 (zero) to indicate the program finished with no errors
	return 0;
}