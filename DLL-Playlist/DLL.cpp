/*
 * DLL.cpp
 *
 *  Created on: Mar 10, 2023
 *      Author: Furdeen Hasan and Elizabeth Kalfas
 */




#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

//Check Playlist.cpp for instructions of what to write here and how to test it

DLL::DLL() {
	last = NULL;
	first = NULL;
	numSongs = 0;
}
DLL::DLL(string t, string l, int m, int s) {
	DNode *n = new DNode(t, l, m, s);
	first = n;
	last = n;
	numSongs = 1;
}
void DLL::push(string n, string a, int m, int s) {
	DNode *new_node = new DNode(n, a, m, s);

	if (first == NULL) {
		first = new_node;
		last = new_node;
		numSongs += 1;
		return;

	}

	else {
		last->next = new_node;
		new_node->prev = last;
		last = new_node;
		numSongs += 1;

	}


}
Song* DLL::pop() {

	Song *lastSong;

	if (numSongs > 1) {
		DNode *tmp = last;
		lastSong = last->song;
		delete tmp;
		last->next = NULL;
		numSongs--;
	}

	else if (numSongs == 1) {
		numSongs = 0;
		lastSong = first->song;
		delete first;
		first = NULL;
		last = NULL;

	}
	return lastSong;


}

void DLL::printList() {
	DNode *current = first;
	for (int i = 0; i < numSongs; i++) {
		current->song->printSong();
		current = current->next;

	}

}

void DLL::moveUp(string s) {
	DNode *current = first;

		while(current->song->title != s){
			current = current->next;
		}

		if(current->prev == NULL){ //first case
			last->next = current;
			current->next->prev = NULL;
			first = current->next;
			current->prev = last;
			last = current;
			current->next = NULL;
			last->next = NULL;
		}else if(current->prev->prev == NULL){ //second case
			current->next->prev = current->prev;
			current->prev->next = current->next;
			current->next = current->prev;
			current->prev->prev = current;
			current->prev = NULL;
			first = current;
		}else if(current->next == NULL){ //last case
			current->prev->prev->next = current;
			current->prev->next = NULL;
			current->next = current->prev;
			DNode *temp;
			temp = current->prev->prev;
			current->prev->prev = current;
			last = current->prev;
			current->prev = temp;
		}else{ //middle case
			current->prev->prev->next = current;
			current->next->prev = current->prev;
			current->prev->next = current->next;
			current->next = current->prev;
			DNode *temp;
			temp = current->prev->prev;
			current->prev->prev = current;
			current->prev = temp;
		}
	}

	/*
	 * moves song with title s down one in the playlist.
	 */
void DLL::moveDown(string s){
		DNode *current = first;
		while(current->song->title != s){
			current = current->next;
		}

		//last
		if(current->next == NULL){
			current->prev->next = NULL;
			last = current->prev;
			first->prev = current;
			current->next = first;
			current->prev = NULL;
			first = current;
		}else if(current->prev == NULL){//first
			current->next->next->prev = current;
			current->next->prev = NULL;
			current->prev = current->next;

			DNode *temp = current->next->next;
			current->next->next = current;
			current->next = temp;
			first = current->prev;
		}else if(current->next->next == NULL){//second to last

	//		point to current to prev to next = current to the next
	//		current to next to prev = current to prev
	//		current to prev = current to next
	//		current to next to next = current
	//		current to next = null
	//		last = current

			current->prev->next = current->next;
			current->next->prev = current->prev;
			current->prev = current->next;
			current->next->next = current;
			current->next = NULL;
			last = current;
	//		current = last;
		}else{//middle
			current->next->next->prev = current;
			current->prev->next = current->next;
			current->next->prev = current->prev;
			current->prev = current->next;

			DNode *temp;
			temp = current->next->next;
			current->next->next = current;
			current->next = temp;
		}
}



void DLL::listDuration(int *tm, int *ts) {
	DNode *tmp = first;
	for (int i = 0; i < numSongs; i++) {
		*tm = *tm + tmp->song->min;
		*ts = *ts + tmp->song->sec;
		tmp = tmp->next;

	}

}




