#### NOTE FROM NOVEMBER 7, 2019: THIS WEBPAGE IS CURRENTLY A WORK IN PROGRESS! :)

Over the span of 2 months, this project was developed by 5 students for the "Advanced C++" course at De Anza College.

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

The movement of the monster objects are dictated by a function that generates a random number. Based on the number, there is a if-else case that moves the monster in one direction, or not move at all if the number isn't in any of the if-statements.

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

### Notable Bugs

// This section in progress

- Big boss respawn

- Remasking door after quitting game

### Animation Process

// This section in progress

### Final Thoughts

While working on the monster algorithm, I had to recall how other games handled their monsters' mechanism. At first, my monsters moved endlessly without pausing, so I had to update my algorithm accordingly to fix that. This project gave me a deeper appreciation of the work that was put into actual games; little details can make some pretty big impacts.

Although a simple game, the development process was incredibly difficult—especially considering that this was everyone's first time creating a game. I picked up animation as a responsibility since no one on my team considered themselves an artistic person. Figuring animation out exposed me to an aspect of programming I've never experienced before; the research and trial & error improved me as a programmer. From this project, I understood the importance of task delegation as well as how critical the design process is at the beginning. In addition, I gained experience with reading other people's code, maintaining a code style throughout the project, and solving tricky bugs. As a leader, I tackled challenges with zest and gained the pride of figuring out a solution. Overall, this simple game required tons of effort and growth from me, which I am grateful to have provided!

### Note

This project requires linking of SFML library and that all assets are in the same directory as the code files.

Theme music size (https://youtu.be/gsr19Kdf3Lk) was too large for GitHub, so know that it could not be included.
