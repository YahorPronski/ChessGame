#include "../../Headers/Model/Moves.h"

void makeMove(Square** leftField, Square** rightField, bool isLeft, Square fromSquare, Square toSquare) {

    // Change left field
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

    // Change right field
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

bool willBeCheck(Square** field, Square fromSquare, Square toSquare) {

    // For example we did this move (then we need to change it back!!!!)
    field[fromSquare.i][fromSquare.j].pieceName = NO_PIECE;
    field[fromSquare.i][fromSquare.j].pieceColor = NO_COLOR;
    field[fromSquare.i][fromSquare.j].colorOfSquare = fromSquare.colorOfSquare;

    field[toSquare.i][toSquare.j].pieceName = fromSquare.pieceName;
    field[toSquare.i][toSquare.j].pieceColor = fromSquare.pieceColor;
    field[toSquare.i][toSquare.j].colorOfSquare = toSquare.colorOfSquare;

    // Get color of king
    PieceColor kingColor = fromSquare.pieceColor;

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

                field[fromSquare.i][fromSquare.j] = fromSquare;
                field[toSquare.i][toSquare.j] = toSquare;
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

                field[fromSquare.i][fromSquare.j] = fromSquare;
                field[toSquare.i][toSquare.j] = toSquare;
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

                field[fromSquare.i][fromSquare.j] = fromSquare;
                field[toSquare.i][toSquare.j] = toSquare;
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

                field[fromSquare.i][fromSquare.j] = fromSquare;
                field[toSquare.i][toSquare.j] = toSquare;
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

                field[fromSquare.i][fromSquare.j] = fromSquare;
                field[toSquare.i][toSquare.j] = toSquare;
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

                field[fromSquare.i][fromSquare.j] = fromSquare;
                field[toSquare.i][toSquare.j] = toSquare;
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

                field[fromSquare.i][fromSquare.j] = fromSquare;
                field[toSquare.i][toSquare.j] = toSquare;
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

                field[fromSquare.i][fromSquare.j] = fromSquare;
                field[toSquare.i][toSquare.j] = toSquare;
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

                field[fromSquare.i][fromSquare.j] = fromSquare;
                field[toSquare.i][toSquare.j] = toSquare;
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

                field[fromSquare.i][fromSquare.j] = fromSquare;
                field[toSquare.i][toSquare.j] = toSquare;
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

            field[fromSquare.i][fromSquare.j] = fromSquare;
            field[toSquare.i][toSquare.j] = toSquare;
            return true;
        }
    }

    tmpI = kingSquare.i - 1;
    tmpJ = kingSquare.j - 1;
    if (tmpI >= 0 && tmpI < 8 && tmpJ >= 0 && tmpJ < 8) {
        if (field[tmpI][tmpJ].pieceColor != kingSquare.pieceColor &&
            (field[tmpI][tmpJ].pieceName == PAWN)) {

            field[fromSquare.i][fromSquare.j] = fromSquare;
            field[toSquare.i][toSquare.j] = toSquare;
            return true;
        }
    }

    field[fromSquare.i][fromSquare.j] = fromSquare;
    field[toSquare.i][toSquare.j] = toSquare;
    return false;
}

std::vector<sf::Vector2<short>> findCurrentPossibleMoves(Square** field, Square square) {
    std::vector<sf::Vector2<short>> coordinates;

	switch (square.pieceName) {

	case KING: {
        coordinates = findKingMoves(field, square);
		break;
	}
	case QUEEN: {
        std::vector<sf::Vector2<short>> moves1 = findDiagonalMoves(field, square);
        std::vector<sf::Vector2<short>> moves2 = findVerticalMoves(field, square);
        std::vector<sf::Vector2<short>> moves3 = findHorizontalMoves(field, square);

		coordinates.insert(coordinates.end(), moves1.begin(), moves1.end());
		coordinates.insert(coordinates.end(), moves2.begin(), moves2.end());
		coordinates.insert(coordinates.end(), moves3.begin(), moves3.end());

		break;
	}
	case BISHOP: {
        coordinates = findDiagonalMoves(field, square);
		break;
	}
	case KNIGHT: {
        coordinates = findKnightMoves(field, square);
		break;
	}
	case ROOK: {
        std::vector<sf::Vector2<short>> moves1 = findHorizontalMoves(field, square);
        std::vector<sf::Vector2<short>> moves2 = findVerticalMoves(field, square);

        coordinates.insert(coordinates.end(), moves1.begin(), moves1.end());
        coordinates.insert(coordinates.end(), moves2.begin(), moves2.end());

		break;
	}
	case PAWN: {
		coordinates = findPawnMoves(field, square);
		break;
	}
        default: {
            throw "Unexpected piece name";
        }
	}

	return coordinates;
}

