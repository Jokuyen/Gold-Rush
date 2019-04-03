
//  GameScreen.h
//  cScreen 3
//
//  Created by Mihika Marathe, Felicia Dewanaga, Johnny Nguyen, Manxin Zhang, Alan Rodriguez.
//  Copyright © 2019 Mihika Marathe, Felicia Dewanaga, Johnny Nguyen, Manxin Zhang, Alan Rodriguez.
//  All rights reserved.

#ifndef screen_3_h
#define screen_3_h

#include <SFML/Audio.hpp>

#include <iostream>
#include <string>

#include "Monster.h"
#include "Player.h"
#include "Coins.h"
#include "Bomb.h"
#include "Explosion.h"

using namespace std;

////////////////////////////////////////
// Initialize score in Score namespace
namespace Score
{
    int score = 0;
}

//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////// Assets

// Game assets (Music + Background)
const char* THEMEMUSIC = "American Beauty.wav";
const char* BACKGROUNDIMAGE = "background.png";
const char* BORDERIMAGE = "backgroundClosedMask.png";
const char* BORDER2IMAGE = "backgroundOpenedMask.png";
const char* DOORIMAGE = "door.png";
const char* KEYIMAGE = "key.png";

// Player assets
const char* PLAYERIMAGE = "catSpriteSheet.png";
const char* SHIELDIMAGE = "catSpriteSheetTwo.png";
const char* FLIPPEDPLAYERIMAGE = "flippedCatSpriteSheet.png";
const char* FLIPPEDSHIELDIMAGE = "flippedCatSpriteSheetTwo.png";
const char* PLAYERAHURTSOUND = "bodyimpact_jack_01.wav";

// Coin assets
const char* COIN_ONE = "coin1.png";
const char* COIN_TWO = "coin2.png";
const char* COIN_THREE = "coin3.png";
const char* COIN_FOUR = "coin4.png";
const char* COIN_FIVE = "coin5.png";
const char* COIN_SIX = "coin6.png";
const char* COIN_SOUND = "1_Coins.wav";

// Monster assets
const char* MONSTERIMAGE = "monster.png";
const char* MONSTERTWOIMAGE = "monsterTwo.png";
const char* MONSTERCOLLISIONIMAGE = "monsterCollision.png";
const char* MONSTERSOUND = "cyborg_hurt.wav";

// BigBoss assets
const char* BIGBOSSIMAGE = "octopus.png";
const char* BIGBOSSTWOIMAGE = "octopus2.png";
const char* BIGBOSSCOLLISIONIMAGE = "octopusCollision.png";
const char* BIGBOSSHURTIMAGE = "octopusHurt.png";

// Bomb assets
const char* BOMBIMAGE = "missile.png";
const char* EXPLOSIONIMAGE = "explosion.png";
const char* EXPLOSIONSOUND = "BOOM.wav";

////////////////////////////////////////////////////////////////
// Declared functions

