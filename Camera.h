//
// Created by Brian Brown on 7/31/23.
//

#ifndef UNTITLEDGAME_CAMERA_H
#define UNTITLEDGAME_CAMERA_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "space.h"


class Camera {
public:
    sf::Vector2f resolution;
    int fov;
    std::vector<float> anglesXY;
    std::vector<float> anglesZ;

    std::vector<sf::Vector3f> directionList;

    sf::Vector3f cameraPos;
public:
    Camera();
    Camera(sf::Vector2f resolution, float fov, sf::Vector3f cameraPos);

    void rotateCamera(int degrees, bool xy);
    void drawLines(space& World, sf::RenderWindow& gameWindow, int layer);
    void moveCamera(std::string direction);
};


#endif //UNTITLEDGAME_CAMERA_H
