#include "../Headers/Model/Data.h"
#include "../Headers/Model/Moves.h"
#include "../Headers/Model/Values.h"
#include "../Headers/ViewModel/OnClickHandling.h"
#include "../Headers/Model/TextureCoordinatesContainer.h"
#include "../Headers/View/Graphic.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map> 







//void makeMove(Square** leftField,Square** rightField, Coords from, Coords to, bool isLeft) {
//    Square fromSq;
//    Square toSq;
//
//    bool wasFoundFrom = false;
//    bool wasFoundTo = false;
//
//    Square** field = isLeft ? leftField : rightField;
//
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            if (field[i][j].x <= from.x &&
//                field[i][j].x + sc > from.x &&
//                field[i][j].y <= from.y &&
//                field[i][j].y + sc > from.y) {
//
//                fromSq = field[i][j];
//
//                wasFoundFrom = true;
//
//                if (wasFoundTo) break;
//            }
//            else if (field[i][j].x <= to.x &&
//                field[i][j].x + sc > to.x &&
//                field[i][j].y <= to.y &&
//                field[i][j].y + sc > to.y) {
//
//                toSq = field[i][j];
//
//                wasFoundTo = true;
//
//                if (wasFoundFrom) break;
//            }
//        }
//        if (wasFoundFrom && wasFoundTo) break;
//    }
//
//    Square leftTmpFrom;
//    leftTmpFrom.colorOfSquare = fromSq.colorOfSquare;
//    leftTmpFrom.i = isLeft ? fromSq.i : 7 - fromSq.i;
//    leftTmpFrom.j = isLeft ? fromSq.j : 7 - fromSq.j;
//    leftTmpFrom.isEmpty = true;
//    leftTmpFrom.x = isLeft ? fromSq.x : 8 * sc - (fromSq.x - (9 * sc + space));
//    leftTmpFrom.y = isLeft ? fromSq.y : 9 * sc - fromSq.y;
//    leftTmpFrom.piece = "em_em";
//    leftTmpFrom.isAbleToMove = false;
//
//    leftField[leftTmpFrom.i][leftTmpFrom.j] = leftTmpFrom;
//
//    Square leftTmpTo;
//    leftTmpTo.colorOfSquare = toSq.colorOfSquare;
//    leftTmpTo.i = isLeft ? toSq.i : 7 - toSq.i;
//    leftTmpTo.j = isLeft ? toSq.j : 7 - toSq.j;
//    leftTmpTo.isEmpty = false;
//    leftTmpTo.piece = fromSq.piece;
//    leftTmpTo.possibleMoves = fromSq.possibleMoves;
//    leftTmpTo.x = isLeft ? toSq.x : 8 * sc - (toSq.x - (9 * sc + space));
//    leftTmpTo.y = isLeft ? toSq.y : 9 * sc - toSq.y;
//    leftTmpTo.isAbleToMove = isLeft ? true : false;
//
//    leftField[leftTmpTo.i][leftTmpTo.j] = leftTmpTo;
//
//    Square rightTmpFrom;
//    rightTmpFrom.colorOfSquare = fromSq.colorOfSquare;
//    rightTmpFrom.i = !isLeft ? fromSq.i : 7 - fromSq.i;
//    rightTmpFrom.j = !isLeft ? fromSq.j : 7 - fromSq.j;
//    rightTmpFrom.isEmpty = true;
//    rightTmpFrom.x = !isLeft ? fromSq.x : (9 * sc + space) + 8 * sc - fromSq.x;
//    rightTmpFrom.y = !isLeft ? fromSq.y : 9 * sc - fromSq.y;
//    rightTmpFrom.piece = "em_em";
//    rightTmpFrom.isAbleToMove = false;
//
//    rightField[rightTmpFrom.i][rightTmpFrom.j] = rightTmpFrom;
//
//    Square rightTmpTo;
//    rightTmpTo.colorOfSquare = toSq.colorOfSquare;
//    rightTmpTo.i = !isLeft ? toSq.i : 7 - toSq.i;
//    rightTmpTo.j = !isLeft ? toSq.j : 7 - toSq.j;
//    rightTmpTo.isEmpty = false;
//    rightTmpTo.piece = fromSq.piece;
//    rightTmpTo.possibleMoves = fromSq.possibleMoves;
//    rightTmpTo.x = !isLeft ? toSq.x : (9 * sc + space) + 8 * sc - toSq.x;
//    rightTmpTo.y = !isLeft ? toSq.y : 9 * sc - toSq.y;
//    rightTmpTo.isAbleToMove = !isLeft ? true : false;
//
//    rightField[rightTmpTo.i][rightTmpTo.j] = rightTmpTo;
//
//}

int main()
{
    int windowWidth = squareSize * 9 + spaceBetweenFields + squareSize * 9;
    int windowHeight = squareSize * 10;

    // create the window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Chess");

    Square** leftField = createAndFillLeftField();
    Square** rightField = createAndFillRightField();

    bool firstClickAccess = true;
    bool isLeftField = true;
    bool showMoves = false;

    TextureCoordinatesContainer container;
    std::vector<sf::Vector2<short>> currentMoves;
    Square** currentField;

    Square fromSquare;
    Square toSquare;

    MovesTexture movesTexture;
    ChessTexture chessTexture;

    if (!chessTexture.load(leftField, rightField, container))
        return -1;

    // run the main loop
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

            currentField = isLeftField ? leftField : rightField;

            if (firstClickAccess) {
                firstClickAccess = false;

                if (isCorrectClick(isLeftField, mousePosition)) {
                    fromSquare = findSquareByCoordinates(currentField, isLeftField, mousePosition);

                    if (fromSquare.pieceColor == (isLeftField ? WHITE : BLACK)) {

                        currentMoves = findCurrentPossibleMoves(currentField, fromSquare);

                        movesTexture.load(currentMoves, isLeftField);
                        showMoves = true;

                    } else { firstClickAccess = true; }
                } else {firstClickAccess = true;}
            } else {

                if (isCorrectMove(currentMoves, isLeftField, mousePosition)) {

                    toSquare = findSquareByCoordinates(currentField, isLeftField, mousePosition);
                    makeMove(leftField, rightField, isLeftField, fromSquare, toSquare);
                    showMoves = false;

                    chessTexture.load(leftField, rightField, container);

                    isLeftField = isLeftField ? false : true;
                    firstClickAccess = true;

                } else if (isCorrectClick(isLeftField, mousePosition)) {

                    fromSquare = findSquareByCoordinates(currentField, isLeftField, mousePosition);

                    if (fromSquare.pieceColor == (isLeftField ? WHITE : BLACK)) {
                        currentMoves = findCurrentPossibleMoves(currentField, fromSquare);

                        movesTexture.load(currentMoves, isLeftField);
                        showMoves = true;

                    } else {
                        showMoves = false;
                        firstClickAccess = true;
                    }
                } else {
                    showMoves = false;
                    firstClickAccess = true;
                }
            }
        }

        window.clear();
        window.draw(chessTexture);
        if (showMoves) window.draw(movesTexture);
        window.display();
    }

    return 0;
}
