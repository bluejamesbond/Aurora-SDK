////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __VERTEXDATA_H__
#define __VERTEXDATA_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      VERTEXDATA
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

class   ;
class   Abstract;
class   Renderable;
class   AbstractComponent;
class   Camera;
struct  CameraProperties;
struct  RenderData;
class   MatrixFactory;
class   BackBuffer;
class   MatrixFactory;
class   ModelFactory;
class   RootPane;
struct  WindowProperties;
class   Window;
class	ImagePanel;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

#define VERTEXDATA_LL(str1, str2)                 str1 str2

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

struct VertexData
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
//    // { ABSTRACT }
//    virtual HRESULT                 Initialize();
//    virtual void                    Deinitialize();
//    virtual LPCWSTR                 GetClass();
//    virtual LPCWSTR                 ToString();
//    virtual bool                    operator==(Abstract * xAbstract);

};

#endif