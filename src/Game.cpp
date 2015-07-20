#include "Game.h"
#include "State.h"

#include "StateMainMenu.h"
#include "StateHowToPlay.h"
#include "StateGame.h"

using namespace std;


Game::Game () :
    Gosu::Window(800, 600),
    mMouseCursor(L"media/handCursor.png")
{
    lDEBUG << Log::CON("Game");

    setCaption(L"FreeGemas");
    
    changeState("stateMainMenu");
}

Game::~Game()
{
    lDEBUG << Log::DES("Game");
}

void Game::update ()
{
    if (mCurrentState)
        mCurrentState -> update();
}

void Game::draw ()
{
    mMouseCursor.draw(input().mouseX(), input().mouseY(), 999);

    if (mCurrentState)
        mCurrentState -> draw();
}

void Game::buttonDown (Gosu::Button button)
{
    if (mCurrentState)
        mCurrentState -> buttonDown(button);
}

void Game::buttonUp (Gosu::Button button)
{
    if (mCurrentState)
        mCurrentState -> buttonUp(button);
}

void Game::changeState(string S)
{
    if(S == mCurrentStateString)
    {
        return;
    }
    else if(S == "stateMainMenu")
    {
        mCurrentState = make_shared<StateMainMenu>(this);
        mCurrentStateString = "stateMainMenu";
    }
    else if(S == "stateGame")
    {
        mCurrentState = make_shared<StateGame>(this);
        mCurrentStateString = "estadoGame";
    }
    else if(S == "stateHowtoplay")
    {
        mCurrentState = make_shared<StateHowtoplay>(this);
        mCurrentStateString = "stateHowtoplay";
    }
    else if(S == "stateQuit")
    {
        close();
    }
}

bool Game::needsCursor() const
{
    return false;
}
