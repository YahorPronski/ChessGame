#include "../../Headers/ViewModel/OnClickHandler.h"
#include "../../Headers/Model/Moves.h"
#include "../../Headers/Model/SquareFinders.h"

#include <map>


std::map<short, short> onFirstClick(Square** field, bool isLeftField, sf::Vector2i mousePosition) {
	std::map<short, short> moves;

	if (!isCorrectClick(isLeftField, mousePosition)) return moves;
	
	Square clickedSquare = findSquareByCoordinates(field, isLeftField, mousePosition);
	moves = findCurrentPossibleMoves(field, clickedSquare);

	return moves;
}






