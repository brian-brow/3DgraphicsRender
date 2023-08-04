//
// Created by Brian Brown on 7/31/23.
//

#include "Camera.h"
#include "math.h"

Camera::Camera() {
    resolution = sf::Vector2f(50, 50);
    fov = 50;
    for(int i = 20; i < 70; i++) {
        anglesXY.push_back(i);
    }
    for(int i = 20; i < 70; i++) {
        anglesZ.push_back(i);
    }
}

Camera::Camera(sf::Vector2f resolution, float fov, sf::Vector3f cameraPos) {
    this->resolution = resolution;
    this->fov = fov;
    this->cameraPos = cameraPos;
    float interval = fov / resolution.x;
    for(int i = 0; i < resolution.x; i++) {
        anglesXY.push_back(interval * i);

    }
    interval = fov / resolution.y;
    for(int i = 0; i < resolution.y; i++) {
        anglesZ.push_back(interval * i);
    }
    for(int i = 0; i < resolution.y; i++) {
        for(int j = 0; j < resolution.x; j++) {
            directionList.push_back(sf::Vector3f(sin(anglesZ[i]) * sin(anglesXY[j]),
                                                sin(anglesZ[i]) * cos(anglesXY[j]),
                                                cos(anglesZ[i])));
//            std::cout << sin(anglesZ[i]) * sin(anglesXY[j]) <<
//                " " << sin(anglesZ[i]) * cos(anglesXY[j]) <<
//                " " << cos(anglesZ[i]) << std::endl;
        }
    }
}

void Camera::rotateCamera(int degrees, bool xy) {
    if(xy) {
        for(int i = 0; i < anglesXY.size(); i++) {
            anglesXY[i] += degrees;
        }
//        for(int i = 0; i < directionList.size(); i++) {
//            for(int j = 0; j < directionList.size(); j++) {
//                directionList[i+j] += sf::Vector3f(0,0,-1);
//                directionList[i+j] /= float(sqrt(pow(directionList[i+j].x, 2) + pow(directionList[i+j].y, 2) + pow(directionList[i+j].z, 2)));
//            }
//        }
    } else {
        for(int i = 0; i < anglesZ.size(); i++) {
            anglesZ[i] += degrees;
        }
    }
}

void Camera::drawLines(space &World, sf::RenderWindow& gameWindow, int layer) {
    bool wait = true;
    int Height = World.getDimensions();
    int Width = World.getDimensions();
    sf::RectangleShape box(sf::Vector2f(1, 1));

    for(int i = 0; i < anglesZ.size(); i++) {
        float radiansZ = anglesZ[i] * 3.14159 / 180.0;
        for(int j = 0; j < anglesXY.size(); j++) {
            box.setPosition(Width * 10 / 2.f, Height * 10 / 2.f);
            float radiansXY = anglesXY[j] * 3.14159 / 180.0;
            float camera_x = floor(cameraPos.x);
            float camera_y = floor(cameraPos.y);
            float camera_z = floor(cameraPos.z);
            float t = 0;
            while (wait) {
                box.setSize(sf::Vector2f(1, 1));
                int y = floor(abs((camera_y + t * cos(radiansXY))));
                int z = floor(abs((camera_z + t * tan(radiansZ))));
                int x = floor(abs((camera_x + t * sin(radiansXY))));
//                std::cout << x << " " << y << " " << z << " ";
//                y = floor(abs((camera_x + t * directionList[i + j].x)));
//                z = floor(abs((camera_y + t * directionList[i + j].y)));
//                x = floor(abs((camera_z + t * directionList[i + j].z)));
//                std::cout << x << " " << y << " " << z << std::endl;
                if (y == Width) {
                    y -= 1;
                }
                if (z == Width) {
                    z -= 1;
                }
                if (x == Width) {
                    x -= 1;
                }
//                std::cout << World.getIsSolid(sf::Vector3i(y, z, x)) << std::endl;
//                std::cout << t << std::endl;
                if (World.getIsSolid(sf::Vector3i(x, y, z))) {
                    wait = false;
                    int screenScale = 8;
                    box.setSize(sf::Vector2f(screenScale, screenScale));
                    box.setFillColor(World.getColorAt(sf::Vector3i(x, y, z)));
                    box.setPosition(1000 - resolution.x * screenScale + j * screenScale, resolution.x * screenScale - i * screenScale);
                    gameWindow.draw(box);
                    std::cout << x << " " << y << " " << z << std::endl;
                } else if (y < 0 || z < 0 || x < 0 || y > Width || z > Height || x > Width) {
//                } else {
                    wait = false;
                    int screenScale = 8;
                    box.setSize(sf::Vector2f(screenScale, screenScale));
                    box.setFillColor(sf::Color::Green);
                    box.setPosition(1000 - resolution.x * screenScale + i * screenScale, j * screenScale);
                    gameWindow.draw(box);
                } else {
//                    box.setSize(sf::Vector2f(1, 1));
//                    box.setFillColor(sf::Color::Blue);
//                    gameWindow.draw(box);
//                    box.move(cos(radiansXY), sin(radiansXY));
                }
                if(abs(x - camera_x) > 20 || abs(y - camera_y) > 20 || abs(z - camera_z) > 20) {
                    t += 0.75;
                } else if(abs(x - camera_x) > 10 || abs(y - camera_y) > 10 || abs(z - camera_z) > 10) {
                    t += 0.5;
                }
                else if(abs(x - camera_x) > 5 || abs(y - camera_y) > 5 || abs(z - camera_z) > 5) {
                    t += 0.25;
                }else{
                    t += 0.05;
                }
            }
            wait = true;
        }
    }
}

