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
const float squareSize = 64;
const float spaceBetweenFields = squareSize * 3;

const std::string textureFilePath = "resource\\chess_texture.jpg";
