
#include "../../include/ExtLibs.h"
#include "../../include/MatrixFactory.h"

D3DXMATRIX * MatrixFactory::createDefaultWorldMatrix()
{
	// Create
	D3DXMATRIX * worldMatrix;

	// Set
	worldMatrix = new D3DXMATRIX;

	// Initialize
	D3DXMatrixIdentity(worldMatrix);

	// Return Pointer
	return worldMatrix;
}

D3DXMATRIX * MatrixFactory::createDefaultProjectionMatrix(Dims * xWindowSize, GXSettings * xSettings)
{
	// Create
	D3DXMATRIX * projectionMatrix;
	FLOAT fieldOfView, screenAspect;

	// Set
	fieldOfView = ((float) D3DX_PI / 4.0f);
	screenAspect = xWindowSize->aWidth / xWindowSize->aHeight;
	projectionMatrix = new D3DXMATRIX;

	// Initialize
	D3DXMatrixPerspectiveFovLH(projectionMatrix, fieldOfView, screenAspect, xSettings->aScreenNear, xSettings->aScreenDepth);

	// Return Pointer
	return projectionMatrix;
}

D3DXMATRIX * MatrixFactory::createDefaultOrthogonalMatrix(Dims * xWindowSize, GXSettings * xSettings)
{
	// Create
	D3DXMATRIX * orthogonalMatrix;

	// Set
	orthogonalMatrix = new D3DXMATRIX;

	// Initialize
	D3DXMatrixOrthoLH(orthogonalMatrix, xWindowSize->aWidth, xWindowSize->aHeight, xSettings->aScreenNear, xSettings->aScreenDepth);

	// Return Pointer
	return orthogonalMatrix;
}


