
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DMatrixFactory.h"

D3DXMATRIX * A2DMatrixFactory::createDefaultWorldMatrix()
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

D3DXMATRIX * A2DMatrixFactory::createDefaultProjectionMatrix(A2DWindowProperties * xWindowProps)
{
	// Create
	D3DXMATRIX * projectionMatrix;
	FLOAT fieldOfView, screenAspect;

	// Set
	fieldOfView = ((float) D3DX_PI / 4.0f);
	screenAspect = ((float) xWindowProps->aRealWidth) / ((float) xWindowProps->aRealHeight);
	projectionMatrix = new D3DXMATRIX;

	// Initialize
	D3DXMatrixPerspectiveFovLH(projectionMatrix, fieldOfView, screenAspect, xWindowProps->aScreenNear, xWindowProps->aScreenDepth);

	// Return Pointer
	return projectionMatrix;
}

D3DXMATRIX * A2DMatrixFactory::createDefaultOrthogonalMatrix(A2DWindowProperties * xWindowProps)
{
	// Create
	D3DXMATRIX * orthogonalMatrix;

	// Set
	orthogonalMatrix = new D3DXMATRIX;

	// Initialize
	D3DXMatrixOrthoLH(orthogonalMatrix, ((float)xWindowProps->aRealWidth), ((float)xWindowProps->aRealHeight), xWindowProps->aScreenNear, xWindowProps->aScreenDepth);

	// Return Pointer
	return orthogonalMatrix;
}


