
//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DGLXEXTLIBS
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xrender.h>

#include <GL/glew.h>
//#include <GL/glxext.h>
#include <GL/gl.h>
#include <GL/glx.h>
//#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <stdlib.h>
#include <string.h>

#define LPCWSTR char*
#define HRESULT int 
#define S_OK 1
#define E_FAIL 0
#define FAILED(x) !x

#define byte char
#define min(a, b)  ((a > b ) ? b : a)
#define max(a, b)  ((a < b ) ? b : a)

#define USE_CHOOSE_FBCONFIG
