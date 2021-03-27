#pragma once

#include <iostream>

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

const float fileSquareSize = 128;
const float squareSize = 100;
const float spaceBetweenFields = squareSize;

const int windowWidth = squareSize * 9 + spaceBetweenFields + squareSize * 9;
const int windowHeight = squareSize * 10;

const std::string textureFilePath = "resource//chess_texture.jpg";
