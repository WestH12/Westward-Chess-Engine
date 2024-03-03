#pragma once
class Movement
{
public:
	static void generateWhiteOccupiedSpaces();

private:
	std::bitset<64> whiteLegalMoves;
	std::bitset<64> blackLegalMoves;
	std::list<int> rightEdge;
	std::list<int> leftEdge;

};

