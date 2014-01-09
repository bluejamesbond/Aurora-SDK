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

#include "../Core/Rect.h"
#include "../Core/Paint.h"

#include "ExtLibs.h"
#include "DXUtils.h"
#include "Texture.h"
#include "QuadData.h"
#include "VertexTypes.h"

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
	
		static inline void				memcpySSE2QuadVertex(TextureVertex * xDest, const TextureVertex * xSrc);
		static inline void				memcpySSE2QuadVertex(ColoredTextureVertex * xDest, const ColoredTextureVertex * xSrc);
		static inline void				memcpySSE2QuadVertex(ColorVertex * xDest, const ColorVertex * xSrc);
		
		bool							updateVertexBuffer(QuadData<QuadExpansionVertex, 1> * xQuadData, Rect * xRect, Texture * xTexture, Paint * xPaint, bool xRepeat);
		bool							updateVertexBuffer(QuadData<ColoredTextureVertex, 6> * xQuadData, Rect * xRect, Texture * xTexture, Paint * xPaint, bool xRepeat);
		bool							updateVertexBuffer(QuadData<TextureVertex, 6> * xQuadData, Rect * xRect, Texture * xTexture, bool xRepeat);
		bool							updateVertexBuffer(QuadData<ColorVertex, 6> * xQuadData, Rect * xRect, Paint * xPaint);

		void							setDepth(float xZ);
		void							renderQuad(ID3D10Buffer * xVertexBuffer, unsigned int xStride);
		bool							setConstraints(Rect * xContraints, float xZ);

	public:
		
		virtual HRESULT                 initialize();
	};

}




#endif