/*
 *  PlayState.h
 *  Normal "play" state
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#ifndef PLAY_STATE_H_
#define PLAY_STATE_H_

#include "GameState.h"
#include "Sprite.h"
#include "InputManager.h"
#include <MapLoader.h>
#include "FinalState.h"
#include "FinalStateP1.h"
#include "FinalStateP2.h"
#include "PauseState.h"
#define BOTMAX 60

class PlayState : public cgf::GameState
{
public:

    void init();
    void cleanup();

    void pause();
    void resume();

    void botWalk();
    void VerifyStatues(cgf::Game* game);
    void VerifyPunch(int player,int PunchDirection,cgf::Game* game);
    void VerifyPunchBot(int player,int PunchDirection,cgf::Game* game);

    void handleEvents(cgf::Game* game);
    void update(cgf::Game* game);
    void draw(cgf::Game* game);
    void doPunch(cgf::Game* game,int player);

    // Implement Singleton Pattern
    static PlayState* instance()
    {
        return &m_PlayState;
    }

protected:

    PlayState() {}

private:

    static PlayState m_PlayState;

    // Get a cell GID from the map (x and y are view coords)
    sf::Uint16 getCellFromMap(uint8_t layernum, float x, float y);

    // Centers the camera on the player position (if player is too close to the borders, stop)
    void centerMapOnPlayer();

    bool checkCollision(uint8_t layer, cgf::Game* game, cgf::Sprite* obj);
    sf::SoundBuffer punchSoundBuffer;
    sf::Sound punchSound;

    sf::SoundBuffer dingSoundBuffer;
    sf::Sound dingSound;

    int x, y;
    int dirx, diry;
    int dirxPlayer2, diryPlayer2;
    int dirbotx[BOTMAX];
    int dirboty[BOTMAX];
    int walk[BOTMAX];
    int botDirection[BOTMAX];
    bool firstTime;
    cgf::Sprite player1;
    cgf::Sprite player2;
    cgf::Sprite bot[BOTMAX];
    cgf::Sprite statue[5];
    sf::RenderWindow* screen;
    cgf::InputManager* im;
    tmx::MapLoader* map;
    sf::Font font;
    sf::Text text;
    int botLoop = 0;
    int statuesPlayer1[4];
    int statuesPlayer2[4];
    sf::Clock clock;
    int GlobalTime;
    int InGameTime;
};

#endif
