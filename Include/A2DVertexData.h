////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DVERTEXDATA_H__
#define __A2DVERTEXDATA_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DVERTEXDATA
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

class   A2D;
class   A2DAbstract;
class   A2DRenderable;
class   A2DAbstractComponent;
class   A2DCamera;
struct  A2DCameraProperties;
struct  A2DRenderData;
class   A2DMatrixFactory;
class   A2DBackBuffer;
class   A2DMatrixFactory;
class   A2DModelFactory;
class   A2DRootPane;
struct  A2DWindowProperties;
class   A2DWindow;
class	A2DImagePanel;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#define A2DVERTEXDATA_LL(str1, str2)                 str1 str2

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

struct A2DVertexData
{
    // Constructor
    // { NONE }
    
    // Deconstructor
    // { NONE }

    // Variables
	D3DXVECTOR3 position;
	D3DXVECTOR2 texture;

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

    // Pure Virtual
    // { NONE }

    // Virtual
    // { NONE }

//public:
//
//    // Implementation
//    // { A2DABSTRACT }
//    virtual HRESULT                 Initialize();
//    virtual void                    Deinitialize();
//    virtual LPCWSTR                 GetClass();
//    virtual LPCWSTR                 ToString();
//    virtual bool                    operator==(A2DAbstract * xAbstract);

};

#endif