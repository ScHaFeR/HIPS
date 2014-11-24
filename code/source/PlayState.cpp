/*
 *  PlayState.cpp
 *  Normal "play" state
 *
 *  Created by Marcelo Cohen on 08/13.
 *  Copyright 2013 PUCRS. All rights reserved.
 *
 */

#include <iostream>
#include <cmath>
#include "Game.h"
#include "PlayState.h"
#include "InputManager.h"


#include <time.h>
#include <stdlib.h>

PlayState PlayState::m_PlayState;

using namespace std;

void PlayState::init()
{
    firstTime = true;
    srand(time(NULL));

    int i=0;
    for(i=0; i<BOTMAX+3; i++)
    {
        int numx = 0;
        int numy = 0;

        int j = 0;
        int k = i;
        if (k > BOTMAX)
        {
            k = BOTMAX;
        }

        int rangexBot = 1280 - 64;
        numx = 32 + rand() / (RAND_MAX / (rangexBot-32+1)+1);
        int rangeyBot = 736 - 64;
        numy = 32 + rand() / (RAND_MAX / (rangeyBot-32+1)+1);

        for (j=0; j < k; j++)
        {

            int botx = bot[j].getPosition().x;
            int boty = bot[j].getPosition().y;

            if ( !((numx > (botx+32)) || (numx < (botx-32))) && !((numy > (boty+32)) || (numy < (boty-32))) )
            {
                int rangexBot = 1280 - 64;
                numx = 32 + rand() / (RAND_MAX / (rangexBot-32+1)+1);
                int rangeyBot = 736 - 64;
                numy = 32 + rand() / (RAND_MAX / (rangeyBot-32+1)+1);
                j=0;
            }

        }

        if (i < BOTMAX)
        {
            bot[i].loadXML("data/img/stormtrooper.xml");
            bot[i].setPosition(numx,numy);
            bot[i].loadAnimation("data/img/stormtrooperanim.xml");
            bot[i].setAnimRate(10);
        }
        if (i == BOTMAX+1)
        {
            player1.loadXML("data/img/stormtrooper.xml");
            player1.setPosition(numx,numy);
            player1.loadAnimation("data/img/stormtrooperanim.xml");
            player1.setAnimRate(10);
        }
        if (i == BOTMAX+2)
        {
            player2.loadXML("data/img/stormtrooper.xml");
            player2.setPosition(numx,numy);
            player2.loadAnimation("data/img/stormtrooperanim.xml");
            player2.setAnimRate(10);
        }

    }

    statue[0].loadXML("data/img/darthvader.xml");
    statue[0].setPosition(320,150);
    statue[1].loadXML("data/img/darthvader.xml");
    statue[1].setPosition(960,150);
    statue[2].loadXML("data/img/darthvader.xml");
    statue[2].setPosition(640,368);
    statue[3].loadXML("data/img/darthvader.xml");
    statue[3].setPosition(320,518);
    statue[4].loadXML("data/img/darthvader.xml");
    statue[4].setPosition(960,518);



    map = new tmx::MapLoader("data/maps");
    map->Load("hips.tmx");

    dirx = 0; // direção do sprite: para a direita (1), esquerda (-1)
    diry = 0;
    int z = 0;
    for (z = 0; z <= BOTMAX ; z ++)
    {
        dirbotx[z] = 0;
        dirboty[z] = 0;
        botDirection[z] = 0;
        walk[z] = 0;
    }

    im = cgf::InputManager::instance();

    //GERAL
    im->addKeyInput("quit", sf::Keyboard::Escape);

    //PLAYER 1
    im->addKeyInput("left", sf::Keyboard::Left);
    im->addKeyInput("right", sf::Keyboard::Right);
    im->addKeyInput("up", sf::Keyboard::Up);
    im->addKeyInput("down", sf::Keyboard::Down);
    im->addKeyInput("RCtrl", sf::Keyboard::RControl);

    //PLAYER 2
    im->addKeyInput("a", sf::Keyboard::A);
    im->addKeyInput("d", sf::Keyboard::D);
    im->addKeyInput("w", sf::Keyboard::W);
    im->addKeyInput("s", sf::Keyboard::S);
    im->addKeyInput("e", sf::Keyboard::E);

    im->addKeyInput("pause", sf::Keyboard::P);

    if (!font.loadFromFile("data/fonts/arial.ttf"))
    {
        cout << "Cannot load arial.ttf font!" << endl;
        exit(1);
    }

    clock.restart();
    sf::Time elapsed1 = clock.getElapsedTime();
    GlobalTime = (int) elapsed1.asSeconds();
    InGameTime = 120;

    cout << "PlayState Init Successful" << endl;
}

