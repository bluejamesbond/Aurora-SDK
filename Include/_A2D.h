
// For internal use only

#ifdef _WIN32

#ifndef GRAPHICS__
#define	 GRAPHICS__	"../Windows/Graphics.h"
#endif

#ifndef GRAPHICS
#define	 GRAPHICS	"../../../Aurora-SDK/Include/Windows/Graphics.h"
#endif

#endif

// Required for Linux
#ifdef _LINUX

#ifndef GRAPHICS__
#define	 GRAPHICS__	"../Linux/Graphics.h"
#endif

#ifndef GRAPHICS
#define	 GRAPHICS "../../../Aurora-SDK/Include/Linux/Graphics.h"
#endif

#endif