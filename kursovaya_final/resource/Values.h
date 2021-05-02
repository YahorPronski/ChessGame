#pragma once

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Window/VideoMode.hpp>

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

const int windowWidth = sf::VideoMode::getDesktopMode().width;
const int windowHeight = sf::VideoMode::getDesktopMode().height;

const float squareSize = windowWidth / 22.f;
const float spaceBetweenFields = squareSize * 4;


// for field's boarders
const float thickness = squareSize / 15.f;
const float margin = thickness * 0.4f;

const float fileSquareSize = 250;

const std::string textureFilePath = "resource//chess.png";
const std::string coordsTextureFilePath = "resource//coords_texture.jpg";
const std::string flagFilePath = "resource//whiteFlag.png";
const std::string font = "resource//terminal.otf";
