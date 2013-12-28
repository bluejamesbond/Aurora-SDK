
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DDXShapeUtils.h"
#include "../../include/A2DBackBuffer.h"

HRESULT A2DDXShapeUtils::CreateDefaultIndexBuffer(ID3D10Device * xDXDevice, ID3D10Buffer ** xIndexBuffer, int xIndices)
{
	HRESULT hr;
	D3D10_BUFFER_DESC indexBufferDesc;
	D3D10_SUBRESOURCE_DATA indexData;

	unsigned long * indices = new unsigned long[xIndices];

	for (int i = 0; i < xIndices; i++)
	{
		indices[i] = i;
	}

	indexBufferDesc.Usage = D3D10_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long)* xIndices;
	indexBufferDesc.BindFlags = D3D10_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;

	hr = xDXDevice->CreateBuffer(&indexBufferDesc, &indexData, xIndexBuffer);
	if (FAILED(hr))	return hr;

	delete[] indices;
	indices = 0;

	return hr;

}
