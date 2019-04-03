//
//  Entity.cpp
//
//  Created by Mihika Marathe, Johnny Nguyen, Manxin Zhang, and Felicia Dewanaga
//  Copyright © 2019 Mihika Marathe, Johnny Nguyen, Manxin Zhang, and Felicia Dewanaga
//  All rights reserved.

#ifndef Entity_h
#define Entity_h

#include <SFML/Graphics.hpp>

static sf::Vector2f BACKGROUNDSIZE = sf::Vector2f(1024.0f, 720.0f);

class Entity
{
protected:
    sf::Sprite sprite;
    static sf::Image image;
    
public:
    enum Direction {Up,Down,Left,Right};
    Entity(sf::Texture& texture, float width, float height);
    virtual ~Entity();
    sf::Vector2f getPosition() const
    {
        return sprite.getPosition();
    }
    sf::Sprite getSprite() const { return sprite; }
    virtual void move(Direction d);
    void draw(sf::RenderWindow& App);
    virtual sf::Vector2f size() const;
    void setPosition(float x, float y);
    static void setImage(const sf::Image &img) { image = img; }
};

#endif /* Character_h */
