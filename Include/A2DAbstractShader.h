////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DABSTRACTSHADER_H__
#define __A2DABSTRACTSHADER_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      A2DABSTRACTSHADER
//
//  Synopsis:
//      Texture quad.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DExtLibs.h"
#include "A2DPipelineComponent.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DAbstract;
class A2DPipelineComponent;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DAbstractShader : public A2DPipelineComponent
{
public:
	A2DAbstractShader(A2DBackBuffer * xBackBuffer);
	~A2DAbstractShader();

	HWND						*	aHWnd;
	ID3D10Effect				*	aEffect;
	ID3D10Device				*	aDXDevice;
	ID3D10EffectTechnique		*	aTechnique;
	ID3D10InputLayout			*	aLayout;
	static ID3D10BlendState		*	aBlendState;
	static ID3D10BlendState		*	aBlendDisabledState;

	virtual HRESULT					CreateResources(void * xArgs[]);
	virtual void					Render(); // Render should be defined seperately but called inside Update

	HRESULT							LoadFromFile(LPCWSTR * xFilename);
	HRESULT							CreateBlendStates();
	void							SysOut(ID3D10Blob * xErrorMessage, LPCWSTR * xFilename);

public:

	//////////////////////////////////////////////////////////
	// A2DABSTRACT IMPLEMENTATION
	//////////////////////////////////////////////////////////

	virtual HRESULT                 Initialize();
	virtual void                    Deinitialize();
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(A2DAbstract * xAbstract);
};



#endif