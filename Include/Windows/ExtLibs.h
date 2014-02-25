
//+-----------------------------------------------------------------------------
//
//  Class:
//      EXTLIBS
//
//  Synopsis:
//      System required dependencies.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

// C RunTime Header Files
#ifndef __EXTLIBS_H_WIN__
#define __EXTLIBS_H_WIN__

#include "../Core/ExtLibs.h"

#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "dxgi.lib")

#include <d3d10.h>

#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\D3DX9.h"
#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\D3DX10.h"
#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\D3DX10math.h"
#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\D3DX9tex.h"

#include <GdiPlus.h>
#include <GdiPlusGraphics.h>
#include <windowsx.h>

#include <sstream>
#include <assert.h> 

#endif