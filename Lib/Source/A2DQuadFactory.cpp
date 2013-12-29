
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DQuadFactory.h"

A2DQuadFactory::A2DQuadFactory(ID3D10Device ** xDXDevice, A2DDims * xWindowDims) : aDXDevice(xDXDevice), aWindowDims(xWindowDims){}

A2DQuadFactory::~A2DQuadFactory(){}

bool A2DQuadFactory::setConstraints(A2DQuadData * aQuadData, A2DRect * xContraints)
{

	A2DRect::memcpySSE2(&aConstraints, xContraints);

	// WHy store contraints into every QuadData
//	if (memcmp(&aQuadData->aPreviousContraints, xContraints, sizeof(A2DRect)) != 0)
//	{
//		x_aligned_memcpy_sse2(&aQuadData->aPreviousContraints, xContraints, sizeof(A2DRect));
//		return aContraintsChanged = true;
//	}
//	else
//	{
//		return aContraintsChanged = false;
//	}

	return true;
}

HRESULT A2DQuadFactory::updateVertexBuffer(A2DQuadData * aQuadData, A2DRect * xRect, A2DRect * xTextureClip,
					A2DDims * xTextureDims, A2DImageProperties * xImageProperties)
{
	HRESULT hr = S_OK;


	A2DRect& contraints = aConstraints;

	int textureDimsChange = 0;
	int textureClipChange = 0;
	int rectChange = 0;
	int imagePropertiesChange = 0;

	float rectX = xRect->aX;
	float rectY = xRect->aY;
	float rectWidth = xRect->aWidth;
	float rectHeight = xRect->aHeight;

	
	if (rectX >= contraints.aWidth || rectY >= contraints.aHeight)	return hr;
	
	/*
	// Compare using built in accelerated-function
	rectChange = memcmp(&aQuadData->aPreviousRect, xRect, sizeof(A2DRect));
	imagePropertiesChange = memcmp(&aQuadData->aPreviousImageProperties, xImageProperties, sizeof(A2DImageProperties));
	imagePropertiesChange = memcmp(&aQuadData->aPreviousImageProperties, xImageProperties, sizeof(A2DImageProperties));

	if (!(rectChange | imagePropertiesChange) && !aContraintsChanged)	return hr;

	// Transfer all previous contraints over using accelerated functions
	x_aligned_memcpy_sse2(&aQuadData->aPreviousRect, xRect, sizeof(A2DRect));
	x_aligned_memcpy_sse2(&aQuadData->aPreviousImageProperties, xImageProperties, sizeof(A2DRect));
	x_aligned_memcpy_sse2(&aQuadData->aPreviousImageProperties, xImageProperties, sizeof(A2DRect));
		*/

	float realX, realY;	
	float textureX = xTextureClip->aX;
	float textureY = xTextureClip->aY;
	float textureWidth = xTextureClip->aWidth;
	float textureHeight = xTextureClip->aHeight;

	float realWidth, realHeight, calcWidth, calcHeight;
	float consOffsetX, consOffsetY;
	float realTWidth, realTHeight, calcTX, calcTY;
	float tWidthOffset, tHeightOffset;

	float left;
	float right;
	float top;
	float bottom;
	float leftTex;
	float rightTex;
	float topTex;
	float bottomTex;

	byte index = 0;
	A2DVertexData * vertices = aQuadData->aVertices;
	void * mappedVertices = 0;
	
	// Bitmap mapping calculations.
	realX = rectX < 0 ? contraints.aX : contraints.aX + rectX;
	realY = rectY < 0 ? contraints.aY : contraints.aY + rectY;

	calcWidth = rectX < 0 ? rectWidth - abs(rectX) : rectWidth;
	calcHeight = rectY < 0 ? rectHeight - abs(rectY) : rectHeight;

	consOffsetX = rectX < 0 ? 0 : rectX;
	consOffsetY = rectY < 0 ? 0 : rectY;

	realWidth = rectX + calcWidth > contraints.aWidth ? contraints.aWidth - consOffsetX : calcWidth;
	realHeight = rectY + calcHeight > contraints.aHeight ? contraints.aHeight - consOffsetY : calcHeight;

	// Handle negative constraint dimensions.
	if (realWidth < 0)
	{
		realWidth = realWidth + rectX > 0 ? realWidth + rectX : 0;
	}
	if (realHeight < 0)
	{
		realHeight = realHeight + rectY > 0 ? realHeight + rectY : 0;
	}

	// Texture mapping calculations.
	calcTX = rectX < 0 ? rectX + (rectWidth * abs(rectX)) / contraints.aWidth : rectX;
	calcTY = rectX < 0 ? rectY + (rectHeight * abs(rectY)) / contraints.aHeight : rectY;

	calcTX += textureX;
	calcTY += textureY;

	// Calculate offset for x and y constraints.
	tWidthOffset = rectX + calcWidth > contraints.aWidth || rectX < 0 ? (rectWidth * abs(rectX)) / contraints.aWidth : 0;
	realTWidth = rectWidth - tWidthOffset;

	realTWidth = textureWidth - realTWidth < 0 ? textureWidth : realTWidth;

	tHeightOffset = rectY + calcHeight > contraints.aHeight || rectY < 0 ? (rectHeight * abs(rectY)) / contraints.aHeight : 0;
	realTHeight = rectHeight - tHeightOffset;

	realTHeight = textureHeight - realTHeight < 0 ? textureHeight : realTHeight;

	// Calculate offset for dimension constraints.
	realTWidth -= rectWidth < contraints.aWidth ? (rectWidth * (contraints.aWidth - rectWidth)) / contraints.aWidth : 0;
	realTHeight -= rectHeight < contraints.aHeight ? (rectHeight * (contraints.aHeight - rectHeight)) / contraints.aHeight : 0;
				
	// Calculate the screen coordinates of the left side of the bitmap.
	left = ((aWindowDims->aWidth / 2) * -1) + realX;

	// Calculate the screen coordinates of the right side of the bitmap.
	right = left + realWidth;

	// Calculate the screen coordinates of the top of the bitmap.
	top = (aWindowDims->aHeight / 2) - realY;

	// Calculate the screen coordinates of the bottom of the bitmap.
	bottom = top - realHeight;

	// Calculate desired texture mapping.
	leftTex = calcTX / xTextureDims->aWidth;
	rightTex = (calcTX + realTWidth) / xTextureDims->aWidth;;
	topTex = calcTY / xTextureDims->aWidth;
	bottomTex = (calcTY + realTHeight) / xTextureDims->aHeight;
	
	// Load the vertex array with data.
	vertices[index].position = D3DXVECTOR3(left, top, 0.0f);  // Top left.
	vertices[index++].texture = D3DXVECTOR2(leftTex, topTex);

	vertices[index].position = D3DXVECTOR3(right, bottom, 0.0f);  // Bottom right.
	vertices[index++].texture = D3DXVECTOR2(rightTex, bottomTex);

	vertices[index].position = D3DXVECTOR3(left, bottom, 0.0f);  // Bottom left.
	vertices[index++].texture = D3DXVECTOR2(leftTex, bottomTex);

	// Second triangle.
	vertices[index].position = D3DXVECTOR3(left, top, 0.0f);  // Top left.
	vertices[index++].texture = D3DXVECTOR2(leftTex, topTex);

	vertices[index].position = D3DXVECTOR3(right, top, 0.0f);  // Top right.
	vertices[index++].texture = D3DXVECTOR2(rightTex, topTex);

	vertices[index].position = D3DXVECTOR3(right, bottom, 0.0f);  // Bottom right.
	vertices[index++].texture = D3DXVECTOR2(rightTex, bottomTex);
	
	// Lock the vertex buffer.
	hr = aQuadData->aVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**)&mappedVertices);
	if (FAILED(hr))	return hr;

	// Copy the data into the vertex buffer.
	memcpy(mappedVertices, (void*)vertices, (sizeof(A2DVertexData)* 6));

	// Unlock the vertex buffer.
	aQuadData->aVertexBuffer->Unmap();

	return hr;

}

