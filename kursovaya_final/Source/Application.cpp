#include "Moves.h"
#include "Data.h"
#include "Values.h"
#include "OnClickHandler.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map> 
#include <map>

// TODO
// Рокировка
// Взятие на проходе
// Проверка на шах
// Проверка на мат

struct SquareTexture {
    PieceName pieceName;
    PieceColor pieceColor;
    PieceColor colorOfSquare;

    bool operator==(const SquareTexture& squareTexture) const {
        return this->pieceName == squareTexture.pieceName &&
            this->pieceColor == squareTexture.pieceColor &&
            this->colorOfSquare == squareTexture.colorOfSquare;
    }
};

class KeyHasher {
public:

    size_t operator()(const SquareTexture& squareTexture) const{
        int result = 1;
        result = 31 * result + squareTexture.pieceName;
        result = 31 * result + squareTexture.pieceColor;
        result = 31 * result + squareTexture.colorOfSquare;
        return result;
    }
};

class TextureCoordinatesContainer {
public:

    TextureCoordinatesContainer() {
        initMap();
    }

    sf::Vector2f find(SquareTexture squareTexture) {
       return textureCoordinatesMap.at(squareTexture);
    }

private:
    // Хранит координаты левого верхнего угла текстур всех фигур и клеткок
    std::unordered_map<SquareTexture, sf::Vector2f, KeyHasher> textureCoordinatesMap;

    // Кол-во нужных строк и столбцов в файле с текстурами
    const static int rows = 6;
    const static int columns = 4;

    void initMap() {

        // Заполняем массив в порядке расположения фигур в файле (сверху вниз)
        PieceName pieceNames[rows] = {
            ROCK,
            KNIGHT,
            BISHOP,
            QUEEN,
            KING,
            PAWN
        };

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {

                SquareTexture squareTexture{
                    pieceNames[i],
                    j < 2 ? WHITE : BLACK,
                    j % 2 == 0 ? WHITE : BLACK
                };

                sf::Vector2f vector{ fileTextureSquareScale * j, fileTextureSquareScale * i };

                std::pair<SquareTexture, sf::Vector2f> myPair(squareTexture, vector);
                textureCoordinatesMap.insert(myPair);
            }
        }

        // Белая пустая клетка
        SquareTexture squareTextureWhitePawn{NO_PIECE, NO_COLOR, WHITE};
        sf::Vector2f vectorWhite{ fileTextureSquareScale * 0, fileTextureSquareScale * 8 };

        std::pair<SquareTexture, sf::Vector2f> myPairWhite(squareTextureWhitePawn, vectorWhite);
        textureCoordinatesMap.insert(myPairWhite);

        // Чёрная пустая клетка
        SquareTexture squareTextureBlackPawn{ NO_PIECE, NO_COLOR, BLACK };
        sf::Vector2f vectorBlack{ fileTextureSquareScale * 1, fileTextureSquareScale * 8 };

        std::pair<SquareTexture, sf::Vector2f> myPairBlack(squareTextureBlackPawn, vectorBlack);
        textureCoordinatesMap.insert(myPairBlack);
    }
};

class ChessBoard : public sf::Drawable, public sf::Transformable
{
public:
    int amountOfQuads = 8 * 8 * 4 * 2 + (8 * 4) * 16;