void PlayState::botWalk()
{
    dirbotx[botLoop] = 0;
    dirboty[botLoop] = 0;

    if(botDirection[botLoop] == 0)
    {
        if(bot[botLoop].getYspeed() >= 0)
        {
            bot[botLoop].setAnimation("walk-up");
            bot[botLoop].play();
        }
        dirboty[botLoop] = -1;
        walk[botLoop] ++;
    }
    else if(botDirection[botLoop] == 1)
    {
        if(bot[botLoop].getYspeed() <= 0)
        {
            bot[botLoop].setAnimation("walk-down");
            bot[botLoop].play();
        }

        dirboty[botLoop] = 1;
        walk[botLoop]++;
    }
    else if(botDirection[botLoop] == 2)
    {
        if(bot[botLoop].getXspeed() >= 0)
        {
            bot[botLoop].setAnimation("walk-left");
            bot[botLoop].play();
        }

        dirbotx[botLoop]  = -1;
        walk[botLoop]++;
    }
    else if(botDirection[botLoop] == 3)
    {
        if(bot[botLoop].getXspeed() <= 0)
        {
            bot[botLoop].setAnimation("walk-right");
            bot[botLoop].play();
        }

        dirbotx[botLoop]  = 1;
        walk[botLoop]++;
    }
    else
    {

    }
    bot[botLoop].setXspeed(dirbotx[botLoop] *100);
    bot[botLoop].setYspeed(dirboty[botLoop] *100);

    if (walk[botLoop] >= 1)
    {
        botDirection[botLoop]++;
        if(botDirection[botLoop]>3)
        {
            botDirection[botLoop]=0;
        }

        walk[botLoop] = 0;

    }
    botLoop++;
    if(botLoop >= BOTMAX)
    {
        botLoop =0;
    }

}

