/*
 * Dog.cpp
 *
 *  Created on: Feb 23, 2023
 *      Author: Furdeen Hasan and Lizzy Kalfas
 */

#include "Board.hpp"
#include "Dog.hpp"
#include <iostream>
using namespace std;

Dog::Dog(string n) {
	n = "Spot";
	name = n;
	strength = 50;
	x = 0;
	y = 0;
}

/* constructor, I made the default be fluffy, but you can make it anything you like!!
 * I set the strength to be 50 (again, I just picked 50), and I made the original
 * coordinates be 0 and 0 because...
 */

Dog::Dog() {
	name = "Spot";
	strength = 50;
	x = 0;
	y = 0;
}

bool Dog::changeStrength(int amt) {
	/*changeStrength modifies the strength property by whatever amt is (basically adding here)
	 * It then calls printDog method to print out current information about the dog.
	 * It also checks to make sure that the dog object's strength is >0.
	 * If the dog object's strength is 0 or less, it calls the die method.
	 * It returns true if the strength is still >0 and false otherwise.
	 */

	strength += amt;
	printDog();
	if (strength <= 0) {
		die();
		return false;
	} else {
		return true;
	}
//

}
void Dog::die() {
	/* This method just prints out a sad pathetic death of a dog message, letting everyone
	 * know of the demise of the dog object.  My message has ACK!!! and judgmental statements
	 * about how the user is a cruel, heartless person for letting a puppy dog die, but
	 * yours can be whatever you like.
	 */

	cout << "Game Over. " << name << " Play Again?" << endl;

}

void Dog::printDog() {
	/* this method just prints out the basic information about the dog - its
	 *name and its current strength.
	 */
	cout << "Dog: " << name << endl;
	cout << "Strength: " << strength << endl;

}

void Dog::won() {
	cout << "Congratulations, you got " << name << " out!" << endl;

}

void Dog::reset() {
	/* this method just resets the strength (for me it was 50) and the x and y to 0 and 0.
	 *
	 */
	strength = 50;
	x = 0;
	y = 0;
}

