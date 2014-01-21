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

#include "../Core/ImageProperties.h"
#include "../Core/Rect.h"
#include "../Core/Pipelineable.h"

#include "ExtLibs.h"
#include "VertexTypes.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	template<class T, int V>
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

		float			m_previousCalcRight = 0.0f;
		float			m_previousCalcBottom = 0.0f;
		float			m_previousCalcWidth = 0.0f;
		float			m_previousCalcHeight = 0.0f;

		// Do not delete only adjust the values! 
		T				aVertices[V];

		int			isSet = 0;

		// Vertex buffer can change (but change only as needed)
		ID3D10Buffer		*			aVertexBuffer;

		// This pretty much stays constant
		// so it will be stored inside Quads instance.
		// ID3D10Buffer		*			aIndexBuffer;

		// Deletion requested by Pipelineable
		~QuadData()
		{
			D3DDESTROY(aVertexBuffer);
		}
	};
}

#endif