    bool load(const std::string& textureFilePath,
        Square** leftField,
        Square** rightField,
        std::map<short, short> possibleMoves,
        TextureCoordinatesContainer container) { 

        // Скачиваем файл с текстурами 
        if (!textureFile.loadFromFile(textureFilePath))
            return false;

        vertices.setPrimitiveType(sf::Quads);
        vertices.resize(amountOfQuads);

        // Рисуем левое поле
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {

                sf::Vertex* quad = &vertices[(j + i * 8) * 4];

                quad[0].position = sf::Vector2f((j + 1) * squareSize, (i + 1) * squareSize);
                quad[1].position = sf::Vector2f((j + 2) * squareSize, (i + 1) * squareSize);
                quad[2].position = sf::Vector2f((j + 2) * squareSize, (i + 2) * squareSize);
                quad[3].position = sf::Vector2f((j + 1) * squareSize, (i + 2) * squareSize);

                SquareTexture squareTexture = { 
                    leftField[i][j].pieceName, 
                    leftField[i][j].pieceColor,
                    leftField[i][j].colorOfSquare };

                // Ищем координаты нужной клетки (в файле с текстурой)
                sf::Vector2f coordinates = container.find(squareTexture);

                quad[0].texCoords = sf::Vector2f(coordinates.x, coordinates.y);
                quad[1].texCoords = sf::Vector2f(coordinates.x + fileTextureSquareScale, coordinates.y);
                quad[2].texCoords = sf::Vector2f(coordinates.x + fileTextureSquareScale, coordinates.y + fileTextureSquareScale);
                quad[3].texCoords = sf::Vector2f(coordinates.x, coordinates.y + fileTextureSquareScale);
            }
        }

        // Рисуем правое поле
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {

                sf::Vertex* quad = &vertices[(j + i * 8) * 4 + 8 * 8 * 4];

                quad[0].position = sf::Vector2f((j + 1) * squareSize + spaceBetweenFields + squareSize * 8, (i + 1) * squareSize);
                quad[1].position = sf::Vector2f((j + 2) * squareSize + spaceBetweenFields + squareSize * 8, (i + 1) * squareSize);
                quad[2].position = sf::Vector2f((j + 2) * squareSize + spaceBetweenFields + squareSize * 8, (i + 2) * squareSize);
                quad[3].position = sf::Vector2f((j + 1) * squareSize + spaceBetweenFields + squareSize * 8, (i + 2) * squareSize);

                SquareTexture squareTexture = {
                    rightField[i][j].pieceName,
                    rightField[i][j].pieceColor,
                    rightField[i][j].colorOfSquare };

                // Ищем координаты нужной клетки (в файле с текстурой)
                sf::Vector2f coordinates = container.find(squareTexture);

                quad[0].texCoords = sf::Vector2f(coordinates.x, coordinates.y);
                quad[1].texCoords = sf::Vector2f(coordinates.x + fileTextureSquareScale, coordinates.y);
                quad[2].texCoords = sf::Vector2f(coordinates.x + fileTextureSquareScale, coordinates.y + fileTextureSquareScale);
                quad[3].texCoords = sf::Vector2f(coordinates.x, coordinates.y + fileTextureSquareScale);
            }
        }


        std::map<short, short>::iterator it = possibleMoves.begin();

        for (int i = 0; it != possibleMoves.end(); it++, i++) { 

            sf::Vertex* quad = &vertices[(i * 16) + 8 * 8 * 4 * 2];

            quad[0].position = sf::Vector2f((it->second + 1) * squareSize + 0.02f * squareSize, (it->first + 1) * squareSize + 0.02f * squareSize);
            quad[1].position = sf::Vector2f((it->second + 1) * squareSize + squareSize - 0.02f * squareSize, (it->first + 1) * squareSize + 0.02f * squareSize);
            quad[2].position = sf::Vector2f((it->second + 1) * squareSize + squareSize - 0.02f * squareSize, (it->first + 1) * squareSize + squareSize * 0.07f - 0.02f * squareSize);
            quad[3].position = sf::Vector2f((it->second + 1) * squareSize + 0.02f * squareSize, (it->first + 1) * squareSize + squareSize * 0.07f - 0.02f * squareSize);

            quad[4].position = sf::Vector2f((it->second + 1) * squareSize + squareSize * 0.95f, (it->first + 1) * squareSize + 0.02f * squareSize);
            quad[5].position = sf::Vector2f((it->second + 1) * squareSize + squareSize - 0.02f * squareSize, (it->first + 1) * squareSize + 0.02f * squareSize);
            quad[6].position = sf::Vector2f((it->second + 1) * squareSize + squareSize - 0.02f * squareSize, (it->first + 1) * squareSize + squareSize - 0.02f * squareSize);
            quad[7].position = sf::Vector2f((it->second + 1) * squareSize + squareSize * 0.95f, (it->first + 1) * squareSize + squareSize - 0.02f * squareSize);

            quad[8].position = sf::Vector2f((it->second + 1) * squareSize + 0.02f * squareSize, (it->first + 1) * squareSize + squareSize * 0.95f);
            quad[9].position = sf::Vector2f((it->second + 1) * squareSize + squareSize - 0.02f * squareSize, (it->first + 1) * squareSize + squareSize * 0.95f);
            quad[10].position = sf::Vector2f((it->second + 1) * squareSize + squareSize - 0.02f * squareSize, (it->first + 1) * squareSize + squareSize - 0.02f * squareSize);
            quad[11].position = sf::Vector2f((it->second + 1) * squareSize + 0.02f * squareSize, (it->first + 1) * squareSize + squareSize - 0.02f * squareSize);

            quad[12].position = sf::Vector2f((it->second + 1) * squareSize + 0.02f * squareSize, (it->first + 1) * squareSize + 0.02f * squareSize);
            quad[13].position = sf::Vector2f((it->second + 1) * squareSize + squareSize * 0.05f, (it->first + 1) * squareSize + 0.02f * squareSize);
            quad[14].position = sf::Vector2f((it->second + 1) * squareSize + squareSize * 0.05f, (it->first + 1) * squareSize + squareSize - 0.02f * squareSize);
            quad[15].position = sf::Vector2f((it->second + 1) * squareSize + 0.02f * squareSize, (it->first + 1) * squareSize + squareSize - 0.02f * squareSize);

            for (int j = 0; j < 16; j++) {
                quad[j].color = sf::Color::Red;
            }
        }
           
        return true;
}

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the texture
        states.texture = &textureFile;

        // draw the vertex array
        target.draw(vertices, states);
    }

    sf::VertexArray vertices;
    sf::Texture textureFile;
};





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

