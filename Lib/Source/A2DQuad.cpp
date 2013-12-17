
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DQuad.h"

A2DQuad::A2DQuad(A2DBackBuffer * xBackBuffer, A2DRect * xRect) :
A2DAbstractShape(xBackBuffer, 6), aQuadWidth(xRect->aWidth), aQuadHeight(xRect->aHeight),
aTexture(0)
{

}

A2DQuad::~A2DQuad(){}

HRESULT A2DQuad::Map()
{	
	HRESULT hr;
	
	// Calculate vertex and texture coordinates.
	CalculateCoords(aTexture->GetClip());

	// Map coordinates to vertex buffer.
	hr = MapCoords();
	
	return hr;
	
}

void A2DQuad::CalculateCoords(A2DRect * xTexRect)
{

	if (aConstraints->aX >= aRect->aWidth || aConstraints->aY >= aRect->aHeight)
	{
		// Render nothing.
		aLeft = aRight = aTop = aBottom = 0.0f;
		aLeftTex = aRightTex = aTopTex = aBottomTex = 0.0f;
	}
	else
	{
		float realX, realY;

		// Bitmap mapping calculations.
		realX = aConstraints->aX < 0 ? aRect->aX : aRect->aX + aConstraints->aX;
		realY = aConstraints->aY < 0 ? aRect->aY : aRect->aY + aConstraints->aY;

		// If the position we are rendering this bitmap to has not changed then don't update the vertex buffer since it
		// currently has the correct parameters.
		if ((realX == aPrevPosX) && (realY == aPrevPosY) && !aCONSTRAINT_CHANGED)
		{
			return;
		}

		float realWidth, realHeight, calcWidth, calcHeight;
		float consOffsetX, consOffsetY;
		float realTWidth, realTHeight, calcTX, calcTY;
		float tWidthOffset, tHeightOffset;

		xTexRect->aX = xTexRect->aX;
		xTexRect->aY = xTexRect->aY;
		xTexRect->aHeight = xTexRect->aHeight;
		xTexRect->aWidth = xTexRect->aWidth;

		calcWidth = aConstraints->aWidth < 0 ? aConstraints->aWidth - abs(aConstraints->aX) : aConstraints->aWidth;
		calcHeight = aConstraints->aHeight < 0 ? aConstraints->aHeight - abs(aConstraints->aY) : aConstraints->aHeight;

		consOffsetX = aConstraints->aX < 0 ? 0 : aConstraints->aX;
		consOffsetY = aConstraints->aY < 0 ? 0 : aConstraints->aY;

		realWidth = aConstraints->aX + calcWidth > aRect->aWidth ? aRect->aWidth - consOffsetX : calcWidth;
		realHeight = aConstraints->aY + calcHeight > aRect->aHeight ? aRect->aHeight - consOffsetY : calcHeight;

		// Handle negative constraint dimensions.

		if (realWidth < 0)
		{
			realWidth = realWidth + aConstraints->aX > 0 ? realWidth + aConstraints->aX : 0;
		}
		if (realHeight < 0)
		{
			realHeight = realHeight + aConstraints->aY > 0 ? realHeight + aConstraints->aY : 0;
		}

		// Texture mapping calculations.
		calcTX = aConstraints->aX < 0 ? xTexRect->aX + (xTexRect->aWidth * abs(aConstraints->aX)) / aRect->aWidth : xTexRect->aX;
		calcTY = aConstraints->aY < 0 ? xTexRect->aY + (xTexRect->aHeight * abs(aConstraints->aY)) / aRect->aHeight : xTexRect->aY;

		// Calculate offset for x and y constraints.
		tWidthOffset = aConstraints->aX + calcWidth > aRect->aWidth || aConstraints->aX < 0 ? (xTexRect->aWidth * abs(aConstraints->aX)) / aRect->aWidth : 0;
		realTWidth = xTexRect->aWidth - tWidthOffset;

		tHeightOffset = aConstraints->aY + calcWidth > aRect->aHeight || aConstraints->aY < 0 ? (xTexRect->aHeight * abs(aConstraints->aY)) / aRect->aHeight : 0;
		realTHeight = xTexRect->aHeight - tHeightOffset;

		// Calculate offset for dimension constraints.
		realTWidth -= aConstraints->aWidth < aRect->aWidth ? (xTexRect->aWidth * (aRect->aWidth - aConstraints->aWidth)) / aRect->aWidth : 0;
		realTHeight -= aConstraints->aHeight < aRect->aHeight ? (xTexRect->aHeight * (aRect->aHeight - aConstraints->aHeight)) / aRect->aHeight : 0;

		// Reset constraint changed flag.
		aCONSTRAINT_CHANGED = false;

		// If it has changed then update the position it is being rendered to.
		aPrevPosX = aRect->aX;
		aPrevPosY = aRect->aY;

		// Calculate the screen coordinates of the left side of the bitmap.
		aLeft = ((aWinProps->aRealWidth / 2) * -1) + realX;

		// Calculate the screen coordinates of the right side of the bitmap.
		aRight = aLeft + realWidth;

		// Calculate the screen coordinates of the top of the bitmap.
		aTop = (aWinProps->aRealHeight / 2) - realY;

		// Calculate the screen coordinates of the bottom of the bitmap.
		aBottom = aTop - realHeight;

		// Calculate desired texture mapping.
		aLeftTex = calcTX / aTexture->GetSize()->aWidth;
		aRightTex = (calcTX + realTWidth) / aTexture->GetSize()->aWidth;
		aTopTex = calcTY / aTexture->GetSize()->aHeight;
		aBottomTex = (calcTY + realTHeight) / aTexture->GetSize()->aHeight;

	}
}

