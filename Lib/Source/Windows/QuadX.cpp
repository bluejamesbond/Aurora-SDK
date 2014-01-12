
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/QuadX.h"



QuadX::QuadX(BackBuffer * xBuffer, Rect xConstraints, int xQuadCount) :
Quad(xBuffer, xConstraints), aQuadCount(xQuadCount){}

QuadX::~QuadX(){}

STATUS QuadX::CreateResources(void * xArgs[])
{
	// initialize buffers depending on the amount of quads we are going to render.
	aVertexCount = aQuadCount * 6;
	aIndexCount = aQuadCount * 6;
	return DXShapeUtils::CreateResources(xArgs);
}

// 0: a2drect
// 1: a2dtexture
// 2: a2dwinprops
// 3: orientation (horizontal/vertical) (?)
// 4: repeat direction x or y (?)
void QuadX::Update(void * xArgs[])
{
	STATUS hr;

	// Set variables.
	aRect = static_cast<Rect*>(xArgs[0]);
	aTexture = static_cast<Texture*>(xArgs[1]); 
	aWindowDims = static_cast<Dims*>(xArgs[2]);

	hr = Map();
	if (FAILED(hr)) return;

	Render();

}

STATUS QuadX::Map()
{

	STATUS hr;
	int i;

	aVertices = new VertexData[aVertexCount];
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

void QuadX::BuildVertex()
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

STATUS QuadX::MapCoords()
{
	STATUS hr;
	void* verticesPtr;

	// initialize the vertex buffer pointer to null first.
	verticesPtr = 0;

	// Lock the vertex buffer.
	hr = aVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**)&verticesPtr);
	if (FAILED(hr))
	{
		return false;
	}

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)aVertices, (sizeof(VertexData)* aVertexCount));

	// Unlock the vertex buffer.
	aVertexBuffer->Unmap();

	return true;
}


LPCWSTR QuadX::getClass()
{
	return L"QuadX";
}

LPCWSTR QuadX::toString()
{
	return L"QuadX";
}

bool QuadX::operator==(Abstract * Abstract)
{
	return this == Abstract;
}