void printCoords(Square** field) {
    std::cout << "=======\n";
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << "(" << field[i][j].i << ", " << field[i][j].j << ")" << field[i][j].pieceName << "   ";
        }
        std::cout << std::endl;
    }
    std::cout << "=======\n";
}

int main()
{
    float windowWidth = squareSize * 9 + spaceBetweenFields + squareSize * 9;
    float windowHeight = squareSize * 10;
    // create the window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Chess");

    Square** leftField = createAndFillLeftField();
    Square** rightField = createAndFillRightField();

    Square fromSq;
    Square toSq;

    sf::Vector2f clickedPos;
    clickedPos.x = 0;
    clickedPos.y = 0;

    sf::Vector2f clickedPos2;
    clickedPos2.x = 0;
    clickedPos2.y = 0;

    bool firstClickAccess = true;

    bool clickAccess = true;

    Square tmp;

    bool leftFieldOrderMove = true;

    TextureCoordinatesContainer container;

    std::map<short, short> mp;

    ChessBoard chess;
    if (!chess.load(textureFilePath, leftField, rightField, mp, container))
        return -1;

    printCoords(leftField);

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

        if (clickAccess) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                clickAccess = false;

                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                Square** currentField = leftFieldOrderMove ? leftField : rightField;

                if (firstClickAccess) {
                    firstClickAccess = false;

                    mp = onFirstClick(currentField, leftFieldOrderMove, mousePosition);

                    if (mp.size() != 0) {
                        chess.load(textureFilePath , leftField, rightField, mp, container);
                        firstClickAccess = true;
                    }
                    else {
                        firstClickAccess = true;
                    }
                }
                else {

                   
                    

                }
                clickAccess = true;
            }
        }

        // draw the map
        window.clear();
        window.draw(chess);
        window.display();
    }

    return 0;
}