void PlayState::VerifyStatues(cgf::Game* game)
{
    int i = 0;
    int xP1 = player1.getPosition().x;
    int yP1 = player1.getPosition().y;
    int xP2 = player2.getPosition().x;
    int yP2 = player2.getPosition().y;
    bool P1Win = true;
    bool P2Win = true;

    if (xP1 >= 304 && xP1 <= 336 && yP1 >= 126 && yP1 <= 174 && statuesPlayer1[0] != 1)
    {
        statuesPlayer1[0] = 1;
        cout << "Player 1 passou pela Estatua 1" << endl;
    }
    if (xP1 >= 944 && xP1 <= 976 && yP1 >= 126 && yP1 <= 174 && statuesPlayer1[1] != 1)
    {
        statuesPlayer1[1] = 1;
        cout << "Player 1 passou pela Estatua 2" << endl;
    }
    if (xP1 >= 624 && xP1 <= 656 && yP1 >= 344 && yP1 <= 392 && statuesPlayer1[2] != 1)
    {
        statuesPlayer1[2] = 1;
        cout << "Player 1 passou pela Estatua 3" << endl;
    }
    if (xP1 >= 304 && xP1 <= 336 && yP1 >= 494 && yP1 <= 542 && statuesPlayer1[3] != 1)
    {
        statuesPlayer1[3] = 1;
        cout << "Player 1 passou pela Estatua 4" << endl;
    }
    if (xP1 >= 944 && xP1 <= 976 && yP1 >= 494 && yP1 <= 542 && statuesPlayer1[4] != 1)
    {
        statuesPlayer1[4] = 1;
        cout << "Player 1 passou pela Estatua 5" << endl;
    }

    for (i=0; i <= 4; i++)
    {
        if (statuesPlayer1[i] != 1)
        {
            P1Win = false;
        }
    }
    if (P1Win == true)
    {
        cout << "Player 1 Wins!" << endl;
        game->changeState(FinalStateP1::instance());
    }



    if (xP2 >= 304 && xP2 <= 336 && yP2 >= 126 && yP2 <= 174 && statuesPlayer2[0] != 1)
    {
        statuesPlayer2[0] = 1;
        cout << "Player 2 passou pela Estatua 1" << endl;
    }
    if (xP2 >= 944 && xP2 <= 976 && yP2 >= 126 && yP2 <= 174 && statuesPlayer2[1] != 1)
    {
        statuesPlayer2[1] = 1;
        cout << "Player 2 passou pela Estatua 2" << endl;
    }
    if (xP2 >= 624 && xP2 <= 656 && yP2 >= 344 && yP2 <= 392 && statuesPlayer2[2] != 1)
    {
        statuesPlayer2[2] = 1;
        cout << "Player 2 passou pela Estatua 3" << endl;
    }
    if (xP2 >= 304 && xP2 <= 336 && yP2 >= 494 && yP2 <= 542 && statuesPlayer2[3] != 1)
    {
        statuesPlayer2[3] = 1;
        cout << "Player 2 passou pela Estatua 4" << endl;
    }
    if (xP2 >= 944 && xP2 <= 976 && yP2 >= 494 && yP2 <= 542 && statuesPlayer2[4] != 1)
    {
        statuesPlayer2[4] = 1;
        cout << "Player 2 passou pela Estatua 5" << endl;
    }

    for (i=0; i <= 4; i++)
    {
        if (statuesPlayer2[i] != 1)
        {
            P2Win = false;
        }
    }
    if (P2Win == true)
    {
        cout << "Player 2 Wins!" << endl;
        game->changeState(FinalStateP2::instance());
    }

}

