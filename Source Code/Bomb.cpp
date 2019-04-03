//
//  Bomb.cpp
//
//  Created by Felicia Dewanaga
//  Copyright © 2019 Felicia Dewanaga
//  All rights reserved.

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Bomb.h"
using namespace std;

/*
 Description: This is the constructor for the Bomb class. It sets the texture, scale and origin.
 */
Bomb::Bomb(sf::Texture &BombTexture)
{
    sprite.setTexture(BombTexture);
    sprite.setScale(.085, .085);
    sprite.setOrigin(sprite.getLocalBounds().width/2.0f,sprite.getLocalBounds().height / 2.0f);
}

/*
 Description: This function moves the bomb to the position of the mouse.
 Parameters: the mouse's x and y position, and the view position
 */
void Bomb::moveBombToStartPosition(float mousePosition_x, float mousePosition_y, float viewPosition_y)
{
    mouseX = mousePosition_x;
    mouseY = mousePosition_y;
    sprite.setPosition(mousePosition_x, viewPosition_y);
}

/*
 Description: This function resets the position of the bomb when it is moved.
 Parameters: the mouse's x and y position, and the view position
 */
bool Bomb::move()
{
    auto position = sprite.getPosition();
    position.y += 5.0f;
    sprite.setPosition(position.x, position.y);
    if (mouseY - position.y < 15)
        return false;
    return true;
}

/*
 Description: This function draws the sprite member of the class to the window.
 Parameters: RenderWindow to which to add the sprite.
 */
void Bomb::paint(sf::RenderWindow& App)
{
    App.draw(sprite);
}

/*
 Description: This function returns the size of the sprite.
 Return: Vector2f containing the height and the width.

 */
sf::Vector2f Bomb::size() const
{
    return sf::Vector2f(sprite.getLocalBounds().width * sprite.getScale().x, sprite.getLocalBounds().height * sprite.getScale().y);
}

/*
 Description: This function returns whether or not the bomb collides with a monster.
 Parameters: x-position, y-position, size of the monster
 Return: True or false based on whether a collision occurs.
 */
bool Bomb::hitByMonster(float monster_x, float monster_y,  sf::Vector2f monster_size)
{
    return getDistance(monster_x, monster_y, monster_size) < (size().x + monster_size.x) * 1.5f;
}

/*
 Description: This function returns the distance between the monster and the bomb.
 Parameters: x-position, y-position, size of the monster
 Return: Distance between the bomb and monster.
 */
double Bomb::getDistance(float monster_x, float monster_y,  sf::Vector2f monster_size)
{
    float diffX = getPosition().x - monster_x;
    float diffY = getPosition().y - monster_y;
    
    return sqrt(diffX * diffX + diffY * diffY);
    
}
