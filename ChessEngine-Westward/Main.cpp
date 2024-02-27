#include "Board.h"
#include <iostream>
#include <bitset>
#include <cassert>
#include <list>
#include <vector>

std::bitset<64> whitePawns{ "0000000011111111000000000000000000000000000000000000000000000000" }; 
std::bitset<64> whiteRooks{ "10000001"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000" };
std::bitset<64> blackPawns{ "00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"11111111"
							"00000000" };
std::bitset<64> blackRooks{ "00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"00000000"
							"10000001" };
std::vector<char> board;
//board.assign(64, '-');

void initBoard() {
	board.assign(64, '-');
}

void printPawns() {
	int i;
	for (i = 0; i < whitePawns.size(); ++i) {
		if (whitePawns[i] == 1) {
			board.at(i) = 'P';
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
	}
	for (i = 0; i < whiteRooks.size(); ++i) {
		if (whiteRooks[i] == 1) {
			board.at(i) = 'R';
		}
	}
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
	printPawns();
	printBoard();

	//std::cout << whitePawns;

	return 0;
}