//  Menu.h
//    cScreen 7
//
//  Created by Mihika Marathe.
//  Copyright © 2019 Mihika Marathe.
//  All rights reserved.

#ifndef Menu_h
#define Menu_h

#include <SFML/Graphics.hpp>

#include <iostream>

#include "cScreen.h"
#include "FileOpenException.h"

class Menu : public cScreen
{
public:
    Menu(void) { }
    virtual int Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT);
};

int Menu::Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT)
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
    
    // "Play" button
    sf::Text htpButton("Play", font);
    htpButton.setCharacterSize(60);
    htpButton.setFillColor(sf::Color::White);
    sf::FloatRect htpButtonRect = htpButton.getLocalBounds();
    htpButton.setOrigin(htpButtonRect.left + htpButtonRect.width / 2.0f, htpButtonRect.top + htpButtonRect.height / 2.0f);
    htpButton.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, (SCREENHEIGHT / 8.0f)));
    
    // "How to Play" button
    sf::Text pButton("How to Play", font);
    pButton.setCharacterSize(60);
    pButton.setFillColor(sf::Color::White);
    sf::FloatRect pButtonRect = pButton.getLocalBounds();
    pButton.setOrigin(pButtonRect.left + pButtonRect.width / 2.0f, pButtonRect.top + pButtonRect.height / 2.0f);
    pButton.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, (3*SCREENHEIGHT / 8.0f)));
    
    // "High Score List" button
    sf::Text hsButton("High Score List", font);
    hsButton.setCharacterSize(60);
    hsButton.setFillColor(sf::Color::White);
    sf::FloatRect hsButtonRect = hsButton.getLocalBounds();
    hsButton.setOrigin(hsButtonRect.left + hsButtonRect.width / 2.0f, hsButtonRect.top + hsButtonRect.height / 2.0f);
    hsButton.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, (5*SCREENHEIGHT / 8.0f)));
    
    // "Quit" button
    sf::Text qButton("Quit", font);
    qButton.setCharacterSize(60);
    qButton.setFillColor(sf::Color::White);
    sf::FloatRect qButtonRect = qButton.getLocalBounds();
    qButton.setOrigin(qButtonRect.left + qButtonRect.width / 2.0f, qButtonRect.top + qButtonRect.height / 2.0f);
    qButton.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, (7*SCREENHEIGHT / 8.0f)));
    
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
                    
                    // "Play" button
                    if((position.x > (htpButton.getPosition().x-(htpButtonRect.width/2)) && position.x < (htpButton.getPosition().x+(htpButtonRect.width/2)) && (position.y > (htpButton.getPosition().y-(htpButtonRect.height/2)) && position.y < (htpButton.getPosition().y + (htpButtonRect.height/2)))))
                    {
                        // Proceed to game mode screen
                        return (8);
                    }
                    // "How to play" button
                    if((position.x > (pButton.getPosition().x-(pButtonRect.width/2)) && position.x < (pButton.getPosition().x+(pButtonRect.width/2)) && (position.y > (pButton.getPosition().y-(pButtonRect.height/2)) && position.y < (pButton.getPosition().y + (pButtonRect.height/2)))))
                    {
                        // Proceed to help screen
                        return (1);
                    }
                    // "High Score List" button
                    if((position.x > (hsButton.getPosition().x-(hsButtonRect.width/2)) && position.x < (hsButton.getPosition().x+(hsButtonRect.width/2)) && (position.y > (hsButton.getPosition().y-(hsButtonRect.height/2)) && position.y < (hsButton.getPosition().y + (hsButtonRect.height/2)))))
                    {
                        // Proceed to score screen
                        return (6);
                    }
                    // "Quit" button
                    if((position.x > (qButton.getPosition().x-(qButtonRect.width/2)) && position.x < (qButton.getPosition().x+(qButtonRect.width/2)) && (position.y > (qButton.getPosition().y-(qButtonRect.height/2)) && position.y < (qButton.getPosition().y + (qButtonRect.height/2)))))
                    {
                        // Exit game
                        return (-1);
                    }
                }
            }
        }
        
        App.clear();
        App.draw(htpButton);
        App.draw(pButton);
        App.draw(hsButton);
        App.draw(qButton);
        App.display();
    }
    
    // Never reach this point normally, but just in case, exit the application
    return (-1);
}

#endif /* Menu_h */
