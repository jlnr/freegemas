#ifndef GAME_INDICATORS_H
#define GAME_INDICATORS_H

#include <Gosu/Gosu.hpp>

#include "BaseButton.h"

#include <string>
#include <memory>

class Game;
class StateGame;

class GameIndicators
{
public:
    GameIndicators();

    void setGame(Game *, StateGame *);

    void loadResources();

    /// Returns the current score
    int getScore();

    /// Sets the score to the given amount
    void setScore (int score);

    /// Increases the score by the given amount
    void increaseScore (int amount);

    /// Updates the remaining time, the argument is given in seconds
    void updateTime (double time);

    void draw();
    void click(int, int);

private:

    /// Regenerates the texture for the score, if necessary
    void regenerateScoreTexture();

    Game * mGame;
    StateGame * mStateGame;

    /// Current score
    int mScore = 0;

    /// Score in the previous frame
    int mScorePrevious = -1;

    /// Remaining time, in seconds
    double mRemainingTime = 0;

    /// Remaining time in the previous frame
    double mRemainingTimePrevious = 0;

    /// Font for the timer
    std::unique_ptr<Gosu::Font> mFontTime;

    /// Font for the current-score text
    std::unique_ptr<Gosu::Font> mFontScore;

   // Background of the timer
    std::unique_ptr<Gosu::Image> mImgTimeBackground;

    /// Background for the current-score board
    std::unique_ptr<Gosu::Image> mImgScoreBackground;

    /// Image for the clock
    std::unique_ptr<Gosu::Image> mImgTime;
    std::unique_ptr<Gosu::Image> mImgTimeHeader;

    /// Image for the current-score
    std::unique_ptr<Gosu::Image> mImgScore;
    std::unique_ptr<Gosu::Image> mImgScoreHeader;

    /// @{
    /// @name Buttons of the interface
    BaseButton mHintButton;
    BaseButton mResetButton;
    BaseButton mExitButton;
    BaseButton mMusicButton;
    /// @}

    /// Game music
    std::unique_ptr<Gosu::Song> sfxSong;
};

#endif