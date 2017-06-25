#include "GameIndicators.h"
#include "Game.h"
#include "inter.h"

#include "StateGame.h"

GameIndicators::GameIndicators() :
    mGame (NULL),
    mStateGame (NULL)
{

}

void GameIndicators::setGame (Game * g, StateGame * sg)
{
    mGame = g;
    mStateGame = sg;
}

void GameIndicators::loadResources()
{
    mImgScoreHeader.reset(new Gosu::Image(Gosu::create_text(_("score"), "media/fuenteNormal.ttf", 37)));

    mImgTimeHeader.reset(new Gosu::Image(Gosu::create_text(_("time left"), "media/fuenteNormal.ttf", 37)));

    // Load the background image for the time
    mImgTimeBackground.reset(new Gosu::Image("media/timeBackground.png"));

    // Load the background image for the scoreboard
    mImgScoreBackground.reset(new Gosu::Image("media/scoreBackground.png"));

    // Buttons
    mHintButton.set(mGame, _("Show hint"), "iconHint.png");
    mResetButton.set(mGame, _("Reset game"), "iconRestart.png");
    mExitButton.set(mGame, _("Exit"), "iconExit.png");
    mMusicButton.set(mGame, _("Turn off music"), "iconMusic.png");

    // Music
    sfxSong.reset(new Gosu::Song("media/music.ogg"));
    sfxSong->play();
}

int GameIndicators::getScore()
{
    return mScore;
}

void GameIndicators::setScore (int score)
{
    mScore = score;

    regenerateScoreTexture();
}

void GameIndicators::increaseScore (int amount)
{
    mScore += amount;

    regenerateScoreTexture();
}

void GameIndicators::regenerateScoreTexture()
{
    // Regenerate the texture if the score has changed
    if (mScore != mScorePrevious)
    {
        mImgScore.reset(new Gosu::Image(Gosu::create_text(std::to_string(mScore), "media/fuentelcd.ttf", 33)));
        mScorePrevious = mScore;
    }
}

void GameIndicators::updateTime (double time)
{
    mRemainingTime = time;

    // Only recreate the tiem string if it's changed
    if (mRemainingTime >= 0 && mRemainingTime != mRemainingTimePrevious)
    {
        int minutes = int(mRemainingTime / 60);
        int seconds = int(mRemainingTime - minutes * 60);

        std::string txtTime = std::to_string(minutes) +
            (seconds < 10 ? ":0" : ":") +
            std::to_string(seconds);

        mImgTime.reset(new Gosu::Image(Gosu::create_text(txtTime, "media/fuentelcd.ttf", 62)));

        mRemainingTimePrevious = mRemainingTime;
    }
}

void GameIndicators::draw()
{
    // Vertical initial position for the buttons
    int vertButStart = 360;

    // Draw the buttons
    mHintButton.draw(17, vertButStart, 2);
    mResetButton.draw(17, vertButStart + 47, 2);
    mMusicButton.draw(17, vertButStart + 47 * 2, 2);
    mExitButton.draw(17, 538, 2);

    // Draw the score
    mImgScoreBackground->draw(17, 124, 2);
    mImgScoreHeader->draw(17 + mImgScoreBackground->width() / 2 - mImgScoreHeader->width() / 2, 84, 3, 1, 1, Gosu::Color(255, 160, 169, 255));
    mImgScoreHeader->draw(18 + mImgScoreBackground->width() / 2 - mImgScoreHeader->width() / 2, 85, 2.95,  1, 1, Gosu::Color(128, 0, 0, 0));
    mImgScore->draw(197 - mImgScore->width(), 127, 2, 1, 1, Gosu::Color(255, 78, 193, 190));

    // Draw the time
    mImgTimeBackground->draw(17, 230, 2);
    mImgTimeHeader->draw(17 + mImgTimeBackground->width() / 2 - mImgTimeHeader->width() / 2, 190, 3, 1, 1, Gosu::Color(255, 160, 169, 255));
    mImgTimeHeader->draw(18 + mImgTimeBackground->width() / 2 - mImgTimeHeader->width() / 2, 191, 2, 1, 1, Gosu::Color(128, 0, 0, 0));
    mImgTime->draw(190 - mImgTime->width(), 232, 2, 1, 1, Gosu::Color(255, 78, 193, 190));
}

void GameIndicators::click(int mouseX, int mouseY)
{
    // Exit button was clicked
    if (mExitButton.clicked(mouseX, mouseY))
    {
        mGame -> changeState("stateMainMenu");
    }

    // Hint button was clicked
    else if (mHintButton.clicked(mouseX, mouseY))
    {
        mStateGame -> showHint();
    }

    // Reset button was clicked
    else if (mResetButton.clicked(mouseX, mouseY))
    {
        mStateGame -> resetGame();
    }

    // Music button was clicked
    else if (mMusicButton.clicked(mouseX, mouseY))
    {
        if (sfxSong->playing())
        {
            mMusicButton.setText(_("Turn on music"));
            sfxSong->stop();
        }
        else
        {
            mMusicButton.setText(_("Turn off music"));
            sfxSong->play();
        }
    }
}
