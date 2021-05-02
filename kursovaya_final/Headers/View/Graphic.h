#pragma once

#include "../../Headers/Model/Data.h"
#include "Button.hpp"
#include "../../resource/Values.h"
#include <SFML/Graphics.hpp>

class ChessTexture : public sf::Drawable, public sf::Transformable
{
public:

    bool load(Square** leftField,
              Square** rightField,
              TextureCoordinatesContainer container) {

        // Скачиваем файл с текстурами
        if (!texture.loadFromFile(textureFilePath))
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
        states.texture = &texture;

        // draw the vertex array
        target.draw(vertices, states);
    }

    sf::VertexArray vertices;
    sf::Texture texture;
};

class CoordinatesTexture : public sf::Drawable, public sf::Transformable
{
public:

    bool load() {

        // Скачиваем файл с текстурами
        if (!texture.loadFromFile(coordsTextureFilePath))
            return false;

        vertices.setPrimitiveType(sf::Quads);
        vertices.resize(8 * 4 * 4);

        // Drawing digits for left field
        for (int i = 0; i < 8; i++) {

            sf::Vertex *quad = &vertices[i * 4];

            float padding = 5.f;
            float offset = padding + margin + thickness;

            quad[0].position = sf::Vector2f(squareSize * (1.f / 3.f) - offset, squareSize*(i+1));
            quad[1].position = sf::Vector2f(squareSize - offset, squareSize*(i+1));
            quad[2].position = sf::Vector2f(squareSize - offset, squareSize*(i+2));
            quad[3].position = sf::Vector2f(squareSize * (1.f / 3.f) - offset, squareSize*(i+2));

            quad[0].texCoords = sf::Vector2f(fileSquareSize * (7 - i), fileSquareSize);
            quad[1].texCoords = sf::Vector2f(fileSquareSize * (8 - i - 1.f / 3.f), fileSquareSize);
            quad[2].texCoords = sf::Vector2f(fileSquareSize * (8 - i - 1.f / 3.f), fileSquareSize * 2);
            quad[3].texCoords = sf::Vector2f(fileSquareSize * (7 - i), fileSquareSize * 2);

        }

        // Drawing letters for left field
        for (int i = 0; i < 8; i++) {

            sf::Vertex *quad = &vertices[i * 4 + 8 * 4];

            float offset = margin + thickness;

            quad[0].position = sf::Vector2f(squareSize*(i + 1), 9 * squareSize + offset);
            quad[1].position = sf::Vector2f(squareSize*(i + 2), 9 * squareSize + offset);
            quad[2].position = sf::Vector2f(squareSize*(i + 2), 10 * squareSize + offset);
            quad[3].position = sf::Vector2f(squareSize*(i + 1), 10 * squareSize + offset);

            quad[0].texCoords = sf::Vector2f(fileSquareSize * i, 0);
            quad[1].texCoords = sf::Vector2f(fileSquareSize * (i + 1), 0);
            quad[2].texCoords = sf::Vector2f(fileSquareSize * (i + 1), fileSquareSize);
            quad[3].texCoords = sf::Vector2f(fileSquareSize * i, fileSquareSize);

        }

        // Drawing digits for right field
        for (int i = 0; i < 8; i++) {

            sf::Vertex *quad = &vertices[i * 4 + 8 * 4 * 2];

            float padding = 5.f;
            float offset = squareSize * 9 + spaceBetweenFields + squareSize * 8 + padding + margin + thickness;

            quad[0].position = sf::Vector2f(offset, squareSize*(i+1));
            quad[1].position = sf::Vector2f(squareSize * (2.f / 3.f) + offset, squareSize*(i+1));
            quad[2].position = sf::Vector2f(squareSize * (2.f / 3.f) + offset, squareSize*(i+2));
            quad[3].position = sf::Vector2f(offset, squareSize*(i+2));

            quad[0].texCoords = sf::Vector2f(fileSquareSize * (i + 1.f / 3.f), fileSquareSize);
            quad[1].texCoords = sf::Vector2f(fileSquareSize * (i + 1), fileSquareSize);
            quad[2].texCoords = sf::Vector2f(fileSquareSize * (i + 1), fileSquareSize * 2);
            quad[3].texCoords = sf::Vector2f(fileSquareSize * (i + 1.f / 3.f), fileSquareSize * 2);

        }

        // Drawing letters for right field
        for (int i = 0; i < 8; i++) {

            sf::Vertex *quad = &vertices[i * 4 + 8 * 4 * 3];

            quad[0].position = sf::Vector2f(squareSize*(i + 9) + spaceBetweenFields , 9 * squareSize + margin + thickness );
            quad[1].position = sf::Vector2f(squareSize*(i + 10) + spaceBetweenFields, 9 * squareSize + margin + thickness);
            quad[2].position = sf::Vector2f(squareSize*(i + 10) + spaceBetweenFields, 10 * squareSize + margin + thickness);
            quad[3].position = sf::Vector2f(squareSize*(i + 9) + spaceBetweenFields, 10 * squareSize + margin + thickness);

            quad[0].texCoords = sf::Vector2f(fileSquareSize * (7 - i), 0);
            quad[1].texCoords = sf::Vector2f(fileSquareSize * (8 - i), 0);
            quad[2].texCoords = sf::Vector2f(fileSquareSize * (8 - i), fileSquareSize);
            quad[3].texCoords = sf::Vector2f(fileSquareSize * (7 - i), fileSquareSize);

        }

        return true;
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the texture
        states.texture = &texture;

        // draw the vertex array
        target.draw(vertices, states);
    }

