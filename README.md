#### NOTE FROM NOVEMBER 7, 2019: THIS WEBPAGE IS CURRENTLY A WORK IN PROGRESS! :)

In the span of 2 months, this project was developed by 5 students for the "Advanced C++" course at De Anza College.

As one of the two leaders, my responsibilities included team coordinations, code integration, animation, developing the monster class and algorithms, and assisting with the development of the player class and main game code.

### Game Play

In this mini survival game, you play as a cat collecting coins. Meanwhile, monsters spawn at random; it is your goal to collect as many coins as possible to increase your score while surviving your encounters with these wandering monsters.

Beginning with 5 lives, any collision with these monsters counts as 1 deduction. You can attack by pressing "A", enabling you to defeat these monsters, or you could press "S" to temporarily brace yourself for 1 incoming attack. 

Monsters will gradually increase in speed and number as you collect more coins. At every 50 coins collected, a key spawns that enables you to open the door to a boss. Defeating this boss with your attacks will grant 3 lives.

If you ever find a cluser of monsters, you can drop a bomb in the selected area with a mouse click!

### Images
Title Screen
![titleScreen](screenshots/titleScreen.png)

Menu
![menu](screenshots/optionsScreen.png)

Idle
![idle](screenshots/idleGame.png)

Shielded
![shield](screenshots/shield.png)

Before attacking
![beforeAtkMonster](screenshots/beforeAtkMon.png)

After attacking
![afterAtkMonster](screenshots/afterAtkMon.png)

Monsters turn red upon collision
![monsterCollision](screenshots/monsterCollision.png)

Before bombing a cluster of monsters
![beforeBomb](screenshots/beforeBomb.png)

After bombing
![afterBomb](screenshots/afterBomb.png)

Closed door
![closeDoor](screenshots/closeDoor.png)

Key spawned 
![key](screenshots/keySpawn.png)

Opened door after obtaining key
![openDoor](screenshots/openDoor.png)

Boss at full health
![bossFullHealth](screenshots/boss1.png)

Boss after a few attacks
![bossBeingAtk](screenshots/boss2.png)

Game over screen
![gameOver](screenshots/gameOver.png)

### Code 
```c++
//  Monster.cpp
//
//  Created by Johnny Nguyen and Felicia Dewanaga
//  Copyright © 2019 Johnny Nguyen and Felicia Dewanaga
//  All rights reserved.

class Monster : public Entity
{
private:
    // Textures
    sf::Texture movementOneTexture;
    sf::Texture movementTwoTexture;
    sf::Texture collisionTexture;
    
    bool alive = true;
    int direction = 0; // 0 = Up, 1 = Down, 2 = Left, 3 = Right
    float movementSpeed = 2;
    int movementCounter = 0;
    int movementLength = 55;
    bool bigBoss;
    
public:
    // Constructor
    Monster(sf::Texture& monsterTexture, sf::Texture& monsterTwoTexture, sf::Texture& monsterCollisionTexture, float chamberx, float chambery, bool boss = false);
    ~Monster();
    
    // Animations
    void movementAnimation();
    void collisionAnimation() { sprite.setTexture(collisionTexture); }
    
    
    // Functions
    int randomNumber(int max);
    bool getAlive();
    void setAlive(bool a);
    void increaseSpeed(float inputSpeedNumber) { if (movementSpeed < 15) movementSpeed += inputSpeedNumber; }
    void updateMovement(const int SCREENWIDTH, const int BG_HEIGHT);
};
```

```c++
//  Monster.cpp
//
//  Created by Johnny Nguyen and Felicia Dewanaga
//  Copyright © 2019 Johnny Nguyen and Felicia Dewanaga
//  All rights reserved.

/*
 Description: This method handles the movement of the monster. It uses a random number calculator to determine the direction and moves by the set speed. There are statements in place to make sure a monster does not move out of the boundaries and reacts correctly.
 Parameters: width of the screen, height of the screen
 */
void Monster::updateMovement(const int SCREENWIDTH, const int BG_HEIGHT)
{
    if (direction == 0) // Up
    {
        if (image.getPixel(sprite.getPosition().x, sprite.getPosition().y - movementSpeed) == sf::Color::White)
        {
            sprite.move(0, -movementSpeed );
        }
    }
    else if (direction == 1) // Down
    {
        if (image.getPixel(sprite.getPosition().x, sprite.getPosition().y + movementSpeed) == sf::Color::White)
        {
            sprite.move(0, movementSpeed);
        }
    }
    else if (direction == 2) // Left
    {
        if (image.getPixel(sprite.getPosition().x - movementSpeed, sprite.getPosition().y) == sf::Color::White)
        {
            if (bigBoss == true)
                sprite.setTextureRect(sf::IntRect(0, 0, 500, 200)); //unflips sprite using sprite.setTextureRect(sf::IntRect(0, 0, width, height));
            sprite.move(-movementSpeed, 0);
        }
    }
    else if (direction == 3) // Right
    {
        if (image.getPixel(sprite.getPosition().x + movementSpeed, sprite.getPosition().y) == sf::Color::White)
        {
            if (bigBoss == true)
                sprite.setTextureRect(sf::IntRect(500, 0, -500, 200)); //flips sprite using sprite.setTextureRect(sf::IntRect(width, 0, -width, height));
            sprite.move(movementSpeed, 0);
        }
    }
    else
    {
        // No movement
    }
    
    // Prevent monsters from leaving the window
    if (image.getPixel(sprite.getPosition().x, sprite.getPosition().y - 30) == sf::Color::Black)//sprite.getPosition().y < 85) // Hitting top wall
    {
        direction = 1;
    }
    else if (image.getPixel(sprite.getPosition().x, sprite.getPosition().y + 30) == sf::Color::Black) //sprite.getPosition().y >  BACKGROUNDSIZE.y + 15)//BG_HEIGHT + 15) // Hitting bottom wall
    {
        direction = 0;
    }
    else if (image.getPixel(sprite.getPosition().x - 30, sprite.getPosition().y) == sf::Color::Black) //sprite.getPosition().x < 35) // Hitting left wall
    {
        direction = 3;
    }
    else if (image.getPixel(sprite.getPosition().x + 30, sprite.getPosition().y) == sf::Color::Black) //sprite.getPosition().x > BACKGROUNDSIZE.x - 20) // SCREENWIDTH - 20) // Hitting right wall
    {
        direction = 2;
    }
    
    
    movementCounter++;
    
    
    if (movementCounter >= movementLength)
    {
        /* If randomNumber(5), and since we only have 4 numbers for direction,
         there will be a 4/5 chance that the monster will move. */
        direction = randomNumber(6);
        movementCounter = 0;
    }
}

/*
 Description: This method returns a random number from 0 to max.
 Paramaters: integer max
 Return: integer generated
 */
int Monster::randomNumber(int max)
{
    
    int randomNumber;
    randomNumber = rand() % (max + 1);
    return randomNumber;
}
```

### Reflection and Thoughts

Even though this is a simple game, the development process was difficult—especially considering that this was everyone's first time creating a game. I picked up animation as a responsibility since no one on my team had artistic talent; figuring out this process added a valuable diversity to my skillset.

### Note

This project requires linking of SFML library and that all assets are in the same directory as the code files.
Theme music size (https://youtu.be/gsr19Kdf3Lk) was too large for GitHub, so know that it could not be included.
