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
#include "PauseState.h"
#include "PlayState.h"
//#include "PlayMap.h"
//#include "PlayMapTop.h"
//#include "PlayMapAI.h"
//#include "PlayPhysics.h"
//#include "PlayMapPhysics.h"

PauseState PauseState::m_PauseState;

using namespace std;

void PauseState::init()
{
    menuSprite.load("data/img/PauseMenu.png"); // load menu state bitmap
    cout << "PauseState Init Successful" << endl;
}

void PauseState::cleanup()
{
    cout << "PauseState Cleanup Successful" << endl;
}

void PauseState::pause()
{
    cout << "PauseState Paused" << endl;
}

void PauseState::resume()
{
    cout << "PauseState Resumed" << endl;
}

void PauseState::handleEvents(cgf::Game* game)
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
                game->popState();
            }
            if(event.key.code == sf::Keyboard::T)
            {
                game->changeState(PlayState::instance());
            }
            if(event.key.code == sf::Keyboard::Escape)
            {
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

void PauseState::update(cgf::Game* game)
{
}

void PauseState::draw(cgf::Game *game)
{
    menuSprite.setPosition(0,0);
//    menuSprite->draw(game->getScreen());
    game->getScreen()->draw(menuSprite);
}

