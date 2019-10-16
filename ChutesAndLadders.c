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
	// Character Array that represents the Chutes and Ladders game board
	char board[100] = "  mHk nH l B He Flq p H  hByHlho H B  jr HFB ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB ";
	/** Alternate game board
	char board[100] = "  mHk  H l B He Flq p H  hByHlho H B  jr HFB ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB "; 
	*/

	// Character pointer variables that represent player 1 and player 2 and 
		// initialize both players to start on the first square on the board
	char* p1 = board[0];
	char* p2 = board[0];
	/* -------------------------------------------- END OF VARIABLE DECLARATIONS ---------------------------------------------- */


	// Used to seed the rand() function 
		// to make sure all calls to the rollDice(){...} function return a truly random number from 1 - 6
	srand(time(0)); 


	// return a 0 (zero) to indicate the program finished with no errors
	return 0;
}