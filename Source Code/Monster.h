//
//  Monster.cpp
//
//  Created by Johnny Nguyen and Felicia Dewanaga
//  Copyright © 2019 Johnny Nguyen and Felicia Dewanaga
//  All rights reserved.

#ifndef MONSTER_H
#define MONSTER_H

#include "Entity.h"

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>

class Monster : public Entity
{
private:
    // Textures
    sf::Texture movementOneTexture;
    sf::Texture movementTwoTexture;
    sf::Texture collisionTexture;
    
    bool alive = true;
    int direction = 0; // 0 = Up, 1 = Down, 2 = Left, 3 = Right
    float movementSpeed = 2;
    int movementCounter = 0;
    int movementLength = 55;
    bool bigBoss;
    
public:
    // Constructor
    Monster(sf::Texture& monsterTexture, sf::Texture& monsterTwoTexture, sf::Texture& monsterCollisionTexture, float chamberx, float chambery, bool boss = false);
    ~Monster();
    
    // Animations
    void movementAnimation();
    void collisionAnimation() { sprite.setTexture(collisionTexture); }
    
    
    // Functions
    int randomNumber(int max);
    bool getAlive();
    void setAlive(bool a);
    void increaseSpeed(float inputSpeedNumber) { if (movementSpeed < 15) movementSpeed += inputSpeedNumber; }
    void updateMovement(const int SCREENWIDTH, const int BG_HEIGHT);
};

#endif // MONSTER_H