std::vector<sf::Vector2<short>> findDiagonalMoves(Square** field, Square square) {
    std::vector<sf::Vector2<short>> coordinates;

	auto i = (short)(square.i + 1);
	auto j = (short)(square.j + 1);

	while (i < 8 && j < 8) {

		if (field[i][j].pieceName == NO_PIECE) {
            if (!willBeCheck(field, square, field[i][j])) {
                coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
            }
		} 
		else if (field[i][j].pieceColor != square.pieceColor) {
            if (!willBeCheck(field, square, field[i][j])) {
                coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
            }
            break;
		}
		else {
			break;
		}

		i++;
		j++;
	}

    i = square.i - 1;
    j = square.j - 1;
	while (i >= 0 && j >= 0) {

		if (field[i][j].pieceName == NO_PIECE) {
            if (!willBeCheck(field, square, field[i][j])) {
                coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
            }
		}
		else if (field[i][j].pieceColor != square.pieceColor) {
            if (!willBeCheck(field, square, field[i][j])) {
                coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
            }
            break;
		}
		else {
			break;
		}

		i--;
		j--;
	}

	i = square.i + 1;
	j = square.j - 1;
	while (i < 8 && j >= 0) {

		if (field[i][j].pieceName == NO_PIECE) {
            if (!willBeCheck(field, square, field[i][j])) {
                coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
            }
		}
		else if (field[i][j].pieceColor != square.pieceColor) {
            if (!willBeCheck(field, square, field[i][j])) {
                coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
            }
			break;
		}
		else {
			break;
		}

		i++;
		j--;
	}

	i = square.i - 1;
	j = square.j + 1;
	while (i >= 0 && j < 8) {

		if (field[i][j].pieceName == NO_PIECE) {
            if (!willBeCheck(field, square, field[i][j])) {
                coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
            }
		}
		else if (field[i][j].pieceColor != square.pieceColor) {
            if (!willBeCheck(field, square, field[i][j])) {
                coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
            }
			break;
		}
		else {
			break;
		}

		i--;
		j++;
	}

	return coordinates;
}

std::vector<sf::Vector2<short>> findHorizontalMoves(Square** field, Square square) {
    std::vector<sf::Vector2<short>> coordinates;

	auto i = (short)(square.i);
	auto j = (short)(square.j + 1);

	while (j < 8) {

		if (field[i][j].pieceName == NO_PIECE) {
            if (!willBeCheck(field, square, field[i][j])) {
                coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
            }
		}
		else if (field[i][j].pieceColor != square.pieceColor) {
            if (!willBeCheck(field, square, field[i][j])) {
                coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
            }
			break;
		}
		else {
			break;
		}

		j++;
	}

	j = square.j - 1;
	while (j >= 0) {

		if (field[i][j].pieceName == NO_PIECE) {
            if (!willBeCheck(field, square, field[i][j])) {
                coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
            }
		}
		else if (field[i][j].pieceColor != square.pieceColor) {
            if (!willBeCheck(field, square, field[i][j])) {
                coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
            }
			break;
		}
		else {
			break;
		}

		j--;
	}

	return coordinates;
}


std::vector<sf::Vector2<short>> findVerticalMoves(Square** field, Square square) {
    std::vector<sf::Vector2<short>> coordinates;

	auto i = (short)(square.i + 1);
	auto j = (short)(square.j);

	while (i < 8) {

		if (field[i][j].pieceName == NO_PIECE) {
            if (!willBeCheck(field, square, field[i][j])) {
                coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
            }
		}
		else if (field[i][j].pieceColor != square.pieceColor) {
            if (!willBeCheck(field, square, field[i][j])) {
                coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
            }
			break;
		}
		else {
			break;
		}

		i++;
	}

	i = square.i - 1;
	while (i >= 0) {

		if (field[i][j].pieceName == NO_PIECE) {
            if (!willBeCheck(field, square, field[i][j])) {
                coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
            }
		}
		else if (field[i][j].pieceColor != square.pieceColor) {
            if (!willBeCheck(field, square, field[i][j])) {
                coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
            }
			break;
		}
		else {
			break;
		}

		i--;
	}

	return coordinates;
}

