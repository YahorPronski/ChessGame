#pragma once

#include "Values.h"

struct Square {

    PieceName pieceName;
    PieceColor pieceColor;
    PieceColor colorOfSquare;

    int i;
    int j;
    bool isAbleToMove;
};

Square** createAndFillLeftField();


Square** createAndFillRightField();
