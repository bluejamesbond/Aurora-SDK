
#include "../../Include/A2DExtLibs.h"
#include "../../Include/A2DGraphicsToolkit.h"

A2DGraphicsToolkit::A2DGraphicsToolkit(A2DGraphics	* xGraphics) :
aGraphics(xGraphics),
aTexture(NULL) {}

A2DGraphicsToolkit::~A2DGraphicsToolkit(){}

HRESULT A2DGraphicsToolkit::Initialize()
{
	HRESULT hr = S_OK;

	// Make a simple pointer
	aDXDevice = aGraphics->aBackBuffer->aDXDevice;
	aHWnd = &aGraphics->aWindowProps->aWindow->aChildHwnd;

	return hr;
}

HRESULT A2DGraphicsToolkit::CreateTexture(LPCWSTR * xSrc)
{
	HRESULT hr = S_OK;

	// Load the texture for this model.
	if (aTexture == NULL)
	{
		if (xSrc != NULL)
		{
			aTexture = new A2DTexture(aGraphics->aBackBuffer, xSrc);
			aTexture->loaded = true;
		}
		else
		{
			return E_FAIL;
		}

		hr = aTexture->Initialize();
		if (FAILED(hr))		return hr;

		aTextureWidth = aTexture->GetWidth();
		aTextureHeight = aTexture->GetHeight();
	}

	aTextureResource = aTexture->GetResource();

	return hr;
}

HRESULT A2DGraphicsToolkit::CreateTexture(A2DTexture * xTexture)
{
	HRESULT hr = S_OK;

	// Load the texture for this model.
	if (xTexture != NULL)
	{
		aTexture = xTexture;
		aTextureWidth = xTexture->GetWidth();
		aTextureHeight = xTexture->GetHeight();
	}
	else
	{
		return E_FAIL;
	}

	aTextureResource = xTexture->GetResource();

	return hr;
}

