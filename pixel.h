//
// Created by Brian Brown on 7/26/23.
//

#ifndef UNTITLEDGAME_PIXEL_H
#define UNTITLEDGAME_PIXEL_H
#include <SFML/Graphics.hpp>
#include <iostream>

class pixel {
    sf::Vector3i color;
    bool solid;
public:
    pixel();
    pixel(sf::Vector3i color);

    void setColor(sf::Vector3i color);

    sf::Color getColor();
    bool getSolid();
};


#endif //UNTITLEDGAME_PIXEL_H
