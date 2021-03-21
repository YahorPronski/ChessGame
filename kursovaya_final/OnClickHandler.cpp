#include "OnClickHandler.h"
#include "Moves.h"
#include "SquareFinders.h"

#include <map>


std::map<short, short> onFirstClick(Square** field, bool isLeftField, sf::Vector2i mousePosition) {
	std::map<short, short> moves;

	if (!isCorrectClick(isLeftField, mousePosition)) return moves;
	
	Square clickedSquare = findSquareByCoordinates(field, isLeftField, mousePosition);
	moves = findCurrentPossibleMoves(field, clickedSquare);

	return moves;
}






