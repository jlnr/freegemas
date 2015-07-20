#include "StateHowToPlay.h"

#include "Game.h"
#include "inter.h"

StateHowtoplay::StateHowtoplay(Game * p) : State(p),
    mImgBackground(L"media/howtoScreen.png"),

    mImgTitle(Gosu::createText(_("How to play"), L"media/fuenteMenu.ttf", 48)),

    mImgSubtitle(Gosu::createText(_("Press escape to go back"), L"media/fuenteMenu.ttf", 23)),

    mImgBodyText(Gosu::createText(
        _("The objective of the game is to swap one gem with an adjacent gem to form a horizontal or vertical chain of three or more gems.") +
        L"\n\n" +
        _("Click the first gem and then click the gem you want to swap it with. If the movement is correct, they will swap and the chained gems will disappear.") +
        L"\n\n" +
        _("Bonus points are given when more than three identical gems are formed. Sometimes chain reactions, called cascades, are triggered, where chains are formed by the falling gems. Cascades are awarded with bonus points."),
        L"media/fuenteNormal.ttf", 28, 0, 450, Gosu::taLeft))
{
    lDEBUG << Log::CON("StateHowtoPlay");
}

void StateHowtoplay::update() { }

void StateHowtoplay::draw()
{
    mImgBackground.draw(0,0,0);

    mImgTitle.draw(300 + 470 / 2 - mImgTitle.width() / 2, 20, 1);
    mImgTitle.draw(301 + 470 / 2 - mImgTitle.width() / 2, 22, 0.9, 1, 1, Gosu::Color(128, 0, 0, 0));

    mImgSubtitle.draw(30, 550, 1);
    mImgSubtitle.draw(30 + 1, 550 + 2, 0.9, 1, 1, Gosu::Color(128, 0, 0, 0));

    mImgBodyText.draw(310, 110, 1);
    mImgBodyText.draw(311, 112, 0.9,  1, 1, Gosu::Color(128, 0, 0, 0));
}

void StateHowtoplay::buttonDown(Gosu::Button btn)
{
    if (btn.id() == Gosu::kbEscape || btn.id() == Gosu::msLeft)
    {
        mGame -> changeState("stateMainMenu");
    }
}

StateHowtoplay::~StateHowtoplay()
{
    lDEBUG << Log::DES("StateHowtoPlay");
}
