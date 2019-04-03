
//    CIS 29 Project
//    Group #4
//    Winter Quarter 2019
//
//  main.cpp
//
//  Created by Mihika Marathe, Felicia Dewanaga, Johnny Nguyen, Manxin Zhang, Alan Rodriguez.
//  Copyright © 2019 Mihika Marathe, Felicia Dewanaga, Johnny Nguyen, Manxin Zhang, Alan Rodriguez.
//  All rights reserved.

/********************************************************************
 Name of each screen and corresponding position within cScreen vector
 because each screen returns a number to the main loop for traversal.
 Introduction: 0
 HowToPlayOne: 1
 HowToPlayTwo: 2
 GameScreen: 3
 GameOver: 4
 HighScorePrompt: 5
 HighScoreDisplay: 6
 Menu: 7
 GameMode: 8
 ********************************************************************/

#include <SFML/Graphics.hpp>

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "screens.h"

int main(int argc, char** argv)
{
    const int SCREENWIDTH = 1024;
    const int SCREENHEIGHT = 720;
    srand(static_cast<unsigned int>(time(NULL))); // To randomize the rand() function
    
    // Screen variables
    std::vector<cScreen*> Screens;
    int screenIndex = 0;
    
    // Window application
    sf::RenderWindow App(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "CIS 29 Game Project");
    App.setFramerateLimit(60);
    
    // Screens preparation
    Introduction s0;
    Screens.push_back(&s0);
    HowToPlayOne s1;
    Screens.push_back(&s1);
    HowToPlayTwo s2;
    Screens.push_back(&s2);
    GameScreen s3;
    Screens.push_back(&s3);
    GameOver s4;
    Screens.push_back(&s4);
    HighScorePrompt s5;
    Screens.push_back(&s5);
    HighScoreDisplay s6;
    Screens.push_back(&s6);
    Menu m;
    Screens.push_back(&m);
    GameMode gm;
    Screens.push_back(&gm);
    
    // Main loop
    while (screenIndex >= 0)
    {
        screenIndex = Screens[screenIndex]->Run(App, SCREENWIDTH, SCREENHEIGHT);
    }
}

/*
 jscreens mihika$ g++ -Wall -std=c++11 *.cpp -Iinclude -I/usr/local/include -L/usr/local/lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -o main
 */

