#pragma once

#include <iostream>
#include <SFML/Window.hpp>
enum PieceName {
	KING,
	QUEEN,
	BISHOP,
	KNIGHT,
	ROOK,
	PAWN,
	NO_PIECE
};

enum PieceColor {
	WHITE,
	BLACK,
	NO_COLOR
};

const float squareSize = sf::VideoMode::getDesktopMode().width / 22;
const float spaceBetweenFields = squareSize * 4;
const float fileSquareSize = 128;

//const int windowWidth = squareSize * 9 + spaceBetweenFields + squareSize * 9;
const int windowWidth = sf::VideoMode::getDesktopMode().width;
const int windowHeight = sf::VideoMode::getDesktopMode().height;
//const int windowHeight = squareSize * 10;

// for field's boarders
const float thickness = squareSize / 15.f;
const float margin = thickness * 0.4f;

const std::string textureFilePath = "resource//chess_orange_theme.jpg";
const std::string coordsTextureFilePath = "resource//coords_texture.jpg";
