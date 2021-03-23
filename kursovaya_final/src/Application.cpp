#include "../Headers/Model/Data.h"
#include "../Headers/Model/Moves.h"
#include "../Headers/ViewModel/OnClickHandling.h"
#include "../Headers/Model/TextureCoordinatesContainer.h"
#include "../Headers/View/Graphic.h"

int main()
{


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
