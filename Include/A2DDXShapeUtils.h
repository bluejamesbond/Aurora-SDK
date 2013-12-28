////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DABSTRACTSHAPE_H__
#define __A2DABSTRACTSHAPE_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      A2DABSTRACTSHAPE
//
//  Synopsis:
//      Abstract class for shapes such as quads/triangles.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DExtLibs.h"
#include "A2DPipelineable.h"
#include "A2DVertexData.h"
#include "A2DRect.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DAbstract;
class A2DPipelineable;
class A2DBackBuffer;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DDXShapeUtils
{

public:
	
	template<class VertexClass>
	static HRESULT CreateDefaultDynamicVertexBuffer(ID3D10Device * xDXDevice, ID3D10Buffer ** xVertexBuffer, int xVertices);
	
	static HRESULT CreateDefaultIndexBuffer(ID3D10Device * xDXDevice, ID3D10Buffer ** xIndexBuffer, int xIndices);
};

template<class VertexClass>
HRESULT A2DDXShapeUtils::CreateDefaultDynamicVertexBuffer(ID3D10Device * xDXDevice, ID3D10Buffer ** xVertexBuffer, int xVertices)
{
	HRESULT hr;
	D3D10_BUFFER_DESC vertexBufferDesc;
	D3D10_SUBRESOURCE_DATA vertexData;
	VertexClass * vertices = new A2DVertexData[xVertices];

	// Initialize vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexClass) * xVertices));

	vertexBufferDesc.Usage = D3D10_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexClass)* xVertices;
	vertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;

	hr = xDXDevice->CreateBuffer(&vertexBufferDesc, &vertexData, xVertexBuffer);
	if (FAILED(hr))	return hr;

	delete[] vertices;
	vertices = 0;

	return hr;
}

#endif