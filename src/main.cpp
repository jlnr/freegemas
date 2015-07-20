#include "Game.h"
#include <Gosu/Gosu.hpp>
#include <unistd.h>

int main()
{
    // If Gosu suggests loading resources from an absolute path (instead of '.'
    // or even ''), then chdir() into that path so that loading things from
    // media/foo.bar automatically works.
    std::wstring resourcePath = Gosu::resourcePrefix();
    if (resourcePath.front() == '/') {
        chdir(Gosu::wstringToUTF8(resourcePath).c_str());
    
    }
    
    Game window;
    window.show();
}
