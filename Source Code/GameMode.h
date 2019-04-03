
//  GameMode.h
//    cScreen 8
//
//  Created by Mihika Marathe.
//  Copyright © 2019 Mihika Marathe.
//  All rights reserved.


#ifndef GameMode_h
#define GameMode_h

#include <SFML/Graphics.hpp>

#include <iostream>

#include "cScreen.h"
#include "FileOpenException.h"

class GameMode : public cScreen
{
public:
    GameMode(void) { }
    virtual int Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT);
};

int GameMode::Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT)
{
    bool Running = true;
    
    // Setting up font
    sf::Font font;
    
    // Throw error if file not opened
    try
    {
        if(!font.loadFromFile(FONTIMAGE))
        {
            throw FileOpenException(FONTIMAGE);
        }
    }
    catch(exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    
    // "Regular Mode" button
    sf::Text regMode("Regular Mode", font);
    regMode.setCharacterSize(60);
    regMode.setFillColor(sf::Color::White);
    sf::FloatRect regButtonRect = regMode.getLocalBounds();
    regMode.setOrigin(regButtonRect.left + regButtonRect.width / 2.0f, regButtonRect.top + regButtonRect.height / 2.0f);
    regMode.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, (2*SCREENHEIGHT / 8.0f)));
    
    // "Test Mode" button
    sf::Text pButton("Test Mode", font);
    pButton.setCharacterSize(60);
    pButton.setFillColor(sf::Color::White);
    sf::FloatRect pButtonRect = pButton.getLocalBounds();
    pButton.setOrigin(pButtonRect.left + pButtonRect.width / 2.0f, pButtonRect.top + pButtonRect.height / 2.0f);
    pButton.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, (4*SCREENHEIGHT / 8.0f)));
    
    // "Menu" button
    sf::Text mButton("Menu", font);
    mButton.setCharacterSize(60);
    mButton.setFillColor(sf::Color::White);
    sf::FloatRect mButtonRect = mButton.getLocalBounds();
    mButton.setOrigin(mButtonRect.left + mButtonRect.width / 2.0f, mButtonRect.top + mButtonRect.height / 2.0f);
    mButton.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, (6*SCREENHEIGHT / 8.0f)));
    
    sf::Event event;
    while (Running)
    {
        // Verifying events
        while (App.pollEvent(event))
        {
            // Window closed
            if (event.type == sf::Event::EventType::Closed)
                return (-1);
            // Mouse pressed
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i position = sf::Mouse::getPosition(App);
                    
                    // Debugging mouse click position
                    /*std::cout << "in";
                     std::cout << position.x << " " << position.y << std::endl;
                     std::cout << nextButton.getPosition().x << std::endl;*/
                    
                    // "Regular Mode" button
                    if((position.x > (regMode.getPosition().x-(regButtonRect.width/2)) && position.x < (regMode.getPosition().x+(regButtonRect.width/2)) && (position.y > (regMode.getPosition().y-(regButtonRect.height/2)) && position.y < (regMode.getPosition().y + (regButtonRect.height/2)))))
                    {
                        // Proceed to game screen
                        return (3);
                    }
                    // "Test Mode" button
                    if((position.x > (pButton.getPosition().x-(pButtonRect.width/2)) && position.x < (pButton.getPosition().x+(pButtonRect.width/2)) && (position.y > (pButton.getPosition().y-(pButtonRect.height/2)) && position.y < (pButton.getPosition().y + (pButtonRect.height/2)))))
                    {
                        // Proceed to game screen
                        testmode = true;
                        return (3);
                    }
                    // "Menu" button
                    if((position.x > (mButton.getPosition().x-(mButtonRect.width/2)) && position.x < (mButton.getPosition().x+(mButtonRect.width/2)) && (position.y > (mButton.getPosition().y-(mButtonRect.height/2)) && position.y < (mButton.getPosition().y + (mButtonRect.height/2)))))
                    {
                        // Return to menu screen
                        return (7);
                    }
                }
            }
        }
        
        App.clear();
        App.draw(mButton);
        App.draw(pButton);
        App.draw(regMode);
        App.display();
    }
    
    // Never reach this point normally, but just in case, exit the application
    return (-1);
}

#endif /* Menu_h */
