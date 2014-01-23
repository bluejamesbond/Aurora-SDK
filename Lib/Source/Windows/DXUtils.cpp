
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/DXUtils.h"

using namespace A2D;

STATUS DXUtils::LoadEffectFromFile(LPCWSTR xFilename, ID3D10Device * aDevice, ID3D10Effect ** xEffect)
{
	ID3D10Blob* errorMessage;

	// initialize the error message.
	errorMessage = 0;

	// Load the shader in from the file.
	SAFELY(D3DX10CreateEffectFromFile(xFilename, NULL, NULL, "fx_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		aDevice, NULL, NULL, xEffect, &errorMessage, NULL));

	return STATUS_OK;
}

void DXUtils::SysOut(ID3D10Blob * xErrorMessage, LPCWSTR * xFilename){}

STATUS DXUtils::CreatePNGCompatibleBlendStates(ID3D10Device * aDevice, ID3D10BlendState ** xBlendState, ID3D10BlendState ** xBlendDisabledState)
{
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

	SAFELY(aDevice->CreateBlendState(&blendDesc, xBlendState));

	blendDesc.BlendEnable[0] = FALSE;

	SAFELY(aDevice->CreateBlendState(&blendDesc, xBlendDisabledState));

	return STATUS_OK;
}

STATUS DXUtils::loadTechniqueFromEffect(ID3D10Device * xDevice, ID3D10Effect * xEffect, ID3D10InputLayout ** xLayout, ID3D10EffectTechnique ** xTechnqiue, D3D10_INPUT_ELEMENT_DESC * xPolygonLayout, LPCSTR xName, unsigned int xElements)
{
	D3D10_PASS_DESC passDesc;

	// Get a pointer to the technique inside the shader.
	NULLCHECK((*xTechnqiue = xEffect->GetTechniqueByName(xName)));
	
	// Get the description of the first pass 
	// described in the shader technique.
	(*xTechnqiue)->GetPassByIndex(0)->GetDesc(&passDesc);

	// Create the input layout.
	SAFELY(xDevice->CreateInputLayout(xPolygonLayout, xElements, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, xLayout));

	return STATUS_OK;
}


STATUS DXUtils::createDefaultWorldMatrix(D3DXMATRIX ** xWorldMatrix)
{
	// Set
	*xWorldMatrix = new D3DXMATRIX;

	// initialize
	D3DXMatrixIdentity(*xWorldMatrix);

	return STATUS_OK;
}

STATUS SYSFASTCALL DXUtils::updateBorderMatrix(D3DXMATRIX * x_borderMatrix, const Dims * x_windowSize)
{
	// Set
	*x_borderMatrix = D3DXMATRIX(2.0f / x_windowSize->aWidth, 0.0f, 0.0f, 0.0f,
							0.0f, 2.0f / x_windowSize->aHeight, 0.0f, 0.0f,
							0.0f, 0.0f, 2.0f / x_windowSize->aWidth, 0.0f,
							0.0f, 0.0f, 0.0f, 2.0f / x_windowSize->aHeight);	

	return STATUS_OK;
}

STATUS DXUtils::createDefaultProjectionMatrix(D3DXMATRIX ** xProjectionMatrix, Dims * xWindowSize, GXSettings * xSettings)
{
	// Create
	FLOAT fieldOfView, screenAspect;

	// Set
	fieldOfView = ((float)D3DX_PI / 4.0f);
	screenAspect = xWindowSize->aWidth / xWindowSize->aHeight;

	*xProjectionMatrix = new D3DXMATRIX;

	// initialize
	D3DXMatrixPerspectiveFovLH(*xProjectionMatrix, fieldOfView, screenAspect, xSettings->aScreenNear, xSettings->aScreenDepth);

	return STATUS_OK;
}

STATUS DXUtils::createDefaultOrthogonalMatrix(D3DXMATRIX ** xProjectionMatrix, Dims * xWindowSize, GXSettings * xSettings)
{
	// Set
	*xProjectionMatrix = new D3DXMATRIX;

	// initialize
	D3DXMatrixOrthoLH(*xProjectionMatrix, xWindowSize->aWidth, xWindowSize->aHeight, xSettings->aScreenNear, xSettings->aScreenDepth);

	return STATUS_OK;
}

STATUS DXUtils::createViewMatrix(D3DXMATRIX ** xViewMatrix, CameraProperties& xCameraProperties)
{
	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;

	// Set
	*xViewMatrix = new D3DXMATRIX;

	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = xCameraProperties.aPositionX;
	position.y = xCameraProperties.aPositionY;
	position.z = xCameraProperties.aPositionZ;

	// Setup where the camera is looking by default.
	lookAt.x = 0;
	lookAt.y = 0;
	lookAt.z = 1;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = xCameraProperties.aRotationX * 0.0174532925f;
	yaw = xCameraProperties.aRotationY * 0.0174532925f;
	roll = xCameraProperties.aRotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(*xViewMatrix, &position, &lookAt, &up);

	return STATUS_OK;
}

STATUS DXUtils::CreateDefaultIndexBuffer(ID3D10Device * xDevice, ID3D10Buffer ** xIndexBuffer, int xIndices)
{
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

	SAFELY(xDevice->CreateBuffer(&indexBufferDesc, &indexData, xIndexBuffer));

	delete[] indices;
	indices = 0;

	return STATUS_OK;

}
