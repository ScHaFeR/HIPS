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
#include "FinalState.h"
#include "PlayState.h"
//#include "PlayMap.h"
//#include "PlayMapTop.h"
//#include "PlayMapAI.h"
//#include "PlayPhysics.h"
//#include "PlayMapPhysics.h"

FinalState FinalState::m_FinalState;

using namespace std;

void FinalState::init()
{
    menuSprite.load("data/img/GameOver.png"); // load menu state bitmap

    winSoundBuffer.loadFromFile("data/audio/imperial_march.wav");
    winSound.setBuffer(winSoundBuffer);
    winSound.setAttenuation(0);

    if(winSound.getStatus() == sf::Sound::Stopped)
    {
        winSound.play();
    }

    cout << "FinalState Init Successful" << endl;
}

void FinalState::cleanup()
{
    cout << "FinalState Cleanup Successful" << endl;
}

void FinalState::pause()
{
    cout << "FinalState Paused" << endl;
}

void FinalState::resume()
{
    cout << "FinalState Resumed" << endl;
}

void FinalState::handleEvents(cgf::Game* game)
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
            break;

        // we don't process other types of events
        default:
            break;
        }
    }
}

void FinalState::update(cgf::Game* game)
{
}

void FinalState::draw(cgf::Game *game)
{
    menuSprite.setPosition(0,0);
//    menuSprite->draw(game->getScreen());
    game->getScreen()->draw(menuSprite);
}

