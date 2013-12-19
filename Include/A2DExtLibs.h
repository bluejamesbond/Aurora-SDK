
//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DEXTLIBS
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32

// C RunTime Header Files
#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "dxgi.lib")

#include <d3d10.h>

#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\D3DX9.h"
#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\D3DX10.h"
#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\D3DX10math.h"
#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\D3DX9tex.h"

#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <wchar.h>
#include <math.h>
#include <iostream> 
#include <fstream>
#include <GdiPlus.h>
#include <GdiPlusGraphics.h>
#include <windowsx.h>

#elif __UNIX

#include <test_DELETE_PLEASE>

#endif