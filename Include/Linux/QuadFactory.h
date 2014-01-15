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
//#include "DXShapeUtils.h"
#include "Texture.h"
#include "../Core/Rect.h"
#include "QuadData.h"
#include "Common.h"
//#include "ColoredTextureVertex.h"
//#include "ColorVertex.h"
//#include "Paint.h"

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

        QuadFactory(Dims * xWindowDims);
		~QuadFactory();

		GLuint				aIndexBuffer;
		GLuint             	aVertexBuffer;
        GLfloat         *   g_vertex_buffer_data;
		float				aDepth = 0.0f;

		///////////////////////////////////////////////////////////

		Rect				aConstraints;
		Dims			*	aWindowDims;
        Texture         *   aTexture;
		///////////////////////////////////////////////////////////

//		HRESULT							updateVertexBuffer(QuadData<ColoredTextureVertex> * xQuadData, Rect * xRect, Texture * xTexture, Paint * xPaint, bool xRepeat);
        HRESULT							updateVertexBuffer(QuadData<float> * xQuadData, Rect * xRect, Texture * xTexture, bool xRepeat);
//		HRESULT							updateVertexBuffer(QuadData<ColorVertex> * xQuadData, Rect * xRect, Paint * xPaint);

		void							setDepth(float xZ);
        void							renderQuad();
        bool							setConstraints(Rect * xConstraints, float xZ);

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
