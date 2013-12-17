////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DABSTRACT_H__
#define __A2DABSTRACT_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      A2DABSTRACT
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class	A2D;
class	A2DAbstract;
class	A2DRenderable;
class	A2DAbstractComponent;
class	A2DCamera;
struct	A2DCameraProperties;
struct	A2DRenderData;
class	A2DMatrixFactory;
class	A2DBackBuffer;
class	A2DMatrixFactory;
class	A2DModelFactory;
class	A2DRootPane;
struct	A2DWindowProperties;
class	A2DWindow;
class	A2DImagePanel;


////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#define A2DABSTRACT_LL(str1, str2)                            str1 str2

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DAbstract
{
public:
    
    // Constructor
    A2DAbstract();
    
    // Deconstructor
	~A2DAbstract();

	// Variables
	// { NONE }

	// Accessors
	// { NONE }

	// Mutators
	// { NONE }

	// Builders
	// { NONE }

	// Factory
	// { NONE }

	// Additional
	// { NONE }

protected:

    // Pure Virtual
    virtual HRESULT                 Initialize() = 0;                           // Initialize  
    virtual void                    Deinitialize() = 0;                         // Shutdown   

    // Virtual    
    virtual LPCWSTR                 GetClass();                                 // Class type    
    virtual bool                    operator==(A2DAbstract * xAbstract);        // Class type       
    virtual LPCWSTR                 ToString();                                 // Class type 

public:
	virtual bool					isClass(LPCWSTR xClass) final; // To prevent it from being overridden, I put a final here.

    // Implementations
    // { NONE}
};

#endif
