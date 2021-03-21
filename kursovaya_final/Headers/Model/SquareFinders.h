#pragma once

#include "Data.h"
#include "Values.h"

#include <SFML/System/Vector2.hpp>

bool isCorrectClick(bool isLeftField, sf::Vector2i mousePosition);

Square findSquareByCoordinates(Square** field, bool isLeftField, sf::Vector2i mousePosition);