

#ifdef _WIN32
#include <fstream>  // For visual studio output to console
#endif

#ifndef SYSOUT_FLT 
#ifdef _WIN32
#define SYSOUT_FLT(x)										  _RPT1( 0, "[Aurora -SDK] %f\n", x )
#elif __linux__
#define SYSOUT_FLT(x)										  _RPT1( 0, "[Aurora -SDK] %f\n", x )
#endif
#endif

#ifndef SYSOUT_INT 
#ifdef _WIN32
#define SYSOUT_SINT(x)										  _RPT1( 0, "[Aurora -SDK] %d\n", x )
#elif __linux__
#define SYSOUT_SINT(x)										  _RPT1( 0, "[Aurora -SDK] %d\n", x )
#endif
#endif

#ifndef SYSOUT_HEX 
#ifdef _WIN32
#define SYSOUT_HEX(x)										   _RPT1( 0, "[Aurora -SDK] 0x%X\n", x )
#elif __linux__
#define SYSOUT_HEX(x)										   _RPT1( 0, "[Aurora -SDK] 0x%X\n", x )
#endif
#endif

#ifndef SYSOUT_STR
#ifdef _WIN32
#define SYSOUT_STR(x)										  _RPT1( 0, "[Aurora -SDK] %s\n", x )
#elif __linux__
#define SYSOUT_STR(x)										  _RPT1( 0, "[Aurora -SDK] %s\n", x )
#endif
#endif

#ifndef SYSOUT_F
#ifdef _WIN32
#define SYSOUT_F(f, ...)									  _RPT1( 0, "[Aurora -SDK] " f "\n", __VA_ARGS__ )
#elif __linux__
#define SYSOUT_F(f, ...)									  _RPT1( 0, "[Aurora -SDK] " f "\n", __VA_ARGS__ )
#endif
#endif

// Used for timing calculations for debugging
#include <time.h>

#ifndef __DEBUG_INIT_CLOCK__
#define __DEBUG_INIT_CLOCK__								  clock_t timeStart;
#endif

#ifndef __DEBUG_START_CLOCK__										
#define __DEBUG_START_CLOCK__							      timeStart = clock();
#endif

#ifndef __DEBUG_END_CLOCK__										
#define __DEBUG_END_CLOCK__									  SYSOUT_F("Time taken: %.9fs", (double)(clock() - timeStart) / CLOCKS_PER_SEC);
#endif

#ifndef speedtest__				
#define speedtest__(data)									  for (long blockTime = NULL; (blockTime == NULL ? (blockTime = clock()) != NULL : false); SYSOUT_F(data "Time taken: %.9fs", (double) (clock() - blockTime) / CLOCKS_PER_SEC))
#endif