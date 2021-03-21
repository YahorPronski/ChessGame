#pragma once

#include <iostream>

enum PieceName {
	KING,
	QUEEN,
	BISHOP,
	KNIGHT,
	ROCK,
	PAWN,

	// Для пустых клеток
	NO_PIECE
};

enum PieceColor {
	WHITE,
	BLACK,

	// Для пустых клеток
	NO_COLOR
};

const float fileTextureSquareScale = 128;
const float squareSize = 86;
const float spaceBetweenFields = squareSize * 3;

const std::string textureFilePath = "chess_texture.jpg";
