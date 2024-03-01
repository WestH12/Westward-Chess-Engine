#include "Board.h"
#include <iostream>
#include <bitset>
#include <cassert>
#include <list>
#include <vector>

std::bitset<64> whitePawns{ 
							"00000000"
							"11111111"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000" }; 
std::bitset<64> whiteRooks{ 
							"10000001"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000" };
std::bitset<64> whiteKnights{ 
							"01000010"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000" };
std::bitset<64> whiteBishops{
							"00100100"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000" };
std::bitset<64> whiteQueen{
							"00001000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000" };
std::bitset<64> whiteKing{
							"00010000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000" };
std::bitset<64> blackPawns{ 
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"11111111"
							"00000000" };
std::bitset<64> blackRooks{ 
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"10000001" };
std::bitset<64> blackKnights{
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"01000010" };
std::bitset<64> blackBishops{
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00100100" };
std::bitset<64> blackQueen{
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00001000" };
std::bitset<64> blackKing{
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00010000" };
std::vector<char> board;

std::bitset<64> whiteOccupiedSpaces;
std::bitset<64> blackOccupiedSpaces;
std::bitset<64> legalMoves;

std::list <int> rightEdge{ 7, 15, 23, 31, 39, 47, 55, 63 };
std::list <int> leftEdge{ 0, 8, 16, 24, 32, 40, 48, 56 };
std::list<int> topEdge{ 56, 57, 58, 59, 60, 61, 62, 63 };
std::list<int> bottomEdge{0, 1, 2, 3, 4, 5, 6, 7};

bool playerColor = true; //Will treat true as white and false as black

//board.assign(64, '-');

void initBoard() {
	board.assign(64, '-');	
}

void placePieces() {
	int i;
	for (i = 0; i < whitePawns.size(); ++i) {
		if (whitePawns[i] == 1) {
			board.at(i) = 'P';
		}
	}
	for (i = 0; i < whiteRooks.size(); ++i) {
		if (whiteRooks[i] == 1) {
			board.at(i) = 'R';
		}
	}
	for (i = 0; i < whiteKnights.size(); ++i) {
		if (whiteKnights[i] == 1) {
			board.at(i) = 'N';
		}
	}
	for (i = 0; i < whiteBishops.size(); ++i) {
		if (whiteBishops[i] == 1) {
			board.at(i) = 'B';
		}
	}
	for (i = 0; i < whiteQueen.size(); ++i) {
		if (whiteQueen[i] == 1) {
			board.at(i) = 'Q';
		}
	}
	for (i = 0; i < whiteKing.size(); ++i) {
		if (whiteKing[i] == 1) {
			board.at(i) = 'K';
		}
	}
	for (i = 0; i < blackPawns.size(); ++i) {
		if (blackPawns[i] == 1) {
			board.at(i) = 'p';
		}
	}
	for (i = 0; i < blackRooks.size(); ++i) {
		if (blackRooks[i] == 1) {
			board.at(i) = 'r';
		}
	}for (i = 0; i < blackKnights.size(); ++i) {
		if (blackKnights[i] == 1) {
			board.at(i) = 'n';
		}
	}
	for (i = 0; i < blackBishops.size(); ++i) {
		if (blackBishops[i] == 1) {
			board.at(i) = 'b';
		}
	}
	for (i = 0; i < blackQueen.size(); ++i) {
		if (blackQueen[i] == 1) {
			board.at(i) = 'q';
		}
	}
	for (i = 0; i < blackKing.size(); ++i) {
		if (blackKing[i] == 1) {
			board.at(i) = 'k';
		}
	}
}

static void generateWhiteOccupiedSpaces() {
	whiteOccupiedSpaces = whitePawns | whiteRooks | whiteKnights | whiteBishops | whiteQueen | whiteKing;
}

static void generateBlackOccupiedSpaces() {
	blackOccupiedSpaces = blackPawns | blackRooks | blackKnights | blackBishops | blackQueen | blackKing;
}

static std::bitset<64> generateDiagonalMoves(int origSpace) {
	std::bitset<64> moves;
	std::vector<int> incrementNum{-9,9, 7, -7};
	
	
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
	std::vector<int> incrementNumber{8, -8};
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
	std::vector<int> incrementNumber{1, -1};
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
				std::cout << "Hi white" << std::endl;
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
	std::vector<int> incrementNumber{15, 17, -15, -17, 10, -6, 6, -10};
	std::vector<int> leftKnightPadding{56,57,48,49,40,41,32,33,24,25,16,17,8,9,0,1};
	std::vector<int> rightKnightPadding{62, 63, 54, 55, 46, 47, 38, 39, 30, 31, 22, 23, 14, 15, 6, 7};
	std::vector<int> topKnightPadding{48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63};
	std::vector<int> bottomKnightPadding{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	int currentSpace;
	int i;

	currentSpace = origSpace;
	
	if (std::find(leftKnightPadding.begin(), leftKnightPadding.end(), origSpace) == leftKnightPadding.end()) {
		for (i = 6; i < incrementNumber.size(); ++i) {
			currentSpace = origSpace;
			currentSpace = currentSpace + incrementNumber[i];
			if (blackOccupiedSpaces[currentSpace] == 1) {
				moves[currentSpace] = 1;
				break;
			}
			if (whiteOccupiedSpaces[currentSpace] == 1) {
				break;
			}
			moves[currentSpace] = 1;
		}
	}
	if (std::find(rightKnightPadding.begin(), rightKnightPadding.end(), origSpace) == rightKnightPadding.end()) {
		for (i = 4; i < 6; ++i) {
			currentSpace = origSpace;
			currentSpace = currentSpace + incrementNumber[i];
			if (blackOccupiedSpaces[currentSpace] == 1) {
				moves[currentSpace] = 1;
				break;
			}
			if (whiteOccupiedSpaces[currentSpace] == 1) {
				break;
			}
			moves[currentSpace] = 1;
		}
	}
	if (std::find(topKnightPadding.begin(), topKnightPadding.end(), origSpace) == topKnightPadding.end()) {
		for (i = 6; i < incrementNumber.size(); ++i) {
			currentSpace = origSpace;
			currentSpace = currentSpace + incrementNumber[i];
			if (blackOccupiedSpaces[currentSpace] == 1) {
				moves[currentSpace] = 1;
				break;
			}
			if (whiteOccupiedSpaces[currentSpace] == 1) {
				break;
			}
			moves[currentSpace] = 1;
		}
	}
	return moves;
}

std::bitset<64> generateLegalMoves(int origSpace) {
	std::bitset<64> temp;
	
	temp = generateDiagonalMoves(origSpace) | generateVerticalMoves(origSpace) | generateHorizontalMoves(origSpace);
	return temp;
}

void printMoveDirections() {
	std::cout << "Please enter your movement directions: (Ie \"c4 to c5\") " << std::endl;
}

int aNotationToBit(std::string aNotation) {
	int bitNum = int(tolower(aNotation[0])) - 97;
	bitNum = bitNum + ( (aNotation[1] - 49) * 8);
	return bitNum;
}

void printBoard() {
	int i;
	for (i = 0; i < board.size(); ++i) {
		std::cout << board.at(i);
		if ((i + 1) % 8 == 0) {
			std::cout << std::endl;
		} 
	}
}


int main() {

	initBoard();
	placePieces();
	printBoard();
	generateWhiteOccupiedSpaces();
	generateBlackOccupiedSpaces();

	
	std::bitset<64> moves = generateKnightMoves(21);

	moves[21] = 1;
	

	std::cout << moves << std::endl;



	int i;
	for (i = 0; i < moves.size(); ++i) {
		std::cout << moves[i];
		if ((i + 1) % 8 == 0) {
			std::cout << std::endl;
		}
	}

	return 0;
}