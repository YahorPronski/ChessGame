#pragma once

#include "Values.h"

struct Square {

    PieceName pieceName;
    PieceColor pieceColor;
    PieceColor colorOfSquare;

    //  оординаты на доске ((ј,8) == (0,0) дл€ левой доски, (H,1) == (0,0) дл€ правой доски)
    int i;
    int j;

    // „ерные фигуры левого пол€ нельз€ передвигать,
    // “ак же как и белые фигуры правого пол€
    bool isAbleToMove;
};

// —оздает двумерный массив клеток 8х8 (левое игровое поле) и заполн€ет фигурами
Square** createAndFillLeftField();

// —оздает двумерный массив клеток 8х8 (правое игровое поле) и заполн€ет фигурами
Square** createAndFillRightField();
