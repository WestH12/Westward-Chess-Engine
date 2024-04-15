#include "Movement.h"
#include "Board.h"
#include "Board.cpp"
#include <iostream>
#include <string>
#include <sstream>
#include <bitset>
#include <cassert>
#include <list>
#include <vector>


std::bitset<64> whiteLegalMoves; //Will hold all legal moves for white
std::bitset<64> blackLegalMoves; //Will hold all legal moves for black


std::list<int> rightEdge{ 7, 15, 23, 31, 39, 47, 55, 63 };
std::list<int> leftEdge{ 0, 8, 16, 24, 32, 40, 48, 56 };

//Might not need top or bottom edge lists
std::list<int> topEdge{ 56, 57, 58, 59, 60, 61, 62, 63 };
std::list<int> bottomEdge{ 0, 1, 2, 3, 4, 5, 6, 7 };

 void Movement::generateWhiteOccupiedSpaces() {
	whiteOccupiedSpaces = Board::getWhitePawns() | Board::getWhiteRooks() | Board::getWhiteKnights() | Board::getWhiteBishops() | Board:getWhiteQueen() | Board::getWhiteKing();
}

void Movement::generateBlackOccupiedSpaces() {
	blackOccupiedSpaces = blackPawns | blackRooks | blackKnights | blackBishops | blackQueen | blackKing;
}

static std::bitset<64> generateDiagonalMoves(int origSpace) {
	std::bitset<64> moves;
	std::vector<int> incrementNum{ -9,9, 7, -7 };


	for (int i = 0; i < incrementNum.size(); ++i) {
		int currentSpace = origSpace;

		currentSpace = currentSpace + incrementNum[i];

		while (true) {
			if ((currentSpace <= 0) || (currentSpace >= 63)) {
				break;
			}
			if (blackOccupiedSpaces[currentSpace] == 1) {
				moves[currentSpace] = 1;
				break;
			}
			if (whiteOccupiedSpaces[currentSpace] == 1) {
				break;
			}
			if (std::find(leftEdge.begin(), leftEdge.end(), currentSpace) != leftEdge.end()) {
				moves[currentSpace] = 1;
				break;
			}
			if (std::find(rightEdge.begin(), rightEdge.end(), currentSpace) != rightEdge.end()) {
				moves[currentSpace] = 1;
				break;
			}
			if (std::find(topEdge.begin(), topEdge.end(), currentSpace) != topEdge.end()) {
				moves[currentSpace] = 1;
				break;
			}
			moves[currentSpace] = 1;
			currentSpace = currentSpace + incrementNum[i];
		}
	}
	return moves;
}

static std::bitset<64> generateVerticalMoves(int origSpace) {
	std::bitset<64> moves;
	std::vector<int> incrementNumber{ 8, -8 };
	int currentSpace;

	for (int i = 0; i < incrementNumber.size(); ++i) {
		currentSpace = origSpace;

		currentSpace = currentSpace + incrementNumber[i];
		while (true) {
			if ((currentSpace <= 0) || (currentSpace >= 63)) {
				break;
			}
			if (blackOccupiedSpaces[currentSpace] == 1) {
				moves[currentSpace] = 1;
				break;
			}
			if (whiteOccupiedSpaces[currentSpace] == 1) {
				break;
			}
			if (std::find(topEdge.begin(), topEdge.end(), currentSpace) != topEdge.end()) {
				moves[currentSpace] = 1;
				break;
			}
			if (std::find(bottomEdge.begin(), bottomEdge.end(), currentSpace) != bottomEdge.end()) {
				moves[currentSpace] = 1;
				break;
			}
			moves[currentSpace] = 1;
			currentSpace = currentSpace + incrementNumber[i];
		}
	}
	return moves;
}

