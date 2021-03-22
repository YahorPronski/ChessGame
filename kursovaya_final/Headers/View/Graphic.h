#pragma once
#include "../../Headers/Model/Data.h"

#include <SFML/Graphics.hpp>

class ChessTexture : public sf::Drawable, public sf::Transformable
{
public:
    int amountOfQuads = 8 * 8 * 4 * 2;

    bool load(Square** leftField,
              Square** rightField,
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


class MovesTexture : public sf::Drawable, public sf::Transformable
{
public:

    bool load(std::vector<sf::Vector2<short>> possibleMoves, bool isLeft) {

        vertices.setPrimitiveType(sf::Quads);
        vertices.resize(possibleMoves.size() * 16);

        float offset = isLeft ? 0 : squareSize * 8 + spaceBetweenFields;

        auto it = possibleMoves.begin();
        for (int i = 0; it != possibleMoves.end(); it++, i++) {

            sf::Vertex *quad = &vertices[i * 16];

            quad[0].position = sf::Vector2f((it->x + 1) * squareSize + 0.02f * squareSize + offset,
                                            (it->y + 1) * squareSize + 0.02f * squareSize);
            quad[1].position = sf::Vector2f((it->x + 1) * squareSize + squareSize - 0.02f * squareSize + offset,
                                            (it->y + 1) * squareSize + 0.02f * squareSize);
            quad[2].position = sf::Vector2f((it->x + 1) * squareSize + squareSize - 0.02f * squareSize + offset,
                                            (it->y + 1) * squareSize + squareSize * 0.07f - 0.02f * squareSize);
            quad[3].position = sf::Vector2f((it->x + 1) * squareSize + 0.02f * squareSize + offset,
                                            (it->y + 1) * squareSize + squareSize * 0.07f - 0.02f * squareSize);

            quad[4].position = sf::Vector2f((it->x + 1) * squareSize + squareSize * 0.95f + offset,
                                            (it->y + 1) * squareSize + 0.02f * squareSize);
            quad[5].position = sf::Vector2f((it->x + 1) * squareSize + squareSize - 0.02f * squareSize + offset,
                                            (it->y + 1) * squareSize + 0.02f * squareSize);
            quad[6].position = sf::Vector2f((it->x + 1) * squareSize + squareSize - 0.02f * squareSize + offset,
                                            (it->y + 1) * squareSize + squareSize - 0.02f * squareSize);
            quad[7].position = sf::Vector2f((it->x + 1) * squareSize + squareSize * 0.95f + offset,
                                            (it->y + 1) * squareSize + squareSize - 0.02f * squareSize);

            quad[8].position = sf::Vector2f((it->x + 1) * squareSize + 0.02f * squareSize + offset,
                                            (it->y + 1) * squareSize + squareSize * 0.95f);
            quad[9].position = sf::Vector2f((it->x + 1) * squareSize + squareSize - 0.02f * squareSize + offset,
                                            (it->y + 1) * squareSize + squareSize * 0.95f);
            quad[10].position = sf::Vector2f((it->x + 1) * squareSize + squareSize - 0.02f * squareSize + offset,
                                             (it->y + 1) * squareSize + squareSize - 0.02f * squareSize);
            quad[11].position = sf::Vector2f((it->x + 1) * squareSize + 0.02f * squareSize + offset,
                                             (it->y + 1) * squareSize + squareSize - 0.02f * squareSize);

            quad[12].position = sf::Vector2f((it->x + 1) * squareSize + 0.02f * squareSize + offset,
                                             (it->y + 1) * squareSize + 0.02f * squareSize);
            quad[13].position = sf::Vector2f((it->x + 1) * squareSize + squareSize * 0.05f + offset,
                                             (it->y + 1) * squareSize + 0.02f * squareSize);
            quad[14].position = sf::Vector2f((it->x + 1) * squareSize + squareSize * 0.05f + offset,
                                             (it->y + 1) * squareSize + squareSize - 0.02f * squareSize);
            quad[15].position = sf::Vector2f((it->x + 1) * squareSize + 0.02f * squareSize + offset,
                                             (it->y + 1) * squareSize + squareSize - 0.02f * squareSize);

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

        // don't need a texture
        states.texture = nullptr;

        // draw the vertex array
        target.draw(vertices, states);
    }

    sf::VertexArray vertices;
};
