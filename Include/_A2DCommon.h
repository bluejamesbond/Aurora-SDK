#ifndef __COMMON_H__
#define __COMMON_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      COMMON
//
//  Synopsis:
//      Contains basic utility functions used by the core as well as the 
//      platform dependent implementations.
//
//------------------------------------------------------------------------------

// Debugging
//------------------------------------------------------------------------------
#include "_A2DDebug.h"

// Core Constants
//------------------------------------------------------------------------------
#define A2D_DEFAULT_TEXTURE								 L"../../../Aurora-SDK/Lib/Assets/Images/transparent [a] 1.png"
#define A2D_WINDOW_BOX_SHADOW_SAFELYTY_RATIO             2
#define A2D_WINDOW_RESIZE_EDGE_DISTANCE                  5
#define A2D_WINDOW_RESIZE_DEFAULT_DISTANCE               3
#define A2D_WINDOW_MOVE_BAR_DISTANCE                     25
#define A2D_WINDOW_MOVE_DEFAULT_DISTANCE                 10

#define A2D_FPS											 120
#define A2D_MAX_Z_DEPTH									 1000000.0f

// System error focusing on speed
//------------------------------------------------------------------------------
#ifndef __STATUS_DEFINED__
#define __STATUS_DEFINED__

typedef unsigned int STATUS;
#define _STATUS_TYPEDEF_(_sc)                           (static_cast<STATUS>(_sc))

#define STATUS_OK                                       _STATUS_TYPEDEF_(0)
#define STATUS_FAIL                                     _STATUS_TYPEDEF_(1)
#define STATUS_RETRY                                    _STATUS_TYPEDEF_(2)
#define STATUS_FORCE_QUIT                               _STATUS_TYPEDEF_(3)

#endif                                  

// Enable/Disable debugging
//------------------------------------------------------------------------------
// #define A2D_DE__                                        "Comment out this line to remove debugging."

// Readability macros
//------------------------------------------------------------------------------
#define G_SAFELY(hr)                                    if(hr != 0) { SYSOUT_STR("Failure detected");   return; }
#define SAFELY(hr)                                      if(hr != 0) { SYSOUT_STR("Failure detected");   return STATUS_FAIL; }
#define NULLCHECK(hr)                                   if(!hr)     { SYSOUT_STR("Failure detected");   return STATUS_FAIL; }
#define DESTROY(x)                                      if(x)       { delete x; x = 0; }
#define D3DDESTROY(x)                                   if(x)       { x->Release(); x = 0; }
#define THREAD_DESTROY(x)                               if(x)       { x->stop(); delete x; x = 0; }
#define SFLOAT(x)                                       static_cast<float>(x)
#define SINT(x)                                         static_cast<int>(x)
#define SLONG(x)                                        static_cast<long>(x)
#define SUINT(x)                                        static_cast<unsigned int>(x)
#define SDOUBLE(x)	                                    static_cast<double>(x)
#define SULONGLONG(x)                                   static_cast<unsigned long long>(x)
#define SULONG(x)                                       static_cast<unsigned long>(x)
#define IMPLEMENT                                       = 0
#define EXECUTE_ONCE(x, y, z)							static x generated_##y = z

#define LOW16UINT32(x)										x & 0xFFFF
#define HI16UINT32(x)										x >> 16

// System independent definitions
//------------------------------------------------------------------------------
#define SYSINLINE                                       __forceinline
#define SYSCDECL                                        __cdecl
#define SYSFASTCALL										__fastcall

// Functions for calculating relative point
//------------------------------------------------------------------------------
SYSINLINE float SYSCDECL pixToRelPoint_cpy_cpy(float xPixelDimension, float xPixels)
{
    return xPixels / (xPixelDimension / 2.0f) - 1.0f;
}

SYSINLINE float SYSCDECL pixToRelDistance_cpy_cpy(float xPixelDimension, float xPixels)
{
    return xPixels / xPixelDimension * 2.0f;
}

SYSINLINE float SYSCDECL pixToRelDistance_cpy_cpy(float xPixelDimension, unsigned int xPixels)
{
	return xPixels / xPixelDimension * 2.0f;
}

