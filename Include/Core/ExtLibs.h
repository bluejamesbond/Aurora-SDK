
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

#ifndef __EXTLIBS_H_CX__
#define __EXTLIBS_H_CX__

#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <math.h>

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<< MOVE THIS
#ifdef _WIN32

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

#endif