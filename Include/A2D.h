
#include "Core/ExtLibs.h"

// Required for Windows
#ifdef _WIN32
#include "Windows/ExtLibs.h"
#include "Windows/Frame.h"
#endif

// Required for Linux
#ifdef __linux__
#include "Linux/ExtLibs.h"
#include "Linux/Frame.h"
#endif

// Platform dependent graphics
#ifndef GRAPHICS
#ifdef _WIN32
#define	 GRAPHICS	"../../../Aurora-SDK/Include/Windows/Graphics.h"
#elif __linux__
#define	 GRAPHICS "../../../Aurora-SDK/Include/Linux/Graphics.h"
#endif
#endif