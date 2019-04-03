//  HighScorePrompt.h
//    cScreen 5
//
//  Created by Manxin Zhang.
//  Copyright © 2019 Manxin Zhang.
//  All rights reserved.

#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <map>

#include "cScreen.h"

using namespace std;

const size_t MaxNumOfScores = 10;
void eraseScoreFile(const char* filename);
void writeToScoreFile(const char* filename, multimap<int, string>);
int readFromScoreFile(const char* filename, multimap<int, string>&);

class HighScorePrompt : public cScreen
{
public:
    HighScorePrompt(void) { }
    virtual int Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT);
};

int HighScorePrompt::Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT)
{
    string name = "";
    int score = Score::score;
    
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
    std::ostringstream sout;
    
    if ((highScores.size() < 10 || score > (highScores.begin())->first) && score > 0) {
        sout << "Congratulations!" << endl;
        sout << "You made it into the top 10!" << endl;
        sout << endl;
        sout << "Enter your name: ";
        sout << endl;
    }
    else {
        sout << "Nice job!" << endl;
        sout << "Play again to be on the" << endl;
        sout << "list of Top 10 players!" << endl;
        sout << endl;
        sout << endl;
    }
    text.setString(sout.str());
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, SCREENHEIGHT / 2.0f));
    
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
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128) {
                    name += static_cast<char>(event.text.unicode);
                    sout << static_cast<char>(event.text.unicode);
                    text.setString(sout.str());
                }
            }
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
                    if (!name.empty()) {
                        highScores.insert({ score, name });
                        if (highScores.size() > 10)
                            highScores.erase((highScores.begin())->first);
                        writeToScoreFile(filename, highScores);
                    }
                    // Proceed to high score list screen
                    return (6);
                }
            }
            App.draw(text);
        }
        
        App.clear();
        App.draw(text);
        App.draw(nextButton);
        App.display();
    }
    
    return (-1);
}

void eraseScoreFile(const char* filename) {
    ofstream fout(filename);
}

void writeToScoreFile(const char* filename, multimap<int, string> myMap) {
    ofstream fout(filename);
    try {
        if (!fout) {
            throw FileOpenException(filename);
        }
    }
    catch (FileOpenException& e) {
        cout << "File not found. Creating new file: " << e.what() << endl;
        ofstream fout(filename);
        fout.close();
        return;
    }
    
    if (myMap.size() == 0) {
        return;
    }
    for (auto it : myMap) {
        fout << it.first << "  " << it.second << endl;
    }
    
    fout.close();
}

int readFromScoreFile(const char* filename, multimap<int, string>& myMap) {
    int count = 0;
    ifstream fin(filename);
    try {
        if (!fin) {
            throw FileOpenException(filename);
        }
    }
    catch (FileOpenException& e) {
        cout << "File not found. Creating new file: " << e.what() << endl;
        ofstream fout(filename);
        fout.close();
        return count;
    }
    
    if (fin.peek() == std::ifstream::traits_type::eof()) {
        return count;
    }
    
    int score = 0;
    string name = "";
    
    while (fin >> score) {
        fin >> name;
        myMap.insert({ score, name });
        count++;
    }
    fin.close();
    return count;
}
