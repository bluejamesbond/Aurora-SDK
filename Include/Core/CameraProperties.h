////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __CAMERAPROPERTIES_H__
#define __CAMERAPROPERTIES_H__

//+-----------------------------------------------------------------------------
//
//  Struct:
//      CAMERAPROPERTIES
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	struct CameraProperties
	{

	public:

		// Constructor
		CameraProperties() :                                   // default values for camera properties
			aPositionX(0.0f),
			aPositionY(0.0f),
			aPositionZ(0.0f),
			aRotationX(0.0f),
			aRotationY(0.0f),
			aRotationZ(0.0f),
			aLookAtX(0.0f),
			aLookAtY(0.0f),
			aLookAtZ(1.0f){}

		CameraProperties(float xPositionX, float xPositionY, float xPositionZ, float xRotationX, float xRotationY, float xRotationZ) :
			aPositionX(xPositionX),
			aPositionY(xPositionY),
			aPositionZ(xPositionZ),
			aRotationX(xRotationX),
			aRotationY(xRotationY),
			aRotationZ(xRotationZ),
			aLookAtX(0.0f),
			aLookAtY(0.0f),
			aLookAtZ(1.0f){}

		// Variables
		float                           aPositionX,
			aPositionY,
			aPositionZ,
			aRotationX,
			aRotationY,
			aRotationZ,
			aLookAtX,
			aLookAtY,
			aLookAtZ;

		float                           aLookAtXDef = 0.0f;
		float                           aLookAtYDef = 0.0f;
		float                           aLookAtZDef = 1.0f;
	};
}
#endif
