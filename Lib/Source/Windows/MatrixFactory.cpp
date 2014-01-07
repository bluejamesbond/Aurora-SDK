
#include "../../../Include/Windows/ExtLibs.h"
#include "../../../Include/Windows/MatrixFactory.h"

using namespace A2D;

HRESULT MatrixFactory::createDefaultWorldMatrix(D3DXMATRIX ** xWorldMatrix)
{
	// Set
	*xWorldMatrix = new D3DXMATRIX;

	// initialize
	D3DXMatrixIdentity(*xWorldMatrix);

	return S_OK;
}

HRESULT MatrixFactory::createDefaultProjectionMatrix(D3DXMATRIX ** xProjectionMatrix, Dims * xWindowSize, GXSettings * xSettings)
{
	// Create
	FLOAT fieldOfView, screenAspect;

	// Set
	fieldOfView = ((float) D3DX_PI / 4.0f);
	screenAspect = xWindowSize->aWidth / xWindowSize->aHeight;

	*xProjectionMatrix = new D3DXMATRIX;

	// initialize
	D3DXMatrixPerspectiveFovLH(*xProjectionMatrix, fieldOfView, screenAspect, xSettings->aScreenNear, xSettings->aScreenDepth);

	return S_OK;
}

HRESULT MatrixFactory::createDefaultOrthogonalMatrix(D3DXMATRIX ** xProjectionMatrix,  Dims * xWindowSize, GXSettings * xSettings)
{
	// Set
	*xProjectionMatrix = new D3DXMATRIX;

	// initialize
	D3DXMatrixOrthoLH(*xProjectionMatrix, xWindowSize->aWidth, xWindowSize->aHeight, xSettings->aScreenNear, xSettings->aScreenDepth);

	return S_OK;
}

HRESULT MatrixFactory::createViewMatrix(D3DXMATRIX ** xViewMatrix, CameraProperties& xCameraProperties)
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

	return S_OK;
}