HRESULT A2DGraphicsToolkit::CreateShader(int xShader)
{
	HRESULT hr = S_OK;

	if (xShader == A2D_GRAPHICSTOOLKIT_BASIC_TEXTURE_SHADER)
	{
		hr = CreateShaderFromFile(L"../MuzzlerSync/texture.fx", xShader);
		if (FAILED(hr))		return hr;
	}
	else if (xShader == A2D_GRAPHICSTOOLKIT_HORIZONTAL_BLUR_TEXTURE_SHADER)
	{
		hr = CreateShaderFromFile(L"../MuzzlerSync/horizontalBlur.fx", xShader);
		if (FAILED(hr))		return hr;

		aScreenWidthPtr->SetFloat(aGraphics->aWindowProps->aRealWidth);
	}
	else if (xShader == A2D_GRAPHICSTOOLKIT_VERTICAL_BLUR_TEXTURE_SHADER)
	{
		hr = CreateShaderFromFile(L"../MuzzlerSync/verticalblur.fx", xShader);
		if (FAILED(hr))		return hr;

		aScreenHeightPtr->SetFloat(aGraphics->aWindowProps->aRealHeight);
	}

	// Set the world matrix variable inside the shader.
	aWorldMatrixPtr->SetMatrix((float*)aGraphics->aWorldMatrix);

	// Set the view matrix variable inside the shader.
	aViewMatrixPtr->SetMatrix((float*)aGraphics->aViewMatrix);

	// Set the projection matrix variable inside the shader.
	aProjectionMatrixPtr->SetMatrix((float*)aGraphics->aOrthogonalMatrix);

	// Force alpha transparency

	return hr;
}
HRESULT A2DGraphicsToolkit::CreateShaderFromFile(WCHAR * xFilename, int xShader)
{
	HRESULT hr;
	ID3D10Blob* errorMessage;
	D3D10_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D10_PASS_DESC passDesc;

	// Initialize the error message.
	errorMessage = 0;

	// Load the shader in from the file.
	hr = D3DX10CreateEffectFromFile(xFilename, NULL, NULL, "fx_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		aDXDevice, NULL, NULL, &aEffect, &errorMessage, NULL);
	if (FAILED(hr))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, xFilename);
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(*aHWnd, xFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	// Get a pointer to the technique inside the shader.
	aTechnique = aEffect->GetTechniqueByName("MainTechnique");
	if (!aTechnique)		return hr;

	// Now setup the layout of the data that goes into the shader.
	// This setup needs to match the VertexType stucture in the ModelClass and in the shader.
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	// Get a count of the elements in the layout.
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Get the description of the first pass described in the shader technique.
	aTechnique->GetPassByIndex(0)->GetDesc(&passDesc);

	// Create the input layout.
	hr = aDXDevice->CreateInputLayout(polygonLayout, numElements, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &aLayout);
	if (FAILED(hr))		return hr;

	D3D10_BLEND_DESC blendDesc;

	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.BlendEnable[0] = TRUE;
	blendDesc.RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;
	blendDesc.SrcBlend = D3D10_BLEND_SRC_ALPHA;
	blendDesc.DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
	blendDesc.BlendOp = D3D10_BLEND_OP_ADD;
	blendDesc.SrcBlendAlpha = D3D10_BLEND_ONE;
	blendDesc.DestBlendAlpha = D3D10_BLEND_ZERO;
	blendDesc.BlendOpAlpha = D3D10_BLEND_OP_ADD;

	hr = aDXDevice->CreateBlendState(&blendDesc, &this->g_pBlendState);
	if (FAILED(hr))		return hr;

	blendDesc.BlendEnable[0] = FALSE;

	hr = aDXDevice->CreateBlendState(&blendDesc, &this->g_pBlendDisableState);
	if (FAILED(hr))		return hr;

	// Get pointers to the three matrices inside the shader so we can update them from this class.
	aWorldMatrixPtr = aEffect->GetVariableByName("worldMatrix")->AsMatrix();
	aViewMatrixPtr = aEffect->GetVariableByName("viewMatrix")->AsMatrix();
	aProjectionMatrixPtr = aEffect->GetVariableByName("projectionMatrix")->AsMatrix();
	aTexturePtr = aEffect->GetVariableByName("shaderTexture")->AsShaderResource();
	
	if (xShader == A2D_GRAPHICSTOOLKIT_VERTICAL_BLUR_TEXTURE_SHADER)
	{
		aScreenHeightPtr = aEffect->GetVariableByName("screenHeight")->AsScalar();
	}
	else if (xShader == A2D_GRAPHICSTOOLKIT_HORIZONTAL_BLUR_TEXTURE_SHADER)
	{
		aScreenWidthPtr = aEffect->GetVariableByName("screenWidth")->AsScalar();
	}

	return hr;
}

void A2DGraphicsToolkit::RenderTextureShader()
{
	D3D10_TECHNIQUE_DESC techniqueDesc;
	unsigned int i;

	if (aTexture->loaded )aDXDevice->OMSetBlendState(g_pBlendState, 0, 0xffffffff);
	else aDXDevice->OMSetBlendState(g_pBlendDisableState, 0, 0xffffffff);

	// Bind the texture.
	aTexturePtr->SetResource(aTextureResource);

	// Set the input layout.
	aDXDevice->IASetInputLayout(aLayout);

	// Get the description structure of the technique from inside the shader so it can be used for rendering.
	aTechnique->GetDesc(&techniqueDesc);

	// Go through each pass in the technique (should be just one currently) and render the triangles.
	for (i = 0; i < techniqueDesc.Passes; ++i)
	{
		aTechnique->GetPassByIndex(i)->Apply(0);
		aDXDevice->DrawIndexed(aIndexCount, 0, 0);
	}
}


HRESULT A2DGraphicsToolkit::CreateQuadBuffers()
{
	A2DVertexData* vertices;
	unsigned long* indices;
	D3D10_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D10_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT hr;
	int i;

	// Set the number of vertices in the vertex array.
	aVertexCount = 6;

	// Set the number of indices in the index array.
	aIndexCount = aVertexCount;

	// Create the vertex array.
	vertices = new A2DVertexData[aVertexCount];
	if (!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[aIndexCount];
	if (!indices)
	{
		return false;
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
	hr = aDXDevice->CreateBuffer(&vertexBufferDesc, &vertexData, &aVertexBuffer);
	if (FAILED(hr))		return hr;

	// Set up the description of the index buffer.
	indexBufferDesc.Usage = D3D10_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long)* aIndexCount;
	indexBufferDesc.BindFlags = D3D10_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;

	// Create the index buffer.
	hr = aDXDevice->CreateBuffer(&indexBufferDesc, &indexData, &aIndexBuffer);
	if (FAILED(hr))		return hr;

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return hr;
}

void A2DGraphicsToolkit::UpdateQuadBuffers(float xImageLeft, float xImageTop, float xImageWidth, float xImageHeight, A2DImageProperties * xImageProps)
{
	A2DVertexData* vertices;
	void* verticesPtr;
	HRESULT hr;

	// Create the vertex array.
	vertices = new A2DVertexData[aVertexCount];

	aRepeat = (xImageProps->aOptRepeat >= A2D_OPT_BACKGROUND_REPEAT_REPEAT_X) && (xImageProps->aOptRepeat <= (A2D_OPT_BACKGROUND_REPEAT_REPEAT_X | A2D_OPT_BACKGROUND_REPEAT_REPEAT_Y));

	aOrigWidth = xImageWidth;
	aOrigHeight = xImageHeight;

	aCalcLeft = max(xImageLeft, 0);
	aCalcTop = max(xImageTop, 0);
	aCalcRight = min(aGraphics->aBoundsWidth, xImageLeft > 0 ? xImageWidth : xImageLeft + xImageWidth);
	aCalcBottom = min(aGraphics->aBoundsHeight, xImageTop > 0 ? xImageHeight : xImageTop + xImageHeight);

	aCalcHeight = aCalcBottom - aCalcTop;
	aCalcWidth = aCalcRight - aCalcLeft;

	aLeft = (float)(((aGraphics->aWindowProps->aRealWidth / 2) * -1) + (aGraphics->aBoundsLeft + aCalcLeft));
	aRight = aLeft + (float)aCalcWidth;
	aTop = (float)((aGraphics->aWindowProps->aRealHeight / 2) - (aGraphics->aBoundsTop + aCalcTop));
	aBottom = aTop - (float)aCalcHeight;

	aTexLeft = xImageLeft > 0 ? 0.0f : (float)abs(xImageLeft);
	aTexTop = xImageTop > 0 ? 0.0f : (float)abs(xImageTop);
	aTexRight = aCalcRight < aGraphics->aBoundsWidth ? aOrigWidth : (float)aCalcWidth;
	aTexBottom = aCalcBottom < aGraphics->aBoundsHeight ? aOrigHeight : (float)aCalcHeight;

	aTexelLeft = aRepeat ? aTexLeft / aTextureWidth : aTexLeft / ((float)aOrigWidth);
	aTexelTop = aRepeat ? aTexTop / aTextureHeight : aTexTop / ((float)aOrigHeight);
	aTexelRight = aRepeat ? ((float)aCalcWidth + aTexLeft) / aTextureWidth : aTexRight / ((float)aOrigWidth);
	aTexelBottom = aRepeat ? ((float)aCalcHeight + aTexTop) / aTextureHeight : aTexBottom / ((float)aOrigHeight);

	// Load the vertex array with data.
	// First triangle.
	vertices[0].position = D3DXVECTOR3(aLeft, aTop, 0.0f);  // Top aLeft.
	vertices[0].texture = D3DXVECTOR2(aTexelLeft, aTexelTop);

	vertices[1].position = D3DXVECTOR3(aRight, aBottom, 0.0f);  // Bottom aRight.
	vertices[1].texture = D3DXVECTOR2(aTexelRight, aTexelBottom);

	vertices[2].position = D3DXVECTOR3(aLeft, aBottom, 0.0f);  // Bottom aLeft.
	vertices[2].texture = D3DXVECTOR2(aTexelLeft, aTexelBottom);

	// Second triangle.
	vertices[3].position = D3DXVECTOR3(aLeft, aTop, 0.0f);  // Top aLeft.
	vertices[3].texture = D3DXVECTOR2(aTexelLeft, aTexelTop);

	vertices[4].position = D3DXVECTOR3(aRight, aTop, 0.0f);  // Top aRight.
	vertices[4].texture = D3DXVECTOR2(aTexelRight, aTexelTop);

	vertices[5].position = D3DXVECTOR3(aRight, aBottom, 0.0f);  // Bottom aRight.
	vertices[5].texture = D3DXVECTOR2(aTexelRight, aTexelBottom);

	// Initialize the vertex buffer pointer to null first.
	verticesPtr = 0;

	// Lock the vertex buffer.
	hr = aVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**)&verticesPtr);

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)vertices, (sizeof(A2DVertexData)* aVertexCount));

	// Unlock the vertex buffer.
	aVertexBuffer->Unmap();

	delete[] vertices;
}

