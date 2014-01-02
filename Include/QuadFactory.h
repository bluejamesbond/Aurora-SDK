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

		QuadFactory(ID3D10Device ** xDXDevice, Dims * xWindowDims);
		~QuadFactory();

		ID3D10Buffer	*	aIndexBuffer;
		ID3D10Buffer	*	aVertexBuffer;

		static unsigned int aStride;
		static unsigned int aOffset;

		float				aDepth = 0.0f;

		///////////////////////////////////////////////////////////

		Rect				aConstraints;
		Dims			*	aWindowDims;
		ID3D10Device	**	aDXDevice;

		///////////////////////////////////////////////////////////
	
		static void						memcpySSE2QuadTextureVertex(TextureVertex * xDest, const TextureVertex * xSrc);
		static void						memcpySSE2QuadColoredTextureVertex(ColoredTextureVertex * xDest, const ColoredTextureVertex * xSrc);
		HRESULT							updateVertexBuffer(QuadData * aQuadData, Rect * xRect, Rect * xTextureClip, Dims * xTextureDims, ImageProperties * xImageProperties);
		void							RenderQuad(QuadData * aQuadData);
		bool							setConstraints(QuadData * aQuadData, Rect * xContraints, float xZ);
		void							setDepth(float xZ);

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