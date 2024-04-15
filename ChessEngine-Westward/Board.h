#pragma once
#include <string>
#include <bitset>
class Board
{
public:
	static std::bitset<64> getWhitePawns();
	static void movePawn(int origSpace, int newSpace);
	static void removePawn(int removalSpace);
	static std::bitset<64> getWhiteRooks();
	static void moveRook(int origSpace, int newSpace);
	static void initBoard();
	static void placePieces();

private:
	static std::bitset<64> whitePawns;
	static std::bitset<64> whiteRooks;
	static std::bitset<64> whiteKnights;
	static std::bitset<64> whiteBishops;
	static std::bitset<64> whiteQueen;
	static std::bitset<64> whiteKing;
};

