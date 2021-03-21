#include "../../Headers/Model/Moves.h"
#include <iostream>
  std::map<short, short> findPawnMoves(Square** field, Square square) {
	std::map<short, short> coordinates;

	short tmpI = square.i - 1;
	short tmpJ = square.j;

	if (tmpI >= 0 && tmpI < 8) {

		if (field[tmpI][tmpJ].pieceName == NO_PIECE)
			coordinates.insert(std::pair<short, short>(tmpI, tmpJ));
	}

	tmpI = square.i - 1;
	tmpJ = square.j + 1;
	if (tmpI >= 0 && tmpI < 8 && tmpJ >= 0 && tmpJ < 8) {

		if (field[tmpI][tmpJ].pieceName != NO_PIECE && field[tmpI][tmpJ].pieceColor != square.pieceColor)
			coordinates.insert(std::pair<short, short>(tmpI, tmpJ));
	}

	tmpI = square.i - 1;
	tmpJ = square.j - 1;
	if (tmpI >= 0 && tmpI < 8 && tmpJ >= 0 && tmpJ < 8) {

		if (field[tmpI][tmpJ].pieceName != NO_PIECE && field[tmpI][tmpJ].pieceColor != square.pieceColor)
			coordinates.insert(std::pair<short, short>(tmpI, tmpJ));
	}

	tmpI = square.i - 2;
	tmpJ = square.j;
	if (square.i == 6) {

		if (field[tmpI + 1][tmpJ].pieceName == NO_PIECE &&
			field[tmpI][tmpJ].pieceName == NO_PIECE)
			coordinates.insert(std::pair<short, short>(tmpI, tmpJ));
	}

	return coordinates;
}

std::map<short, short> findCurrentPossibleMoves(Square** field, Square square) {
	std::map<short, short> coordinates;

	switch (square.pieceName) {

	case KING: {
		std::map<short, short> moves = findKingMoves(field, square);

		std::map<short, short> :: iterator it = moves.begin();
		while (it != moves.end()) {  

			coordinates.insert(std::pair<short, short>(it->first, it->second));
			it++;
		}

		break;
	}
	case QUEEN: {
		std::map<short, short> moves1 = findDiagonalMoves(field, square);
		std::map<short, short> moves2 = findVerticalMoves(field, square);
		std::map<short, short> moves3 = findHorizontalMoves(field, square);

		std::map<short, short> :: iterator it = moves1.begin();
		while (it != moves1.end()) {
			coordinates.insert(std::pair<short, short>(it->first, it->second));
			it++;
		}

		it = moves2.begin();
		while (it != moves2.end()) {
			coordinates.insert(std::pair<short, short>(it->first, it->second));
			it++;
		}

		it = moves3.begin();
		while (it != moves3.end()) {
			coordinates.insert(std::pair<short, short>(it->first, it->second));
			it++;
		}

		break;
	}
	case BISHOP: {
		std::map<short, short> moves = findDiagonalMoves(field, square);

		std::map<short, short> :: iterator it = moves.begin();
		while (it != moves.end()) {
			coordinates.insert(std::pair<short, short>(it->first, it->second));
			it++;
		}

		break;
	}
	case KNIGHT: {
		std::map<short, short> moves = findKnightMoves(field, square);

		std::map<short, short> :: iterator it = moves.begin();
		while (it != moves.end()) {
			coordinates.insert(std::pair<short, short>(it->first, it->second));
			it++;
		}

		break;
	}
	case ROOK: {
		std::map<short, short> moves1 = findVerticalMoves(field, square);
		std::map<short, short> moves2 = findHorizontalMoves(field, square);

		std::map<short, short> :: iterator it = moves1.begin();
		while (it != moves1.end()) {
			coordinates.insert(std::pair<short, short>(it->first, it->second));
			it++;
		}

		it = moves2.begin();
		while (it != moves2.end()) {
			coordinates.insert(std::pair<short, short>(it->first, it->second));
			it++;
		}

		break;
	}
	case PAWN: {
		std::map<short, short> moves = findPawnMoves(field, square);

		std::map<short, short> :: iterator it = moves.begin();
		while (it != moves.end()) {
			coordinates.insert(std::pair<short, short>(it->first, it->second));
			it++;
		}

		break;
	}
	}

	return coordinates;
}