void PlayState::VerifyPunch(int player,int PunchDirection,cgf::Game* game)
{
    bool win = false;
    if (player == 1)
    {
        switch(PunchDirection)
        {
        case 0:
            //PUNCH UP
            if ( (player1.getPosition().x - player2.getPosition().x >= -20 && player1.getPosition().x - player2.getPosition().x <= 20) &&
                    (player1.getPosition().y - player2.getPosition().y >= -48 && player1.getPosition().y - player2.getPosition().y <= 0) &&
                    win == false)
            {
                win = true;
            }
            break;
        case 1:
            //PUNCH LEFT
            if ( (player1.getPosition().x - player2.getPosition().x >= -20 && player1.getPosition().x - player2.getPosition().x <= 0) &&
                    (player1.getPosition().y - player2.getPosition().y >= -30 && player1.getPosition().y - player2.getPosition().y <= 30) &&
                    win == false)
            {
                win = true;
            }
            break;
        case 2:
            //PUNCH DOWN
            if ( (player1.getPosition().x - player2.getPosition().x >= -20 && player1.getPosition().x - player2.getPosition().x <= 20) &&
                    (player1.getPosition().y - player2.getPosition().y >= -30 && player1.getPosition().y - player2.getPosition().y <= 30) &&
                    win == false)
            {
                win = true;
            }
            break;
        case 3:
            //PUNCH RIGHT
            if ( (player1.getPosition().x - player2.getPosition().x >= 0 && player1.getPosition().x - player2.getPosition().x <= 20) &&
                    (player1.getPosition().y - player2.getPosition().y >= -30 && player1.getPosition().y - player2.getPosition().y <= 30) &&
                    win == false)
            {
                win = true;
            }
            break;
        }

        if (win == true)
        {
            cout << " Player 1 Wins!" << endl;
            game->changeState(FinalStateP1::instance());
        }
    }
    if (player == 2)
    {
        switch(PunchDirection)
        {
        case 0:
            //PUNCH UP
            if ( (player1.getPosition().x - player2.getPosition().x >= -20 && player1.getPosition().x - player2.getPosition().x <= 20) &&
                    (player1.getPosition().y - player2.getPosition().y >= -48 && player1.getPosition().y - player2.getPosition().y <= 0) &&
                    win == false)
            {
                win = true;
            }
            break;
        case 1:
            //PUNCH LEFT
            if ( (player1.getPosition().x - player2.getPosition().x >= -20 && player1.getPosition().x - player2.getPosition().x <= 0) &&
                    (player1.getPosition().y - player2.getPosition().y >= -30 && player1.getPosition().y - player2.getPosition().y <= 30) &&
                    win == false)
            {
                win = true;
            }
            break;
        case 2:
            //PUNCH DOWN
            if ( (player1.getPosition().x - player2.getPosition().x >= -20 && player1.getPosition().x - player2.getPosition().x <= 20) &&
                    (player1.getPosition().y - player2.getPosition().y >= -30 && player1.getPosition().y - player2.getPosition().y <= 30) &&
                    win == false)
            {
                win = true;
            }
            break;
        case 3:
            //PUNCH RIGHT
            if ( (player1.getPosition().x - player2.getPosition().x >= 0 && player1.getPosition().x - player2.getPosition().x <= 20) &&
                    (player1.getPosition().y - player2.getPosition().y >= -30 && player1.getPosition().y - player2.getPosition().y <= 30) &&
                    win == false)
            {
                win = true;
            }
            break;
        }

        if (win == true)
        {
            cout << " Player 2 Wins!" << endl;
            game->changeState(FinalStateP2::instance());

        }
    }
}

void PlayState::cleanup()
{
    cout << "PlayState Clean Successful" << endl;
    delete map;
}

void PlayState::pause()
{
    cout << "PlayState Paused" << endl;
}

void PlayState::resume()
{
    cout << "PlayState Resumed" << endl;
}

