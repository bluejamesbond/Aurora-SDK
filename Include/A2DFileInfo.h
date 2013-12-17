////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DFILEINFO_H__
#define __A2DFILEINFO_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      A2DFILEINFO
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DExtLibs.h"
#include "A2DCommon.h"
#include "A2DAbstract.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class	A2DAbstract;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DFileInfo : public A2DAbstract
{

public:

	// Constructor
	A2DFileInfo(LPCWSTR * xFileName);

	// Deconstructor
	~A2DFileInfo();

private:

	// Variables
	D3DXIMAGE_INFO		  * 	aFileInfo;
	LPCWSTR               *     aFileName;


public:
	// Accessors
	float							GetHeight();
	float							GetWidth();
	int							GetDepth();
	int							GetMipLevels();
	D3DXIMAGE_INFO		*		GetInfo();

	// Mutators
	// { NONE }

	// Builders
	// { NONE }

	// Factory
	// { NONE }

	// Additional
	// { NONE }

	// Additional
	// { NONE }

	// Pure Virtual
	// { NONE }

	// Virtual
	// { NONE }

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
