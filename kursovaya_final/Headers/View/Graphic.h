#pragma once
#include "../../Headers/Model/Data.h"

#include <SFML/Graphics.hpp>

class ChessTexture : public sf::Drawable, public sf::Transformable
{
public:

    bool load(Square** leftField,
              Square** rightField,
              TextureCoordinatesContainer container) {

        // Скачиваем файл с текстурами
        if (!textureFile.loadFromFile(textureFilePath))
            return false;

        vertices.setPrimitiveType(sf::Quads);
        vertices.resize(8 * 8 * 4 * 2);

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
                quad[1].texCoords = sf::Vector2f(coordinates.x + fileSquareSize, coordinates.y);
                quad[2].texCoords = sf::Vector2f(coordinates.x + fileSquareSize, coordinates.y + fileSquareSize);
                quad[3].texCoords = sf::Vector2f(coordinates.x, coordinates.y + fileSquareSize);
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
                quad[1].texCoords = sf::Vector2f(coordinates.x + fileSquareSize, coordinates.y);
                quad[2].texCoords = sf::Vector2f(coordinates.x + fileSquareSize, coordinates.y + fileSquareSize);
                quad[3].texCoords = sf::Vector2f(coordinates.x, coordinates.y + fileSquareSize);
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

/*class ChessCoordinatesTexture : public sf::Drawable, public sf::Transformable
{
public:

    bool load(Square** leftField,
              Square** rightField,
              TextureCoordinatesContainer container) {

        // Скачиваем файл с текстурами
        if (!textureFile.loadFromFile(textureFilePath))
            return false;

        vertices.setPrimitiveType(sf::Quads);
        vertices.resize(8 * 4 * 4);

        // Рисуем координаты (буквы) для левого поля
        for (int i = 0; i < 8; i++) {
                sf::Vertex* quad = &vertices[i * 4];

                quad[0].position = sf::Vector2f(squareSize * (2.f / 3.f) , (i + 1) * squareSize);
                quad[1].position = sf::Vector2f(squareSize, (i + 1) * squareSize);
                quad[2].position = sf::Vector2f(squareSize, (i + 2) * squareSize);
                quad[3].position = sf::Vector2f(squareSize * (2.f / 3.f), (i + 2) * squareSize);

                quad[0].texCoords = sf::Vector2f(fileSquareSize * , coordinates.y);
                quad[1].texCoords = sf::Vector2f(coordinates.x + fileSquareSize, coordinates.y);
                quad[2].texCoords = sf::Vector2f(coordinates.x + fileSquareSize, coordinates.y + fileSquareSize);
                quad[3].texCoords = sf::Vector2f(coordinates.x, coordinates.y + fileSquareSize);
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
                quad[1].texCoords = sf::Vector2f(coordinates.x + fileSquareSize, coordinates.y);
                quad[2].texCoords = sf::Vector2f(coordinates.x + fileSquareSize, coordinates.y + fileSquareSize);
                quad[3].texCoords = sf::Vector2f(coordinates.x, coordinates.y + fileSquareSize);
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
};*/

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
                quad[j].color = sf::Color::Magenta;
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


class CoordinatesTexture : public sf::Drawable, public sf::Transformable
{
public:

    bool load() {

        // Скачиваем файл с текстурами
        if (!textureFile.loadFromFile(textureFilePath))
            return false;

        vertices.setPrimitiveType(sf::Quads);
        vertices.resize(8 * 4 * 4);


        // Drawing digits for left field
        for (int i = 0; i < 8; i++) {

            sf::Vertex *quad = &vertices[i * 4];

            quad[0].position = sf::Vector2f(squareSize * (2.f/3.f), squareSize*(i+1));
            quad[1].position = sf::Vector2f(squareSize, squareSize*(i+1));
            quad[2].position = sf::Vector2f(squareSize, squareSize*(i+2));
            quad[3].position = sf::Vector2f(squareSize * (2.f/3.f), squareSize*(i+2));

            quad[0].texCoords = sf::Vector2f(fileSquareSize * (5 + 2.f/3.f), fileSquareSize * (7 - i));
            quad[1].texCoords = sf::Vector2f(fileSquareSize * (6), fileSquareSize * (7 - i));
            quad[2].texCoords = sf::Vector2f(fileSquareSize * (6), fileSquareSize * (8 - i));
            quad[3].texCoords = sf::Vector2f(fileSquareSize * (5 + 2.f / 3.f), fileSquareSize * (8 - i));

        }

        // Drawing letters for left field
        for (int i = 0; i < 8; i++) {

            sf::Vertex *quad = &vertices[i * 4 + 8 * 4];

            quad[0].position = sf::Vector2f(squareSize*(i + 1), 9 * squareSize);
            quad[1].position = sf::Vector2f(squareSize*(i + 2), 9 * squareSize);
            quad[2].position = sf::Vector2f(squareSize*(i + 2), 10 * squareSize);
            quad[3].position = sf::Vector2f(squareSize*(i + 1), 10 * squareSize);

            quad[0].texCoords = sf::Vector2f(fileSquareSize * (4), fileSquareSize * (i));
            quad[1].texCoords = sf::Vector2f(fileSquareSize * (5), fileSquareSize * (i));
            quad[2].texCoords = sf::Vector2f(fileSquareSize * (5), fileSquareSize * (i + 1));
            quad[3].texCoords = sf::Vector2f(fileSquareSize * (4), fileSquareSize * (i + 1));

        }

        // Drawing digits for right field
        for (int i = 0; i < 8; i++) {

            sf::Vertex *quad = &vertices[i * 4 + 8 * 4 * 2];

            quad[0].position = sf::Vector2f(squareSize * 17  + spaceBetweenFields, squareSize*(i+1));
            quad[1].position = sf::Vector2f(squareSize * (17 + 1.f / 3.f)  + spaceBetweenFields, squareSize*(i+1));
            quad[2].position = sf::Vector2f(squareSize * (17 + 1.f / 3.f)  + spaceBetweenFields, squareSize*(i+2));
            quad[3].position = sf::Vector2f(squareSize * 17 + spaceBetweenFields, squareSize*(i+2));

            quad[0].texCoords = sf::Vector2f(fileSquareSize * (5 + 2.f/3.f), fileSquareSize * (i));
            quad[1].texCoords = sf::Vector2f(fileSquareSize * (6), fileSquareSize * (i));
            quad[2].texCoords = sf::Vector2f(fileSquareSize * (6), fileSquareSize * (i + 1));
            quad[3].texCoords = sf::Vector2f(fileSquareSize * (5 + 2.f/3.f), fileSquareSize * (i + 1));

        }

        // Drawing letters for right field
        for (int i = 0; i < 8; i++) {

            sf::Vertex *quad = &vertices[i * 4 + 8 * 4 * 3];

            quad[0].position = sf::Vector2f(squareSize*(i + 9) + spaceBetweenFields , 9 * squareSize);
            quad[1].position = sf::Vector2f(squareSize*(i + 10) + spaceBetweenFields, 9 * squareSize);
            quad[2].position = sf::Vector2f(squareSize*(i + 10) + spaceBetweenFields, 10 * squareSize);
            quad[3].position = sf::Vector2f(squareSize*(i + 9) + spaceBetweenFields, 10 * squareSize);

            quad[0].texCoords = sf::Vector2f(fileSquareSize * (4), fileSquareSize * (7 - i));
            quad[1].texCoords = sf::Vector2f(fileSquareSize * (5), fileSquareSize * (7 - i));
            quad[2].texCoords = sf::Vector2f(fileSquareSize * (5), fileSquareSize * (8 - i));
            quad[3].texCoords = sf::Vector2f(fileSquareSize * (4), fileSquareSize * (8 - i));

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
