#include "../../Headers/ViewModel/OnClickHandling.h"

bool isCorrectClick(bool isLeftField, sf::Vector2i mousePosition) {
    if (isLeftField) {
        return mousePosition.x >= squareSize && mousePosition.x <= squareSize * 9 &&
               mousePosition.y >= squareSize && mousePosition.y <= squareSize * 9;
    }
    else {
        return mousePosition.x >= squareSize * 9 + spaceBetweenFields &&
               mousePosition.x <= squareSize * 9 + spaceBetweenFields + squareSize * 8 &&
               mousePosition.y >= squareSize && mousePosition.y <= squareSize * 9;
    }
}

Square findSquareByCoordinates(Square** field, bool isLeft, sf::Vector2i mousePosition) {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((isLeft ? (j + 1) * squareSize : (j + 1) * squareSize + squareSize * 8 + spaceBetweenFields)  <= mousePosition.x &&
                (isLeft ? (j + 2) * squareSize : (j + 2) * squareSize + squareSize * 8 + spaceBetweenFields) >= mousePosition.x &&
                (i + 1) * squareSize <= mousePosition.y &&
                (i + 2) * squareSize >= mousePosition.y) {

                return field[i][j];
            }
        }
    }

    throw "Square wasn't found";
}

bool isCorrectMove(std::vector<sf::Vector2<short>> currentMoves, bool isLeft, sf::Vector2i mousePosition) {


    auto it = currentMoves.begin();
    while(it != currentMoves.end()) {

        if ((isLeft ? (it->x + 1) * squareSize : (it->x + 9) * squareSize + spaceBetweenFields) <= mousePosition.x &&
            (isLeft ? (it->x + 2) * squareSize : (it->x + 10) * squareSize + spaceBetweenFields) >= mousePosition.x &&
            (it->y + 1) * squareSize <= mousePosition.y && (it->y + 2) * squareSize >= mousePosition.y) {

            return true;
        }

        it++;
    }

    return false;
}