unsigned int A2DQuadFactory::aStride = sizeof(A2DVertexData);
unsigned int A2DQuadFactory::aOffset = 0;



void A2DQuadFactory::RenderQuad(A2DQuadData * aQuadData)
{
	ID3D10Device  *	device = *aDXDevice;

	// Set the vertex buffer to active in the input 
	// assembler so it can be rendered.
	device->IASetVertexBuffers(0, 1, &aQuadData->aVertexBuffer, &aStride, &aOffset);

	// Set the index buffer to active in the input
	// assembler so it can be rendered.
	device->IASetIndexBuffer(aIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be 
	// rendered from this vertex buffer, in this case triangles.
	device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

HRESULT A2DQuadFactory::Initialize()
{
	HRESULT hr = S_OK;

	hr = A2DDXShapeUtils::CreateDefaultDynamicVertexBuffer<A2DVertexData>(*aDXDevice, &aVertexBuffer, 6);
	if (FAILED(hr))	return hr;

	hr = A2DDXShapeUtils::CreateDefaultIndexBuffer(*aDXDevice, &aIndexBuffer, 6);
	if (FAILED(hr))	return hr;

	return hr;
}

void A2DQuadFactory::Deinitialize()
{
	if (aVertexBuffer)
	{
		aVertexBuffer->Release();
		delete aVertexBuffer;
		aVertexBuffer = 0;
	}

	if (aIndexBuffer)
	{
		aIndexBuffer->Release();
		delete aIndexBuffer;
		aIndexBuffer = 0;
	}
}

LPCWSTR A2DQuadFactory::GetClass()
{
	return L"A2DQuadFactory";
}

LPCWSTR A2DQuadFactory::ToString()
{
	return L"A2DQuadFactory";
}

bool A2DQuadFactory::operator==(A2DAbstract * A2DAbstract)
{
	return false;
}