void PlayState::handleEvents(cgf::Game* game)
{
    sf::Event event;
    sf::View view = screen->getView();
    int direcaoSocoP1 = 2;
    bool socoPlayer1= false;
    int direcaoSocoP2 = 2;
    bool socoPlayer2 = false;

    while (screen->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            game->quit();
        if(event.type == sf::Event::KeyPressed)
            if(event.key.code == sf::Keyboard::F1)
                game->toggleStats();
    }

    dirx = diry = 0;
    dirxPlayer2 = diryPlayer2 = 0;

    if(im->testEvent("up"))
    {
        if(player1.getYspeed() >= 0)
        {
            player1.setAnimation("walk-up");
            player1.play();
        }
        diry = -1;

        //DIRECAO DO SOCO
        direcaoSocoP1 = 0;
    }

    if(im->testEvent("left"))
    {
        if(player1.getXspeed() >= 0)
        {
            player1.setAnimation("walk-left");
            player1.play();
        }
        dirx = -1;

        //DIRECAO DO SOCO
        direcaoSocoP1 = 1;
    }

    if(im->testEvent("down"))
    {
        if(player1.getYspeed() <= 0)
        {
            player1.setAnimation("walk-down");
            player1.play();
        }
        diry = 1;

        //DIRECAO DO SOCO
        direcaoSocoP1 = 2;
    }

    if(im->testEvent("right"))
    {
        if(player1.getXspeed() <= 0)
        {
            player1.setAnimation("walk-right");
            player1.play();
        }
        dirx = 1;

        //DIRECAO DO SOCO
        direcaoSocoP1 = 3;
    }


    if(im->testEvent("RCtrl"))
    {
        socoPlayer1 = true;
        switch(direcaoSocoP1)
        {
        case 0:
            player1.setAnimation("punch-up");
            VerifyPunch(1,0,game);
            break;
        case 1:
            player1.setAnimation("punch-left");
            VerifyPunch(1,1,game);
            break;
        case 2:
            player1.setAnimation("punch-down");
            VerifyPunch(1,2,game);
            break;
        case 3:
            player1.setAnimation("punch-right");
            VerifyPunch(1,3,game);
            break;
        }

        if(punchSound.getStatus() == sf::Sound::Stopped)
        {
            punchSound.play();
        }

        player1.play();
    }


    if(!dirx && !diry && !socoPlayer1) // parado?
    {
        player1.setCurrentFrame(0);
        player1.pause();

        //PARA O SOCO
        socoPlayer1 = false;

        //DIRECIONA SOCO PARA BAIXO
        direcaoSocoP1 = 2;
    }

    // Player DOIS
    if(im->testEvent("w"))
    {
        if(player2.getYspeed() >= 0)
        {
            player2.setAnimation("walk-up");
            player2.play();
        }
        diryPlayer2 = -1;

        //DIRECIONA O SOCO
        direcaoSocoP2 = 0;
    }

    if(im->testEvent("a"))
    {
        if(player2.getXspeed() >= 0)
        {
            player2.setAnimation("walk-left");
            player2.play();
        }
        dirxPlayer2 = -1;

        //DIRECAO DO SOCO
        direcaoSocoP2 = 1;
    }

    if(im->testEvent("s"))
    {
        if(player2.getYspeed() <= 0)
        {
            player2.setAnimation("walk-down");
            player2.play();
        }
        diryPlayer2 = 1;

        //DIRECAO DO SOCO
        direcaoSocoP2 = 2;
    }

    if(im->testEvent("d"))
    {
        if(player2.getXspeed() <= 0)
        {
            player2.setAnimation("walk-right");
            player2.play();
        }
        dirxPlayer2 = 1;

        //DIRECAO DO SOCO
        direcaoSocoP2 = 3;
    }



    if(im->testEvent("e"))
    {
        socoPlayer2 = true;
        switch(direcaoSocoP2)
        {
        case 0:
            player2.setAnimation("punch-up");
            VerifyPunch(2,0,game);
            break;
        case 1:
            player2.setAnimation("punch-left");
            VerifyPunch(2,1,game);
            break;
        case 2:
            player2.setAnimation("punch-down");
            VerifyPunch(2,2,game);
            break;
        case 3:
            player2.setAnimation("punch-right");
            VerifyPunch(2,3,game);
            break;
        }


        if(punchSound.getStatus() == sf::Sound::Stopped)
        {
            punchSound.play();
        }
        player2.play();
    }

    if(!dirxPlayer2 && !diryPlayer2 && !socoPlayer2) // parado?
    {
        player2.setCurrentFrame(0);
        player2.pause();

        //PARA O SOCO
        socoPlayer2 = false;

        //DIRECIONA SOCO PARA BAIXO
        direcaoSocoP2 = 2;
    }

    if(im->testEvent("pause"))
    {
        game->pushState(PauseState::instance());
    }

    if(im->testEvent("quit"))
        game->quit();

    player1.setXspeed(dirx*100);
    player1.setYspeed(diry*100);

    player2.setXspeed(dirxPlayer2*100);
    player2.setYspeed(diryPlayer2*100);

}

