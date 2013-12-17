////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DABSTRACTTEXTURE_H__
#define __A2DABSTRACTTEXTURE_H__

//+-----------------------------------------------------------------------------
//
//  Class:  
//      A2DABSTRACTTEXTURE
//
//  Synopsis:
//      Texture container class.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DAbstractPipelineComponent.h"
#include "A2DRect.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DAbstract;
class A2DAbstractTexture;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DAbstractTexture : public A2DAbstractPipelineComponent
{
public:
	// Constructor
	A2DAbstractTexture(A2DBackBuffer * xBackBuffer);

	// Deconstructor
	~A2DAbstractTexture();

protected:
	// Variables
	A2DDims							aDims;
	A2DRect							aClip;
	ID3D10ShaderResourceView	*	aResource;

public:
	// Accessors
	virtual A2DDims			*		GetSize();
	virtual A2DRect			*		GetClip(int xIndex = 0);

	// Mutators
	virtual void					SetClip(A2DRect * xClip, int xIndex = 0);

	// Builders
	// { NONE }

	// Factory
	// { NONE }

	// Additional
	// { NONE }

	// Pure Virtual
	// { NONE }

	// Virtual
	ID3D10ShaderResourceView	*	GetResource();
	virtual	bool					hasAlpha();

public:

	// Implementation
	// { A2DABSTRACTPIPELINECOMPONENT }
	virtual HRESULT					CreateResources(void * xArgs[]) = 0;
	virtual void					Update(void * xArgs[]) = 0;
	virtual void					Render() = 0; // Render should be defined seperately but called inside Update
	virtual void					DestroyResources();

public:
	// Implementation
	// { A2DABSTRACT }
	virtual HRESULT                 Initialize();
	virtual void                    Deinitialize();
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(A2DAbstract * xAbstract);

};



#endif