std::bitset<64> generateHorizontalMoves(int origSpace) {
	std::bitset<64> moves;
	std::vector<int> incrementNumber{ 1, -1 };
	int currentSpace;

	for (int i = 0; i < incrementNumber.size(); ++i) {
		currentSpace = origSpace;

		currentSpace = currentSpace + incrementNumber[i];
		while (true) {
			if ((currentSpace <= 0) || (currentSpace >= 63)) {
				break;
			}
			if (blackOccupiedSpaces[currentSpace] == 1) {
				moves[currentSpace] = 1;
				break;
			}
			if (whiteOccupiedSpaces[currentSpace] == 1) {
				break;
			}
			if (std::find(leftEdge.begin(), leftEdge.end(), currentSpace) != leftEdge.end()) {
				moves[currentSpace] = 1;
				break;
			}
			if (std::find(rightEdge.begin(), rightEdge.end(), currentSpace) != rightEdge.end()) {
				moves[currentSpace] = 1;
				break;
			}
			moves[currentSpace] = 1;
			currentSpace = currentSpace + incrementNumber[i];
		}
	}
	return moves;
}

std::bitset<64> generateKnightMoves(int origSpace) {
	std::bitset<64> moves;
	std::vector<int> incrementNumber{ 15, 17, -15, -17, 10, -6, 6, -10 };
	std::vector<int> leftKnightPadding{ 57, 49, 41, 33, 25, 17, 9, 1 };
	std::vector<int> rightKnightPadding{ 62, 54, 46, 38, 30, 22, 14, 6 };
	int currentSpace;
	int i;

	//Checking to see if knight will go off left side of board if it moves two spaces to the left
	if (std::find(leftKnightPadding.begin(), leftKnightPadding.end(), origSpace) != leftKnightPadding.end()) {
		for (i = 0; i < 6; ++i) {
			currentSpace = origSpace;
			currentSpace = currentSpace + incrementNumber[i];
			if ((currentSpace <= -1) || (currentSpace >= 64)) {
				continue;
			}
			else if (blackOccupiedSpaces[currentSpace] == 1) {
				moves[currentSpace] = 1;
				continue;
			}
			else if (whiteOccupiedSpaces[currentSpace] == 1) {
				continue;
			}
			moves[currentSpace] = 1;
		}
	}
	else if (std::find(rightKnightPadding.begin(), rightKnightPadding.end(), origSpace) != rightKnightPadding.end()) {
		//Checking to see if knight will go off left side of board if it moves two spaces to the right
		for (i = 0; i < incrementNumber.size(); ++i) {
			if ((i == 4) || (i == 5)) {
				continue;
			}
			currentSpace = origSpace;
			currentSpace = currentSpace + incrementNumber[i];
			if ((currentSpace <= -1) || (currentSpace >= 64)) {
				continue;
			}
			else if (blackOccupiedSpaces[currentSpace] == 1) {
				moves[currentSpace] = 1;
				continue;
			}
			else if (whiteOccupiedSpaces[currentSpace] == 1) {
				continue;
			}
			moves[currentSpace] = 1;
		}
	}
	else if (std::find(leftEdge.begin(), leftEdge.end(), origSpace) != leftEdge.end()) {//Checking to see if knight will go off left side of board when going up two and left one
		for (i = 1; i < 6; ++i) {
			if ((i == 3)) {
				continue;
			}
			currentSpace = origSpace;
			currentSpace = currentSpace + incrementNumber[i];
			if ((currentSpace <= -1) || (currentSpace >= 64)) {
				continue;
			}
			else if (blackOccupiedSpaces[currentSpace] == 1) {
				moves[currentSpace] = 1;
				continue;
			}
			else if (whiteOccupiedSpaces[currentSpace] == 1) {
				continue;
			}
			moves[currentSpace] = 1;
		}
	}
	else if (std::find(rightEdge.begin(), rightEdge.end(), origSpace) != rightEdge.end()) {//Checking to see if knight will go off left side of board when going up two and right one
		for (i = 0; i < incrementNumber.size(); ++i) {
			if ((i == 1) || (i == 2) || (i == 4) || (i == 5)) {
				continue;
			}
			currentSpace = origSpace;
			currentSpace = currentSpace + incrementNumber[i];
			if ((currentSpace <= -1) || (currentSpace >= 64)) {
				continue;
			}
			else if (blackOccupiedSpaces[currentSpace] == 1) {
				moves[currentSpace] = 1;
				continue;
			}
			else if (whiteOccupiedSpaces[currentSpace] == 1) {
				continue;
			}
			moves[currentSpace] = 1;
		}
	}
	else {
		//If knight is not near any of the border of the board then this else statement runs for all possible movement directions for the knight
		for (i = 0; i < incrementNumber.size(); ++i) {
			currentSpace = origSpace;
			currentSpace = currentSpace + incrementNumber[i];
			if ((currentSpace <= -1) || (currentSpace >= 64)) {
				continue;
			}
			else if (whiteOccupiedSpaces[currentSpace] == 1) {
				continue;
			}
			else if (blackOccupiedSpaces[currentSpace] == 1) {
				moves[currentSpace] = 1;
				continue;
			}
			moves[currentSpace] = 1;
		}
	}
	return moves;
}

