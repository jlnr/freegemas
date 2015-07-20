#include "Game.h"
#include <Gosu/Gosu.hpp>

#ifdef GOSU_IS_UNIX
#include <unistd.h>
#endif

int main()
{
#ifdef GOSU_IS_UNIX
    // If Gosu suggests loading resources from an absolute path (instead of '.'
    // or even ''), then chdir() into that path so that loading things from
    // media/foo.bar automatically works.
    std::wstring resourcePath = Gosu::resourcePrefix();
    if (resourcePath.front() == '/') {
        chdir(Gosu::wstringToUTF8(resourcePath).c_str());
    }
#endif
    
    Game window;
    window.show();
}
