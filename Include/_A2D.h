
// For internal use only

#ifndef GRAPHICS__
#ifdef _WIN32
#define	 GRAPHICS__	"../Windows/Graphics.h"
#elif _LINUX
#define	 GRAPHICS__	"../Linux/Graphics.h"
#endif
#endif

#ifndef GRAPHICS
#ifdef _WIN32
#define	 GRAPHICS	"../../../Aurora-SDK/Include/Windows/Graphics.h"
#elif _LINUX
#define	 GRAPHICS "../../../Aurora-SDK/Include/Linux/Graphics.h"
#endif
#endif