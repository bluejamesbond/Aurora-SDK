////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __RENDERDATA_H__
#define __RENDERDATA_H__

//+-----------------------------------------------------------------------------
//
//  Struct:
//      RENDERDATA
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "Abstract.h"
#include "AbstractWindow.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;
	class Renderable;
	class AbstractComponent;
	class Camera;
	struct RenderData;
	class BackBuffer;
	class TextureBuffer;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	struct RenderData
	{
		// Variables
		float                *     aViewMatrix;
		float                *     aWorldMatrix;
		float                *     aProjection2DMatrix;
		float                *     aProjection3DMatrix;

		Dims					  *		aWindowDims;
		Camera				  *     aCamera;
		BackBuffer             *     aBackBuffer;
		TextureBuffer          *     aTextureBuffer;
		TextureBuffer          *     aBlurBuffer;
	};
}

#endif
