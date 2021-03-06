//
//  Coins.h
//
//  Created by Mihika Marathe and Alan Rodriguez
//  Copyright © 2019 Mihika Marathe and Alan Rodriguez
//  All rights reserved.

#ifndef COINS_H
#define COINS_H

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>

class Coins : public Entity
{
private:
    
    int currentTexture;
    sf::Texture textureOne;
    sf::Texture textureTwo;
    sf::Texture textureThree;
    sf::Texture textureFour;
    sf::Texture textureFive;
    sf::Texture textureSix;
    sf::Texture textureArr[6];
    
public:
    Coins(sf::Texture& textOne, sf::Texture& textTwo, sf::Texture& textThree, sf::Texture& textFour, sf::Texture& textFive, sf::Texture& textSix, float h, float w);
    double getRandom(int lower, int upper);
    void collide();
    void animate();
    ~Coins();
};



#endif