HRESULT A2DQuad::MapCoords()
{
	HRESULT result;
	
	void* verticesPtr;

	// Create the vertex array.
	aVertices = new A2DVertexData[aVertexCount];
	if (!aVertices && !(aVertexCount % 6))
	{
		// If aVertexCount does not contain a proper quad vertex count
		return false;
	}
	
	while(aVertexCount != aIndex)
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

	// Initialize the vertex buffer pointer to null first.
	verticesPtr = 0;

	// Lock the vertex buffer.
	result = aVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**)&verticesPtr);
	if (FAILED(result))
	{
		return false;
	}

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)aVertices, (sizeof(A2DVertexData)* aVertexCount));

	// Unlock the vertex buffer.
	aVertexBuffer->Unmap();

	return true;
}



// 0 : a2drect
// 1 : texture
// 2 : winprops
void A2DQuad::Update(void* xArgs[])
{

	// Set variables.
	aRect = static_cast<A2DRect*>(xArgs[0]);
	aTexture = static_cast<A2DTexture*>(xArgs[1]);
	aWinProps = static_cast<A2DWindowProperties*>(xArgs[2]);

	HRESULT hr;

	// Map vertices.
	hr = Map();
	if (FAILED(hr))
	{
		// Mapping failed. 
		return;
	}

	// Render vertices to back buffer.
	Render();
	
	return;
}


void A2DQuad::SetConstraints(A2DRect * xRect)
{
	if (xRect->aX != aConstraints->aX ||
		xRect->aY != aConstraints->aY ||
		xRect->aWidth != aConstraints->aWidth ||
		xRect->aHeight != aConstraints->aHeight)
	{
		aConstraints->aX = xRect->aX;
		aConstraints->aY = xRect->aY;
		aConstraints->aWidth = xRect->aWidth;
		aConstraints->aHeight = xRect->aHeight;
		aCONSTRAINT_CHANGED = true;
	}
}

//////////////////////////////////////////////////////////
// A2DABSTRACT IMPLEMENTATION
//////////////////////////////////////////////////////////

HRESULT A2DQuad::Initialize()
{
	HRESULT hr;
	
	aConstraints = new A2DRect();

	// Default point of constraint is NULL relative to location of quad.
	aConstraints->aX = 0;
	aConstraints->aY = 0;

	// Default dimensions of constraints is original width/height of quad.
	aConstraints->aWidth = aQuadWidth;
	aConstraints->aHeight = aQuadHeight;

	aCONSTRAINT_CHANGED = false; 

	// Initialize the previous rendering position to negative one.
	aPrevPosX = -1;
	aPrevPosY = -1;

	return hr;
}

void A2DQuad::DestroyResources()
{
	if (aRect)
	{
		delete aRect;
		aRect = 0;
	}

	if (aConstraints)
	{
		delete aConstraints;
		aConstraints = 0;
	}

	if (aVertices)
	{
		delete[] aVertices;
		aVertices = 0;
	}

	A2DAbstractShape::DestroyResources();
}

void A2DQuad::Deinitialize()
{
	// Delete the pointer but do not deallocate memory.
	aTexture = 0;
	aBackBuffer = 0;
	aWinProps = 0;
}

LPCWSTR A2DQuad::GetClass()
{
	return L"A2DQuad";
}

LPCWSTR A2DQuad::ToString()
{
	return L"A2DQuad";
}

bool A2DQuad::operator==(A2DAbstract * A2DAbstract)
{
	return false;
}

