#pragma once

#include "../Model/Data.h"
#include "../../resource/Values.h"

#include <vector>
#include <SFML/System/Vector2.hpp>

Square findSquareByCoordinates(Square** field, bool isLeftField, sf::Vector2i mousePosition);

bool isCorrectClick(bool isLeftField, sf::Vector2i mousePosition);

bool isCorrectMove(std::vector<sf::Vector2<short>>, bool isLeft, sf::Vector2i mousePosition);

