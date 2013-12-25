#include "../../include/A2DGLCamera.h"


A2DGLCamera::A2DGLCamera() : aCameraProps(NULL){}

A2DGLCamera::A2DGLCamera(A2DGLCameraProperties * xCameraProps) : aCameraProps(xCameraProps){}

A2DGLCamera::~A2DGLCamera(){}

float* A2DGLCamera::GetViewMatrix()
{
	return aViewMatrix;
}

A2DCameraProperties* A2DGLCamera::GetProperties()
{
	return aCameraProps;
}

void A2DGLCamera::CreateResources()
{
	VectorType up, position, lookAt;
	float yaw, pitch, roll;
	float rotationMatrix[9];


	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = aCameraProps->aPositionX;
	position.y = aCameraProps->aPositionY;
	position.z = aCameraProps->aPositionZ;

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = aCameraProps->aRotationX * 0.0174532925f;
	yaw   = aCameraProps->aRotationY * 0.0174532925f;
	roll  = aCameraProps->aRotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	MatrixRotationYawPitchRoll(rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	TransformCoord(lookAt, rotationMatrix);
	TransformCoord(up, rotationMatrix);
	
	// Translate the rotated camera position to the location of the viewer.
	lookAt.x = position.x + lookAt.x;
	lookAt.y = position.y + lookAt.y;
	lookAt.z = position.z + lookAt.z;

	// Finally create the view matrix from the three updated vectors.
	BuildViewMatrix(position, lookAt, up);							//sets aViewMatrix inside the method below

	return;
}

void A2DGLCamera::MatrixRotationYawPitchRoll(float* matrix, float yaw, float pitch, float roll)
{
	float cYaw, cPitch, cRoll, sYaw, sPitch, sRoll;


	// Get the cosine and sin of the yaw, pitch, and roll.
	cYaw = cosf(yaw);
	cPitch = cosf(pitch);
	cRoll = cosf(roll);

	sYaw = sinf(yaw);
	sPitch = sinf(pitch);
	sRoll = sinf(roll);

	// Calculate the yaw, pitch, roll rotation matrix.
	matrix[0] = (cRoll * cYaw) + (sRoll * sPitch * sYaw);
	matrix[1] = (sRoll * cPitch);
	matrix[2] = (cRoll * -sYaw) + (sRoll * sPitch * cYaw);
	
	matrix[3] = (-sRoll * cYaw) + (cRoll * sPitch * sYaw);
	matrix[4] = (cRoll * cPitch);
	matrix[5] = (sRoll * sYaw) + (cRoll * sPitch * cYaw);
	
	matrix[6] = (cPitch * sYaw);
	matrix[7] = -sPitch;
	matrix[8] = (cPitch * cYaw);

	return;
}

void A2DGLCamera::TransformCoord(VectorType& vector, float* matrix)
{
	float x, y, z;


	// Transform the vector by the 3x3 matrix.
	x = (vector.x * matrix[0]) + (vector.y * matrix[3]) + (vector.z * matrix[6]);
	y = (vector.x * matrix[1]) + (vector.y * matrix[4]) + (vector.z * matrix[7]);
	z = (vector.x * matrix[2]) + (vector.y * matrix[5]) + (vector.z * matrix[8]);

	// Store the result in the reference.
	vector.x = x;
	vector.y = y;
	vector.z = z;

	return;
}


void A2DGLCamera::BuildViewMatrix(VectorType position, VectorType lookAt, VectorType up)
{
	VectorType zAxis, xAxis, yAxis;
	float length, result1, result2, result3;


	// zAxis = normal(lookAt - position)
	zAxis.x = lookAt.x - position.x;
	zAxis.y = lookAt.y - position.y;
	zAxis.z = lookAt.z - position.z;
	length = sqrt((zAxis.x * zAxis.x) + (zAxis.y * zAxis.y) + (zAxis.z * zAxis.z));
	zAxis.x = zAxis.x / length;
	zAxis.y = zAxis.y / length;
	zAxis.z = zAxis.z / length;

	// xAxis = normal(cross(up, zAxis))
	xAxis.x = (up.y * zAxis.z) - (up.z * zAxis.y);
	xAxis.y = (up.z * zAxis.x) - (up.x * zAxis.z);
	xAxis.z = (up.x * zAxis.y) - (up.y * zAxis.x);
	length = sqrt((xAxis.x * xAxis.x) + (xAxis.y * xAxis.y) + (xAxis.z * xAxis.z));
	xAxis.x = xAxis.x / length;
	xAxis.y = xAxis.y / length;
	xAxis.z = xAxis.z / length;

	// yAxis = cross(zAxis, xAxis)
	yAxis.x = (zAxis.y * xAxis.z) - (zAxis.z * xAxis.y);
	yAxis.y = (zAxis.z * xAxis.x) - (zAxis.x * xAxis.z);
	yAxis.z = (zAxis.x * xAxis.y) - (zAxis.y * xAxis.x);

	// -dot(xAxis, position)
	result1 = ((xAxis.x * position.x) + (xAxis.y * position.y) + (xAxis.z * position.z)) * -1.0f;

	// -dot(yaxis, eye)
	result2 = ((yAxis.x * position.x) + (yAxis.y * position.y) + (yAxis.z * position.z)) * -1.0f;

	// -dot(zaxis, eye)
	result3 = ((zAxis.x * position.x) + (zAxis.y * position.y) + (zAxis.z * position.z)) * -1.0f;

	// Set the computed values in the view matrix.
	aViewMatrix[0]  = xAxis.x;
	aViewMatrix[1]  = yAxis.x;
	aViewMatrix[2]  = zAxis.x;
	aViewMatrix[3]  = 0.0f;

	aViewMatrix[4]  = xAxis.y;
	aViewMatrix[5]  = yAxis.y;
	aViewMatrix[6]  = zAxis.y;
	aViewMatrix[7]  = 0.0f;

	aViewMatrix[8]  = xAxis.z;
	aViewMatrix[9]  = yAxis.z;
	aViewMatrix[10] = zAxis.z;
	aViewMatrix[11] = 0.0f;

	aViewMatrix[12] = result1;
	aViewMatrix[13] = result2;
	aViewMatrix[14] = result3;
	aViewMatrix[15] = 1.0f;

	return;
}

void A2DGLCamera::SetViewMatrix(float* matrix)
{
	aViewMatrix[0]  = matrix[0];
	aViewMatrix[1]  = matrix[1];
	aViewMatrix[2]  = matrix[2];
	aViewMatrix[3]  = matrix[3];
	aViewMatrix[4]  = matrix[4];
	aViewMatrix[5]  = matrix[5];
	aViewMatrix[6]  = matrix[6];
	aViewMatrix[7]  = matrix[7];
	aViewMatrix[8]  = matrix[8];
	aViewMatrix[9]  = matrix[9];
	aViewMatrix[10]  = matrix[10];
	aViewMatrix[11]  = matrix[11];
	aViewMatrix[12]  = matrix[12];
	aViewMatrix[13]  = matrix[13];
	aViewMatrix[14]  = matrix[14];
	aViewMatrix[15]  = matrix[15];

	return;
}

void A2DGLCamera::SetPosition(float x, float y, float z)
{
	aCameraProps->aPositionX = x;
	aCameraProps->aPositionY = y;
	aCameraProps->aPositionZ = z;
	return;
}


void CameraClass::SetRotation(float x, float y, float z)
{
	aCameraProps->aRotationX = x;
	aCameraProps->aRotationY = y;
	aCameraProps->aRotationZ = z;
	return;
}

HRESULT A2DGLCamera::Initialize() //	WE DON'T WANT TO USE HRESULT THOUGH...
{
	aCameraProps = aCameraProps == NULL ? new A2DCameraProperties() : aCameraProps;
    
    for(x=0;x<aViewMatrix.size();x++)
    {
    	aViewMatrix[x]=0;
    }

    return S_OK; //NOT COOL
}
    
void A2DGLCamera::Deinitialize()
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
                aViewMatrix = NULL;
        }
}
    
LPCWSTR A2DGLCamera::GetClass()
{
	return L"A2DGLCamera";
}

LPCWSTR A2DGLCamera::ToString()
{
	return L"A2DGLCamera";
}
   
bool A2DGLCamera::operator==(A2DAbstract * xAbstract)
{
	if(this ==xAbstract)
	{
		return true;
	}

	return false;
}