std::vector<sf::Vector2<short>> findKingMoves(Square** field, Square square) {
    std::vector<sf::Vector2<short>> coordinates;

    short moves[8][2] {
		{1, 1},
		{-1, -1},
		{-1, 1},
		{1, -1},
		{1, 0},
		{0, 1},
		{-1, 0},
		{0, -1}
	};

	for (auto & move : moves) {

		auto tmpI = (short)(square.i + move[0]);
		auto tmpJ = (short)(square.j + move[1]);

		if (tmpI < 8 && tmpI >= 0 && tmpJ >= 0 && tmpJ < 8) { 

			if (field[tmpI][tmpJ].pieceColor != square.pieceColor) {
                if (!willBeCheck(field, square, field[tmpI][tmpJ])) {
                    coordinates.insert(coordinates.end(), sf::Vector2<short>(tmpJ, tmpI));
                }
            }
		}
	}

	return coordinates;
}

std::vector<sf::Vector2<short>> findKnightMoves(Square** field, Square square) {
    std::vector<sf::Vector2<short>> coordinates;

    short moves[8][2] {
		{1, 2},
		{2, 1},
		{2, -1},
		{1, -2},
		{-1, -2},
		{-2, -1},
		{-2, 1},
		{-1, 2}
	};

	for (auto & move : moves) {

		auto tmpI = (short)(square.i + move[0]);
		auto tmpJ = (short)(square.j + move[1]);

		if (tmpI < 8 && tmpI >= 0 && tmpJ >= 0 && tmpJ < 8) {

			if (field[tmpI][tmpJ].pieceColor != square.pieceColor) {
                if (!willBeCheck(field, square, field[tmpI][tmpJ])) {
                    coordinates.insert(coordinates.end(), sf::Vector2<short>(tmpJ, tmpI));
                }
            }
		}
	}

	return coordinates;
}

std::vector<sf::Vector2<short>> findPawnMoves(Square** field, Square square) {
    std::vector<sf::Vector2<short>> coordinates;

    auto tmpI = (short)(square.i - 1);
    auto tmpJ = (short)(square.j);

    if (tmpI >= 0 && tmpI < 8) {
        if (field[tmpI][tmpJ].pieceName == NO_PIECE) {
            if (!willBeCheck(field, square, field[tmpI][tmpJ])) {

                coordinates.insert(coordinates.end(), sf::Vector2<short>(tmpJ, tmpI));
            }
        }
    }

    tmpI = square.i - 1;
    tmpJ = square.j + 1;
    if (tmpI >= 0 && tmpI < 8 && tmpJ >= 0 && tmpJ < 8) {
        if (field[tmpI][tmpJ].pieceName != NO_PIECE && field[tmpI][tmpJ].pieceColor != square.pieceColor) {
            if (!willBeCheck(field, square, field[tmpI][tmpJ])) {

                coordinates.insert(coordinates.end(), sf::Vector2<short>(tmpJ, tmpI));
            }
        }
    }

    tmpI = square.i - 1;
    tmpJ = square.j - 1;
    if (tmpI >= 0 && tmpI < 8 && tmpJ >= 0 && tmpJ < 8) {
        if (field[tmpI][tmpJ].pieceName != NO_PIECE && field[tmpI][tmpJ].pieceColor != square.pieceColor) {
            if (!willBeCheck(field, square, field[tmpI][tmpJ])) {

                coordinates.insert(coordinates.end(), sf::Vector2<short>(tmpJ, tmpI));
            }
        }
    }

    tmpI = square.i - 2;
    tmpJ = square.j;
    if (square.i == 6) {
        if (field[tmpI + 1][tmpJ].pieceName == NO_PIECE &&
            field[tmpI][tmpJ].pieceName == NO_PIECE) {
            if (!willBeCheck(field, square, field[tmpI][tmpJ])) {

                coordinates.insert(coordinates.end(), sf::Vector2<short>(tmpJ, tmpI));
            }
        }
    }

    return coordinates;
}

