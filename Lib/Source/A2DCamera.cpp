
#include "../../include/ExtLibs.h"
#include "../../include/Camera.h"

Camera::Camera() :
aCameraProps(NULL){}

Camera::Camera(CameraProperties * xCameraProps) :
aCameraProps(xCameraProps){}

Camera::~Camera(){}

CameraProperties * Camera::GetProperties()
{
	return aCameraProps;
}

D3DXMATRIX* Camera::GetViewMatrix()
{
	return aViewMatrix;
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY ABSTRACT_AURORA
/////////////////////////////////////////////////////////////////////////////

LPCWSTR Camera::GetClass()
{
	return L"Camera";
}

LPCWSTR Camera::ToString()
{
	return L"Camera";
}

bool Camera::operator==(Abstract * xAbstract)
{
	return false;
}

HRESULT Camera::Initialize()
{
	// -----------------------------------------------------

	aCameraProps = aCameraProps == NULL ? new CameraProperties() : aCameraProps;
	aViewMatrix = new D3DXMATRIX();

	// -----------------------------------------------------
	
	return S_OK;
}

void Camera::CreateResources()
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
	lookAt.x = 0;
	lookAt.y = 0;
	lookAt.z = 1;

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

void Camera::Deinitialize()
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
