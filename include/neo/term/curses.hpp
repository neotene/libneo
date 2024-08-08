#ifndef NEO_TERM_CURSES
#define NEO_TERM_CURSES
#include <neo/config.hpp>

#if defined(NEO_SYSTEM_WINDOWS)
# include <curses.h>
# include <windows.h>

#elif defined(NEO_SYSTEM_LINUX)
# include <cursesw.h>
#else
# include <curses.h>
#endif   // NEO_SYSTEM_WINDOWS

#endif
