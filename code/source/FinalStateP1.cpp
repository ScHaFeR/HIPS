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
#include "FinalStateP1.h"
#include "PlayState.h"
//#include "PlayMap.h"
//#include "PlayMapTop.h"
//#include "PlayMapAI.h"
//#include "PlayPhysics.h"
//#include "PlayMapPhysics.h"

FinalStateP1 FinalStateP1::m_FinalStateP1;

using namespace std;

void FinalStateP1::init()
{
    menuSprite.load("data/img/P1Wins.png"); // load menu state bitmap

    winSoundBuffer.loadFromFile("data/audio/imperial_march.mp3");
    winSound.setBuffer(winSoundBuffer);
    winSound.setAttenuation(0);

    if(winSound.getStatus() == sf::Sound::Stopped)
    {
        winSound.play();
    }

    cout << "FinalStateP1 Init Successful" << endl;

}

void FinalStateP1::cleanup()
{
    cout << "FinalStateP1 Cleanup Successful" << endl;
}

void FinalStateP1::pause()
{
    cout << "FinalStateP1 Paused" << endl;
}

void FinalStateP1::resume()
{
    cout << "FinalStateP1 Resumed" << endl;
}

void FinalStateP1::handleEvents(cgf::Game* game)
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
                game->changeState(PlayState::instance());
            if(event.key.code == sf::Keyboard::Escape){
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

void FinalStateP1::update(cgf::Game* game)
{
}

void FinalStateP1::draw(cgf::Game *game)
{
    menuSprite.setPosition(0,0);
//    menuSprite->draw(game->getScreen());
    game->getScreen()->draw(menuSprite);
}