//void Camera::drawLines(space &World, sf::RenderWindow& gameWindow, int layer) {
//    bool wait = true;
//    int Height = World.getDimensions();
//    int Width = World.getDimensions();
//    sf::RectangleShape box(sf::Vector2f(1, 1));
//    for(int i = 0; i < directionList.size(); i++) {
//        box.setPosition(Width * 10 / 2.f, Height * 10 / 2.f);
//        float t = 0;
//        while(wait) {
//            int y = floor(abs((cameraPos.x + t * directionList[i].x)));
//            int z = floor(abs((cameraPos.y + t * directionList[i].y)));
//            int x = floor(abs((cameraPos.z + t * directionList[i].z)));
//            if(World.getIsSolid(sf::Vector3i(x,y,z))) {
//                wait = false;
//                int screenScale = 8;
//                box.setSize(sf::Vector2f(screenScale, screenScale));
//                box.setFillColor(World.getColorAt(sf::Vector3i(x, y, z)));
//                box.setPosition(1000 - resolution.x * screenScale + i * screenScale, i * screenScale);
//                gameWindow.draw(box);
//            } else if (y < 0 || z < 0 || x < 0 || y > Width || z > Height || x > Width) {
//                wait = false;
//                int screenScale = 8;
//                box.setSize(sf::Vector2f(screenScale, screenScale));
//                box.setFillColor(sf::Color::Magenta);
//                box.setPosition(1000 - resolution.x * screenScale + i * screenScale, i * screenScale);
//                gameWindow.draw(box);
//            }
//            t += 0.05;
//        }
//    }
//}

void Camera::moveCamera(std::string direction) {
    int midAngle = anglesXY[floor(anglesXY.size()/2)];
    std::cout << cos(midAngle) << " " << sin(midAngle) << std::endl;
    if(direction == "FORWARD") {
        cameraPos += sf::Vector3f(cos(midAngle), sin(midAngle), 0);
    } else if(direction == "LEFT") {
        cameraPos += sf::Vector3f(cos(midAngle + 1.5708), sin(midAngle + 1.5708), 0);
    } else if(direction == "RIGHT") {
        cameraPos += sf::Vector3f(cos(midAngle - 1.5708), sin(midAngle - 1.5708), 0);
    } else if(direction == "BACKWARD") {
        cameraPos -= sf::Vector3f(cos(midAngle), sin(midAngle), 0);
    } else if(direction == "UP") {
        cameraPos += sf::Vector3f(0, 0, 1);
    } else if(direction == "DOWN") {
        cameraPos += sf::Vector3f(0, 0, -1);
    }
}
