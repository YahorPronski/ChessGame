#pragma once
#include "../../resource/Values.h"
#include <SFML/Graphics.hpp>

class flag: public sf::Drawable {
public:
    flag(sf::Vector2f coord) {
        origin = coord;
    }

    bool isSelected(Vector2i _mouse) {
        if((_mouse.x > origin.x && _mouse.x < origin.x + squareSize / 3) && (_mouse.y > origin.y && _mouse.y < origin.y + squareSize)) {
            return  true;
        } else {
            return false;
        }
    }
private:
    sf::Vector2f origin;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        sf::ConvexShape flagStick;
        flagStick.setPointCount(5);
        flagStick.setPoint(0, origin);
        flagStick.setPoint(1, sf::Vector2f(origin.x, origin.y + squareSize / 1.25));
        flagStick.setPoint(2, sf::Vector2f(origin.x + squareSize / 15, origin.y + squareSize / 1.25));
        flagStick.setPoint(3, sf::Vector2f(origin.x + squareSize / 15, origin.y));
        flagStick.setPoint(4, sf::Vector2f(origin));
        flagStick.setFillColor(sf::Color::Yellow);
        sf::ConvexShape flag;
        flag.setPointCount(4);
        flag.setPoint(0, sf::Vector2f(origin.x + squareSize / 15, origin.y + squareSize / 12));
        flag.setPoint(1, sf::Vector2f(origin.x + squareSize / 3, origin.y + squareSize / 12 + squareSize / 4));
        flag.setPoint(2, sf::Vector2f(origin.x + squareSize / 15, origin.y + squareSize / 12 + squareSize / 2));
        flag.setPoint(3, sf::Vector2f(origin.x + squareSize / 15, origin.y + squareSize / 12));
        target.draw(flag);
        target.draw(flagStick);
    }
};