    sf::VertexArray vertices;
    sf::Texture texture;
};

class Options: public sf::Drawable {
public:
    Button oneMinute = Button(10*squareSize, squareSize * 1.5, squareSize * 2, squareSize * 0.75);
    Button twoMinutes = Button(10*squareSize, squareSize * 2.25, squareSize * 2, squareSize * 0.75);
    Button threeMinutes = Button(10*squareSize, squareSize * 3, squareSize * 2, squareSize * 0.75);
    Button fiveMinutes = Button(10*squareSize, squareSize * 3.75, squareSize * 2, squareSize * 0.75);
    Button tenMinutes = Button(10*squareSize, squareSize * 4.5, squareSize * 2, squareSize * 0.75);
    Button fifteenMinutes = Button(10*squareSize, squareSize * 5.25, squareSize * 2, squareSize * 0.75);
    Button fivePlusFive = Button(10*squareSize, squareSize * 6, squareSize * 2, squareSize * 0.75);
    Button fifteenPlusFive = Button(10*squareSize, squareSize * 6.75, squareSize * 2, squareSize * 0.75);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        sf::Font myFont;
        if (!myFont.loadFromFile(font)) {
            throw "Can't load";
        }
        // one minute
        sf::Text one;
        one.setString("1 minute");
        one.setPosition(10 * squareSize + squareSize / 8, squareSize * 1.5 + squareSize / 4);
        one.setCharacterSize(squareSize * 0.35);
        one.setFont(myFont);
        // 2 minutes
        sf::Text two;
        two.setString("2 minutes");
        two.setPosition(10 * squareSize + squareSize / 8, squareSize * 2.25 + squareSize / 4);
        two.setCharacterSize(squareSize * 0.35);
        two.setFont(myFont);
        // 3 minutes
        sf::Text three;
        three.setString("3 minutes");
        three.setCharacterSize(squareSize * 0.35);
        three.setPosition(10 * squareSize + squareSize / 8, squareSize * 3 + squareSize / 4);
//        three.scale(1.9, 1.9);
        three.setFont(myFont);
        // 5
        sf::Text five = three;
        five.setString("5 minutes");
        five.setPosition(10 * squareSize + squareSize / 8, squareSize * 3.75 + squareSize / 4);
        //10
        sf::Text ten = three;
        ten.setString("10 minutes");
        ten.setPosition(10 * squareSize + squareSize / 8, squareSize * 4.5 + squareSize / 4);
        // 15
        sf::Text fifteen = three;
        fifteen.setString("15 minutes");
        fifteen.setPosition(10 * squareSize + squareSize / 8, squareSize * 5.25 + squareSize / 4);
        // 5 | 5
        sf::Text fivePlusFiveMin = three;
        fivePlusFiveMin.setString("5 | 5 min.");
        fivePlusFiveMin.setPosition(10 * squareSize + squareSize / 8, squareSize * 6 + squareSize / 4);
        // 15 | 5
        sf::Text fifteenPlusFiveMin = three;
        fifteenPlusFiveMin.setString("15 | 5 min.");
        fifteenPlusFiveMin.setPosition(10 * squareSize + squareSize / 8, squareSize * 6.75 + squareSize / 4);
        //
        target.draw(oneMinute.displayButton());
        target.draw(twoMinutes.displayButton());
        target.draw(threeMinutes.displayButton());
        target.draw(fiveMinutes.displayButton());
        target.draw(tenMinutes.displayButton());
        target.draw(fifteenMinutes.displayButton());
        target.draw(fivePlusFive.displayButton());
        target.draw(fifteenPlusFive.displayButton());
        //drawing text
        target.draw(one);
        target.draw(two);
        target.draw(three);
        target.draw(five);
        target.draw(ten);
        target.draw(fifteen);
        target.draw(fivePlusFiveMin);
        target.draw(fifteenPlusFiveMin);
    }
};

