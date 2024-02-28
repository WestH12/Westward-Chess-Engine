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

void generateLegalMoves() {
	
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

	//std::bitset<64> whitePawns{"0000000011111111000000000000000000000000000000000000000000000000"};

	initBoard();
	placePieces();
	printBoard();
	generateBlackOccupiedSpaces();

	return 0;
}