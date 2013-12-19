////////////////////////////////////////////////////////////////////////////////
// GUARDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DABSTRACTBACKBUFFER_H__
#define __A2DABSTRACTBACKBUFFER_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DABSTRACTBACKBUFFER
//
//  Synopsis:
//      Abstract Class of Back Buffer to allow a Cross Platform implementation
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DWindowProperties.h"
#include "A2DAbstract.h"
#include "A2DCPWindowHandle.h"
#include "A2DCPString.h"
#include "A2DCPResultHandle.h"
#include "A2DCPInstanceHandle.h"
#include "A2DCPDevice.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DAbstract;
class A2DRenderable;
class A2DAbstractComponent;
class A2DCamera;
struct A2DCameraProperties;
struct A2DRenderData;
class A2DMatrixFactory;
class A2DModelFactory;
class A2DRootPane;
struct A2DWindowProperties;
class A2DWindow;
class A2DImagePanel;
class A2DAbstractBackBuffer;
class A2DCPDevice;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////
            

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DAbstractBackBuffer : public A2DAbstract
{

public:

    // Constructor
	A2DAbstractBackBuffer(A2DWindow * xWindow, A2DWindowProperties * xWindowProps);

    // Deconstructor
    ~A2DBackBuffer();

    // Variables

private:
	// Variables
	A2DWindowProperties       *     aWindowProps;
	A2DWindow				  *     aWindow;

public:
    // Accessors
    virtual A2DCPDevice               *     GetDevice() = 0;

public:
    // Mutators
    virtual void                            SetZBuffer(bool val) = 0;
    
    // Builders
    // { NONE }

    // Factory
    // { NONE }

public:
    // Additional
    virtual void                            SetActive() = 0;
    virtual void                            Swap() = 0;
    virtual void                            Clear() = 0;

    // Pure Virtual
    // { NONE }

    // Virtual
    // { NONE }

public:

    // Implementation
    // { A2DABSTRACT }
    virtual A2DCPResultHandle       Initialize();
    virtual void                    Deinitialize();
    virtual A2DCPString             GetClass();
    virtual A2DCPString             ToString();
    virtual bool                    operator==(A2DAbstract * xAbstract);

};

#endif