std::bitset<64> generatePawnMoves(int origSpace) {
	std::bitset<64> moves;
	std::vector<int> incrementNumber{ 7, 9, -8, -16 };
	std::vector<int> whiteStartingLine{ 48, 49, 50, 51, 52, 53, 54, 55 };
	bool startingSpace = false;
	int currentSpace;

	if (std::find(whiteStartingLine.begin(), whiteStartingLine.end(), origSpace) != whiteStartingLine.end()) { //Checks to see if pawn is on starting space and if so then checks for double movement out
		for (int i = 2; i < incrementNumber.size(); ++i) {
			currentSpace = origSpace;
			currentSpace = currentSpace + incrementNumber[i];
			if ((currentSpace <= -1) || (currentSpace >= 64)) {

			}
			else if (blackOccupiedSpaces[currentSpace] == 1) {
				moves[currentSpace] = 1;
			}
			else if (whiteOccupiedSpaces[currentSpace] == 1) {
			}
			moves[currentSpace] = 1;
		}
	}
	else {
		currentSpace = origSpace + incrementNumber[2];
		if ((currentSpace <= -1) || (currentSpace >= 64)) {
		}
		else if (blackOccupiedSpaces[currentSpace] == 1) {
		}
		else if (whiteOccupiedSpaces[currentSpace] == 1) {
		}
		moves[currentSpace] = 1;
	}

	if (std::find(leftEdge.begin(), leftEdge.end(), origSpace) != leftEdge.end()) {
		//Prevents checking left diagonal pawn attack
		currentSpace = origSpace + incrementNumber[1];
		if ((currentSpace <= -1) || (currentSpace >= 64)) { //Does not add move if space is off the top or bottom of the board
		}
		else if (blackOccupiedSpaces[currentSpace] == 1) { //Can only move diagonally if their is an opponent piece there
			moves[currentSpace] = 1;
		}
		else if (whiteOccupiedSpaces[currentSpace] == 1) { //Does not add move if space if occupied by same color piece
		}

	}
	else if (std::find(rightEdge.begin(), rightEdge.end(), origSpace) != rightEdge.end()) {
		//Prevents checking right diagonal pawn attack
		currentSpace = origSpace + incrementNumber[0];
		if ((currentSpace <= -1) || (currentSpace >= 64)) {
		}
		else if (blackOccupiedSpaces[currentSpace] == 1) {
			moves[currentSpace] = 1;
		}
		else if (whiteOccupiedSpaces[currentSpace] == 1) {
		}
	}
	else {
		//Since left and right diagonal are not going off the board, then we check both diagonal attack directions
		for (int i = 0; i < 2; ++i) {
			currentSpace = origSpace + incrementNumber[i];
			if ((currentSpace <= -1) || (currentSpace >= 64)) {
			}
			else if (blackOccupiedSpaces[currentSpace] == 1) {
				moves[currentSpace] = 1;
			}
			else if (whiteOccupiedSpaces[currentSpace] == 1) {
			}
		}
	}
	return moves;
}

