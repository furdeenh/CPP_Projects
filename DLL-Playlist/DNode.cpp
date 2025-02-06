/*
 * DNode.cpp
 *
 *  Created on: Mar 10, 2023
 *      Author: Furdeen Hasan and Elizabeth Kalfas
 */


#include "DLL.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;


DNode::DNode() {
	song = new Song();
	prev = NULL;
	next = NULL;
}

DNode::DNode(string s, string a, int lenmin, int lensec) {
	song= new Song(s,a,lenmin,lensec);
	prev = NULL;
	next = NULL;
}


