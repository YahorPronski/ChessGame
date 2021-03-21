#pragma once

#include "../Model/Data.h"
#include <iostream>
#include <SFML/System/Vector2.hpp>
#include <map>

std::map<short, short> onFirstClick(Square** field, bool isLeftField, sf::Vector2i mousePosition);