class BordersTexture : public sf::Drawable, public sf::Transformable
{
public:

    bool load() {

        vertices.setPrimitiveType(sf::Quads);
        vertices.resize( 8 * 4 * 4 + 16 * 2);

        for (int i = 0; i < 2; i++) {
            sf::Vertex *quad = &vertices[i * 16];

            float offset = i == 0 ? 0 : squareSize * 8 + spaceBetweenFields;

            quad[0].position = sf::Vector2f(squareSize - margin - thickness + offset, squareSize - margin - thickness);
            quad[1].position = sf::Vector2f(squareSize * 9 + margin + offset, squareSize - margin - thickness);
            quad[2].position = sf::Vector2f(squareSize * 9 + margin + offset, squareSize - margin);
            quad[3].position = sf::Vector2f(squareSize - margin - thickness + offset, squareSize - margin);

            quad[4].position = sf::Vector2f(squareSize * 9 + margin + offset, squareSize - margin - thickness);
            quad[5].position = sf::Vector2f(squareSize * 9 + margin + thickness + offset, squareSize - margin - thickness);
            quad[6].position = sf::Vector2f(squareSize * 9 + margin + thickness + offset, squareSize * 9 + margin);
            quad[7].position = sf::Vector2f(squareSize * 9 + margin + offset, squareSize * 9 + margin);

            quad[8].position = sf::Vector2f(squareSize - margin + offset, squareSize * 9 + margin);
            quad[9].position = sf::Vector2f(squareSize * 9 + margin + thickness + offset, squareSize * 9 + margin);
            quad[10].position = sf::Vector2f(squareSize * 9 + margin + thickness + offset, squareSize * 9 + margin + thickness);
            quad[11].position = sf::Vector2f(squareSize - margin + offset, squareSize * 9 + margin + thickness);

            quad[12].position = sf::Vector2f(squareSize - margin - thickness + offset, squareSize - margin);
            quad[13].position = sf::Vector2f(squareSize - margin + offset, squareSize - margin);
            quad[14].position = sf::Vector2f(squareSize - margin + offset, squareSize * 9 + margin + thickness);
            quad[15].position = sf::Vector2f(squareSize - margin - thickness + offset, squareSize * 9 + margin + thickness);

            for (int j = 0; j < 16; j++) {
                quad[j].color = sf::Color::White;
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
                quad[j].color = sf::Color::Blue;
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