// Used to randomly place monsters on x-axis
float randomNumber(int lower, int upper)
{
    float num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

sf::Image getBorderImage()
{
    // Background mask
    sf::Texture borderTexture;
    
    try
    {
        if (!borderTexture.loadFromFile(BORDERIMAGE))
        {
            throw FileOpenException(BORDERIMAGE);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    
    return borderTexture.copyToImage();
}

sf::Image getBorder2Image()
{
    // Background mask
    sf::Texture border2Texture;
    try
    {
        if (!border2Texture.loadFromFile(BORDER2IMAGE))
        {
            throw FileOpenException(BORDER2IMAGE);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    
    return border2Texture.copyToImage();
}

/////////////////////////////////////////////////////
////////////////////////////////// GameScreen class
class GameScreen : public cScreen
{
public:
    GameScreen(void) { }
    virtual int Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT);
};

///////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////// Game setup
int GameScreen::Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT)
{
    bool Running = true;
    bool pause = false;
    
    ///////////////////////////////////////////////////////
    //////////////////////////////////// Setting up files
    
    // Font setup
    sf::Font font;
    try
    {
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
    
    // Music setup
    sf::Music theme;
    try
    {
        if (!theme.openFromFile(THEMEMUSIC))
        {
            throw FileOpenException(THEMEMUSIC);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    theme.setLoop(true);
    theme.setVolume(30);
    theme.play();
    
    // Background setup
    const int BG_WIDTH = 2700;
    const int BG_HEIGHT = 1800;
    sf::RectangleShape background(sf::Vector2f(BG_WIDTH, BG_HEIGHT));
    background.setPosition(sf::Vector2f(0, 0));
    sf::Texture backgroundTexture;
    try
    {
        if (!backgroundTexture.loadFromFile(BACKGROUNDIMAGE))
        {
            throw FileOpenException(BACKGROUNDIMAGE);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    background.setTexture(&backgroundTexture);
    
    // Key setup
    sf::RectangleShape key(sf::Vector2f(60, 60));
    sf::Texture keyTexture;
    try
    {
        if (!keyTexture.loadFromFile(KEYIMAGE))
        {
            throw FileOpenException(KEYIMAGE);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    key.setTexture(&keyTexture);
    bool gotKey = false;
    
    // Door setup
    sf::RectangleShape door(sf::Vector2f(160, 60));
    door.setPosition(sf::Vector2f(1210, 700));
    sf::Texture doorTexture;
    try
    {
        if (!doorTexture.loadFromFile(DOORIMAGE))
        {
            throw FileOpenException(DOORIMAGE);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    door.setTexture(&doorTexture);
    
    // Player setup
    sf::Texture playerTexture;
    try
    {
        if (!playerTexture.loadFromFile(PLAYERIMAGE))
        {
            throw FileOpenException(PLAYERIMAGE);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    sf::Texture shieldTexture;
    try
    {
        if (!shieldTexture.loadFromFile(SHIELDIMAGE))
        {
            throw FileOpenException(SHIELDIMAGE);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    
    sf::Texture flippedPlayerTexture;
    try
    {
        if (!flippedPlayerTexture.loadFromFile(FLIPPEDPLAYERIMAGE))
        {
            throw FileOpenException(FLIPPEDPLAYERIMAGE);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    sf::Texture flippedShieldTexture;
    try
    {
        if (!flippedShieldTexture.loadFromFile(FLIPPEDSHIELDIMAGE))
        {
            throw FileOpenException(FLIPPEDSHIELDIMAGE);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    Player playerObj(playerTexture, shieldTexture, flippedPlayerTexture, flippedShieldTexture, SCREENWIDTH, BG_HEIGHT);
    playerObj.setPosition(200, 1000);
    
    // Player sound setup
    sf::SoundBuffer playerhurtBuffer;
    try
    {
        if (!playerhurtBuffer.loadFromFile(PLAYERAHURTSOUND))
        {
            throw FileOpenException(PLAYERAHURTSOUND);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    sf::Sound playerhurtsound;
    playerhurtsound.setBuffer(playerhurtBuffer);
    playerhurtsound.setVolume(100);
    
    // Bomb setup
    sf::Texture bombTexture;
    Bomb* bombPtr = nullptr;
    try
    {
        if (!bombTexture.loadFromFile(BOMBIMAGE))
        {
            throw FileOpenException(BOMBIMAGE);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    int count = 0;
    bool explode = false;
    
    // Explosion setup
    sf::Texture explosionTexture;
    try
    {
        if (!explosionTexture.loadFromFile(EXPLOSIONIMAGE))
        {
            throw FileOpenException(EXPLOSIONIMAGE);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    Explosion explosion(explosionTexture);
    sf::SoundBuffer explosionBuffer;
    try
    {
        if (!explosionBuffer.loadFromFile(EXPLOSIONSOUND))
        {
            throw FileOpenException(EXPLOSIONSOUND);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    sf::Sound explosionSound;
    explosionSound.setBuffer(explosionBuffer);
    explosionSound.setVolume(100);
    
    // Header line setup
    string name = "Gold Rush";
    sf::Text txt(name + "\t\t\t\tScore: " + to_string(playerObj.getScore()) + "\t\t\t\tLives: " + to_string(playerObj.getLives()), font);
    txt.setCharacterSize(25);
    txt.setFillColor(sf::Color::White);
    
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////// Setting up monsters
    
    // Monster Vector Array
    std::vector<Monster *>::const_iterator monsterIterator;
    std::vector<Monster *> monsterArray;
    
    // Monster
    sf::Texture monsterTexture;
    sf::Texture monsterTwoTexture;
    sf::Texture monsterCollisionTexture;
    sf::SoundBuffer monsterSoundBuffer;
    try
    {
        if (!monsterTexture.loadFromFile(MONSTERIMAGE))
        {
            throw FileOpenException(MONSTERIMAGE);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    try
    {
        if (!monsterTwoTexture.loadFromFile(MONSTERTWOIMAGE))
        {
            throw FileOpenException(MONSTERTWOIMAGE);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    try
    {
        if (!monsterCollisionTexture.loadFromFile(MONSTERCOLLISIONIMAGE))
        {
            throw FileOpenException(MONSTERCOLLISIONIMAGE);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    try
    {
        if (!monsterSoundBuffer.loadFromFile(MONSTERSOUND))
        {
            throw FileOpenException(MONSTERSOUND);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    sf::Sound monsterSound;
    monsterSound.setBuffer(monsterSoundBuffer);
    monsterSound.setVolume(100);
    float speedNumber = 0.5;
    int spawnCount = 1;
    
    // Big Boss
    sf::Texture bigBossTexture;
    sf::Texture bigBossTwoTexture;
    sf::Texture bigBossCollisionTexture;
    sf::Texture bigBossHurtTexture;
    try
    {
        if (!bigBossTexture.loadFromFile(BIGBOSSIMAGE))
        {
            throw FileOpenException(BIGBOSSIMAGE);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    try
    {
        if (!bigBossTwoTexture.loadFromFile(BIGBOSSTWOIMAGE))
        {
            throw FileOpenException(BIGBOSSTWOIMAGE);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    try
    {
        if (!bigBossCollisionTexture.loadFromFile(BIGBOSSCOLLISIONIMAGE))
        {
            throw FileOpenException(BIGBOSSCOLLISIONIMAGE);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    try
    {
        if (!bigBossHurtTexture.loadFromFile(BIGBOSSHURTIMAGE))
        {
            throw FileOpenException(BIGBOSSHURTIMAGE);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    Monster* bigBoss = new Monster(bigBossTexture, bigBossTwoTexture, bigBossCollisionTexture, 2 * 2100, 2 * 300, true);
    bool bigBossAlive = true;
    int bigBossCountdown = 0;
    
    // Big Boss health bar
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(300, 15));
    rectangle.setFillColor(sf::Color::Magenta);
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setOutlineThickness(5);
    sf::Text bossTxt("Monster Health", font);
    bossTxt.setCharacterSize(30);
    bossTxt.setFillColor(sf::Color::Red);
    
    ///////////////////////////////////////////////////////////////
    //////////////////////////////////////////// Setting up coins
    
    // Coins
    std::vector<Coins*> coinArray;
    
    sf::Texture cOne;
    cOne.loadFromFile(COIN_ONE);
    sf::Texture cTwo;
    cTwo.loadFromFile(COIN_TWO);
    sf::Texture cThree;
    cThree.loadFromFile(COIN_THREE);
    sf::Texture cFour;
    cFour.loadFromFile(COIN_FOUR);
    sf::Texture cFive;
    cFive.loadFromFile(COIN_FIVE);
    sf::Texture cSix;
    cSix.loadFromFile(COIN_SIX);
    
    for (int i = 0; i < 15; i++)
    {
        Coins* coinPtr = new Coins(cOne, cTwo, cThree, cFour, cFive, cSix, BG_HEIGHT, SCREENWIDTH);
        coinArray.push_back(coinPtr);
    }
    
    // Coin sound setup
    sf::SoundBuffer coinSoundBuffer;
    try
    {
        if (!coinSoundBuffer.loadFromFile(COIN_SOUND))
        {
            throw FileOpenException(COIN_SOUND);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    sf::Sound coinSound;
    coinSound.setBuffer(coinSoundBuffer);
    coinSound.setVolume(100);
    
    ///////////////////////////////////////////////////
    //////////////////////////////////////////// Misc
    
    // Camera view
    sf::View view;
    view.reset(sf::FloatRect(0, 0, SCREENWIDTH, SCREENHEIGHT));
    sf::Vector2f viewPosition(SCREENWIDTH / 2, SCREENHEIGHT / 2);
    
    // Time management variables
    sf::Clock monsterSpawnClock;
    sf::Clock monsterSpeedClock;
    sf::Clock shieldDelayClock;
    sf::Clock shieldPopClock;
    
    sf::Event event;
    
    //////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////// Game loop
    while (Running)
    {
        // Time management
        sf::Time monsterSpawnTimer = monsterSpawnClock.getElapsedTime();
        sf::Time monsterSpeedTimer = monsterSpeedClock.getElapsedTime();
        sf::Time shieldDelayTimer = shieldDelayClock.getElapsedTime();
        sf::Time shieldPopTimer = shieldPopClock.getElapsedTime();
        
        // Verifying events
        while (App.pollEvent(event))
        {
            // Window closed
            if (event.type == sf::Event::EventType::Closed)
                return (-1);
            // Key pressed
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Q: // Back to menu
                        testmode = false;
						Entity::setImage(getBorderImage());
                        App.setView(App.getDefaultView());
                        return (7);
                        break;
                    case sf::Keyboard::Space:
                        pause = !pause;
                        break;
                    case sf::Keyboard::R:
                        testmode = false;
                    default:
                        break;
                }
            }
        }
        
        bool attack = false;
        
        if (!pause)
        {
            App.draw(background);
            
            //////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////// Player mechanism
            
            // Attack
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                attack = true;
                playerObj.incrementCurrentAttackTexture();
                playerObj.attackAnimation();
            }
            // Movement
            else
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    playerObj.move(Player::Left);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    playerObj.move(Player::Right);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    playerObj.move(Player::Up);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    playerObj.move(Player::Down);
                }
            }
            
            // Shield
            if (shieldDelayTimer.asSeconds() > 3)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    playerObj.applyShield();
                    shieldDelayClock.restart();
                    shieldPopClock.restart();
                }
            }
            if (shieldPopTimer.asSeconds() > 2.8 && shieldPopTimer.asSeconds() < 2.9)
            {
                playerObj.loseShield();
            }
            
            // Draw door first, then player (so player sprite is on top of door image)
            App.draw(door);
            playerObj.draw(App);
            
            // Bomb
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bombPtr == nullptr)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(App);
                if (mousePos.x > 0 && mousePos.y > 0)
                {
                    bombPtr = new Bomb(bombTexture);
                    bombPtr->moveBombToStartPosition(static_cast<float>(mousePos.x + viewPosition.x - SCREENWIDTH / 2), static_cast<float>(mousePos.y + viewPosition.y - SCREENHEIGHT / 2), static_cast<float>(viewPosition.y - SCREENHEIGHT / 2));
                }
            }
            bool bombDrop = false;
            if (bombPtr)
            {
                if (!bombPtr->move())
                {
                    bombDrop = true;
                }
            }
            if (bombPtr)
            {
                bombPtr->paint(App);
            }
            
            // Camera view
            if (playerObj.getPosition().x > SCREENWIDTH / 2)
            {
                if (playerObj.getPosition().x < 2700 - SCREENWIDTH / 2)
                {
                    viewPosition.x = playerObj.getPosition().x;
                }
                else
                {
                    viewPosition.x = 2700 - SCREENWIDTH / 2;
                }
            }
            else
            {
                viewPosition.x = SCREENWIDTH / 2;
            }
            
            if (playerObj.getPosition().y > SCREENHEIGHT / 2)
            {
                if (playerObj.getPosition().y < 1800 - SCREENHEIGHT / 2)
                {
                    viewPosition.y = playerObj.getPosition().y;
                }
                else
                {
                    viewPosition.y = 1800 - SCREENHEIGHT / 2;
                }
            }
            else
            {
                viewPosition.y = SCREENHEIGHT / 2;
            }
            
            view.setCenter(viewPosition);
            txt.setPosition(viewPosition.x - SCREENWIDTH / 2, viewPosition.y - SCREENHEIGHT / 2);
            bossTxt.setPosition(viewPosition.x - SCREENWIDTH / 2, viewPosition.y + SCREENHEIGHT / 2 - 50);
            rectangle.setPosition(viewPosition.x - SCREENWIDTH / 2 + 400, viewPosition.y + SCREENHEIGHT / 2 - 30);
            App.setView(view);
            
            ////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////// Monsters
            
            // Create new monster
            if (monsterSpawnTimer.asSeconds() > 5)
            {
                for (int i = 0; i < spawnCount; i++)
                {
                    monsterArray.push_back(new Monster(monsterTexture, monsterTwoTexture, monsterCollisionTexture, randomNumber(2 * 200, 2 * 1330), 2 * 1720));
                }
                monsterSpawnClock.restart();
            }
            
            // Monster loop
            int counter = 0;
            for (monsterIterator = monsterArray.begin(); monsterIterator != monsterArray.end(); monsterIterator++)
            {
                monsterArray[counter]->updateMovement(SCREENWIDTH, BG_HEIGHT);
                
                // Increase monsters' speed
                if (monsterSpeedTimer.asSeconds() > 5)
                {
                    monsterArray[counter]->movementAnimation();
                    monsterArray[counter]->increaseSpeed(speedNumber);
                    monsterSpeedClock.restart();
                }
                
                // Collision detection
                if (playerObj.hitByMonster(monsterArray[counter]->getPosition().x, monsterArray[counter]->getPosition().y, monsterArray[counter]->size()))
                {
                    monsterSound.play();
                    if (playerObj.getHit() == -1) {
                        std::cout << "Hit by monster!" << std::endl;
                        playerObj.setHit(counter);
                        if (testmode == false)
                        {
                            playerObj.loseLife();
                        }
                        txt.setString(name + "\t\t\t\tScore: " + to_string(playerObj.getScore()) + "\t\t\t\tLives: " + to_string(playerObj.getLives()));
                        monsterArray[counter]->collisionAnimation();
                    }
                }
                else
                {
                    if (playerObj.getHit() == counter)
                        playerObj.setHit(-1);
                }
                if (attack == true)
                {
                    if (playerObj.attack(monsterArray[counter]->getPosition().x, monsterArray[counter]->getPosition().y, monsterArray[counter]->size()))
                    {
                        playerhurtsound.play();
                        monsterArray[counter]->setAlive(false);
                        cout << "Attacked a monster!" << endl;
                        break;
                    }
                }
                
                if (bombDrop == true)
                {
                    if (bombPtr->hitByMonster(monsterArray[counter]->getPosition().x, monsterArray[counter]->getPosition().y, monsterArray[counter]->size()))
                    {
                        monsterArray[counter]->setAlive(false);
                    }
                }
                
                if ((*monsterIterator)->getAlive())
                {
                    monsterArray[counter]->draw(App);
                }
                counter++;
            }
            
            // Delete defeated monsters
            counter = 0;
            for (monsterIterator = monsterArray.begin(); monsterIterator != monsterArray.end(); monsterIterator++)
            {
                if (monsterArray[counter]->getAlive() == false)
                {
                    delete monsterArray[counter];
                    monsterArray[counter] = nullptr;
                }
                
                counter++;
            }
            monsterArray.erase(std::remove_if(monsterArray.begin(), monsterArray.end(), [](Monster *x) {return x == nullptr; }), monsterArray.end());
            
            // Bomb collision with monsters
            if (bombDrop == true)
            {
                explosionSound.play();
                explosion.startExplosion(bombPtr->getPosition());
                delete bombPtr;
                bombPtr = nullptr;
                bombDrop = false;
                explode = true;
            }
            if (explode)
            {
                explosion.draw(App);
                count++;
                if (count > 10)
                {
                    explode = false;
                    count = 0;
                    explosionSound.stop();
                }
            }
            
            //////////////////////////////////////////////////////////
            ////////////////////////////////////////////////// Coins
            
            // Coin generation
            for (int i = 0; i < 15; i++)
            {
                coinArray[i]->draw(App);
                coinArray[i]->animate();
                if (playerObj.collectCoin(coinArray[i]->getPosition().x, coinArray[i]->getPosition().y, coinArray[i]->size().x, coinArray[i]->size().y))
                {
                    coinSound.play();
                    coinArray[i]->collide();
                    txt.setString(name + "\t\t\t\tScore: " + to_string(playerObj.getScore()) + "\t\t\t\tLives: " + to_string(playerObj.getLives()));
                    // Coin events based on number of collected coins
                    
                    // Increase monster difficulty
                    if (playerObj.getScore() % 10 == 0)
                    {
                        speedNumber += 0.05;
                    }
                    if (playerObj.getScore() % 100 == 0)
                    {
                        spawnCount++;
                    }
                    
                    // Respawn boss
                    if (bigBossAlive == false && playerObj.getScore() % 50 == 0)
                    {
                        bigBossAlive = true;
                        rectangle.setSize(sf::Vector2f(300, 15));
                        rectangle.setFillColor(sf::Color::Magenta);
                        rectangle.setOutlineColor(sf::Color::Red);
                        rectangle.setOutlineThickness(5);
                        bossTxt.setFillColor(sf::Color::Red);
                    }
                    
                    // Spawn key
                    if (bigBossAlive == true && playerObj.getScore() % 50 == 0)
                    {
                        std::cout << "Key spawned!\n";
                        key.setPosition(sf::Vector2f(playerObj.getPosition().x, playerObj.getPosition().y + 150));
                        key.setFillColor(sf::Color::White);
                    }
                    
                    // Reclose door
                    if (gotKey == true && bigBossAlive == false)
                    {
                        gotKey = false;
                        Entity::setImage(getBorderImage());
                        door.setFillColor(sf::Color::White);
                    }
                }
            }
            
            // Open door
            if (gotKey == false && abs(playerObj.getPosition().x - key.getPosition().x) < 30 && abs(playerObj.getPosition().y - key.getPosition().y) < 30)
            {
                std::cout << "Key obtained!\n";
                gotKey = true;
                key.setFillColor(sf::Color::Transparent);
                key.setPosition(sf::Vector2f(0, 0));
                door.setFillColor(sf::Color::Transparent);
                Entity::setImage(getBorder2Image());
            }
            App.draw(key);
            
            /////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////// Big Boss
            if (bigBossAlive == true)
            {
                if (bigBossCountdown < 35)
                {
                    bigBossCountdown++;
                }
                if (bigBossCountdown > 10)
                {
                    bigBoss->updateMovement(SCREENWIDTH, BG_HEIGHT);
                    bigBoss->movementAnimation();
                    bigBoss->increaseSpeed(speedNumber);
                    bigBossCountdown = 0;
                }
                
                // Big boss collision detection
                if (attack == false)
                {
                    if (playerObj.hitByMonster(bigBoss->getPosition().x, bigBoss->getPosition().y, bigBoss->size()))
                    {
                        if (playerObj.getHit() == -1)
                        {
                            playerObj.setHit(-20);
                            if (testmode == false)
                            {
                                playerObj.loseLife();
                            }
                            txt.setString(name + "\t\t\t\tScore: " + to_string(playerObj.getScore()) + "\t\t\t\tLives: " + to_string(playerObj.getLives()));
                            bigBoss->collisionAnimation();
                        }
                    }
                    else
                    {
                        if (playerObj.getHit() == -20)
                        {
                            playerObj.setHit(-1);
                        }
                    }
                }
                
                if (attack == true)
                {
                    if (playerObj.attack(bigBoss->getPosition().x, bigBoss->getPosition().y, bigBoss->size()))
                    {
                        if (playerObj.getHit() == -1)
                        {
                            playerhurtsound.play();
                            playerObj.setHit(-20);
                            rectangle.setSize(sf::Vector2f(rectangle.getSize().x - 100, 15));
                        }
                    }
                    else
                    {
                        if (playerObj.getHit() == -20)
                        {
                            playerObj.setHit(-1);
                        }
                    }
                }
                
                // Health bar under zero
                if (rectangle.getSize().x < 0)
                {
                    rectangle.setFillColor(sf::Color::Transparent);
                    rectangle.setOutlineColor(sf::Color::Transparent);
                    App.draw(rectangle);
                    bigBossAlive = false;
                    if (testmode == false)
                    {
                        playerObj.increaseLife();
                    }
                    txt.setString(name + "\t\t\t\tScore: " + to_string(playerObj.getScore()) + "\t\t\t\tLives: " + to_string(playerObj.getLives()));
                    playerObj.setHit(-1);
                }
                else
                {
                    bigBoss->draw(App);
                }
                
                App.draw(bossTxt);
                if (rectangle.getSize().x >= 0)
                {
                    App.draw(rectangle);
                }
            }
            
            ////////////////////////////////////////////////////////////////////
            /////////////////////////////////////// Game Over + Memory Cleanup
            if (playerObj.getLives() == 0 && testmode == false)
            {
                counter = 0;
                for (monsterIterator = monsterArray.begin(); monsterIterator != monsterArray.end(); monsterIterator++)
                {
                    delete monsterArray[counter];
                    monsterArray[counter] = nullptr;
                    counter++;
                }
                for (int i = 0; i < coinArray.size(); i++)
                {
                    delete coinArray[i];
                    coinArray[i] = nullptr;
                }
                if (bigBoss != nullptr)
                {
                    delete bigBoss;
                    bigBoss = nullptr;
                }
				Entity::setImage(getBorderImage());
                App.setView(App.getDefaultView());
                Score::score = playerObj.getScore();
                // Proceed to game over screen
                return (4);
            }
            
            App.draw(txt);
            App.display();
            App.clear();
        }
    }
    
    // Never reach this point normally, but just in case, exit the application
    return (-1);
}

// Initialize static variable in Entity.h with declared function
sf::Image Entity::image = getBorderImage();

#endif /* screen_3_h */
