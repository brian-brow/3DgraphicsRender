//
// Created by Brian Brown on 7/27/23.
//

#include <cmath>
#include "space.h"

space::space(int dimensions) {
    this->dimensions = dimensions;
    for(int x = 0; x < dimensions; x++) {
        std::vector<std::vector<pixel>> row;
        for(int y = 0; y < dimensions; y++) {
            std::vector<pixel> column;
            for(int z = 0; z < dimensions; z++) {
                pixel square(sf::Vector3i(0,0,0));
                column.push_back(square);
            }
            row.push_back(column);
        }
        map.push_back(row);
    }
}

bool space::getIsSolid(sf::Vector3<int> Pos) {
    if(Pos.x < dimensions && Pos.y < dimensions && Pos.z < dimensions) {
        return map[Pos.x][Pos.y][Pos.z].getSolid();
    } else {
        return false;
    }
}

sf::Color space::getColorAt(sf::Vector3<int> Pos) {
    if(Pos.x < dimensions && Pos.y < dimensions && Pos.z < dimensions) {
        return map[Pos.x][Pos.y][Pos.z].getColor();
    } else {
        return sf::Color::Black;
    }
}

void space::setWallColor(sf::Vector3i color) {
    for(int x = 0; x < dimensions; x++) {
        for(int y = 0; y < dimensions; y++) {
            for(int z = 0; z < dimensions; z++) {
                if(x == 0 || y == 0 || z == 0 || x == dimensions - 1 || y == dimensions - 1 || z == dimensions - 1) {
                    if(!(z == dimensions-1)) {
                        map[x][y][z].setColor(color);
                    } else {
                        map[x][y][z].setColor(sf::Vector3i(255, 255, 255));
                    }
                    if(x == dimensions / 2 || y == dimensions / 2 || z == dimensions / 2) {
                        map[x][y][z].setColor(sf::Vector3i(0, 0, 0));
                    }
                    if(x == 1 || y == 1 || z == 1 || x == dimensions - 2 || y == dimensions - 2 || z == dimensions - 2) {
                        map[x][y][z].setColor(sf::Vector3i(0, 0, 0));
                    }
                }
            }
        }
    }
}

void space::makeCube(sf::Vector3i Pos, int size) {
    std::cout << "Pos: " << Pos.x << " " << Pos.y << " " << Pos.z << std::endl;
    for(int x = Pos.x - ceil(size / 2); x < Pos.x + ceil(size / 2); x++) {
        for(int y = Pos.y - ceil(size / 2); y < Pos.y + ceil(size / 2); y++) {
            for(int z = Pos.z - ceil(size / 2); z < Pos.z + ceil(size / 2); z++) {
                if(y == 28 && x == 23) {
                    map[x][y][z].setColor(sf::Vector3i(0, 0, 0));
                } else {
                    map[x][y][z].setColor(sf::Vector3i(255, 255, 255));
                }
                std::cout << x << " " << y << " " << z << std::endl;
            }
        }
    }
}

void space::printPixels() {
    for(int i = 0; i < dimensions; i++) {
        for(int j = 0; j < dimensions; j++) {
            for(int l = 0; l < dimensions; l++) {
                std::cout << getColorAt(sf::Vector3i(i,j,l)).r;
            }
            std::cout << std::endl;
        }
        std::cout << "////////////////////////////////" << std::endl;
    }
    std::cout << map.size() << " " << map[0].size() << " " << map[0][0].size() << std::endl;
}

pixel& space::mapAt(sf::Vector3i Pos) {
    return map[Pos.x][Pos.y][Pos.x];
}

int space::getDimensions() {
    return dimensions;
}
