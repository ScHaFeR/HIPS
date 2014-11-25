/*
 *  MenuState.cpp
 *  Example "menu" state
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */


#include <iostream>
#include "Game.h"
#include "InputManager.h"
#include "FinalStateP2.h"
#include "PlayState.h"
//#include "PlayMap.h"
//#include "PlayMapTop.h"
//#include "PlayMapAI.h"
//#include "PlayPhysics.h"
//#include "PlayMapPhysics.h"

FinalStateP2 FinalStateP2::m_FinalStateP2;

using namespace std;

void FinalStateP2::init()
{
    menuSprite.load("data/img/P2Wins.png"); // load menu state bitmap

    winSoundBuffer.loadFromFile("data/audio/imperial_march.wav");
    winSound.setBuffer(winSoundBuffer);
    winSound.setAttenuation(0);

    if(winSound.getStatus() == sf::Sound::Stopped)
    {
        winSound.play();
    }

    cout << "FinalStateP2 Init Successful" << endl;
}

void FinalStateP2::cleanup()
{
    cout << "FinalStateP2 Cleanup Successful" << endl;
}

void FinalStateP2::pause()
{
    cout << "FinalStateP2 Paused" << endl;
}

void FinalStateP2::resume()
{
    cout << "FinalStateP2 Resumed" << endl;
}

void FinalStateP2::handleEvents(cgf::Game* game)
{
    sf::Event event;
    sf::RenderWindow* screen = game->getScreen();

    while (screen->pollEvent(event))
    {
        // check the type of the event...
        switch (event.type)
        {
        // window closed
        case sf::Event::Closed:
            game->quit();
            break;

        // key pressed
        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::R)
            {
                winSound.stop();
                game->changeState(PlayState::instance());
            }
            if(event.key.code == sf::Keyboard::Escape)
            {
                winSound.stop();
                game->quit();
            }
            //game->changeState(PlayMap::instance());
            //game->changeState(PlayMapTop::instance());
            //game->changeState(PlayMapAI::instance());
            //game->changeState(PlayPhysics::instance());
            //game->changeState(PlayMapPhysics::instance());
            break;

        // we don't process other types of events
        default:
            break;
        }
    }
}

void FinalStateP2::update(cgf::Game* game)
{
}

void FinalStateP2::draw(cgf::Game *game)
{
    menuSprite.setPosition(0,0);
//    menuSprite->draw(game->getScreen());
    game->getScreen()->draw(menuSprite);
}