void PlayState::update(cgf::Game* game)
{

    screen = game->getScreen();

    checkCollision(1, game, &player1); // 3a. camada
    checkCollision(1, game, &player2);

    int i=0;
    for(i=0; i<BOTMAX; i++)
    {

        checkCollision(1, game, &bot[i]);
    }
    if(firstTime)
    {
        punchSoundBuffer.loadFromFile("data/audio/kung_fu_punch.wav");
        punchSound.setBuffer(punchSoundBuffer);
        punchSound.setAttenuation(0);

        firstTime = false;
    }

    botWalk();
    VerifyStatues(game);
    centerMapOnPlayer();

    //tempo
    sf::Time elapsed1 = clock.getElapsedTime();
    int tempo = (int) elapsed1.asSeconds();
    if(tempo != GlobalTime)
    {

        GlobalTime = tempo;

        text.setFont(font);
        InGameTime -- ;
        ostringstream aux;
        aux << "Time: " << InGameTime;

        text.setString(aux.str());
        text.setPosition(585,0);
        text.setCharacterSize(24); // in pixels, not points!
        text.setColor(sf::Color::Red);
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        if(InGameTime <= 0)
        {
            game->changeState(FinalState::instance());
        }
    }


}

bool PlayState::checkCollision(uint8_t layer, cgf::Game* game, cgf::Sprite* obj)
{
    int i, x1, x2, y1, y2;
    bool bump = false;

    // Get the limits of the map
    sf::Vector2u mapsize = map->GetMapSize();
    // Get the width and height of a single tile
    sf::Vector2u tilesize = map->GetMapTileSize();

    mapsize.x /= tilesize.x;
    mapsize.y /= tilesize.y;
    mapsize.x--;
    mapsize.y--;

    // Get the height and width of the object (in this case, 100% of a tile)
    sf::Vector2u objsize = obj->getSize();
    objsize.x *= obj->getScale().x;
    objsize.y *= obj->getScale().y;

    float px = obj->getPosition().x;
    float py = obj->getPosition().y;

    double deltaTime = game->getUpdateInterval();

    sf::Vector2f offset(obj->getXspeed()/1000 * deltaTime, obj->getYspeed()/1000 * deltaTime);

    float vx = offset.x;
    float vy = offset.y;

    // Test the horizontal movement first
    i = objsize.y > tilesize.y ? tilesize.y : objsize.y;

    for (;;)
    {
        x1 = (px + vx) / tilesize.x;
        x2 = (px + vx + objsize.x - 1) / tilesize.x;

        y1 = (py) / tilesize.y;
        y2 = (py + i - 1) / tilesize.y;

        if (x1 >= 0 && x2 < mapsize.x && y1 >= 0 && y2 < mapsize.y)
        {
            if (vx > 0)
            {
                // Trying to move right

                int upRight   = getCellFromMap(layer, x2*tilesize.x, y1*tilesize.y);
                int downRight = getCellFromMap(layer, x2*tilesize.x, y2*tilesize.y);
                if (upRight || downRight)
                {
                    // Place the player as close to the solid tile as possible
                    px = x2 * tilesize.x;
                    px -= objsize.x;// + 1;
                    vx = 0;
                    bump = true;
                }
            }

            else if (vx < 0)
            {
                // Trying to move left

                int upLeft   = getCellFromMap(layer, x1*tilesize.x, y1*tilesize.y);
                int downLeft = getCellFromMap(layer, x1*tilesize.x, y2*tilesize.y);
                if (upLeft || downLeft)
                {
                    // Place the player as close to the solid tile as possible
                    px = (x1+1) * tilesize.x;
                    vx = 0;
                    bump = true;
                }
            }
        }

        if (i == objsize.y) // Checked player height with all tiles ?
        {
            break;
        }

        i += tilesize.y; // done, check next tile upwards

        if (i > objsize.y)
        {
            i = objsize.y;
        }
    }

    // Now test the vertical movement

    i = objsize.x > tilesize.x ? tilesize.x : objsize.x;

    for (;;)
    {
        x1 = (px / tilesize.x);
        x2 = ((px + i-1) / tilesize.x);

        y1 = ((py + vy) / tilesize.y);
        y2 = ((py + vy + objsize.y-1) / tilesize.y);

        if (x1 >= 0 && x2 < mapsize.x && y1 >= 0 && y2 < mapsize.y)
        {
            if (vy > 0)
            {
                // Trying to move down
                int downLeft  = getCellFromMap(layer, x1*tilesize.x, y2*tilesize.y);
                int downRight = getCellFromMap(layer, x2*tilesize.x, y2*tilesize.y);
                if (downLeft || downRight)
                {
                    // Place the player as close to the solid tile as possible
                    py = y2 * tilesize.y;
                    py -= objsize.y;
                    vy = 0;
                    bump = true;
                }
            }

            else if (vy < 0)
            {
                // Trying to move up

                int upLeft  = getCellFromMap(layer, x1*tilesize.x, y1*tilesize.y);
                int upRight = getCellFromMap(layer, x2*tilesize.x, y1*tilesize.y);
                if (upLeft || upRight)
                {
                    // Place the player as close to the solid tile as possible
                    py = (y1 + 1) * tilesize.y;
                    vy = 0;
                    bump = true;
                }
            }
        }

        if (i == objsize.x)
        {
            break;
        }

        i += tilesize.x; // done, check next tile to the right

        if (i > objsize.x)
        {
            i = objsize.x;
        }
    }

    // Now apply the movement and animation

    obj->setPosition(px+vx,py+vy);
    px = obj->getPosition().x;
    py = obj->getPosition().y;

    obj->update(deltaTime, false); // only update animation

    // Check collision with edges of map
    if (px < 0)
        obj->setPosition(px,py);
    else if (px + objsize.x >= mapsize.x * tilesize.x)
        obj->setPosition(mapsize.x*tilesize.x - objsize.x - 1,py);

    if(py < 0)
        obj->setPosition(px,0);
    else if(py + objsize.y >= mapsize.y * tilesize.y)
        obj->setPosition(px, mapsize.y*tilesize.y - objsize.y - 1);

    return bump;
}

