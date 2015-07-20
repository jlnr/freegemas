#include "StateGame.h"

#include "Game.h"

#include <map>
#include <string>

StateGame::StateGame(Game * p) : State(p),
    // Load the loading screen
    mImgLoadingBanner(L"media/loadingBanner.png")
{
    lDEBUG << Log::CON("StateGame");

    setState(eInitial);

    // Initialise game indicator
    mGameIndicators.setGame(p, this);

    // Initialise game board
    mGameBoard.setGame(p, this);
}

StateGame::~StateGame ()
{
    lDEBUG << Log::DES("StateGame");
}

void StateGame::update()
{
    // On the eInitial state, don't do anything about logic
    if (mState == eInitial)
    {
        return;
    }

    // On this state, start loading the resources
    else if (mState == eStartLoading)
    {
        loadResources();
        setState(eSteady);

        // Start the clock
        resetTime();

        // Reset the scoreboard
        mGameIndicators.setScore(0);
    }

    // Compute remaining time
    double remainingTime = (mTimeStart - Gosu::milliseconds()) / 1000;

    mGameIndicators.updateTime(remainingTime);

    if (remainingTime <= 0)
    {
        // Tell the board that the game ended with the given score
        mGameBoard.endGame(mGameIndicators.getScore());
    }

    mGameBoard.update();
}

void StateGame::draw()
{
    // On this state, show the loading screen and switch the state
    if (mState == eInitial)
    {
        mImgLoadingBanner.draw(156, 200, 2);
        setState(eStartLoading);

        return;
    }

    // In all the other states, the full window is drawn
    mImgBoard->draw(0,0,0);

    // Draw the indicators (buttons and labels)
    mGameIndicators.draw();

    // Draw the main game board
    mGameBoard.draw();
}

void StateGame::buttonDown(Gosu::Button btn)
{
    if (btn.id() == Gosu::kbEscape)
    {
        mGame -> changeState("stateMainMenu");
    }

    else if (btn.id() == Gosu::kbH)
    {
        showHint();
    }
    
    // Left mouse button was pressed
    else if (btn.id() == Gosu::msLeft)
    {
        mMousePressed = true;
        
        // Get click location
        int mouseX = mGame->input().mouseX();
        int mouseY = mGame->input().mouseY();
        
        // Inform the UI
        mGameIndicators.click(mouseX, mouseY);
        
        // Inform the board
        mGameBoard.mouseButtonDown(mouseX, mouseY);
    }

}

void StateGame::buttonUp(Gosu::Button btn)
{
    // Left mouse button was released
    if (btn.id() == Gosu::msLeft)
    {
        mMousePressed = false;

        // Get click location
        int mouseX = mGame->input().mouseX();
        int mouseY = mGame->input().mouseY();

        // Inform the board
        mGameBoard.mouseButtonUp(mouseX, mouseY);
    }
}

void StateGame::setState (tState state)
{
    // static std::map<tState, std::string> stateToString = {
    //     { eInitial, "eInitial"},
    //     { eStartLoading, "eStartLoading"},
    //     { eLoading, "eLoading"},
    //     { eLaunched, "eLaunched"},
    //     { eNewGemsFalling, "eNewGemsFalling"},
    //     { eOldGemsFalling, "eOldGemsFalling"},
    //     { eWaiting, "eWaiting"},
    //     { eGemSelected, "eGemSelected"},
    //     { eGemsSwitching, "eGemsSwitching"},
    //     { eGemsDisappearing, "eGemsDisappearing"},
    //     { eFirstFlip, "eFirstFlip"},
    //     { eInicialGemas, "eInicialGemas"},
    //     { eEspera, "eEspera"},
    //     { eGemaMarcada, "eGemaMarcada"},
    //     { eGemasCambiando, "eGemasCambiando"},
    //     { eGemasDesapareciendo, "eGemasDesapareciendo"},
    //     { eGemasNuevasCayendo, "eGemasNuevasCayendo"},
    //     { eDesapareceBoard, "eDesapareceBoard"},
    //     { eTimeFinished, "eTimeFinished"},
    //     { eShowingScoreTable, "eShowingScoreTable"}
    // };

    // lDEBUG << "New state: " << stateToString[state];
    mState = state;
}

// ----------------------------------------------------------------------------

void StateGame::loadResources()
{
    // Load the background image
    mImgBoard.reset(new Gosu::Image(L"media/board.png"));

    mGameIndicators.loadResources();
    mGameBoard.loadResources();
}

void StateGame::resetGame()
{
    resetTime();
    mGameBoard.resetGame();
}

void StateGame::resetTime()
{
    // Default time is 2 minutes
    mTimeStart = Gosu::milliseconds() + 2 * 60 * 1000;
}

void StateGame::showHint()
{
    mGameBoard.showHint();
}

void StateGame::increaseScore (int amount)
{
    mGameIndicators.increaseScore(amount);
}

