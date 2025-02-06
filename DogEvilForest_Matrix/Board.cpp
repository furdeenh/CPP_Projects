/*
 * Board.cpp
 *
 *  Created on: Feb 22, 2023
 *     Author: Furdeen Hasan and Lizzy Kalfas
 */



#include "Board.hpp"
#include <iostream>
using namespace std;

Board::Board(char diff, bool d) {
	level = diff;
	debug = d;
	wallStrength = 6;
	InitAll();
}
Board::Board(bool d) {
	level = 'e';
	debug = d;
	wallStrength = 6;
	InitAll();
}
Board::Board(char diff, string name, bool d) {
	level = diff;
	debug = d;
	mydog.name = name;
	wallStrength = 6;
	InitAll();
}
void Board::InitAll() {
	bool keepPlaying = true;
	while (keepPlaying) {
		cout << "What level of difficulty do you want (e, m, or h)?" << endl;
		char c;
		cin >> c;
		level = c;
		startx = rand() % size;
		starty = 0;
		endx = rand() % size;
		endy = size - 1;
		mydog.x = startx;
		mydog.y = starty;
		boardConfig();
		addFood();
		addTraps();
		printBoard();
		playGame();
		cout << "Play again? " << endl;
		string s = "no";
		cin >> s;
		if (s == "yes" || s == "Yes" || s == "Y" || s == "y") {
			keepPlaying = true;
			mydog.reset();
		} else {
			cout << "Thanks for playing!" << endl;
			keepPlaying = false;
		}
	}

}

/***********************************************************************/
/* HERE'S WHERE THE CODE GOES!                                         */
/***********************************************************************/

void Board::printBoard() {
	//(8 pts)
	//Instructions for this method:
//	 this method first uses the dog's printDog method to print out info
//	 about the dog, and then it prints out the board as follows:
//	 *
//	 This method prints out the board such that it looks like a board.  It
//	 prints a blank space for any square (for squares that do not have
//	 food, traps, walls, the dog, and aren't the beginning or the ending.
//   (at first, there will be no food or traps, or even walls or dog, but we
//   will be adding food as 'F' character, traps as 'T' character, walls as
//   '|' or '_' characters, and the dog 'D' character to the board, so you want
//   to print a space for everything that isn't a 'T','F','|','_',or'D'.
//	 Otherwise it prints out the character in the square. Note that I printed a
//	 border around the entire board so it was easier to look at, and, equally,
//	 I placed an -> arro (thats a minus and a greater than sign) in the border
//	 for where the beginning of the game was and where the end of the game was.

	mydog.printDog();// COMMENT THIS IN WHEN YOU Write your Dog class!!



	for (int i = 0; i < 21; i++) {
		cout << " _";

	}
	cout << endl;

	for (int i = 0; i < size; i++) {

		if (i == startx) {
			cout << "->";
			board[endx][endy] = 'E';
		} else {
			cout << "| ";
		}

		for (int j = 0; j < size; j++) {
			char boardChar = board[i][j];
			if (boardChar == ' ') {
				cout << " ";

			}

			else {

				cout << board[i][j];

			}

			cout << " ";
		}

		if (i == endx) {
			cout << "->";
			cout << endl;
		} else {
			cout << "|" << endl;
		}
	}

	for (int i = 0; i < 21; i++) {
		cout << " ‾";

	}
	cout << endl;

}

void Board::boardConfig() {
	//(8 pts)
	//Instructions for writing boardConfig:
	/* this method and the moveDog method are probably the longest methods.
	 * This method first puts dummy values in every square (I used '+' - I just didn't want
	 * every square to have gibberish, so I chose a character I wasn't using for any other
	 * purpose and initialized every square to have that value).
	 * I then added my random horizontal and vertical walls.
	 *
	 * Here's how I did it the walls:
	 *
	 * I only placed walls in the odd numbered rows and columns (in other words, row one might
	 * have a row, but then row 2 would not, whereas row three could and row 4 could not.
	 * Same with columns (although you can have flexibility.
	 *
	 * I picked an odd row or column that did not already have a wall in it at all.
	 *
	 * I generated a total of 10 walls.

	 * For each wall, I picked randomly for vertical or horizontal (just rand() % 2 to get either
	 * 0 for vertical, 1 for horizontal.
	 *
	 * I set the easy version to have at most 9 squares in a row or column as a wall, the
	 * medium to have at most 13 squares as walls in a row or column, and the hard version to
	 * have at most 16 squares per row or column.(but you can play with this because sometimes
	 * the hard version was seriously hard!!!
	 *
	 * Let's say I randomly decided to place a wall in row 3.  I then randomly chose 9 squares in
	 * row 3 to be a wall (if it was the easy version, 13 if it was the medium, and 16 if it was
	 * the hard)
	 *
	 * So that's the walls.  Then I added the 'D' to the beginning square nad an 'E' to the end square.
	 *
	 *
	 */

// Easy
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j] = ' ';
		}

	}

	if (level == 'e') {

		for (int i = 0; i < 10; i++) {

			int tempz = (rand() % 20);

			int wall_dir = rand() % 2;

			if (wall_dir == 0) {
				bool is_wall = false;
				for (int tempm = 0; tempm < size; tempm++) {
					if (board[tempm][tempz] == '|'
							|| board[tempm][tempz] == '_') {
						is_wall = true;
					}

				}
				if (is_wall == false) {

					for (int k = 0; k < 9; k++) {
						int tempz = ((rand() % 10) * 2) + 1;
						int temp = rand() % 20;

						if (board[temp][tempz] == ' ') {
							board[temp][tempz] = '|';
						}

					}
				}

			}

			else if (wall_dir == 1) {
				bool is_wall = false;
				for (int tempm = 0; tempm < size; tempm++) {
					if (board[tempz][tempm] == '|'
							|| board[tempz][tempm] == '_') {
						is_wall = true;
					}
				}
				if (is_wall == false) {
					for (int k = 0; k < 9; k++) {
						int tempz = ((rand() % 10) * 2) + 1;
						int temp = rand() % 20;
						if (board[temp][tempz] == ' ') {
							board[temp][tempz] = '_';
						}

					}

				}
			}

		}

	}

