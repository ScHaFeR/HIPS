/*
 *  MenuState.h
 *  Example "menu" state
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#ifndef _FINALP2_STATE_H_
#define _FINALP2_STATE_H_

#include "GameState.h"
#include "Sprite.h"

class FinalStateP2 : public cgf::GameState
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
    static FinalStateP2* instance()
    {
        return &m_FinalStateP2;
    }

    protected:

    FinalStateP2() {}

    private:

    static FinalStateP2 m_FinalStateP2;

    cgf::Sprite menuSprite;
    sf::SoundBuffer winSoundBuffer;
    sf::Sound winSound;
};

#endif

