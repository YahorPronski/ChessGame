#pragma once

#include "Values.h"

struct Square {

    PieceName pieceName;
    PieceColor pieceColor;
    PieceColor colorOfSquare;

    // ���������� �� ����� ((�,8) == (0,0) ��� ����� �����, (H,1) == (0,0) ��� ������ �����)
    int i;
    int j;

    // ������ ������ ������ ���� ������ �����������,
    // ��� �� ��� � ����� ������ ������� ����
    bool isAbleToMove;
};

// ������� ��������� ������ ������ 8�8 (����� ������� ����) � ��������� ��������
Square** createAndFillLeftField();

// ������� ��������� ������ ������ 8�8 (������ ������� ����) � ��������� ��������
Square** createAndFillRightField();
