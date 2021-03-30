#include "../Headers/Model/Data.h"
#include "../Headers/Model/Moves.h"
#include "../Headers/ViewModel/OnClickHandling.h"
#include "../Headers/Model/TextureCoordinatesContainer.h"
#include "../Headers/View/Graphic.h"

#include <SFML/Audio.hpp>

// Доделать:
// Звуки
// Рокировка
// Таймер
// Проверка на мат
// Добавить текстуры координаты доски
// Превращение пешки
// Взятие на проходе


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
    CoordinatesTexture coordsTexture;
    BordersTexture fieldBordersTexture;
    MovesTexture movesTexture;

    if (!chessTexture.load(leftField, rightField, container)) return -1;
    if (!coordsTexture.load()) return -1;
    if (!fieldBordersTexture.load()) return -1;

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
        window.draw(fieldBordersTexture);
        if (showMoves) window.draw(movesTexture);
        window.display();

        sf::sleep(sf::milliseconds(40));
    }

    return 0;
}
