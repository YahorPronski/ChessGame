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

const float fileTextureSquareScale = 128;
const float squareSize = 128;
const float spaceBetweenFields = squareSize * 3;

const std::string textureFilePath = "chess_texture.jpg";
