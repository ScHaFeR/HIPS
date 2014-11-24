/*
 *  MenuState.h
 *  Example "menu" state
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#ifndef _FINALP1_STATE_H_
#define _FINALP1_STATE_H_

#include "GameState.h"
#include "Sprite.h"

class FinalStateP1 : public cgf::GameState
{
    public:

    void init();
    void cleanup();

    void pause();
    void resume();

    void handleEvents(cgf::Game* game);
    void update(cgf::Game* game);
    void draw(cgf::Game* game);

    // Implement Singleton Pattern
    static FinalStateP1* instance()
    {
        return &m_FinalStateP1;
    }

    protected:

    FinalStateP1() {}

    private:

    static FinalStateP1 m_FinalStateP1;

    cgf::Sprite menuSprite;
    sf::SoundBuffer winSoundBuffer;
    sf::Sound winSound;

};

#endif

