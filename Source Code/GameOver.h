#include <iostream>
#include "cScreen.h"
#include <string>

#include <SFML/Graphics.hpp>


/*
 This screen contains a message saying the game is over and controls to move forward.
 */
class GameOver : public cScreen
{
public:
    GameOver(void) { }
    virtual int Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT);
};

int GameOver::Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT)
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
    
    sf::Text text("Game Over", font);
    text.setCharacterSize(70);
    text.setFillColor(sf::Color::Red);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, 4*SCREENHEIGHT / 10.0f));
    
    string score = "Score: ";
    sf::Text sPrint(score + to_string(Score::score), font);
    sPrint.setCharacterSize(60);
    sPrint.setFillColor(sf::Color::White);
    sf::FloatRect sRect = sPrint.getLocalBounds();
    sPrint.setOrigin(sRect.left + sRect.width / 2.0f, sRect.top + sRect.height / 2.0f);
    sPrint.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, SCREENHEIGHT / 2.0f));
    
    // "Next" button
    sf::Text nextButton("Next", font);
    nextButton.setCharacterSize(50);
    nextButton.setFillColor(sf::Color::Green);
    sf::FloatRect nextButtonRect = nextButton.getLocalBounds();
    nextButton.setOrigin(nextButtonRect.left + nextButtonRect.width / 2.0f, nextButtonRect.top + nextButtonRect.height / 2.0f);
    nextButton.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, (3*SCREENHEIGHT / 5.0f)));
    
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
                
                // "Next" button
                if((position.x > (nextButton.getPosition().x-(nextButtonRect.width/2)) && position.x < (nextButton.getPosition().x+(nextButtonRect.width/2)) && (position.y > (nextButton.getPosition().y-(nextButtonRect.height/2)) && position.y < (nextButton.getPosition().y + (nextButtonRect.height/2)))))
                {
                    // Proceed to high score prompt screen
                    return (5);
                }
            }
        }
        
        App.clear();
        App.draw(text);
        App.draw(sPrint);
        App.draw(nextButton);
        App.display();
    }
    
    // Never reach this point normally, but just in case, exit the application
    return (-1);
}
