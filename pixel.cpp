//
// Created by Brian Brown on 7/26/23.
//

#include "pixel.h"

pixel::pixel() {
    this->color = sf::Vector3i(0,0,0);
    this->solid = false;
}

pixel::pixel(sf::Vector3i color) {
    this->color = color;
    this->solid = false;
}

void pixel::setColor(sf::Vector3i color) {
    this->color = color;
    this->solid = true;
}

sf::Color pixel::getColor() {
    return sf::Color(color.x, color.y, color.z);
}

bool pixel::getSolid() {
    return solid;
}
