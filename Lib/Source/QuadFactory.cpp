
#include "../../include/ExtLibs.h"
#include "../../include/QuadFactory.h"

using namespace A2D;

QuadFactory::QuadFactory(ID3D10Device ** xDXDevice, Dims * xWindowDims) : aDXDevice(xDXDevice), aWindowDims(xWindowDims){}

QuadFactory::~QuadFactory(){}

bool QuadFactory::setConstraints(QuadData * aQuadData, Rect * xContraints)
{

	Rect::memcpySSE2(&aConstraints, xContraints);

	// WHy store contraints into every QuadData
//	if (memcmp(&aQuadData->aPreviousContraints, xContraints, sizeof(Rect)) != 0)
//	{
//		x_aligned_memcpy_sse2(&aQuadData->aPreviousContraints, xContraints, sizeof(Rect));
//		return aContraintsChanged = true;
//	}
//	else
//	{
//		return aContraintsChanged = false;
//	}

	return true;
}

void  QuadFactory::memcpySSE2VertexData(void * xDest, const void * xSrc)
{
	// Memcopy built specifically for VertexData (120 bytes)
	// Unaligned D3DData
	// @author MK - Based on William Chan and Google

	__asm
	{
		// Store
		mov esi, xSrc;
		mov edi, xDest;

		// Prefetch
		prefetchnta 64[ESI]; 
		prefetchnta 96[ESI]; 

		// Move into Xmms - 128 bit
		movdqu xmm0, 0[ESI];	
		movdqu xmm1, 16[ESI];	
		movdqu xmm2, 32[ESI];   
		movdqu xmm3, 48[ESI];   
		movdqu xmm4, 64[ESI];   
		movdqu xmm5, 80[ESI];
		movdqu xmm6, 96[ESI];	

		// Move into Mmx - 64 bit
		movq   mm0, 112[ESI];	

		movdqu 0[EDI], xmm0; 
		movdqu 16[EDI], xmm1;
		movdqu 32[EDI], xmm2;
		movdqu 48[EDI], xmm3;
		movdqu 64[EDI], xmm4;
		movdqu 80[EDI], xmm5;
		movdqu 96[EDI], xmm6;

		movq   112[EDI], mm0;
	}
}


HRESULT QuadFactory::updateVertexBuffer(QuadData * aQuadData, Rect * xRect, Rect * xTextureClip,
					Dims * xTextureDims, ImageProperties * xImageProperties)
{
	HRESULT hr = S_OK;


	Rect& contraints = aConstraints;

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
	rectChange = memcmp(&aQuadData->aPreviousRect, xRect, sizeof(Rect));
	imagePropertiesChange = memcmp(&aQuadData->aPreviousImageProperties, xImageProperties, sizeof(ImageProperties));
	imagePropertiesChange = memcmp(&aQuadData->aPreviousImageProperties, xImageProperties, sizeof(ImageProperties));

	if (!(rectChange | imagePropertiesChange) && !aContraintsChanged)	return hr;

	// Transfer all previous contraints over using accelerated functions
	x_aligned_memcpy_sse2(&aQuadData->aPreviousRect, xRect, sizeof(Rect));
	x_aligned_memcpy_sse2(&aQuadData->aPreviousImageProperties, xImageProperties, sizeof(Rect));
	x_aligned_memcpy_sse2(&aQuadData->aPreviousImageProperties, xImageProperties, sizeof(Rect));
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
	VertexData * vertices = aQuadData->aVertices;
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

	// Calculate dESIred texture mapping.
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
	memcpySSE2VertexData(mappedVertices, (void*)vertices);

	// Unlock the vertex buffer.
	aQuadData->aVertexBuffer->Unmap();

	return hr;

}

unsigned int QuadFactory::aStride = sizeof(VertexData);
unsigned int QuadFactory::aOffset = 0;



void QuadFactory::RenderQuad(QuadData * aQuadData)
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

HRESULT QuadFactory::Initialize()
{
	HRESULT hr = S_OK;

	hr = DXShapeUtils::CreateDefaultDynamicVertexBuffer<VertexData>(*aDXDevice, &aVertexBuffer, 6);
	if (FAILED(hr))	return hr;

	hr = DXShapeUtils::CreateDefaultIndexBuffer(*aDXDevice, &aIndexBuffer, 6);
	if (FAILED(hr))	return hr;

	return hr;
}

void QuadFactory::Deinitialize()
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

LPCWSTR QuadFactory::GetClass()
{
	return L"QuadFactory";
}

LPCWSTR QuadFactory::ToString()
{
	return L"QuadFactory";
}

bool QuadFactory::operator==(Abstract * Abstract)
{
	return false;
}