void DLL::makeRandom() {
	if (numSongs == 0 || numSongs == 1) {
		return;
	}

	DLL *playlist_2 = new DLL();
	DNode *tmp = first;
	int i = 0;
	int k = rand() % numSongs;

	for (; i < k; i++) {
		tmp = tmp->next;
	}

	if (i == 0) {
		first = tmp->next;
		tmp->next->prev = NULL;
		tmp->prev = NULL;
		tmp->next = NULL;
		playlist_2->first = tmp;
		playlist_2->last = tmp;
		playlist_2->numSongs += 1;
	} else if (i == numSongs - 1) {
		last = tmp->prev;
		tmp->prev = NULL;
		tmp->next = NULL;
		playlist_2->first = tmp;
		playlist_2->last = tmp;
		last->next = NULL;
		playlist_2->numSongs += 1;
	} else {
		DNode *lastN = tmp->prev;
		DNode *nextN = tmp->next;
		lastN->next = nextN;
		nextN->prev = lastN;
		tmp->prev = NULL;
		tmp->next = NULL;
		playlist_2->first = tmp;
		playlist_2->last = tmp;
		playlist_2->numSongs += 1;
	}

	numSongs -= 1;

	if (numSongs > 2) {
		while (numSongs > 2) {
			tmp = first;
			i = 0;
			k = rand() % numSongs;

			for (; i < k; i++) {
				tmp = tmp->next;
			}

			if (i == 0) {
				first = tmp->next;
				tmp->next->prev = NULL;
				tmp->next = NULL;
				tmp->prev = playlist_2->last;
				playlist_2->last->next = tmp;
				playlist_2->last = playlist_2->last->next;
				playlist_2->numSongs += 1;
			} else if (i == numSongs - 1) {
				last = tmp->prev;
				tmp->next = NULL;
				tmp->prev = playlist_2->last;
				playlist_2->last->next = tmp;
				playlist_2->last = playlist_2->last->next;
				last->next = NULL;
				playlist_2->numSongs += 1;
			} else {
				DNode *lastN = tmp->prev;
				DNode *nextN = tmp->next;
				lastN->next = nextN;
				nextN->prev = lastN;

				tmp->next = NULL;
				tmp->prev = playlist_2->last;
				playlist_2->last->next = tmp;
				playlist_2->last = playlist_2->last->next;
				playlist_2->numSongs += 1;

			}
			numSongs -= 1;
		}
	}

	if (rand() % 2 > 0) {
		playlist_2->last->next = last;
		last->prev = playlist_2->last;
		last->next = NULL;
		playlist_2->last = playlist_2->last->next;
		playlist_2->numSongs += 1;

		playlist_2->last->next = first;
		first->prev = playlist_2->last;
		first->next = NULL;
		playlist_2->last = playlist_2->last->next;
		playlist_2->numSongs += 1;
	} else {
		playlist_2->last->next = first;
		first->prev = playlist_2->last;
		first->next = NULL;
		playlist_2->last = playlist_2->last->next;
		playlist_2->numSongs += 1;
		playlist_2->last->next = last;

		last->prev = playlist_2->last;
		last->next = NULL;
		playlist_2->last = playlist_2->last->next;
		playlist_2->numSongs += 1;
	}

	first = playlist_2->first;
	last = playlist_2->last;
	numSongs = playlist_2->numSongs;

}
int DLL::remove(string s) {
// note that the int returned is the index - this is standard for a remove, but we won't be using it.

	DNode *tmp;
	for (tmp = first; tmp != NULL; tmp = tmp->next) {
		if (tmp->song->title == s) {
			if (tmp->prev == NULL) {
				first = tmp->next;
			} else if (tmp->next == NULL) {
				tmp->prev->next = NULL;
				last = tmp ->prev;
			}

			else { /* Remove from middle */
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
			}
			delete tmp;


		}

	}

return 0;


}

DLL::~DLL() {
	DNode *current = first;
			DNode *next;

			while(current != NULL){
				next = current->next;
				delete current;
				current = next;
			}
			last = NULL;
			first = NULL;
			numSongs = 0;
}
