////////////////////////////////////////////////////////////////////////////////
// GUARDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __QUADFACTORY_H__
#define __QUADFACTORY_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      QUADFACTORY
//
//  Synopsis:
//      Quad class to be rendered.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "DXShapeUtils.h"
#include "Texture.h"
#include "Rect.h"
#include "QuadData.h"
#include "ColoredTextureVertex.h"
#include "ColorVertex.h"
#include "Paint.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;
	class DXShapeUtils;
	class Texture;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class QuadFactory
	{
	public:

		QuadFactory(ID3D10Device ** xDevice, Dims * xWindowDims);
		~QuadFactory();

		ID3D10Buffer	*	aIndexBuffer;
		ID3D10Buffer	*	aVertexBuffer;
		
		float				aDepth = 0.0f;

		///////////////////////////////////////////////////////////

		Rect				aConstraints;
		Dims			*	aWindowDims;
		ID3D10Device	**	aDevice;

		///////////////////////////////////////////////////////////
	
		static void						memcpySSE2QuadVertex(TextureVertex * xDest, const TextureVertex * xSrc);
		static void						memcpySSE2QuadVertex(ColoredTextureVertex * xDest, const ColoredTextureVertex * xSrc);
		static void						memcpySSE2QuadVertex(ColorVertex * xDest, const ColorVertex * xSrc);
		
		HRESULT							updateVertexBuffer(QuadData<ColoredTextureVertex> * xQuadData, Rect * xRect, Texture * xTexture, Paint * xPaint, bool xRepeat);
		HRESULT							updateVertexBuffer(QuadData<TextureVertex> * xQuadData, Rect * xRect, Texture * xTexture, bool xRepeat);
		HRESULT							updateVertexBuffer(QuadData<ColorVertex> * xQuadData, Rect * xRect, Paint * xPaint);

		void							setDepth(float xZ);
		void							renderQuad(ID3D10Buffer * xVertexBuffer, unsigned int xStride);
		bool							setConstraints(Rect * xContraints, float xZ);

	public:

		//////////////////////////////////////////////////////////
		// ABSTRACT IMPLEMENTATION
		//////////////////////////////////////////////////////////

		virtual HRESULT                 initialize();
		virtual LPCWSTR                 getClass();
		virtual LPCWSTR                 toString();
	};

}




#endif