std::bitset<64> generateKingMoves(int origSpace) {
	std::bitset<64> moves;
	int currentSpace;
	std::vector<int> incrementNumber{ -9, -1, 7, 8, -8, 9, 1, -7 };
	int i;

	if (std::find(leftEdge.begin(), leftEdge.end(), origSpace) != leftEdge.end()) {
		for (i = 3; i < incrementNumber.size(); ++i) {
			currentSpace = origSpace + incrementNumber[i];
			if ((currentSpace <= -1) || (currentSpace >= 64)) {
				continue;
			}
			else if (blackOccupiedSpaces[currentSpace] == 1) {
				moves[currentSpace] = 1;
			}
			else if (whiteOccupiedSpaces[currentSpace] == 1) {
				continue;
			}
			/*else if (isSpaceUnderAttack(currentSpace)) { #TO BE IMPLEMENTED
				continue;
			}*/
			moves[currentSpace] = 1;
		}
	}
	else if (std::find(rightEdge.begin(), rightEdge.end(), origSpace) != rightEdge.end()) {
		for (i = 0; i < 5; ++i) {
			currentSpace = origSpace + incrementNumber[i];
			if ((currentSpace <= -1) || (currentSpace >= 64)) {
				continue;
			}
			else if (blackOccupiedSpaces[currentSpace] == 1) {
				moves[currentSpace] = 1;
			}
			else if (whiteOccupiedSpaces[currentSpace] == 1) {
				continue;
			}
			/*else if (isSpaceUnderAttack(currentSpace)) { #TO BE IMPLEMENTED
				continue;
			}*/
			moves[currentSpace] = 1;
		}
	}
	else {
		for (i = 0; i < incrementNumber.size(); ++i) {
			currentSpace = origSpace + incrementNumber[i];
			if ((currentSpace <= -1) || (currentSpace >= 64)) {
				continue;
			}
			else if (blackOccupiedSpaces[currentSpace] == 1) {
				moves[currentSpace] = 1;
			}
			else if (whiteOccupiedSpaces[currentSpace] == 1) {
				continue;
			}
			/*else if (isSpaceUnderAttack(currentSpace)) { #TO BE IMPLEMENTED
				continue;
			}*/
			moves[currentSpace] = 1;
		}
	}
	return moves;
}

std::bitset<64> generateLegalMoves() {
	std::bitset<64> temp;
	for (int i = 0; i < 64; ++i) {
		if (whitePawns[i] == 1) {
			temp = temp | generatePawnMoves(i);
		}
		else if (whiteKnights[i] == 1) {
			temp = temp | generateKnightMoves(i);
		}
		else if (whiteBishops[i] == 1) {
			temp = temp | generateDiagonalMoves(i);
		}
		else if (whiteRooks[i] == 1) {
			temp = temp | generateHorizontalMoves(i) | generateVerticalMoves(i);
		}
		else if (whiteQueen[i] == 1) {
			temp = temp | generateHorizontalMoves(i) | generateVerticalMoves(i) | generateDiagonalMoves(i);
		}
		else if (whiteKing[i] == 1) {
			temp = temp | generateKingMoves(i);
		}
	}
	return temp;
}

void printMoveDirections() {
	std::cout << "Please enter your movement directions: (Ie \"c4 to c5\") " << std::endl;
}

void movePieces() {
	std::string inputLine;
	std::string startingSpace;
	std::string targetSpace;

	//printMoveDirections();
	std::getline(std::cin, inputLine);
	startingSpace = inputLine.substr(0, 2);
	targetSpace = inputLine.substr(6, 2);

	std::cout << startingSpace << " " << targetSpace;

}

int aNotationToBit(std::string aNotation) {
	int bitNum = int(tolower(aNotation[0])) - 97;
	bitNum = bitNum + ((aNotation[1] - 49) * 8);
	return bitNum;
}