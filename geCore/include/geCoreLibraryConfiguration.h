#pragma once

// Core export macros
#if GE_PLATFORM == GE_PLATFORM_WIN32
# if GE_COMPILER == GE_COMPILER_MSVC || GE_COMPILER == GE_COMPILER_GNUC || GE_COMPILER == GE_COMPILER_INTEL
#   if defined(GE_STATIC_LIB)
#     define GE_CORE_EXPORT
#   else
#     if defined(geCore_EXPORTS)
#       define GE_CORE_EXPORT __declspec(dllexport)
#     else
#       define GE_CORE_EXPORT __declspec(dllimport)
#     endif
#   endif
# endif
# define GE_CORE_HIDDEN
#else // Linux / Mac
# if defined(GE_STATIC_LIB)
#  define GE_CORE_EXPORT
#  define GE_CORE_HIDDEN
# else
#  define GE_CORE_EXPORT __attribute__ ((visibility("default")))
#  define GE_CORE_HIDDEN __attribute__ ((visibility("hidden")))
# endif
#endif

// DLL export for plug-ins
#if GE_PLATFORM == GE_PLATFORM_WIN32
# if GE_COMPILER == GE_COMPILER_MSVC || GE_COMPILER == GE_COMPILER_GNUC || GE_COMPILER == GE_COMPILER_INTEL
#   define GE_PLUGIN_EXPORT __declspec(dllexport)
# endif
# define GE_PLUGIN_HIDDEN
#else // Linux / Mac
# define GE_PLUGIN_EXPORT __attribute__ ((visibility("default")))
# define GE_PLUGIN_HIDDEN __attribute__ ((visibility("hidden")))
#endif