void A2DGraphicsToolkit::RenderQuadBuffers()
{

	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(A2DVertexData);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	aDXDevice->IASetVertexBuffers(0, 1, &aVertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	aDXDevice->IASetIndexBuffer(aIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	aDXDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void A2DGraphicsToolkit::Deinitialize()
{
	// Release the texture object.
	if (aTextureResource)
	{
		aTextureResource->Release();
		aTextureResource = 0;
	}
}

LPCWSTR A2DGraphicsToolkit::GetClass()
{
	return L"A2DGraphicsToolkit";
}

LPCWSTR A2DGraphicsToolkit::ToString()
{
	return L"A2DGraphicsToolkit";
}

bool A2DGraphicsToolkit::operator==(A2DAbstract * xAbstract)
{
	return false;
}

void A2DGraphicsToolkit::OutputShaderErrorMessage(ID3D10Blob * xErrorMessage, WCHAR * xFilename)
{
/*	char* compileErrors;
	unsigned long bufferSize, i;
	// ofstream fout;

	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(xErrorMessage->GetBufferPointer());

	// Get the length of the message.
	bufferSize = xErrorMessage->GetBufferSize();

	// Open a file to write the error message to.
	// fout.open("shader-error.txt");

	// Write out the error message.
	for (i = 0; i < bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	// Close the file.
	// fout.close();

	// Release the error message.
	xErrorMessage->Release();
	xErrorMessage = 0;

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox(*aHWnd, L"Error compiling shader.  Check shader-error.txt for message.", xFilename, MB_OK);

	return;*/
}