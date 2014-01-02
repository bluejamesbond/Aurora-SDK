////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __QUADDATA_H__
#define __QUADDATA_H__


//+-----------------------------------------------------------------------------
//
//  Class:  
//      QUADDATA
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "TextureVertex.h"
#include "ColoredTextureVertex.h"
#include "ImageProperties.h"
#include "Rect.h"
#include "Pipelineable.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	struct QuadData : public Pipelineable
	{
		// Before adjusting the ID3D10Buffer
		// check if any of these values are different
		// Do a memcompare(ptr1, ptr2) of these with the new ones
		Rect			aPreviousRect;			  // cached
		Rect			aPreviousContraints;	  // cached
		Rect			aPreviousTextureClip;	  // cached
		Dims			aPreviousTextureSize;	  // cached
		ImageProperties aPreviousImageProperties; // cached

		// Do not delete only adjust the values! 
		ColoredTextureVertex			aVertices[6];

		// Vertex buffer can change (but change only as needed)
		ID3D10Buffer		*			aVertexBuffer;

		// This pretty much stays constant
		// so it will be stored inside Quads instance.
		// ID3D10Buffer		*			aIndexBuffer;
	};
}

#endif