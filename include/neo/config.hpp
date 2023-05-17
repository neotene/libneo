#pragma once

#if defined(_WIN32)
# define NEO_SYSTEM_WINDOWS
#elif defined(__APPLE__) && defined(__MACH__)
# include "TargetConditionals.h"
# if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#  define NEO_SYSTEM_IOS
# elif TARGET_OS_MAC
#  define NEO_SYSTEM_MACOS
# else
#  error This Apple operating system is not supported by NEO library
# endif
#elif defined(__unix__)
# if defined(__ANDROID__)
#  define NEO_SYSTEM_ANDROID
# elif defined(__linux__)
#  define NEO_SYSTEM_LINUX
# elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
#  define NEO_SYSTEM_FREEBSD
# else
#  error This UNIX operating system is not supported by NEO library
# endif
#else
# error This operating system is not supported by NEO library
#endif

#if !defined(NEO_STATIC)
# if defined(NEO_SYSTEM_WINDOWS)
#  define NEO_SYMBOL_EXPORT __declspec(dllexport)
#  define NEO_SYMBOL_IMPORT __declspec(dllimport)
#  ifdef _MSC_VER
#   pragma warning(disable : 4251)
#  endif
# else   // Linux, FreeBSD, Mac OS X
#  if __GNUC__ >= 4
#   define NEO_SYMBOL_EXPORT __attribute__((__visibility__("default")))
#   define NEO_SYMBOL_IMPORT __attribute__((__visibility__("default")))
#  else
#   define NEO_SYMBOL_EXPORT
#   define NEO_SYMBOL_IMPORT
#  endif
# endif
#else
# define NEO_SYMBOL_EXPORT
# define NEO_SYMBOL_IMPORT
#endif

#if defined(NEO_BUILDING_THE_LIB)
# define NEO_API NEO_SYMBOL_EXPORT
#else
# define NEO_API NEO_SYMBOL_IMPORT
#endif
