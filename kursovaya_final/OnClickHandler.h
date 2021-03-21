#pragma once

#include "Data.h"

#include <SFML/System/Vector2.hpp>
#include <map>

std::map<short, short> onFirstClick(Square** field, bool isLeftField, sf::Vector2i mousePosition);