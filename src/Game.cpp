#include "Game.h"
#include "State.h"

#include "StateMainMenu.h"
#include "StateHowToPlay.h"
#include "StateGame.h"

using namespace std;


Game::Game () :
    Gosu::Window(800, 600),
    mMouseCursor("media/handCursor.png")
{
    lDEBUG << Log::CON("Game");

    set_caption("FreeGemas");
    
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
    mMouseCursor.draw(input().mouse_x(), input().mouse_y(), 999);
    #endif

    if (mCurrentState)
        mCurrentState -> draw();
}

void Game::button_down (Gosu::Button button)
{
    if (mCurrentState)
        mCurrentState -> buttonDown(button);
}

void Game::button_up (Gosu::Button button)
{
    if (mCurrentState)
        mCurrentState -> buttonUp(button);
}

void Game::touch_began(Gosu::Touch touch)
{
    if (mCurrentState && mMouseSimulatingTouch == nullptr) {
        mMouseSimulatingTouch = touch.id;
        input().set_mouse_position(touch.x, touch.y);
        mCurrentState->buttonDown(Gosu::MS_LEFT);
    }
}

void Game::touch_moved(Gosu::Touch touch)
{
    if (mCurrentState && mMouseSimulatingTouch == touch.id) {
        input().set_mouse_position(touch.x, touch.y);
    }
}

void Game::touch_ended(Gosu::Touch touch)
{
    if (mCurrentState && mMouseSimulatingTouch == touch.id) {
        input().set_mouse_position(touch.x, touch.y);
        mCurrentState->buttonUp(Gosu::MS_LEFT);
        mMouseSimulatingTouch = nullptr;
    }
}

void Game::touch_cancelled(Gosu::Touch touch)
{
    touch_ended(touch);
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

bool Game::needs_cursor() const
{
    return false;
}
