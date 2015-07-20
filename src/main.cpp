#include "Game.h"
#include <Gosu/Gosu.hpp>


#ifdef GOSU_IS_IPHONE

Gosu::Window& windowInstance()
{
    static Game window;
    return window;
}

#else

int main()
{
    Gosu::useResourceDirectory();
    
    Game window;
    window.show();
}

#endif
