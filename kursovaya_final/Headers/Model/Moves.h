#pragma once

#include "Data.h"

#include <iostream>
#include <vector>
#include <SFML/System/Vector2.hpp>

extern bool whiteKingLongCastleAvailable;
extern bool whiteKingShortCastleAvailable;

extern bool blackKingLongCastleAvailable;
extern bool blackKingShortCastleAvailable;

void makeMove(Square** leftField, Square** rightField, bool isLeft, Square fromSquare, Square toSquare);
bool willBeCheck(Square** field, Square fromSquare, Square toSquare);

void makeRookCastleMove(Square** leftField, Square** rightField, bool isLeft, Square kingFromSquare, Square kingToSquare);
void updateCastlePossibility(Square fromSquare);

std::vector<sf::Vector2<short>> findCurrentPossibleMoves(Square** field, Square square);

std::vector<sf::Vector2<short>> findDiagonalMoves(Square** field, Square square);
std::vector<sf::Vector2<short>> findHorizontalMoves(Square** field, Square square);
std::vector<sf::Vector2<short>> findVerticalMoves(Square** field, Square square);
std::vector<sf::Vector2<short>> findKingMoves(Square** field, Square square);
std::vector<sf::Vector2<short>> findKnightMoves(Square** field, Square square);
std::vector<sf::Vector2<short>> findPawnMoves(Square** field, Square square);