//Medium
	if (level == 'm') {

		for (int i = 0; i < 10; i++) {

			int tempz = (rand() % 20);

			int wall_dir = rand() % 2;

			if (wall_dir == 0) {
				bool is_wall = false;
				for (int tempm = 0; tempm < size; tempm++) {
					if (board[tempm][tempz] == '|'
							|| board[tempm][tempz] == '_') {
						is_wall = true;
					}

				}
				if (is_wall == false) {

					for (int k = 0; k < 13; k++) {
						int tempz = ((rand() % 10) * 2) + 1;
						int temp = rand() % 20;

						if (board[temp][tempz] == ' ') {
							board[temp][tempz] = '|';
						}

					}
				}

			}

			else if (wall_dir == 1) {
				bool is_wall = false;
				for (int tempm = 0; tempm < size; tempm++) {
					if (board[tempz][tempm] == '|'
							|| board[tempz][tempm] == '_') {
						is_wall = true;
					}
				}
				if (is_wall == false) {
					for (int k = 0; k < 13; k++) {
						int tempz = ((rand() % 10) * 2) + 1;
						int temp = rand() % 20;
						if (board[temp][tempz] == ' ') {
							board[temp][tempz] = '_';
						}

					}

				}
			}

		}

	}
// Hard
	if (level == 'h') {

		for (int i = 0; i < 10; i++) {

			int tempz = (rand() % 20);

			int wall_dir = rand() % 2;

			if (wall_dir == 0) {
				bool is_wall = false;
				for (int tempm = 0; tempm < size; tempm++) {
					if (board[tempm][tempz] == '|'
							|| board[tempm][tempz] == '_') {
						is_wall = true;
					}

				}
				if (is_wall == false) {

					for (int k = 0; k < 16; k++) {
						int tempz = ((rand() % 10) * 2) + 1;
						int temp = rand() % 20;

						if (board[temp][tempz] == ' ') {
							board[temp][tempz] = '|';
						}

					}
				}

			}

			else if (wall_dir == 1) {
				bool is_wall = false;
				for (int tempm = 0; tempm < size; tempm++) {
					if (board[tempz][tempm] == '|'
							|| board[tempz][tempm] == '_') {
						is_wall = true;
					}
				}
				if (is_wall == false) {
					for (int k = 0; k < 16; k++) {
						int tempz = ((rand() % 10) * 2) + 1;
						int temp = rand() % 20;
						if (board[temp][tempz] == ' ') {
							board[temp][tempz] = '_';
						}

					}

				}
			}

		}

	}
	board[mydog.x][mydog.y] = 'D';
	board[endx][endy] = 'E';

}

void Board::addFood() {
	// (5 pts)
	/* Instructions for writing addFood:
	 /* this method randomly adds food around the board.  For easy, I added the field size
	 //	 * number of foods randomly around the board.  For medium, I added size-2 foods, and for
	 //	 * hard I added size-4 foods.  The amount of strength the dog gets when they eat (aka
	 //	 * move onto) the food is determined in the moveDog method.
	 //	 */

	int diff = 0;
	int numFood = 0;
	if (level == 'm') {
		diff = 2;

	} else if (level == 'h') {

		diff = 4;

	}

	while (numFood < size - diff) {
		int randx = (rand() % 20);
		int randy = (rand() % 20);

		if (board[randx][randy] != '|' && board[randx][randy] != '_'
				&& board[randx][randy] != 'D' && board[randx][randy] != 'E') {
			board[randx][randy] = 'F';
			numFood++;
		}

	}

}

