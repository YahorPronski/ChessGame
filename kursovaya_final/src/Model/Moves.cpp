#include "../../Headers/Model/Moves.h"
#include <iostream>


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
			coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
		} 
		else if (field[i][j].pieceColor != square.pieceColor) {
            coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
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
            coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
		}
		else if (field[i][j].pieceColor != square.pieceColor) {
            coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
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
            coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
		}
		else if (field[i][j].pieceColor != square.pieceColor) {
            coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
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
            coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
		}
		else if (field[i][j].pieceColor != square.pieceColor) {
            coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
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
            coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
		}
		else if (field[i][j].pieceColor != square.pieceColor) {
            coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
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
            coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
		}
		else if (field[i][j].pieceColor != square.pieceColor) {
			coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
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
            coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
		}
		else if (field[i][j].pieceColor != square.pieceColor) {
            coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
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
            coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
		}
		else if (field[i][j].pieceColor != square.pieceColor) {
            coordinates.insert(coordinates.end(), sf::Vector2<short>(j, i));
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
		{0, -1},
	};

	for (auto & move : moves) {

		auto tmpI = (short)(square.i + move[0]);
		auto tmpJ = (short)(square.j + move[1]);

		if (tmpI < 8 && tmpI >= 0 && tmpJ >= 0 && tmpJ < 8) { 

			if (field[tmpI][tmpJ].pieceColor != square.pieceColor)
                coordinates.insert(coordinates.end(), sf::Vector2<short>(tmpJ, tmpI));
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
		{-1, 2},
	};

	for (auto & move : moves) {

		auto tmpI = (short)(square.i + move[0]);
		auto tmpJ = (short)(square.j + move[1]);

		if (tmpI < 8 && tmpI >= 0 && tmpJ >= 0 && tmpJ < 8) {

			if (field[tmpI][tmpJ].pieceColor != square.pieceColor)
                coordinates.insert(coordinates.end(), sf::Vector2<short>(tmpJ, tmpI));
		}
	}

	return coordinates;
}

std::vector<sf::Vector2<short>> findPawnMoves(Square** field, Square square) {
    std::vector<sf::Vector2<short>> coordinates;

    auto tmpI = (short)(square.i - 1);
    auto tmpJ = (short)(square.j);

    if (tmpI >= 0 && tmpI < 8) {

        if (field[tmpI][tmpJ].pieceName == NO_PIECE)
            coordinates.insert(coordinates.end(), sf::Vector2<short>(tmpJ, tmpI));
    }

    tmpI = square.i - 1;
    tmpJ = square.j + 1;
    if (tmpI >= 0 && tmpI < 8 && tmpJ >= 0 && tmpJ < 8) {

        if (field[tmpI][tmpJ].pieceName != NO_PIECE && field[tmpI][tmpJ].pieceColor != square.pieceColor)
            coordinates.insert(coordinates.end(), sf::Vector2<short>(tmpJ, tmpI));
    }

    tmpI = square.i - 1;
    tmpJ = square.j - 1;
    if (tmpI >= 0 && tmpI < 8 && tmpJ >= 0 && tmpJ < 8) {

        if (field[tmpI][tmpJ].pieceName != NO_PIECE && field[tmpI][tmpJ].pieceColor != square.pieceColor)
            coordinates.insert(coordinates.end(), sf::Vector2<short>(tmpJ, tmpI));
    }

    tmpI = square.i - 2;
    tmpJ = square.j;
    if (square.i == 6) {

        if (field[tmpI + 1][tmpJ].pieceName == NO_PIECE &&
            field[tmpI][tmpJ].pieceName == NO_PIECE)
            coordinates.insert(coordinates.end(), sf::Vector2<short>(tmpJ, tmpI));
    }

    return coordinates;
}

