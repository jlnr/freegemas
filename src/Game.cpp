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
    
    mMouseSimulatingTouch = nullptr;
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
    #ifndef GOSU_IS_MOBILE
    mMouseCursor.draw(input().mouseX(), input().mouseY(), 999);
    #endif

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

void Game::touchBegan(Gosu::Touch touch)
{
    if (mCurrentState && mMouseSimulatingTouch == nullptr) {
        mMouseSimulatingTouch = touch.id;
        input().setMousePosition(touch.x, touch.y);
        mCurrentState->buttonDown(Gosu::msLeft);
    }
}

void Game::touchMoved(Gosu::Touch touch)
{
    if (mCurrentState && mMouseSimulatingTouch == touch.id) {
        input().setMousePosition(touch.x, touch.y);
    }
}

void Game::touchEnded(Gosu::Touch touch)
{
    if (mCurrentState && mMouseSimulatingTouch == touch.id) {
        input().setMousePosition(touch.x, touch.y);
        mCurrentState->buttonUp(Gosu::msLeft);
        mMouseSimulatingTouch = nullptr;
    }
}

void Game::touchCancelled(Gosu::Touch touch)
{
    touchEnded(touch);
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
