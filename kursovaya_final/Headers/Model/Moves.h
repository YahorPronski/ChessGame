#pragma once

#include "Data.h"

#include <map>

// Находит координаты текущих возможных ходов заданной фигуры
std::map<short, short> findCurrentPossibleMoves(Square** field, Square square);

std::map<short, short> findDiagonalMoves(Square** field, Square square);
std::map<short, short> findHorizontalMoves(Square** field, Square square);
std::map<short, short> findVerticalMoves(Square** field, Square square);
std::map<short, short> findKingMoves(Square** field, Square square);
std::map<short, short> findKnightMoves(Square** field, Square square);
std::map<short, short> findPawnMoves(Square** field, Square square);