sf::Uint16 PlayState::getCellFromMap(uint8_t layernum, float x, float y)
{
    auto& layers = map->GetLayers();
    tmx::MapLayer& layer = layers[layernum];
    sf::Vector2u mapsize = map->GetMapSize();
    sf::Vector2u tilesize = map->GetMapTileSize();
    mapsize.x /= tilesize.x;
    mapsize.y /= tilesize.y;
    int col = floor(x / tilesize.x);
    int row = floor(y / tilesize.y);
    return layer.tiles[row*mapsize.x + col].gid;
}

void PlayState::centerMapOnPlayer()
{
    sf::View view = screen->getView();
    sf::Vector2u mapsize = map->GetMapSize();
    sf::Vector2f viewsize = view.getSize();
    viewsize.x /= 2;
    viewsize.y /= 2;
    sf::Vector2f pos = player1.getPosition();

    float panX = viewsize.x; // minimum pan
    if(pos.x >= viewsize.x)
        panX = pos.x;

    if(panX >= mapsize.x - viewsize.x)
        panX = mapsize.x - viewsize.x;

    float panY = viewsize.y; // minimum pan
    if(pos.y >= viewsize.y)
        panY = pos.y;

    if(panY >= mapsize.y - viewsize.y)
        panY = mapsize.y - viewsize.y;

    view.setCenter(sf::Vector2f(panX,panY));
    screen->setView(view);
}

void PlayState::draw(cgf::Game* game)
{
    //sf::View view = screen->getView();
    int i = 0;
    screen->clear(sf::Color(0,0,0));

    map->Draw(*screen, 0);
    screen->draw(player1);
    screen->draw(player2);
    for(i=0; i<BOTMAX; i++)
    {
        screen->draw(bot[i]);
    }
    for(i=0; i < 5; i++)
    {
        screen->draw(statue[i]);
    }
    map->Draw(*screen, 1);



    screen->draw(text);
}
