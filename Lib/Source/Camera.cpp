
#include "../../include/ExtLibs.h"
#include "../../include/Camera.h"

using namespace A2D;

Camera::Camera()
{
	xCameraProperties = NULL;
}

Camera::Camera(CameraProperties * xCameraProps)
{
	xCameraProperties = xCameraProps;
}

Camera::~Camera()
{
	DESTROY(xCameraProperties);
	DESTROY(aViewMatrix);
}

CameraProperties& Camera::getProperties()
{
	return xCameraProperties;
}

D3DXMATRIX* Camera::GetViewMatrix()
{
	return aViewMatrix;
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY ABSTRACT_AURORA
/////////////////////////////////////////////////////////////////////////////

LPCWSTR Camera::getClass()
{
	return L"Camera";
}

LPCWSTR Camera::toString()
{
	return L"Camera";
}

HRESULT Camera::initialize()
{
	// -----------------------------------------------------

	xCameraProperties = xCameraProperties == NULL ? new CameraProperties() : xCameraProperties;
	aViewMatrix = new D3DXMATRIX();

	// -----------------------------------------------------
	
	return S_OK;
}