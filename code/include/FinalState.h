/*
 *  MenuState.h
 *  Example "menu" state
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#ifndef _FINAL_STATE_H_
#define _FINAL_STATE_H_

#include "GameState.h"
#include "Sprite.h"

class FinalState : public cgf::GameState
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
    static FinalState* instance()
    {
        return &m_FinalState;
    }

    protected:

    FinalState() {}

    private:

    static FinalState m_FinalState;

    cgf::Sprite menuSprite;
    sf::SoundBuffer winSoundBuffer;
    sf::Sound winSound;

};

#endif

