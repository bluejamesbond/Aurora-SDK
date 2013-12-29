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

		///////////////////////////////////////////////////////////

		Rect				aConstraints;
		Dims			*	aWindowDims;
		ID3D10Device	**	aDXDevice;

		///////////////////////////////////////////////////////////

		bool						aContraintsChanged;

		// Rect				*			aRect;
		VertexData		*			aVertices; // DONT FORGET TO RELEASE THIS AFTER

		static void					memcpySSE2VertexData(void * xDest, const void * xSrc);

		float							aPrevPosX;
		float							aPrevPosY;

		HRESULT							updateVertexBuffer(QuadData * aQuadData, Rect * xRect, Rect * xTextureClip, Dims * xTextureDims, ImageProperties * xImageProperties);
		void							RenderQuad(QuadData * aQuadData);
		bool							setConstraints(QuadData * aQuadData, Rect * xContraints);

	public:

		//////////////////////////////////////////////////////////
		// ABSTRACT IMPLEMENTATION
		//////////////////////////////////////////////////////////

		virtual HRESULT                 Initialize();
		virtual void                    Deinitialize();
		virtual LPCWSTR                 GetClass();
		virtual LPCWSTR                 ToString();
		virtual bool                    operator==(Abstract * xAbstract); // Don't campare against quad but against any Object
	};
}


#endif