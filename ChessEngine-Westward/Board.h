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
	

private:
	static std::bitset<64> whitePawns;
};

