#ifndef _GAME_H_
#define _GAME_H_

#include <string>
#include <memory>

#include <Gosu/Gosu.hpp>


class State;

class Game : public Gosu::Window
{

public:
    Game();
    ~Game() override;

    void update() override;

    void draw() override;

    void button_down(Gosu::Button button) override;
    void button_up(Gosu::Button button) override;
    void touch_began(Gosu::Touch touch) override;
    void touch_moved(Gosu::Touch touch) override;
    void touch_ended(Gosu::Touch touch) override;
    void touch_cancelled(Gosu::Touch touch) override;

    void changeState(std::string S);
    
    bool needs_cursor() const override;

private:
    std::shared_ptr<State> mCurrentState = nullptr;
    std::string mCurrentStateString;

    Gosu::Image mMouseCursor;
    void * mMouseSimulatingTouch = nullptr;
};

#endif /* _GAME_H_ */
