#include "../../Headers/Model/Core.h"
#include "../../Headers/Model/MovesFinders.h"

bool whiteKingLongCastleAvailable = true;
bool whiteKingShortCastleAvailable = true;

bool blackKingLongCastleAvailable = true;
bool blackKingShortCastleAvailable = true;

void makeMove(Square** leftField, Square** rightField, bool isLeft, Square fromSquare, Square toSquare) {

    // Checking for pawn transformation
    if (fromSquare.pieceName == PAWN && toSquare.i == 0) {
        transformPawn(leftField, rightField, isLeft, fromSquare);
    }

    // Updating castle possibility
    updateCastlePossibility(fromSquare);

    // If castle then move rook too
    if (fromSquare.pieceName == KING && abs(fromSquare.j - toSquare.j) == 2) {
        makeRookCastleMove(leftField, rightField, isLeft, fromSquare, toSquare);
    }

    // Changing left field
    short tmpI = isLeft ? fromSquare.i : (short)(7 - fromSquare.i);
    short tmpJ = isLeft ? fromSquare.j : (short)(7 - fromSquare.j);

    leftField[tmpI][tmpJ].pieceName = NO_PIECE;
    leftField[tmpI][tmpJ].pieceColor = NO_COLOR;
    leftField[tmpI][tmpJ].colorOfSquare = fromSquare.colorOfSquare;
    leftField[tmpI][tmpJ].i = tmpI;
    leftField[tmpI][tmpJ].j = tmpJ;

    tmpI = isLeft ? toSquare.i : (short)(7 - toSquare.i);
    tmpJ = isLeft ? toSquare.j : (short)(7 - toSquare.j);

    leftField[tmpI][tmpJ].pieceName = fromSquare.pieceName;
    leftField[tmpI][tmpJ].pieceColor = fromSquare.pieceColor;
    leftField[tmpI][tmpJ].colorOfSquare = toSquare.colorOfSquare;
    leftField[tmpI][tmpJ].i = tmpI;
    leftField[tmpI][tmpJ].j = tmpJ;

    // Changing right field
    tmpI = !isLeft ? fromSquare.i : (short)(7 - fromSquare.i);
    tmpJ = !isLeft ? fromSquare.j : (short)(7 - fromSquare.j);

    rightField[tmpI][tmpJ].pieceName = NO_PIECE;
    rightField[tmpI][tmpJ].pieceColor = NO_COLOR;
    rightField[tmpI][tmpJ].colorOfSquare = fromSquare.colorOfSquare;
    leftField[tmpI][tmpJ].i = tmpI;
    leftField[tmpI][tmpJ].j = tmpJ;

    tmpI = !isLeft ? toSquare.i : (short)(7 - toSquare.i);
    tmpJ = !isLeft ? toSquare.j : (short)(7 - toSquare.j);

    rightField[tmpI][tmpJ].pieceName = fromSquare.pieceName;
    rightField[tmpI][tmpJ].pieceColor = fromSquare.pieceColor;
    rightField[tmpI][tmpJ].colorOfSquare = toSquare.colorOfSquare;
    leftField[tmpI][tmpJ].i = tmpI;
    leftField[tmpI][tmpJ].j = tmpJ;

}

void transformPawn(Square** leftField, Square** rightField, bool isLeft, Square& fromSquare) {

    fromSquare.pieceName = QUEEN;

    short tmpI = isLeft ? fromSquare.i : (short)(7 - fromSquare.i);
    short tmpJ = isLeft ? fromSquare.j : (short)(7 - fromSquare.j);

    leftField[tmpI][tmpJ].pieceName = QUEEN;
    leftField[tmpI][tmpJ].pieceColor = fromSquare.pieceColor;
    leftField[tmpI][tmpJ].i = tmpI;
    leftField[tmpI][tmpJ].j = tmpJ;

    tmpI = !isLeft ? fromSquare.i : (short)(7 - fromSquare.i);
    tmpJ = !isLeft ? fromSquare.j : (short)(7 - fromSquare.j);

    rightField[tmpI][tmpJ].pieceName = QUEEN;
    rightField[tmpI][tmpJ].pieceColor = fromSquare.pieceColor;
    rightField[tmpI][tmpJ].i = tmpI;
    rightField[tmpI][tmpJ].j = tmpJ;

}

void updateCastlePossibility(Square fromSquare) {
    if (fromSquare.pieceColor == WHITE) {
        if (fromSquare.pieceName == KING) {
            whiteKingShortCastleAvailable = false;
            whiteKingLongCastleAvailable = false;
        } else if (fromSquare.pieceName == ROOK) {
            if (fromSquare.j == 7) whiteKingShortCastleAvailable = false;
            else whiteKingLongCastleAvailable = false;
        }
    } else if (fromSquare.pieceColor == BLACK) {
        if (fromSquare.pieceName == KING) {
            blackKingShortCastleAvailable = false;
            blackKingLongCastleAvailable = false;
        } else if (fromSquare.pieceName == ROOK) {
            if (fromSquare.j == 7) blackKingLongCastleAvailable = false;
            else blackKingShortCastleAvailable = false;
        }
    }
}

