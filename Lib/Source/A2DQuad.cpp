
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DQuad.h"

A2DQuad::A2DQuad(A2DBackBuffer * xBackBuffer, A2DRect xConstraints) :
A2DAbstractShape(xBackBuffer, 6), aConstraints(xConstraints), aTexture(0){}

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

	if (aRect->aX >= aConstraints.aWidth || aRect->aY >= aConstraints.aHeight)
	{
		// Render nothing.
		aLeft = aRight = aTop = aBottom = 0.0f;
		aLeftTex = aRightTex = aTopTex = aBottomTex = 0.0f;
	}
	else
	{
		float realX, realY;

		// Bitmap mapping calculations.
		realX = aRect->aX < 0 ? aConstraints.aX : aConstraints.aX + aRect->aX;
		realY = aRect->aY < 0 ? aConstraints.aY : aConstraints.aY + aRect->aY;

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

		calcWidth = aRect->aX < 0 ? aRect->aWidth - abs(aRect->aX) : aRect->aWidth;
		calcHeight = aRect->aY < 0 ? aRect->aHeight - abs(aRect->aY) : aRect->aHeight;

		consOffsetX = aRect->aX < 0 ? 0 : aRect->aX;
		consOffsetY = aRect->aY < 0 ? 0 : aRect->aY;

		realWidth = aRect->aX + calcWidth > aConstraints.aWidth ? aConstraints.aWidth - consOffsetX : calcWidth;
		realHeight = aRect->aY + calcHeight > aConstraints.aHeight ? aConstraints.aHeight - consOffsetY : calcHeight;

		// Handle negative constraint dimensions.
		if (realWidth < 0)
		{
			realWidth = realWidth + aRect->aX > 0 ? realWidth + aRect->aX : 0;
		}
		if (realHeight < 0)
		{
			realHeight = realHeight + aRect->aY > 0 ? realHeight + aRect->aY : 0;
		}

		// Texture mapping calculations.
		calcTX = aRect->aX < 0 ? aRect->aX + (aRect->aWidth * abs(aRect->aX)) / aConstraints.aWidth : aRect->aX;
		calcTY = aRect->aX < 0 ? aRect->aY + (aRect->aHeight * abs(aRect->aY)) / aConstraints.aHeight : aRect->aY;

		calcTX += xTexRect->aX;
		calcTY += xTexRect->aY;

		// Calculate offset for x and y constraints.
		tWidthOffset = aRect->aX + calcWidth > aConstraints.aWidth || aRect->aX < 0 ? (aRect->aWidth * abs(aRect->aX)) / aConstraints.aWidth : 0;
		realTWidth = aRect->aWidth - tWidthOffset;

		realTWidth = xTexRect->aWidth - realTWidth < 0 ? xTexRect->aWidth : realTWidth;

		tHeightOffset = aRect->aY + calcHeight > aConstraints.aHeight || aRect->aY < 0 ? (aRect->aHeight * abs(aRect->aY)) / aConstraints.aHeight : 0;
		realTHeight = aRect->aHeight - tHeightOffset;

		realTHeight = xTexRect->aHeight - realTHeight < 0 ? xTexRect->aHeight : realTHeight;

		// Calculate offset for dimension constraints.
		realTWidth -= aRect->aWidth < aConstraints.aWidth ? (aRect->aWidth * (aConstraints.aWidth - aRect->aWidth)) / aConstraints.aWidth : 0;
		realTHeight -= aRect->aHeight < aConstraints.aHeight ? (aRect->aHeight * (aConstraints.aHeight - aRect->aHeight)) / aConstraints.aHeight : 0;

		// Reset constraint changed flag.
		aCONSTRAINT_CHANGED = false;

		// If it has changed then update the position it is being rendered to.
		aPrevPosX = aConstraints.aX;
		aPrevPosY = aConstraints.aY;


		// Calculate the screen coordinates of the left side of the bitmap.
		aLeft = ((aWindowDims->aWidth / 2) * -1) + realX;

		// Calculate the screen coordinates of the right side of the bitmap.
		aRight = aLeft + realWidth;

		// Calculate the screen coordinates of the top of the bitmap.
		aTop = (aWindowDims->aHeight / 2) - realY;

		// Calculate the screen coordinates of the bottom of the bitmap.
		aBottom = aTop - realHeight;

		// Calculate desired texture mapping.
		aLeftTex = calcTX / aTexture->GetSize()->aWidth;
		aRightTex = (calcTX + realTWidth) / aTexture->GetSize()->aWidth;;
		aTopTex = calcTY / aTexture->GetSize()->aHeight;;
		aBottomTex = (calcTY + realTHeight) / aTexture->GetSize()->aHeight;;
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

	while (aVertexCount != aIndex)
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

	// Reset the index for future rendering.
	aIndex = 0;

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
	aWindowDims = static_cast<A2DDims*>(xArgs[2]);

	HRESULT hr;

	//aConstraints.aHeight = 500;
	//aConstraints.aWidth = 400;
	//aConstraints.aX = 0;
	//aConstraints.aY = 0;

	//aRect->aHeight = 300;
	//aRect->aWidth = 500;
	//aRect->aX = 0;
	//aRect->aY = 0;

	//aTexture->GetClip()->aX = 0;
	//aTexture->GetClip()->aY = 400;
	//aTexture->GetClip()->aWidth = 500;
	//aTexture->GetClip()->aHeight = 300;

	//aTexture->GetClip()->aHeight = 3;
	//aTexture->GetClip()->aWidth = 3;

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
	if (xRect->aX != aConstraints.aX ||
		xRect->aY != aConstraints.aY ||
		xRect->aWidth != aConstraints.aWidth ||
		xRect->aHeight != aConstraints.aHeight)
	{
		aConstraints.aX = xRect->aX;
		aConstraints.aY = xRect->aY;
		aConstraints.aWidth = xRect->aWidth;
		aConstraints.aHeight = xRect->aHeight;
		aCONSTRAINT_CHANGED = true;
	}
}

//////////////////////////////////////////////////////////
// A2DABSTRACT IMPLEMENTATION
//////////////////////////////////////////////////////////

HRESULT A2DQuad::Initialize()
{
	HRESULT hr = S_OK;

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
	aWindowDims = 0;
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

