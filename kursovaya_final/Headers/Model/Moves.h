#pragma once

#include "Data.h"

#include <iostream>
#include <vector>
#include <SFML/System/Vector2.hpp>

void makeMove(Square** leftField, Square** rightField, bool isLeft, Square fromSquare, Square toSquare);

std::vector<sf::Vector2<short>> findCurrentPossibleMoves(Square** field, Square square);

std::vector<sf::Vector2<short>> findDiagonalMoves(Square** field, Square square);
std::vector<sf::Vector2<short>> findHorizontalMoves(Square** field, Square square);
std::vector<sf::Vector2<short>> findVerticalMoves(Square** field, Square square);
std::vector<sf::Vector2<short>> findKingMoves(Square** field, Square square);
std::vector<sf::Vector2<short>> findKnightMoves(Square** field, Square square);
std::vector<sf::Vector2<short>> findPawnMoves(Square** field, Square square);
