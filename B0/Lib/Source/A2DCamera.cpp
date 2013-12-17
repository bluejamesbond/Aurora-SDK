
#include "../../Include/A2DExtLibs.h"
#include "../../Include/A2DCamera.h"

A2DCamera::A2DCamera() :
aCameraProps(NULL){}

A2DCamera::A2DCamera(A2DCameraProperties * xCameraProps) :
aCameraProps(xCameraProps){}

A2DCamera::~A2DCamera(){}

A2DCameraProperties * A2DCamera::GetProperties()
{
	return aCameraProps;
}

D3DXMATRIX* A2DCamera::GetViewMatrix()
{
	return aViewMatrix;
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY ABSTRACT_AURORA
/////////////////////////////////////////////////////////////////////////////

LPCWSTR A2DCamera::GetClass()
{
	return L"A2DCamera";
}

LPCWSTR A2DCamera::ToString()
{
	return L"A2DCamera";
}

bool A2DCamera::operator==(A2DAbstract * xAbstract)
{
	return false;
}

HRESULT A2DCamera::Initialize()
{
	// -----------------------------------------------------

	aCameraProps = aCameraProps == NULL ? new A2DCameraProperties() : aCameraProps;
	aViewMatrix = new D3DXMATRIX();

	// -----------------------------------------------------
	
	return S_OK;
}

void A2DCamera::CreateResources()
{

	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;

	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = aCameraProps->aPositionX;
	position.y = aCameraProps->aPositionY;
	position.z = aCameraProps->aPositionZ;

	// Setup where the camera is looking by default.
	lookAt.x = aCameraProps->aLookAtXDef;
	lookAt.y = aCameraProps->aLookAtYDef;
	lookAt.z = aCameraProps->aLookAtZDef;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = aCameraProps->aRotationX * 0.0174532925f;
	yaw = aCameraProps->aRotationY * 0.0174532925f;
	roll = aCameraProps->aRotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(aViewMatrix, &position, &lookAt, &up);
}

void A2DCamera::Deinitialize()
{
	// Release the CameraProperties object.
	if (aCameraProps)
	{
		// aCameraProps->Shutdown();
		delete aCameraProps;
		aCameraProps = 0;
	}

	// Release the ViewMatrix object.
	if (aViewMatrix)
	{
		// aViewMatrix->Shutdown();
		delete aViewMatrix;
		aViewMatrix = 0;
	}
}
