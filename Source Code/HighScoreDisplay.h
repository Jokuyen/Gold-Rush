//  HighScoreDisplay.h
//    cScreen 6
//
//  Created by Manxin Zhang.
//  Copyright © 2019 Manxin Zhang.
//  All rights reserved.

#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "cScreen.h"

using namespace std;

class HighScoreDisplay : public cScreen
{
public:
    HighScoreDisplay(void) { }
    virtual int Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT);
};

int HighScoreDisplay::Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT)
{
    multimap<int, string> highScores;
    const char* filename = "ScoreFile.txt";
    readFromScoreFile(filename, highScores);
    
    bool Running = true;
    
    
    sf::Font font;
    
    // Throw error if file not opened
    try {
        if (!font.loadFromFile(FONTIMAGE))
        {
            throw FileOpenException(FONTIMAGE);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    
    sf::Text text("", font);
    ostringstream sout;
    sout << "Score Board" << endl;
    
    int count = 0;
    for (auto it = highScores.rbegin(); it != highScores.rend(); ++it) {
        sout << setw(2) << (++count) << setw(10) << it->first << "\t\t" << it->second << endl;
    }
    text.setString(sout.str());
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    
    // "Menu" button
    sf::Text mButton("Menu", font);
    mButton.setCharacterSize(50);
    mButton.setFillColor(sf::Color::Green);
    sf::FloatRect mButtonRect = mButton.getLocalBounds();
    mButton.setOrigin(mButtonRect.left + mButtonRect.width / 2.0f, mButtonRect.top + mButtonRect.height / 2.0f);
    mButton.setPosition(sf::Vector2f(8*SCREENWIDTH / 9.0f, (SCREENHEIGHT / 20.0f)));
    
    sf::Event event;
    while (Running)
    {
        // Verifying events
        while (App.pollEvent(event))
        {
            // Window closed
            if (event.type == sf::Event::EventType::Closed)
                return (-1);
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
            }
        }
        
        App.clear();
        App.draw(text);
        App.draw(mButton);
        App.display();
    }
    
    return (-1);
}

