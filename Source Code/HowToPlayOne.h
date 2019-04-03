//  HowToPlayOne.h
//    cScreen 1
//
//  Created by Johnny Nguyen and Mihika Marathe.
//  Copyright © 2019 Johnny Nguyen and Mihika Marathe.
//  All rights reserved.

// This screen includes an explanation of the game

#include <SFML/Graphics.hpp>

#include <iostream>

#include "cScreen.h"


class HowToPlayOne : public cScreen
{
public:
    HowToPlayOne(void) { }
    virtual int Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT);
};

int HowToPlayOne::Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT)
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
    sf::Text text("Collect coins to increase \nyour score."
                  "\n\nBe careful of wandering monsters!"
                  "\nAttack monsters to defeat them."
                  "\nDefend yourself by shielding."
                  
                  "\n\nDefeat the boss to earn lives."
                  
                  "\n\nMonsters will gradually increase"
                  "\nin speed and number as you"
                  "\ncollect more coins. Good luck!", font);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, SCREENHEIGHT / 2.5f));
    
    // "Next" button
    sf::Text nextButton("Next", font);
    nextButton.setCharacterSize(40);
    nextButton.setFillColor(sf::Color::Green);
    sf::FloatRect nextButtonRect = nextButton.getLocalBounds();
    nextButton.setOrigin(nextButtonRect.left + nextButtonRect.width / 2.0f, nextButtonRect.top + nextButtonRect.height / 2.0f);
    nextButton.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, (9*SCREENHEIGHT / 10.0f)));
    
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
                
                if((position.x > (nextButton.getPosition().x-(nextButtonRect.width/2)) && position.x < (nextButton.getPosition().x+(nextButtonRect.width/2)) && (position.y > (nextButton.getPosition().y-(nextButtonRect.height/2)) && position.y < (nextButton.getPosition().y + (nextButtonRect.height/2)))))
                {
                    // Proceed to next help screen
                    return (2);
                }
            }
        }
        
        App.clear();
        App.draw(text);
        App.draw(nextButton);
        App.display();
    }
    
    // Never reach this point normally, but just in case, exit the application
    return (-1);
}
