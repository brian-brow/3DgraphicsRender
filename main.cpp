#include <iostream>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>
#include "space.h"
#include "Camera.h"

int main() {

    int Height = 500;
    int Width = 500;

    int layer = 21;

    space World(Width/10);
    World.setWallColor(sf::Vector3i(150,150,150));
    World.makeCube(sf::Vector3i(Width/10/2, Width/10 - 20, Width/10 - 20), 4);
//    World.printPixels();

    Camera camera(sf::Vector2f(50, 50), 60, sf::Vector3f(25,25,25));

    sf::RenderWindow gameWindow(sf::VideoMode(1000, 1000), "SFML works!");
    sf::RectangleShape box(sf::Vector2f(10, 10));
    box.setFillColor(sf::Color::White);
    box.setPosition(Width * 9 / 10.f,Height * 9 / 10.f);
    box.setSize(sf::Vector2f(Width / 10, Height / 10));

    sf::RectangleShape line(sf::Vector2f(1.f,1.f));
    line.setFillColor(sf::Color::Blue);
    line.setPosition(500.f, 500.f);

    sf::RectangleShape placeHolder(sf::Vector2f(1.f, 1.f));

    bool Rainbow = false;
    int r = 0;
    int g = 0;
    int b = 127;

    std::vector<int> angles;
    for(int i = 0; i < 54; i++) {
        angles.push_back(-90 + i * 2);
    }

    while(gameWindow.isOpen()){
        sf::Event event;
        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
                return 0;
            }
            if (event.type == sf::Event::KeyPressed) {
                if(sf::Keyboard::isKeyPressed((sf::Keyboard::Left))) {
                    camera.rotateCamera(-5, true);
                }
                if(sf::Keyboard::isKeyPressed((sf::Keyboard::Right))) {
                    camera.rotateCamera(5, true);
                }
                if(sf::Keyboard::isKeyPressed((sf::Keyboard::Up))) {
                    if(layer > 0) {layer -= 1;}
                    camera.rotateCamera(-5, false);
                }
                if(sf::Keyboard::isKeyPressed((sf::Keyboard::Down))) {
                    if(layer < Width/10-1) {layer += 1;}
                    camera.rotateCamera(5, false);
                }
                if(sf::Keyboard::isKeyPressed((sf::Keyboard::R))) {
                    Rainbow = !Rainbow;
                }
                if(sf::Keyboard::isKeyPressed((sf::Keyboard::W))) {
                    camera.moveCamera("FORWARD");
                }
                if(sf::Keyboard::isKeyPressed((sf::Keyboard::A))) {
                    camera.moveCamera("LEFT");
                }
                if(sf::Keyboard::isKeyPressed((sf::Keyboard::S))) {
                    camera.moveCamera("BACKWARD");
                }
                if(sf::Keyboard::isKeyPressed((sf::Keyboard::D))) {
                    camera.moveCamera("RIGHT");
                }
                if(sf::Keyboard::isKeyPressed((sf::Keyboard::Space))) {
                    camera.moveCamera("UP");
//                    layer += 1;
                }
                if(sf::Keyboard::isKeyPressed((sf::Keyboard::LShift))) {
                    camera.moveCamera("DOWN");
//                    layer -= 1;
                }
            }
        }

        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> uni(0,255);

        if(Rainbow){
            if(r < 127 && g < 1){
                r += 1;
                b -= 1;
            } else if(g < 127 && b < 1) {
                r -= 1;
                g += 1;
            } else if(b < 127 && r < 1) {
                g -= 1;
                b += 1;
            }
            std::cout << r << " " << g << " " << b << std::endl;
            box.setFillColor(sf::Color(r, g, b));
        }

        gameWindow.clear(sf::Color::Blue);

        for(int i = 0; i < Width/10; i++) {
            for(int j = 0; j < Width/10; j++) {
                placeHolder.setFillColor(World.getColorAt(sf::Vector3i(layer,i,j)));
                placeHolder.setPosition(i * 10, j * 10);
                placeHolder.setSize(sf::Vector2f(Width/10, Width/10));
                gameWindow.draw(placeHolder);
            }
        }

        camera.drawLines(World, gameWindow, layer);

//        bool wait = true;
//
//        for(int i = 0; i < angles.size(); i++) {
//            box.setPosition(0 + (20 * i),Height * 9 / 10.f);
//            line.setPosition(Width/2.f, Height/2.f);
//            float tempX = Width/2;
//            float tempY = Height/2;
//            std::cout << !World.getIsSolid(sf::Vector3i(layer, floor(abs(tempX/10)), floor(abs(tempY/10)))) << std::endl;
//            while (wait) {
//                radians = angles[i] * 3.14159 / 180;
//                if ((tempX > 0 && tempY > 0) && (tempX < Width && tempY < Height)) {
////                if(World.getIsSolid(sf::Vector3i(layer, floor(abs(tempX/10)), floor(abs(tempY/10))))) {
//                    gameWindow.draw(line);
//                    line.move(cos(radians), sin(radians));
//                    tempX += cos(radians);
//                    tempY += sin(radians);
//                } else {
//                    wait = false;
//                    tempX = floor(abs(tempX / 10));
//                    tempY = floor(abs(tempY / 10));
//                    if (tempX == Width / 10) {
//                        tempX -= 1;
//                    }
//                    if (tempY == Width / 10) {
//                        tempY -= 1;
//                    }
//                    std::cout << tempX << " " << tempY << std::endl;
//                    box.setFillColor(World.getColorAt(sf::Vector3i(layer, tempX, tempY)));
//                    gameWindow.draw(box);
//                }
//            }
//            wait = true;
//        }

        gameWindow.display();
    }
    return 0;
}