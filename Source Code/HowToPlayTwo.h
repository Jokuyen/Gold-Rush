//  HowToPlayTwo.h
//    cScreen 2
//
//  Created by Johnny Nguyen and Mihika Marathe.
//  Copyright © 2019 Johnny Nguyen and Mihika Marathe.
//  All rights reserved.

// This screen specially has an explanation the control functions of the game

#include <SFML/Graphics.hpp>

#include <iostream>

#include "cScreen.h"

class HowToPlayTwo : public cScreen
{
public:
    HowToPlayTwo(void) { }
    virtual int Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT);
};

int HowToPlayTwo::Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT)
{
    bool Running = true;
    
    // Setting up font
    sf::Font font;
    
    // Throw error if file not opened
    try {
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
    sf::Text text("Controls: \n\nMovement (Arrow keys) \nAttack (A) \nShield (S) \n\nShield lasts for a few seconds. \nClick (Left) to drop a bomb.", font);
    text.setCharacterSize(45);
    text.setFillColor(sf::Color::White);
    
    // "Menu" button
    sf::Text mButton("Menu", font);
    mButton.setCharacterSize(50);
    mButton.setFillColor(sf::Color::Green);
    sf::FloatRect mButtonRect = mButton.getLocalBounds();
    mButton.setOrigin(mButtonRect.left + mButtonRect.width / 2.0f, mButtonRect.top + mButtonRect.height / 2.0f);
    mButton.setPosition(sf::Vector2f(SCREENWIDTH / 14.0f, (8*SCREENHEIGHT / 9.0f)));
    
    // "Play" button
    sf::Text pButton("Play", font);
    pButton.setCharacterSize(50);
    pButton.setFillColor(sf::Color::Green);
    sf::FloatRect pButtonRect = pButton.getLocalBounds();
    pButton.setOrigin(pButtonRect.left + pButtonRect.width / 2.0f, pButtonRect.top + pButtonRect.height / 2.0f);
    pButton.setPosition(sf::Vector2f(13*SCREENWIDTH / 14.0f, (8*SCREENHEIGHT / 9.0f)));
    
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
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i position = sf::Mouse::getPosition(App);
                
                // Debugging mouse click position
                /*std::cout << "in";
                 std::cout << position.x << " " << position.y << std::endl;
                 std::cout << nextButton.getPosition().x << std::endl;*/
                
                // "Menu" button
                if((position.x > (mButton.getPosition().x-(mButtonRect.width/2)) && position.x < (mButton.getPosition().x+(mButtonRect.width/2)) && (position.y > (mButton.getPosition().y-(mButtonRect.height/2)) && position.y < (mButton.getPosition().y + (mButtonRect.height/2)))))
                {
                    // Return to menu screen
                    return (7);
                }
                // "Play" button
                if((position.x > (pButton.getPosition().x-(pButtonRect.width/2)) && position.x < (pButton.getPosition().x+(pButtonRect.width/2)) && (position.y > (pButton.getPosition().y-(pButtonRect.height/2)) && position.y < (pButton.getPosition().y + (pButtonRect.height/2)))))
                {
                    // Proceed to game mode screen
                    return (8);
                }
            }
        }
        
        App.clear();
        App.draw(text);
        App.draw(mButton);
        App.draw(pButton);
        App.display();
    }
    
    // Never reach this point normally, but just in case, exit the application
    return (-1);
}
