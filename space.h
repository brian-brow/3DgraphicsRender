//
// Created by Brian Brown on 7/27/23.
//

#ifndef UNTITLEDGAME_SPACE_H
#define UNTITLEDGAME_SPACE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "pixel.h"


class space {
    std::vector<std::vector<std::vector<pixel>>> map;
    int dimensions;
public:
    space(int dimensions);

    void setWallColor(sf::Vector3i color);
    void makeCube(sf::Vector3i Pos, int size);

    bool getIsSolid(sf::Vector3<int> Pos);
    sf::Color getColorAt(sf::Vector3<int> Pos);
    int getDimensions();

    pixel& mapAt(sf::Vector3i Pos);

    //debug functions

    void printPixels();
};


#endif //UNTITLEDGAME_SPACE_H
