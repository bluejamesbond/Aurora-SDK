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
//#include "TextureVertex.h"
//#include "ColoredTextureVertex.h"
//#include "ImageProperties.h"
#include "../Core/Rect.h"

namespace A2D {


	struct VertexType
	{
		float x, y, z;
		float r, g, b;
	};


	struct GL3DTEXCOORD
	{
		float m_x, m_y;

		GL3DTEXCOORD() :
			m_x(0.0f),
			m_y(0.0f)
		{
		}

		GL3DTEXCOORD(float x_x, float x_y) :
			m_x(x_x),
			m_y(x_y)
		{
		}
	};

	struct GL3DPOSITION
	{
		float m_x, m_y, m_z;

		GL3DPOSITION() :
			m_x(0.0f),
			m_y(0.0f),
			m_z(0.0f)
		{
		}

		GL3DPOSITION(float x_x, float x_y, float x_z) :
			m_x(x_x),
			m_y(x_y),
			m_z(x_z)
		{
		}
	};

	struct TextureVertex
	{
		GL3DPOSITION m_position;
		GL3DTEXCOORD m_textCoord;
	};


	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	template<class T>
	struct QuadData
	{
		// Before adjusting the ID3D10Buffer
		// check if any of these values are different
		// Do a memcompare(ptr1, ptr2) of these with the new ones
		Rect			aPreviousRect;			  // cached
		Rect			aPreviousContraints;	  // cached
		Rect			aPreviousTextureClip;	  // cached
		Dims			aPreviousTextureSize;	  // cached
//		ImageProperties aPreviousImageProperties; // cached

		// Do not delete only adjust the values! 
//        T				aVertices[18];       //should be six but I'm going to make it a float array of 6*3 (x,y,z)
        T            *   aVertices;
		// Vertex buffer can change (but change only as needed)
		GLuint		*	aVertexBuffer;

		unsigned int * m_indices;
		unsigned int m_vertexArrayId;
		unsigned int m_vertexBufferId;
		unsigned int m_indexBufferId;

		// This pretty much stays constant
		// so it will be stored inside Quads instance.
		// ID3D10Buffer		*			aIndexBuffer;
	};
}

#endif