void makeRookCastleMove(Square** leftField, Square** rightField, bool isLeft, Square kingFromSquare, Square kingToSquare){

    short rookFromSquarePosJ;
    short rookToSquarePosJ;

    if (kingFromSquare.pieceColor == WHITE) {
        // Long white castle
        if (kingFromSquare.j - kingToSquare.j > 0) {
            rookFromSquarePosJ = (short)(kingFromSquare.j - 4);
            rookToSquarePosJ = (short)(kingFromSquare.j - 1);
        }
            // Short white castle
        else {
            rookFromSquarePosJ = (short)(kingFromSquare.j + 3);
            rookToSquarePosJ = (short)(kingFromSquare.j + 1);
        }
    } else {
        // Short black castle
        if (kingFromSquare.j - kingToSquare.j > 0) {
            rookFromSquarePosJ = (short)(kingFromSquare.j - 3);
            rookToSquarePosJ = (short)(kingFromSquare.j - 1);
        }
            // Long black castle
        else {
            rookFromSquarePosJ = (short)(kingFromSquare.j + 4);
            rookToSquarePosJ = (short)(kingFromSquare.j + 1);
        }
    }

    Square rookFromSquare = isLeft ? leftField[kingFromSquare.i][rookFromSquarePosJ] : rightField[kingFromSquare.i][rookFromSquarePosJ];
    Square rookToSquare = isLeft ? leftField[kingFromSquare.i][rookToSquarePosJ] : rightField[kingFromSquare.i][rookToSquarePosJ];
    makeMove(leftField, rightField, isLeft, rookFromSquare, rookToSquare);

}



bool isStaleMate(Square** field, PieceColor color) {
    bool isMate = true;
    for (short i = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            // If we have possible moves, it is not mate
            if (field[i][j].pieceName != NO_PIECE && field[i][j].pieceColor == color) {
                if (!findCurrentPossibleMoves(field, field[i][j]).empty()) {
                    isMate = false;
                    break;
                }
            }
        }
        if(!isMate) break;
    }
    return isMate;
}