void Board::addTraps() {
	// (5 pts)
	//Instructions for addTraps
	/* this method randomly adds traps around the board.  For easy I added size - 6 traps,
	 * for medium, I added size - 8 traps, and for hard I added size - 10 traps.  Note: Traps are
	 * only printed on the board when the game is in debug mode.  The amount of strength each trap
	 * saps from the dog is determined in the moveDog method when the dog moves on a Trap.
	 */
	int diff = 0;
	int numTrap = 0;
	if (level == 'e') {
		diff = 6;

	} else if (level == 'm') {

		diff = 8;

	} else if (level == 'h') {

		diff = 10;

	}

	while (numTrap < size - diff) {
		int randx = (rand() % 20);
		int randy = (rand() % 20);

		if (board[randx][randy] == ' ') {
			board[randx][randy] = 'T';
			numTrap++;
		}

	}

}

bool Board::moveDog(char c) {
	// (12 pts)
	//Instructions for moveDog
	/* This is a somewhat long method.
	 * First, it determines the new coordinats of the dog, based on teh direction in which the
	 * dog wants to move (based on what c holds - u is up, d is down, l is left, r is right).
	 *
	 * If the dog is at teh edge of the board, teh dog should not move
	 *
	 * If the dog moves over food, a random number between 2 and 17 is generated, and the
	 * dog's changeStrength method is used to increase the dog's strength by the random amount.
	 *
	 * If the dog moves over the end of the board, the dog's won method is called and false is
	 * returned from this method.
	 *
	 * If the dog moves over a Trap, a random number between 2 and 17 is generated and the dog's
	 * changeStrength method is called with that negative number.  (Note that the changeStrength
	 * method returns a boolean indicating whether the dog's strength has gone to 0 or less, and
	 * thus the dog has died and the game is over. That boolean value is returned from this method).
	 *
	 * If the dog moves over a wall, the method checks to see if the dog has enough strength to
	 * knock down the wall (I made it cost 6 strength points to knock down a wall).  If the dog
	 * has enough strength, the user is asked, "Do you want to knock down that wall?"  If the user
	 * responds "yes", then the wall is knocked down, the dog moves into that square, adn the dog's
	 * strength decreases by 6.  If the answer is "no", the dog loses 1 strength point, just because.
	 *
	 * If the dog moves into a blank square, the dog loses 2 strength points using the changeStrength
	 * method (which, again, will return false if the dog has lost all their strength and died.
	 *
	 * NOTE: I am not concerned with the precise rules here.  If you want to change the range of
	 * random numbers for food, if you are worried about whether you still lose 2 strength points for
	 * moving even though you gained points for moving over food - I'm leaving all that to your preference.
	 * I am concerned that you are using classes, objects, and object methods and accessing object
	 * fields correctly!
	 *
	 */

	int tempX = mydog.x;
	int tempY = mydog.y;
	int strength = rand() % 16 + 2;

	if (c == 'u') {
		tempX--;
	} else if (c == 'd') {
		tempX++;
	} else if (c == 'l') {
		tempY--;
	} else if (c == 'r') {
		tempY++;
	}

	if (tempX < 0 || tempY < 0 || tempX > 19 || tempY > 19) {
		return true;
	}

	char board_pos = board[tempX][tempY];

	if (board_pos == 'T') {
		board[mydog.x][mydog.y] = ' ';
		board[tempX][tempY] = 'D';
		mydog.x = tempX;
		mydog.y = tempY;
		cout << mydog.name << " stepped into a trap! " << endl;
		return (mydog.changeStrength(-strength));

	}

	else if (board_pos == 'F') {
		board[mydog.x][mydog.y] = ' ';
		board[tempX][tempY] = 'D';
		mydog.x = tempX;
		mydog.y = tempY;
		cout << mydog.name << " eats food. He thinks it's delicious! " << endl;
		return (mydog.changeStrength(strength));

	}

	else if (board_pos == ' ') {
		board[mydog.x][mydog.y] = ' ';
		board[tempX][tempY] = 'D';
		mydog.x = tempX;
		mydog.y = tempY;
		return (mydog.changeStrength(-2));
	} else if (board_pos == 'E') {
		board[mydog.x][mydog.y] = ' ';
		board[tempX][tempY] = 'D';
		mydog.x = tempX;
		mydog.y = tempY;
		mydog.won();
		return false;
	}

	else {
		string answer;
		bool input_yes = true;
		while (input_yes) {
			cout
					<< "Do you want to knock down a wall? It will cost you 6 strength points!"
					<< endl;
			cin >> answer;
			if (answer == "y" || answer == "yes" || answer == "Yes"
					|| answer == "YES" || answer == "Y") {
				board[mydog.x][mydog.y] = ' ';
				board[tempX][tempY] = 'D';
				mydog.x = tempX;
				mydog.y = tempY;
				return (mydog.changeStrength(-6));
			} else if (answer == "n" || answer == "no" || answer == "No"
					|| answer == "NO" || answer == "N") {
				input_yes = false;
			}
		}
		return (mydog.changeStrength(-1));

	}

}

void Board::playGame() {
	bool play = true;
	while (play) {
		cout << "Move (u, d, l, r) " << endl;
		char c;
		cin >> c;
		play = moveDog(c); // issue
		printBoard(); // issue
	}

}

