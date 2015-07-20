#ifndef _GAME_H_
#define _GAME_H_

#include <string>
#include <memory>

#include <Gosu/Gosu.hpp>


class State;

class Game : public Gosu::Window
{

public:
    Game ();
    ~Game() override;

    void update() override;

    void draw() override;

    void buttonDown(Gosu::Button button) override;
    void buttonUp(Gosu::Button button) override;
    void touchBegan(Gosu::Touch touch) override;
    void touchMoved(Gosu::Touch touch) override;
    void touchEnded(Gosu::Touch touch) override;
    void touchCancelled(Gosu::Touch touch) override;

    void changeState(std::string S);
    
    bool needsCursor() const;

private:

    std::shared_ptr<State> mCurrentState = nullptr;
    std::string mCurrentStateString;

    Gosu::Image mMouseCursor;
    void * mMouseSimulatingTouch = nullptr;
};

#endif /* _GAME_H_ */
