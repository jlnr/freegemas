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
    ~Game();

    void update();

    void draw();

    void buttonDown(Gosu::Button button);
    void buttonUp(Gosu::Button button);

    void changeState(std::string S);
    
    bool needsCursor() const;

private:

    std::shared_ptr<State> mCurrentState = nullptr;
    std::string mCurrentStateString;

    Gosu::Image mMouseCursor;

};

#endif /* _GAME_H_ */
