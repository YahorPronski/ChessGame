#pragma once

#include "Values.h"

struct Square {

    PieceName pieceName;
    PieceColor pieceColor;
    PieceColor colorOfSquare;

    short i;
    short j;
};

Square** createAndFillLeftField();
Square** createAndFillRightField();