std::map<short, short> findDiagonalMoves(Square** field, Square square) {
	std::map<short, short> coordinates;

	short i = square.i + 1;
	short j = square.j + 1;

	while (i < 8 && j < 8) {

		if (field[i][j].pieceName == NO_PIECE) {
			coordinates.insert(std::pair<short, short>(i, j));
		} 
		else if (field[i][j].pieceColor != square.pieceColor) {
			coordinates.insert(std::pair<short, short>(i, j));
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
			coordinates.insert(std::pair<short, short>(i, j));
		}
		else if (field[i][j].pieceColor != square.pieceColor) {
			coordinates.insert(std::pair<short, short>(i, j));
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
			coordinates.insert(std::pair<short, short>(i, j));
		}
		else if (field[i][j].pieceColor != square.pieceColor) {
			coordinates.insert(std::pair<short, short>(i, j));
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
			coordinates.insert(std::pair<short, short>(i, j));
		}
		else if (field[i][j].pieceColor != square.pieceColor) {
			coordinates.insert(std::pair<short, short>(i, j));
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

std::map<short, short> findHorizontalMoves(Square** field, Square square) {
	std::map<short, short> coordinates;

	short i = square.i;
	short j = square.j + 1;

	while (j < 8) {

		if (field[i][j].pieceName == NO_PIECE) {
			coordinates.insert(std::pair<short, short>(i, j));
		}
		else if (field[i][j].pieceColor != square.pieceColor) {
			coordinates.insert(std::pair<short, short>(i, j));
			break;
		}
		else {
			break;
		}

		j++;
	}

	j = square.j - 1;
	while (i >= 0) {

		if (field[i][j].pieceName == NO_PIECE) {
			coordinates.insert(std::pair<short, short>(i, j));
		}
		else if (field[i][j].pieceColor != square.pieceColor) {
			coordinates.insert(std::pair<short, short>(i, j));
			break;
		}
		else {
			break;
		}

		j--;
	}

	return coordinates;
}


std::map<short, short> findVerticalMoves(Square** field, Square square) {
	std::map<short, short> coordinates;

	short i = square.i + 1;
	short j = square.j;

	while (i < 8) {

		if (field[i][j].pieceName == NO_PIECE) {
			coordinates.insert(std::pair<short, short>(i, j));
		}
		else if (field[i][j].pieceColor != square.pieceColor) {
			coordinates.insert(std::pair<short, short>(i, j));
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
			coordinates.insert(std::pair<short, short>(i, j));
		}
		else if (field[i][j].pieceColor != square.pieceColor) {
			coordinates.insert(std::pair<short, short>(i, j));
			break;
		}
		else {
			break;
		}

		i--;
	}

	return coordinates;
}

std::map<short, short> findKingMoves(Square** field, Square square) {
	std::map<short, short> coordinates;

	std::map <short, short> moves{
		{1, 1},
		{-1, -1},
		{-1, 1},
		{1, -1},
		{1, 0},
		{0, 1},
		{-1, 0},
		{0, -1},
	};

	std::map<short, short> :: iterator it = moves.begin();
	while(it != moves.end()) {  

		short tmpI = square.i + it->first;
		short tmpJ = square.j + it->second;

		if (tmpI < 8 && tmpI >= 0 && tmpJ >= 0 && tmpJ < 8) { 

			if (field[tmpI][tmpJ].pieceColor != square.pieceColor) 
				coordinates.insert(std::pair<short, short>(tmpI, tmpJ));
		}

		it++;
	}

	return coordinates;
}

std::map<short, short> findKnightMoves(Square** field, Square square) {
	std::map<short, short> coordinates;

	std::map <short, short> moves{
		{1, 2},
		{2, 1},
		{2, -1},
		{1, -2},
		{-1, -2},
		{-2, -1},
		{-2, 1},
		{-1, 2},
	};

	std::map<short, short> :: iterator it = moves.begin();
	while (it != moves.end()) {

		short tmpI = square.i + it->first;
		short tmpJ = square.j + it->second;

		if (tmpI < 8 && tmpI >= 0 && tmpJ >= 0 && tmpJ < 8) {

			if (field[tmpI][tmpJ].pieceColor != square.pieceColor) 
				coordinates.insert(std::pair<short, short>(tmpI, tmpJ));
		}

		it++;
	}

	return coordinates;
}

