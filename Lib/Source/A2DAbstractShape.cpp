
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DAbstractShape.h"
#include "../../include/A2DBackBuffer.h"


A2DAbstractShape::A2DAbstractShape(A2DBackBuffer * xBackBuffer, int xVertexCount) : 
aBackBuffer(xBackBuffer),
aVertexCount(xVertexCount), aIndexCount(xVertexCount) {}

A2DAbstractShape::~A2DAbstractShape(){}

//args
// 1: vertexcount
HRESULT A2DAbstractShape::CreateResources(void * xArgs[])
{
	HRESULT hr = S_OK;

	A2DVertexData * vertices;
	unsigned long * indices;
	D3D10_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D10_SUBRESOURCE_DATA vertexData, indexData;
	int i;

	// Create the vertex array.
	vertices = new A2DVertexData[aVertexCount];
	if (!vertices)
	{
		return E_FAIL;
	}

	// Create the index array.
	indices = new unsigned long[aIndexCount];
	if (!indices)
	{
		return E_FAIL;
	}

	// Initialize vertex array to zeros at first.
	memset(vertices, 0, (sizeof(A2DVertexData)* aVertexCount));

	// Load the index array with data.
	for (i = 0; i < aIndexCount; i++)
	{
		indices[i] = i;
	}

	// Set up the description of the dynamic vertex buffer.
	vertexBufferDesc.Usage = D3D10_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(A2DVertexData)* aVertexCount;
	vertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;

	// Now finally create the vertex buffer.
	hr = aBackBuffer->aDXDevice->CreateBuffer(&vertexBufferDesc, &vertexData, &aVertexBuffer);
	if (FAILED(hr))
	{
		return hr;
	}

	// Set up the description of the index buffer.
	indexBufferDesc.Usage = D3D10_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long)* aIndexCount;
	indexBufferDesc.BindFlags = D3D10_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;

	// Create the index buffer.
	hr = aBackBuffer->aDXDevice->CreateBuffer(&indexBufferDesc, &indexData, &aIndexBuffer);
	if (FAILED(hr))
	{
		return hr;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return hr;
	
}

void A2DAbstractShape::Render()
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(A2DVertexData);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	aBackBuffer->aDXDevice->IASetVertexBuffers(0, 1, &aVertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	aBackBuffer->aDXDevice->IASetIndexBuffer(aIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	aBackBuffer->aDXDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

void A2DAbstractShape::DestroyResources()
{

	// Release the index buffer.
	if (aIndexBuffer)
	{
		aIndexBuffer->Release();
		aIndexBuffer = 0;
	}

	// Release the vertex buffer.
	if (aVertexBuffer)
	{
		aVertexBuffer->Release();
		aVertexBuffer = 0;
	}

	return;
}


LPCWSTR A2DAbstractShape::GetClass()
{
	return L"A2DAbstractShape";
}

LPCWSTR A2DAbstractShape::ToString()
{
	return L"A2DAbstractShape";
}

bool A2DAbstractShape::operator==(A2DAbstract * A2DAbstract)
{
	return false;
}
