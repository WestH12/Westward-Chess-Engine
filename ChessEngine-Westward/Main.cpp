#include "Board.h"
#include "Movement.h"
#include <iostream>
#include <string>
#include <sstream>
#include <bitset>
#include <cassert>
#include <list>
#include <vector>


bool playerColor = true; //Will treat true as white and false as black


int main() {

	initBoard();
	placePieces();
	printBoard();
	generateWhiteOccupiedSpaces();
	generateBlackOccupiedSpaces();

	movePieces();

	return 0;
}