#include "Game.h"
#include <Gosu/Gosu.hpp>

int main()
{
    Gosu::useResourceDirectory();
    
    Game window;
    window.show();
}
