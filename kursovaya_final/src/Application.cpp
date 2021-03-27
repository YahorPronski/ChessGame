#include "../Headers/Model/Data.h"
#include "../Headers/Model/Moves.h"
#include "../Headers/ViewModel/OnClickHandling.h"
#include "../Headers/Model/TextureCoordinatesContainer.h"
#include "../Headers/View/Graphic.h"

// Доделать:
// Звуки
// Взятие на проходе
// Рокировка
// Таймер
// Проверка на мат
// Добавить текстуры координаты доски
// Превращение пешки

int main()
{
    // Create the window
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

    ChessTexture chessTexture;
    if (!chessTexture.load(leftField, rightField, container))
        return -1;

    CoordinatesTexture coordsTexture;
    if (!coordsTexture.load())
        return -1;

    MovesTexture movesTexture;

    // Run the main loop
    while (window.isOpen())
    {
        // Handle exit event
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

                    // Show moves if true
                    if (fromSquare.pieceColor == (isLeftField ? WHITE : BLACK)) {

                        currentMoves = findCurrentPossibleMoves(currentField, fromSquare);

                        movesTexture.load(currentMoves, isLeftField);
                        showMoves = true;

                    } else { firstClickAccess = true; }
                } else {firstClickAccess = true;}
            } else {

                // Make move if true
                if (isCorrectMove(currentMoves, isLeftField, mousePosition)) {

                    toSquare = findSquareByCoordinates(currentField, isLeftField, mousePosition);
                    makeMove(leftField, rightField, isLeftField, fromSquare, toSquare);
                    showMoves = false;

                    chessTexture.load(leftField, rightField, container);

                    isLeftField = isLeftField ? false : true;
                    firstClickAccess = true;

                }
                else if (isCorrectClick(isLeftField, mousePosition)) {

                    fromSquare = findSquareByCoordinates(currentField, isLeftField, mousePosition);

                    // Show moves if true
                    if (fromSquare.pieceColor == (isLeftField ? WHITE : BLACK)) {
                        currentMoves = findCurrentPossibleMoves(currentField, fromSquare);

                        movesTexture.load(currentMoves, isLeftField);
                        showMoves = true;

                    }
                    // Hide moves
                    else {
                        showMoves = false;
                        firstClickAccess = true;
                    }
                }
                // Hide moves
                else {
                    showMoves = false;
                    firstClickAccess = true;
                }
            }
        }

        // Draw
        window.clear();
        window.draw(chessTexture);
        window.draw(coordsTexture);
        if (showMoves) window.draw(movesTexture);
        window.display();
    }

    return 0;
}
