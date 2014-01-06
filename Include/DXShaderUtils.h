////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __DXSHADERUTILS_H__
#define __DXSHADERUTILS_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      DXSHADERUTILS
//
//  Synopsis:
//      Texture quad.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "BackBuffer.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;
	class Pipelineable;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class DXShaderUtils
	{

	public:

		// Load a shader from file
		static HRESULT					LoadEffectFromFile(LPCWSTR xFilename, ID3D10Device * xDevice, ID3D10Effect ** xEffect);

		// Create Alpha transpareny supportable PNG
		static HRESULT					CreatePNGCompatibleBlendStates(ID3D10Device * xDevice, ID3D10BlendState ** xBlendState, ID3D10BlendState ** xBlendDisabledState);

		// Output Error - Use SYSOUT in the future
		static void						SysOut(ID3D10Blob * xErrorMessage, LPCWSTR * xFilename);

		// Load technieque from shader
		static HRESULT					loadTechniqueFromEffect(ID3D10Device * xDevice, ID3D10Effect * xEffect, ID3D10InputLayout ** xLayout, ID3D10EffectTechnique ** xTechnqiue, D3D10_INPUT_ELEMENT_DESC * xPolygonLayout, LPCSTR xName, unsigned int xElements);
	};
}


#endif