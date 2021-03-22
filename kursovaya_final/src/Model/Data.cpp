#include "../../Headers/Model/Data.h"

Square** createAndFillLeftField() {
    Square** field = new Square*[8];
    for (short i = 0; i < 8; i++) {
        field[i] = new Square[8];
    }

    field[0][0].pieceName = ROOK;
    field[0][1].pieceName = KNIGHT;
    field[0][2].pieceName = BISHOP;
    field[0][3].pieceName = QUEEN;
    field[0][4].pieceName = KING;
    field[0][5].pieceName = BISHOP;
    field[0][6].pieceName = KNIGHT;
    field[0][7].pieceName = ROOK;

    for (short j = 0; j < 8; j++) {
        field[0][j].pieceColor = BLACK;
        field[0][j].colorOfSquare = j % 2 != 0 ? BLACK : WHITE;
        field[0][j].i = 0;
        field[0][j].j = j;
    }

    for (short j = 0; j < 8; j++) {
        field[1][j].pieceName = PAWN;
        field[1][j].pieceColor = BLACK;
        field[1][j].colorOfSquare = j % 2 == 0 ? BLACK : WHITE;
        field[1][j].i = 1;
        field[1][j].j = j;
    }

    for (short i = 5; i >= 2; i--) {
        for (short j = 0; j < 8; j++) {
            field[i][j].pieceName = NO_PIECE;
            field[i][j].pieceColor = NO_COLOR;
            field[i][j].colorOfSquare = i % 2 == 0 ? 
                (j % 2 != 0 ? BLACK : WHITE):(j % 2 == 0 ? BLACK : WHITE);
            field[i][j].i = i;
            field[i][j].j = j;
        }
    }

    for (short j = 0; j < 8; j++) {
        field[6][j].pieceName = PAWN;
        field[6][j].pieceColor = WHITE;
        field[6][j].colorOfSquare = j % 2 != 0 ? BLACK : WHITE;
        field[6][j].i = 6;
        field[6][j].j = j;
    }

    field[7][0].pieceName = ROOK;
    field[7][1].pieceName = KNIGHT;
    field[7][2].pieceName = BISHOP;
    field[7][3].pieceName = QUEEN;
    field[7][4].pieceName = KING;
    field[7][5].pieceName = BISHOP;
    field[7][6].pieceName = KNIGHT;
    field[7][7].pieceName = ROOK;

    for (short j = 0; j < 8; j++) {
        field[7][j].pieceColor = WHITE;
        field[7][j].colorOfSquare = j % 2 == 0 ? BLACK : WHITE;
        field[7][j].i = 7;
        field[7][j].j = j;
    }

    return field;
}

Square** createAndFillRightField() {

    Square** field = new Square * [8];
    for (int i = 0; i < 8; i++) {
        field[i] = new Square[8];
    }

    field[0][0].pieceName = ROOK;
    field[0][1].pieceName = KNIGHT;
    field[0][2].pieceName = BISHOP;
    field[0][3].pieceName = KING;
    field[0][4].pieceName = QUEEN;
    field[0][5].pieceName = BISHOP;
    field[0][6].pieceName = KNIGHT;
    field[0][7].pieceName = ROOK;

    for (short j = 0; j < 8; j++) {
        field[0][j].pieceColor = WHITE;
        field[0][j].colorOfSquare = j % 2 != 0 ? BLACK : WHITE;
        field[0][j].i = 0;
        field[0][j].j = j;
    }

    for (short j = 0; j < 8; j++) {
        field[1][j].pieceName = PAWN;
        field[1][j].pieceColor = WHITE;
        field[1][j].colorOfSquare = j % 2 == 0 ? BLACK : WHITE;
        field[1][j].i = 1;
        field[1][j].j = j;
    }

    for (short i = 5; i >= 2; i--) {
        for (int j = 0; j < 8; j++) {
            field[i][j].pieceName = NO_PIECE;
            field[i][j].pieceColor = NO_COLOR;
            field[i][j].colorOfSquare = i % 2 == 0 ?
                (j % 2 != 0 ? BLACK : WHITE) : (j % 2 == 0 ? BLACK : WHITE);
            field[i][j].i = i;
            field[i][j].j = j;
        }
    }
   
    for (short j = 0; j < 8; j++) {
        field[6][j].pieceName = PAWN;
        field[6][j].pieceColor = BLACK;
        field[6][j].colorOfSquare = j % 2 != 0 ? BLACK : WHITE;
        field[6][j].i = 6;
        field[6][j].j = j;
    }

    field[7][0].pieceName = ROOK;
    field[7][1].pieceName = KNIGHT;
    field[7][2].pieceName = BISHOP;
    field[7][3].pieceName = KING;
    field[7][4].pieceName = QUEEN;
    field[7][5].pieceName = BISHOP;
    field[7][6].pieceName = KNIGHT;
    field[7][7].pieceName = ROOK;

    for (short j = 0; j < 8; j++) {
        field[7][j].pieceColor = BLACK;
        field[7][j].colorOfSquare = j % 2 == 0 ? BLACK : WHITE;
        field[7][j].i = 7;
        field[7][j].j = j;
    }

    return field;
}
