#ifndef _STATEHOWTOPLAY_H_
#define _STATEHOWTOPLAY_H_

#include <memory>

#include "State.h"
#include <Gosu/Gosu.hpp>

class TextBlock;
class Game;

class StateHowtoplay : public State {
public:

    StateHowtoplay(Game * p);

    void update() override;
    void draw() override;

    void buttonDown(Gosu::Button btn) override;

    ~StateHowtoplay() override;

private:
    Gosu::Image mImgBackground;

    Gosu::Image mImgTitle;
    Gosu::Image mImgSubtitle;

    Gosu::Image mImgBodyText;
};

#endif /* _STATEHOWTOPLAY_H_ */
