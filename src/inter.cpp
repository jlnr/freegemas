#include "inter.h"
#include <Gosu/Gosu.hpp>

#if defined(GOSU_IS_UNIX) && !defined(GOSU_IS_MAC)
#include <libintl.h>
#include <locale.h>
#endif

std::string _(const char * stringName) {
    const char * translation;
    
    #if defined(GOSU_IS_UNIX) && !defined(GOSU_IS_MAC)
    translation = gettext(x);
    #else
    // TODO - find a way to localize this game on Windows and OS X.
    translation = stringName;
    #endif
    
    return translation ? translation : std::string();
}
