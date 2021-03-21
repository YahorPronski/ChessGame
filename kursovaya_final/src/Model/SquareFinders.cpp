#include "../../Headers/Model/SquareFinders.h"

bool isCorrectClick(bool isLeftField, sf::Vector2i mousePosition) {
	if (isLeftField) {
		return mousePosition.x >= squareSize && mousePosition.x <= squareSize * 9 &&
			mousePosition.y >= squareSize && mousePosition.y <= squareSize * 9;
	}
	else {
		return mousePosition.x >= squareSize + spaceBetweenFields + squareSize * 8 &&
			mousePosition.x <= squareSize * 8 + spaceBetweenFields + squareSize * 8 &&
			mousePosition.y >= squareSize && mousePosition.y <= squareSize * 8;
	}
}

Square findSquareByCoordinates(Square** field, bool isLeft, sf::Vector2i mousePosition) {

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((isLeft ? (j + 1) * squareSize : (j + 1) * squareSize + squareSize * 8 + spaceBetweenFields)  <= mousePosition.x &&
				(isLeft ? (j + 2) * squareSize : (j + 2) * squareSize + squareSize * 8 + spaceBetweenFields) >= mousePosition.x &&
				(i + 1) * squareSize <= mousePosition.y &&
				(i + 2) * squareSize >= mousePosition.y) {
				std::cout << field[i][j].pieceName << std::endl;
				return field[i][j];
			}
		}
	}

	throw "Square wasn't found";
	return field[0][0];
}