#pragma once
class Movement
{
public:
	static void generateWhiteOccupiedSpaces();
	static void generateBlackOccupiedSpaces();

private:
	static std::bitset<64> whiteOccupiedSpaces;
	static std::bitset<64> blackOccupiedSpaces;
	std::bitset<64> whiteLegalMoves;
	std::bitset<64> blackLegalMoves;
	std::list<int> rightEdge;
	std::list<int> leftEdge;

};

