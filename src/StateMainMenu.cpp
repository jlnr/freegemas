#include "StateMainMenu.h"

#include "Game.h"
#include "log.h"
#include "inter.h"

#include <cmath>


StateMainMenu::StateMainMenu(Game * p) : State(p),
    // Init background image
    mImgBackground("media/stateMainMenu/mainMenuBackground.png"),
    // Init logo image
    mImgLogo("media/stateMainMenu/mainMenuLogo.png"),
    // Init menu highlight image
    mImgHighl("media/stateMainMenu/menuHighlight.png")
{
    lDEBUG << Log::CON("StateMainMenu");

    mCurrentTransitionState = TransitionIn;

    // Menu target states
    mMenuTargets = {"stateGame", "stateHowtoplay", "stateQuit"};

    // Menu text items
    mMenuRenderedTexts.push_back(Gosu::Image(Gosu::create_text(_("Timetrial mode"), "media/fuenteMenu.ttf", 30)));
    mMenuRenderedTexts.push_back(Gosu::Image(Gosu::create_text(_("How to play?"), "media/fuenteMenu.ttf", 30)));
    mMenuRenderedTexts.push_back(Gosu::Image(Gosu::create_text(_("Exit"), "media/fuenteMenu.ttf", 30)));

    // Jewel group animation
    mJewelAnimation.loadResources(p);

    mAnimationTotalSteps = 30;
    mAnimationLogoSteps = 30;
    mAnimationCurrentStep = 0;

    mMenuSelectedOption = 0;
    mMenuYStart = 350;
    mMenuYGap = 42;
    mMenuYEnd = 350 + (int) mMenuTargets.size() * mMenuYGap;
}

void StateMainMenu::update(){

    if(mCurrentTransitionState == TransitionIn)
    {
        mAnimationCurrentStep ++;

        if(mAnimationCurrentStep == mAnimationTotalSteps)
        {
            mCurrentTransitionState = Active;
        }

    } else if(mCurrentTransitionState == Active){

    } else if(mCurrentTransitionState == TransitionOut){

    }

    // Update menu highlighting according to mouse position
    int mY = (int) mGame -> input().mouse_y();

    if(mY >= mMenuYStart && mY < mMenuYEnd)
    {
        mMenuSelectedOption = (mY - mMenuYStart) / mMenuYGap;
    }
}

void StateMainMenu::draw(){

    // Draw the background
    mImgBackground.draw(0, 0, 1);

    // Calculate the alpha value for the logo
    int logoAlfa = Gosu::clamp( (int)(255 * (float)mAnimationCurrentStep / mAnimationLogoSteps),
                          0, 255);

    // Draw the logo
    mImgLogo.draw(86, 0, 2, 1, 1, Gosu::Color(logoAlfa, 255, 255, 255));

    // Loop to draw the menu items
    for(size_t i = 0, s = mMenuTargets.size(); i < s; ++i)
    {
        // Calculate the horizontal and vertical positions
		int posX = std::round(800 / 2 - mMenuRenderedTexts[i].width() / 2),
            posY = mMenuYStart + i * mMenuYGap;

        // Draw the text and the shadow
        mMenuRenderedTexts[i].draw(posX, posY, 3);
        mMenuRenderedTexts[i].draw(posX, posY + 2, 2.9, 1, 1, Gosu::Color(128, 0, 0, 0));

    }

    #ifndef GOSU_IS_MOBILE
    // Draw the menu highlighting
    mImgHighl.draw(266, mMenuYStart + 5 + mMenuSelectedOption * mMenuYGap, 2);
    #endif

    // Draw the jewel animation
    mJewelAnimation.draw();
}

void StateMainMenu::buttonDown(Gosu::Button btn)
{
    switch (btn.id())
    {
        case Gosu::KB_ESCAPE:
            mGame->close();
            break;

        case Gosu::KB_DOWN:
            mMenuSelectedOption =
                Gosu::wrap(mMenuSelectedOption + 1, 0, (int)mMenuTargets.size());
            break;

        case Gosu::KB_UP:
            mMenuSelectedOption =
                Gosu::wrap(mMenuSelectedOption - 1, 0, (int)mMenuTargets.size());
            break;

        case Gosu::KB_RETURN:
        case Gosu::KB_ENTER:
            optionChosen();
            break;
        
        case Gosu::MS_LEFT: {
            // Get mouse vertical position
            int mY = mGame->input().mouse_y();
            
            if (mY >= mMenuYStart && mY <= mMenuYEnd)
            {
                mMenuSelectedOption = (mY - mMenuYStart) / mMenuYGap;
                optionChosen();
            }
        }
    }
}

void StateMainMenu::optionChosen()
{
    mGame -> changeState(mMenuTargets[mMenuSelectedOption]);
}

StateMainMenu::~StateMainMenu()
{
    lDEBUG << Log::DES("StateMainMenu");
}
