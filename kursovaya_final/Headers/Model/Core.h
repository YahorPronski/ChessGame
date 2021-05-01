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
bool isCheckMate(Square** field, PieceColor color);

void makeRookCastleMove(Square** leftField, Square** rightField, bool isLeft, Square kingFromSquare, Square kingToSquare);
void updateCastlePossibility(Square fromSquare);


