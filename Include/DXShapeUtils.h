////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ABSTRACTSHAPE_H__
#define __ABSTRACTSHAPE_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      ABSTRACTSHAPE
//
//  Synopsis:
//      Abstract class for shapes such as quads/triangles.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "Common.h"
#include "Rect.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Abstract;
	class Pipelineable;
	class BackBuffer;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class DXShapeUtils
	{

	public:

		template<class VertexClass>
		static HRESULT CreateDefaultDynamicVertexBuffer(ID3D10Device * xDXDevice, ID3D10Buffer ** xVertexBuffer, int xVertices);
		static HRESULT CreateDefaultIndexBuffer(ID3D10Device * xDXDevice, ID3D10Buffer ** xIndexBuffer, int xIndices);
	};

	template<class VertexClass>
	HRESULT DXShapeUtils::CreateDefaultDynamicVertexBuffer(ID3D10Device * xDXDevice, ID3D10Buffer ** xVertexBuffer, int xVertices)
	{
		D3D10_BUFFER_DESC vertexBufferDesc;
		D3D10_SUBRESOURCE_DATA vertexData;
		VertexClass * vertices = new VertexClass[xVertices];

		// initialize vertex array to zeros at first.
		memset(vertices, 0, (sizeof(VertexClass)* xVertices));

		vertexBufferDesc.Usage = D3D10_USAGE_DYNAMIC;
		vertexBufferDesc.ByteWidth = sizeof(VertexClass)* xVertices;
		vertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		vertexBufferDesc.MiscFlags = 0;

		// Give the subresource structure a pointer to the vertex data.
		vertexData.pSysMem = vertices;

		SAFELY(xDXDevice->CreateBuffer(&vertexBufferDesc, &vertexData, xVertexBuffer));

		delete[] vertices;
		vertices = 0;

		return S_OK;
	}
}

#endif