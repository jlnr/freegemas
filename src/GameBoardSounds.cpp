#include "GameBoardSounds.h"

void GameBoardSounds::loadResources()
{
    mSfxSelect.reset(new Gosu::Sample("media/select.ogg"));
    mSfxFall.reset(new Gosu::Sample("media/fall.ogg"));
    mSfxMatch1.reset(new Gosu::Sample("media/match1.ogg"));
    mSfxMatch2.reset(new Gosu::Sample("media/match2.ogg"));
    mSfxMatch3.reset(new Gosu::Sample("media/match3.ogg"));
}

void GameBoardSounds::playSoundSelect()
{
    mSfxSelect->play(0.3);
}

void GameBoardSounds::playSoundFall()
{
    mSfxFall->play(0.3);
}

void GameBoardSounds::playSoundMatch1()
{
    mSfxMatch1->play(0.25);
}

void GameBoardSounds::playSoundMatch2()
{
    mSfxMatch2->play(0.25);
}

void GameBoardSounds::playSoundMatch3()
{
    mSfxMatch3->play(0.25);
}
