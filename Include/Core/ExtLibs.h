
//+-----------------------------------------------------------------------------
//
//  Class:
//      EXTLIBS
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

// C RunTime Header Files

#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <wchar.h>
#include <math.h>
#include <iostream> 
#include <fstream>

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<< MOVE THIS
#ifndef __DXLIBS__
#define __DXLIBS__

#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "dxgi.lib")

#include <d3d10.h>

#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\D3DX9.h"
#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\D3DX10.h"
#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\D3DX10math.h"
#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\D3DX9tex.h"

#endif
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< TO EXTLIBS.H FOR WINDOWS