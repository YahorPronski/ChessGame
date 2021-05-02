#include "../Headers/Model/Data.h"
#include "../Headers/Model/Core.h"
#include "../Headers/Model/MovesFinders.h"
#include "../Headers/ViewModel/OnClickHandling.h"
#include "../Headers/Model/TextureCoordinatesContainer.h"
#include "../Headers/View/Graphic.h"
#include <string>

#include <SFML/Audio.hpp>
#include <sstream>

// Доделать:
// Звуки
// Рокировка
// Таймер
// Проверка на мат
// Добавить текстуры координаты доски
// Превращение пешки
// Взятие на проходе

std::string timeFormat(int time) {
    std::stringstream ss;
    if (time % 60 < 10 && time % 60 != 0) {
        ss << time / 60 << ":" << 0 << time % 60;
    } else {
        ss << time / 60 << ":" << time % 60;
    }
    if (time % 60 == 0) {
        ss << 0;
    }
    return ss.str();
}

int main()
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Chess");

    Square** leftField = createAndFillLeftField();
    Square** rightField = createAndFillRightField();

    bool firstClickAccess = true;
    bool isLeftField = true;
    bool showMoves = false;
    bool gameStarted = false;
    bool isWhitesMove = true;
    bool gameEnded = false;
    bool whiteWon;
    bool addFiveSeconds = false;
    bool somethingWasSelected = false;

    Options options;
    Button* currentlySelected = &options.fiveMinutes;
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

    sf::Font myFont;
    sf::Text win;
    Button restart = Button(squareSize * 10, squareSize * 11, squareSize * 2, squareSize / 2);
    sf::Text restartText;
    if (!myFont.loadFromFile(font)) {
        throw "Flaj";
    }
    int whiteCountdown = 300;
    int blackCountdown = 300;

    sf::Text whiteTimer;
    whiteTimer.setFont(myFont);
    whiteTimer.setPosition(squareSize * 4, squareSize * 10.5);
    whiteTimer.setString(timeFormat(whiteCountdown));
    whiteTimer.setCharacterSize(squareSize * 0.5);
    sf::Text blackTimer;
    blackTimer.setFont(myFont);
    blackTimer.setCharacterSize(squareSize * 0.5);
    blackTimer.setPosition(squareSize * 16, squareSize * 10.5);
    blackTimer.setString(timeFormat(blackCountdown));
    sf::Clock clock;

    // Run the main loop
    while (window.isOpen())
    {
        double elapsed = clock.getElapsedTime().asSeconds();
        // Handle exit event
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (gameStarted && !gameEnded) {
            if (clock.getElapsedTime().asSeconds() > 1) {
                if (whiteCountdown <= 0 || blackCountdown <= 0) {
                    gameEnded = true;
                    whiteWon = whiteCountdown > 0;
                } else {
                    if (isWhitesMove) {
                        whiteCountdown--;
                        whiteTimer.setString(timeFormat(whiteCountdown));
                        clock.restart();
                    } else {
                        blackCountdown--;
                        blackTimer.setString(timeFormat(blackCountdown));
                        clock.restart();
                    }
                }
            }
        }

        if (!gameEnded) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                //Button checking(game time selected)
                if (!gameStarted) {
                    if (options.oneMinute.isSelected(mousePosition)) {
                        (*currentlySelected).unselect();
                        currentlySelected = &options.oneMinute;
                        options.oneMinute.select();
                        whiteCountdown = blackCountdown = 60;
                        blackTimer.setString(timeFormat(blackCountdown));
                        whiteTimer.setString(timeFormat(whiteCountdown));
                        addFiveSeconds = false;
                    } else if (options.twoMinutes.isSelected(mousePosition)) {
                        (*currentlySelected).unselect();
                        currentlySelected = &options.twoMinutes;
                        (*currentlySelected).select();
                        whiteCountdown = blackCountdown = 120;
                        blackTimer.setString(timeFormat(blackCountdown));
                        whiteTimer.setString(timeFormat(whiteCountdown));
                        addFiveSeconds = false;
                    } else if (options.threeMinutes.isSelected(mousePosition)) {
                        (*currentlySelected).unselect();
                        currentlySelected = &options.threeMinutes;
                        (*currentlySelected).select();
                        whiteCountdown = blackCountdown = 180;
                        blackTimer.setString(timeFormat(blackCountdown));
                        whiteTimer.setString(timeFormat(whiteCountdown));
                        addFiveSeconds = false;
                    } else if (options.fiveMinutes.isSelected(mousePosition)) {
                        (*currentlySelected).unselect();
                        currentlySelected = &options.fiveMinutes;
                        (*currentlySelected).select();
                        whiteCountdown = blackCountdown = 300;
                        blackTimer.setString(timeFormat(blackCountdown));
                        whiteTimer.setString(timeFormat(whiteCountdown));
                        addFiveSeconds = false;
                    } else if (options.tenMinutes.isSelected(mousePosition)) {
                        (*currentlySelected).unselect();
                        currentlySelected = &options.tenMinutes;
                        (*currentlySelected).select();
                        whiteCountdown = blackCountdown = 600;
                        blackTimer.setString(timeFormat(blackCountdown));
                        whiteTimer.setString(timeFormat(whiteCountdown));
                        addFiveSeconds = false;
                    } else if (options.fifteenMinutes.isSelected(mousePosition)) {
                        (*currentlySelected).unselect();
                        currentlySelected = &options.fifteenMinutes;
                        (*currentlySelected).select();
                        whiteCountdown = blackCountdown = 900;
                        blackTimer.setString(timeFormat(blackCountdown));
                        whiteTimer.setString(timeFormat(whiteCountdown));
                        addFiveSeconds = false;
                    } else if (options.fivePlusFive.isSelected(mousePosition)) {
                        (*currentlySelected).unselect();
                        currentlySelected = &options.fivePlusFive;
                        (*currentlySelected).select();
                        whiteCountdown = blackCountdown = 300;
                        blackTimer.setString(timeFormat(blackCountdown));
                        whiteTimer.setString(timeFormat(whiteCountdown));
                        addFiveSeconds = true;
                    } else if (options.fifteenPlusFive.isSelected(mousePosition)) {
                        (*currentlySelected).unselect();
                        currentlySelected = &options.fifteenPlusFive;
                        (*currentlySelected).select();
                        whiteCountdown = blackCountdown = 900;
                        blackTimer.setString(timeFormat(blackCountdown));
                        whiteTimer.setString(timeFormat(whiteCountdown));
                        addFiveSeconds = true;
                    }
                }
                //
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

                        // Change action if mate
                        // Check for mate or stalemate (stalemate + check == mate)
                        if (isStaleMate(isLeftField ? rightField : leftField, isLeftField ? BLACK : WHITE)) {

                            if (isCheck(isLeftField ? rightField : leftField, isLeftField ? BLACK : WHITE)) {
                                // Mate action
                                if (isWhitesMove) {
                                    whiteWon = true;
                                }
                                gameEnded = true;
                            } else {
                                // Stalemate action
                                win.setString("Draw");
                                gameEnded = true;
                            }
                        }

                        isLeftField = isLeftField ? false : true;
                        firstClickAccess = true;
                        //timer.stop
                        gameStarted = true;
                        if (addFiveSeconds && gameStarted) {
                            if (!isWhitesMove) {
                                blackCountdown += 5;
                                blackTimer.setString(timeFormat(blackCountdown));
                            } else {
                                whiteCountdown += 5;
                                whiteTimer.setString(timeFormat(whiteCountdown));
                            }
                        }
                        isWhitesMove = !isWhitesMove;
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
        } else {
            win.setFont(myFont);
            if (win.getString() == "") {
                win.setString(whiteWon ? "White won" : "Black won");
            }
            win.setCharacterSize(squareSize * 0.6);
            win.setPosition(squareSize * 10, squareSize * 10);
            restartText.setFont(myFont);
            restartText.setString("Restart");
            restartText.setCharacterSize(squareSize * 0.35);
            restartText.setPosition(squareSize*10 + squareSize / 5, squareSize * 11);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (restart.isSelected(mousePosition)) {
                    main();
                    return 0;
                }
            }
        }
        // Draw
        window.clear();
        window.draw(chessTexture);
        window.draw(coordsTexture);
        window.draw(fieldBordersTexture);
        window.draw(options);
        window.draw(whiteTimer);
        window.draw(blackTimer);
        if (gameEnded)  {
            window.draw(win);
            window.draw(restart.displayButton());
            window.draw(restartText);
        }
        if (showMoves) window.draw(movesTexture);
        window.display();
        sf::sleep(sf::milliseconds(10));
    }

    return 0;
}


