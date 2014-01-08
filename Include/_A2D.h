
// For internal use only

#ifndef GRAPHICS__
#ifdef _WIN32
#define	 GRAPHICS__	"../Windows/Graphics.h"
#elif __linux__
#define	 GRAPHICS__	"../Linux/Graphics.h"
#endif
#endif

#ifndef GRAPHICS
#ifdef _WIN32
#define	 GRAPHICS	"../../../Aurora-SDK/Include/Windows/Graphics.h"
#elif __linux__
#define	 GRAPHICS "../../../Aurora-SDK/Include/Linux/Graphics.h"
#endif
#endif
