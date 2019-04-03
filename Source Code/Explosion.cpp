//
//  Explosion.cpp
//
//  Created by Felicia Dewanaga
//  Copyright © 2019 Felicia Dewanaga
//  All rights reserved.

#include <cstdlib>
#include <iostream>
#include "Explosion.h"

/*
 Description: This is the constructor for explosion. It sets the texture, the scale, and the origin.
 
 */
Explosion::Explosion(sf::Texture& texture)
: exploding(false), count(0)
{
    explosion.setTexture(texture);
    explosion.setScale(0.3, 0.3);
    explosion.setOrigin(explosion.getLocalBounds().width/2.0f,explosion.getLocalBounds().height / 2.0f);
}

/*
 Description: This function draws the sprite member of the class to the window.
 Parameters: RenderWindow to which to add the sprite.
 */
void Explosion::draw(sf::RenderWindow& App)
{
    App.draw(explosion);
}
