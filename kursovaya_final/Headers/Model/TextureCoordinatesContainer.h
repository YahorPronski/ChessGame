#pragma once

#include <unordered_map>

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
                ROOK,
                KNIGHT,
                BISHOP,
                QUEEN,
                KING,
                PAWN
        };

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {

                SquareTexture squareTexture {
                        pieceNames[i],
                        j < 2 ? WHITE : BLACK,
                        j % 2 == 0 ? WHITE : BLACK
                };

                sf::Vector2f vector {fileSquareSize * j, fileSquareSize * i };

                std::pair<SquareTexture, sf::Vector2f> myPair(squareTexture, vector);
                textureCoordinatesMap.insert(myPair);
            }
        }

        // Белая пустая клетка
        SquareTexture emptySquareTextureWhite {NO_PIECE, NO_COLOR, WHITE};
        sf::Vector2f vectorWhite{fileSquareSize * 0, fileSquareSize * 7 };

        std::pair<SquareTexture, sf::Vector2f> myPairWhite(emptySquareTextureWhite, vectorWhite);
        textureCoordinatesMap.insert(myPairWhite);

        // Чёрная пустая клетка
        SquareTexture emptySquareTextureBlack {NO_PIECE, NO_COLOR, BLACK };
        sf::Vector2f vectorBlack {fileSquareSize * 1, fileSquareSize * 7 };

        std::pair<SquareTexture, sf::Vector2f> myPairBlack(emptySquareTextureBlack, vectorBlack);
        textureCoordinatesMap.insert(myPairBlack);
    }
};