bool isCheck(Square** field, PieceColor kingColor) {

    // Find king of required color
    bool wasFound = false;
    Square kingSquare;
    for (short i = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            if (field[i][j].pieceName == KING &&
                field[i][j].pieceColor == kingColor) {

                kingSquare = field[i][j];
                wasFound = true;
                break;
            }
        }
    }
    if (!wasFound) throw "King wasn't found";

    // Then check if will be check

    auto tmpI = (short)kingSquare.i + 1;
    auto tmpJ = (short)kingSquare.j + 1;

    // Diagonals
    while (tmpI < 8 && tmpJ < 8) {

        if (field[tmpI][tmpJ].pieceColor == kingSquare.pieceColor) {
            break;
        }
        else {
            if (field[tmpI][tmpJ].pieceName == QUEEN ||
                field[tmpI][tmpJ].pieceName == BISHOP) {
                return true;
            } else if (field[tmpI][tmpJ].pieceColor != NO_COLOR){
                break;
            }
        }
        tmpI++;
        tmpJ++;
    }

    tmpI = kingSquare.i - 1;
    tmpJ = kingSquare.j + 1;
    while (tmpI >= 0 && tmpJ < 8) {

        if (field[tmpI][tmpJ].pieceColor == kingSquare.pieceColor) {
            break;
        }
        else {
            if (field[tmpI][tmpJ].pieceName == QUEEN ||
                field[tmpI][tmpJ].pieceName == BISHOP) {
                return true;
            } else if (field[tmpI][tmpJ].pieceColor != NO_COLOR){
                break;
            }
        }
        tmpI--;
        tmpJ++;
    }

    tmpI = kingSquare.i + 1;
    tmpJ = kingSquare.j - 1;
    while (tmpI < 8 && tmpJ >= 0) {

        if (field[tmpI][tmpJ].pieceColor == kingSquare.pieceColor) {
            break;
        }
        else {
            if (field[tmpI][tmpJ].pieceName == QUEEN ||
                field[tmpI][tmpJ].pieceName == BISHOP) {
                return true;
            } else if (field[tmpI][tmpJ].pieceColor != NO_COLOR){
                break;
            }
        }
        tmpI++;
        tmpJ--;
    }

    tmpI = kingSquare.i - 1;
    tmpJ = kingSquare.j - 1;
    while (tmpI >= 0 && tmpJ >= 0) {

        if (field[tmpI][tmpJ].pieceColor == kingSquare.pieceColor) {
            break;
        }
        else {
            if (field[tmpI][tmpJ].pieceName == QUEEN ||
                field[tmpI][tmpJ].pieceName == BISHOP) {
                return true;
            } else if (field[tmpI][tmpJ].pieceColor != NO_COLOR){
                break;
            }
        }
        tmpI--;
        tmpJ--;
    }

    // Horizontal
    tmpI = kingSquare.i;
    tmpJ = kingSquare.j - 1;
    while (tmpJ >= 0) {

        if (field[tmpI][tmpJ].pieceColor == kingSquare.pieceColor) {
            break;
        }
        else {
            if (field[tmpI][tmpJ].pieceName == QUEEN ||
                field[tmpI][tmpJ].pieceName == ROOK) {
                return true;
            } else if (field[tmpI][tmpJ].pieceColor != NO_COLOR){
                break;
            }
        }
        tmpJ--;
    }

    tmpI = kingSquare.i;
    tmpJ = kingSquare.j + 1;
    while (tmpJ < 8) {

        if (field[tmpI][tmpJ].pieceColor == kingSquare.pieceColor) {
            break;
        }
        else {
            if (field[tmpI][tmpJ].pieceName == QUEEN ||
                field[tmpI][tmpJ].pieceName == ROOK) {
                return true;
            } else if (field[tmpI][tmpJ].pieceColor != NO_COLOR){
                break;
            }
        }
        tmpJ++;
    }

    // Vertical
    tmpI = kingSquare.i - 1;
    tmpJ = kingSquare.j;
    while (tmpI >= 0) {

        if (field[tmpI][tmpJ].pieceColor == kingSquare.pieceColor) {
            break;
        }
        else {
            if (field[tmpI][tmpJ].pieceName == QUEEN ||
                field[tmpI][tmpJ].pieceName == ROOK) {
                return true;
            } else if (field[tmpI][tmpJ].pieceColor != NO_COLOR){
                break;
            }
        }
        tmpI--;
    }

    tmpI = kingSquare.i + 1;
    tmpJ = kingSquare.j;
    while (tmpI < 8) {

        if (field[tmpI][tmpJ].pieceColor == kingSquare.pieceColor) {
            break;
        }
        else {
            if (field[tmpI][tmpJ].pieceName == QUEEN ||
                field[tmpI][tmpJ].pieceName == ROOK) {
                return true;
            } else if (field[tmpI][tmpJ].pieceColor != NO_COLOR){
                break;
            }
        }
        tmpI++;
    }

    // Knight moves
    short knightMoves[8][2] {
            {1, 2},
            {2, 1},
            {2, -1},
            {1, -2},
            {-1, -2},
            {-2, -1},
            {-2, 1},
            {-1, 2}
    };

    for (auto & move : knightMoves) {

        tmpI = kingSquare.i + move[0];
        tmpJ = kingSquare.j + move[1];

        if (tmpI >= 0 && tmpI < 8 && tmpJ >= 0 && tmpJ < 8) {
            if (field[tmpI][tmpJ].pieceColor != kingSquare.pieceColor &&
                (field[tmpI][tmpJ].pieceName == KNIGHT)) {
                return true;
            }
        }
    }

    // King moves
    short kingMoves[8][2] {
            {1, 1},
            {-1, -1},
            {-1, 1},
            {1, -1},
            {1, 0},
            {0, 1},
            {-1, 0},
            {0, -1}
    };

    for (auto & move : kingMoves) {

        tmpI = kingSquare.i + move[0];
        tmpJ = kingSquare.j + move[1];

        if (tmpI >= 0 && tmpI < 8 && tmpJ >= 0 && tmpJ < 8) {
            if (field[tmpI][tmpJ].pieceColor != kingSquare.pieceColor &&
                (field[tmpI][tmpJ].pieceName == KING)) {
                return true;
            }
        }
    }

    // Pawn moves
    tmpI = kingSquare.i - 1;
    tmpJ = kingSquare.j + 1;
    if (tmpI >= 0 && tmpI < 8 && tmpJ >= 0 && tmpJ < 8) {
        if (field[tmpI][tmpJ].pieceColor != kingSquare.pieceColor &&
            (field[tmpI][tmpJ].pieceName == PAWN)) {
            return true;
        }
    }

    tmpI = kingSquare.i - 1;
    tmpJ = kingSquare.j - 1;
    if (tmpI >= 0 && tmpI < 8 && tmpJ >= 0 && tmpJ < 8) {
        if (field[tmpI][tmpJ].pieceColor != kingSquare.pieceColor &&
            (field[tmpI][tmpJ].pieceName == PAWN)) {
            return true;
        }
    }

    return false;
}

bool willBeCheck(Square** field, Square fromSquare, Square toSquare) {

    // For example we did this move (then we need to change it back!!!!)
    field[fromSquare.i][fromSquare.j].pieceName = NO_PIECE;
    field[fromSquare.i][fromSquare.j].pieceColor = NO_COLOR;
    field[fromSquare.i][fromSquare.j].colorOfSquare = fromSquare.colorOfSquare;

    field[toSquare.i][toSquare.j].pieceName = fromSquare.pieceName;
    field[toSquare.i][toSquare.j].pieceColor = fromSquare.pieceColor;
    field[toSquare.i][toSquare.j].colorOfSquare = toSquare.colorOfSquare;

    bool willBeCheck = isCheck(field, fromSquare.pieceColor);
    field[fromSquare.i][fromSquare.j] = fromSquare;
    field[toSquare.i][toSquare.j] = toSquare;

    return willBeCheck;
}