// Fastest min/max/abs functions
//------------------------------------------------------------------------------
SYSINLINE float SYSCDECL max_cpy_cpy(float a, float b)
{
    return (((a) > (b)) ? (a) : (b));
}

SYSINLINE float SYSCDECL min_cpy_cpy(float a, float b)
{
    return (((a) < (b)) ? (a) : (b));
}

SYSINLINE float SYSCDECL abs_cpy(float a)
{
    return (((a) < (0.0f)) ? (-a) : (a));
}

SYSINLINE int SYSCDECL max_cpy_cpy(int a, int b)
{
    return (((a) > (b)) ? (a) : (b));
}

SYSINLINE int SYSCDECL min_cpy_cpy(int a, int b)
{
    return (((a) < (b)) ? (a) : (b));
}

SYSINLINE int SYSCDECL min_cpy_cpy(unsigned int a, unsigned int b)
{
	return (((a) < (b)) ? (a) : (b));
}

SYSINLINE int SYSCDECL abs_cpy(int a)
{
    return (((a) < (0)) ? (-a) : (a));
}

//////////////////////////////////////////////////////////////////////////////
// PLATFORM DEPENDENT - START
//////////////////////////////////////////////////////////////////////////////

// FIXME This code is messy because it has an extra include in here.
#ifdef _WIN32

#include "Windows/ExtLibs.h"

// Long lived frequency
static LARGE_INTEGER freq;

inline bool get_rdtsc_cpu_frequency()
{
	QueryPerformanceFrequency(&freq);

	return true;
}

// Time access
// NOTE: Use QueryPerformanceFrequency for raw frequency based time
inline double platform_dependent_kernel_time_high_precision()
{
	static bool singleton = get_rdtsc_cpu_frequency();

	LARGE_INTEGER counter1;
	
	QueryPerformanceCounter(&counter1);

	return SDOUBLE(counter1.QuadPart) / SDOUBLE(freq.QuadPart);
}

// System time used for primarily 
// animations
//------------------------------------------------------------------------------
#ifndef kerneltimelp__
#define kerneltimelp__									GetTickCount()
#endif

#ifndef kerneltimehp__
#define kerneltimehp__									platform_dependent_kernel_time_high_precision()
#endif

#ifndef threadid__										
#define	threadid__										SINT(GetCurrentThreadId())
#endif 

#endif
//////////////////////////////////////////////////////////////////////////////
// PLATFORM DEPENDENT - END
//////////////////////////////////////////////////////////////////////////////

#define nanotime__									Toolkit::SYSTEM_NANOTIME

//High performance min/max/abs for
//floats and int. Any extra variables that need
//to be used should be added.
//------------------------------------------------------------------------------
#define max__(x, y)                                     max_cpy_cpy(x, y)
#define min__(x, y)                                     min_cpy_cpy(x, y)
#define abs__(x)                                        abs_cpy(x)

// High performance pixel to relative distance
// functions.
//------------------------------------------------------------------------------
#define cvtpx2rp__(x, y)                                pixToRelPoint_cpy_cpy(x, y)
#define cvtpx2rd__(x, y)                                pixToRelDistance_cpy_cpy(x, y)

// Convert from units to distance
//------------------------------------------------------------------------------
#define cvtsu2px__(x_units, x_value, x_range)           ((x_units == Style::PERCENTAGE) ? SINT(x_range * (x_value / 100.0f)) : SINT(x_value))

// unconst is very dangerous
// Use with caution.
//------------------------------------------------------------------------------
#define	unconst__(x)									(const_cast<x>(this))
#define	sunconst__(y, x)									(const_cast<y>(x))

#include <time.h>

// Speed functions
//------------------------------------------------------------------------------
#ifndef timeinit__
#define timeinit__										clock_t blockTime;
#endif

#ifndef timestart__
#define timestart__										blockTime = clock();
#endif

#ifndef timeend__
#define timeend__										SYSOUT_F(data "%.9fs", (double) (clock() - blockTime) / CLOCKS_PER_SEC);
#endif

#ifndef timeblock__             
#define timeblock__(data)								for (long blockTime = NULL; (blockTime == NULL ? (blockTime = clock()) != NULL : false); SYSOUT_F(data "%.9fs", (double) (clock() - blockTime) / CLOCKS_PER_SEC))
#endif

#endif
