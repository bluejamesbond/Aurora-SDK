
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DQuadX.h"



A2DQuadX::A2DQuadX(A2DBackBuffer * xBuffer, A2DRect * xRect, int xQuadCount) :
A2DQuad(xBuffer, xRect), aQuadCount(xQuadCount){}

A2DQuadX::~A2DQuadX(){}

HRESULT A2DQuadX::CreateResources(void * xArgs[])
{
	// Initialize buffers depending on the amount of quads we are going to render.
	aVertexCount = aQuadCount * 6;
	aIndexCount = aQuadCount * 6;
	return A2DAbstractShape::CreateResources(xArgs);
}

// 0: a2drect
// 1: a2dtexture
// 2: a2dwinprops
// 3: orientation (horizontal/vertical) (?)
// 4: repeat direction x or y (?)
void A2DQuadX::Update(void * xArgs[])
{
	HRESULT hr;

	// Set variables.
	aRect = static_cast<A2DRect*>(xArgs[0]);
	aTexture = static_cast<A2DTexture*>(xArgs[1]); 
	aWindowDims = static_cast<A2DDims*>(xArgs[2]);

	hr = Map();
	if (FAILED(hr)) return;

	Render();

}

HRESULT A2DQuadX::Map()
{

	HRESULT hr;
	int i;

	aVertices = new A2DVertexData[aVertexCount];
	aIndex = i = 0;

	while (aVertexCount > aIndex)
	{
		CalculateCoords(aTexture->GetClip(i++ % aQuadCount)); // repeat textures if we run out of new ones.
		BuildVertex();
		aHorizontal ? aRect->aX += aRect->aWidth : aRect->aY += aRect->aHeight;
	}
	
	hr = MapCoords();
	
	return hr;
}

void A2DQuadX::BuildVertex()
{
	// Load the vertex array with data.
	aVertices[aIndex].position = D3DXVECTOR3(aLeft, aTop, 0.0f);  // Top left.
	aVertices[aIndex++].texture = D3DXVECTOR2(aLeftTex, aTopTex);

	aVertices[aIndex].position = D3DXVECTOR3(aRight, aBottom, 0.0f);  // Bottom right.
	aVertices[aIndex++].texture = D3DXVECTOR2(aRightTex, aBottomTex);

	aVertices[aIndex].position = D3DXVECTOR3(aLeft, aBottom, 0.0f);  // Bottom left.
	aVertices[aIndex++].texture = D3DXVECTOR2(aLeftTex, aBottomTex);

	// Second triangle.
	aVertices[aIndex].position = D3DXVECTOR3(aLeft, aTop, 0.0f);  // Top left.
	aVertices[aIndex++].texture = D3DXVECTOR2(aLeftTex, aTopTex);

	aVertices[aIndex].position = D3DXVECTOR3(aRight, aTop, 0.0f);  // Top right.
	aVertices[aIndex++].texture = D3DXVECTOR2(aRightTex, aTopTex);

	aVertices[aIndex].position = D3DXVECTOR3(aRight, aBottom, 0.0f);  // Bottom right.
	aVertices[aIndex++].texture = D3DXVECTOR2(aRightTex, aBottomTex);	
}

HRESULT A2DQuadX::MapCoords()
{
	HRESULT hr;
	void* verticesPtr;

	// Initialize the vertex buffer pointer to null first.
	verticesPtr = 0;

	// Lock the vertex buffer.
	hr = aVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**)&verticesPtr);
	if (FAILED(hr))
	{
		return false;
	}

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)aVertices, (sizeof(A2DVertexData)* aVertexCount));

	// Unlock the vertex buffer.
	aVertexBuffer->Unmap();

	return true;
}


LPCWSTR A2DQuadX::GetClass()
{
	return L"A2DQuadX";
}

LPCWSTR A2DQuadX::ToString()
{
	return L"A2DQuadX";
}

bool A2DQuadX::operator==(A2DAbstract * A2DAbstract)
{
	return this == A2DAbstract;
}
