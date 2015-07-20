#ifndef GAME_BOARD_SOUNDS_H
#define GAME_BOARD_SOUNDS_H

#include <Gosu/Gosu.hpp>
#include <memory>

class GameBoardSounds
{

public:
    /// Loads the sounds
    void loadResources();

    void playSoundSelect();
    void playSoundFall();
    void playSoundMatch1();
    void playSoundMatch2();
    void playSoundMatch3();

private:

    /// @{
    /// @name Sounds of the game
    std::unique_ptr<Gosu::Sample> mSfxMatch1, mSfxMatch2, mSfxMatch3;
    std::unique_ptr<Gosu::Sample> mSfxSelect;
    std::unique_ptr<Gosu::Sample> mSfxFall;
    /// @}
};

#endif