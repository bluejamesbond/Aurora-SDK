////////////////////////////////////////////////////////////////////////////////
// GUARDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DQUADFACTORY_H__
#define __A2DQUADFACTORY_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      A2DQUADFACTORY
//
//  Synopsis:
//      Quad class to be rendered.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DExtLibs.h"
#include "A2DDXShapeUtils.h"
#include "A2DTexture.h"
#include "A2DRect.h"
#include "A2DQuadData.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DAbstract;
class A2DDXShapeUtils;
class A2DTexture;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DQuadFactory
{
public:

	A2DQuadFactory(ID3D10Device ** xDXDevice, A2DDims * xWindowDims);
	~A2DQuadFactory();

	ID3D10Buffer	*	aIndexBuffer;
	ID3D10Buffer	*	aVertexBuffer;

	static unsigned int aStride;
	static unsigned int aOffset;

	///////////////////////////////////////////////////////////

	A2DRect				aConstraints;
	A2DDims			*	aWindowDims;
	ID3D10Device	**	aDXDevice;
	
	///////////////////////////////////////////////////////////

	bool						aContraintsChanged;

	// A2DRect				*			aRect;
	A2DVertexData		*			aVertices; // DONT FORGET TO RELEASE THIS AFTER
	
	void							x_aligned_memcpy_sse2(void* dest, const void* src, const unsigned long size_t);
	
	float							aPrevPosX;
	float							aPrevPosY;

	HRESULT							updateVertexBuffer(A2DQuadData * aQuadData, A2DRect * xRect, A2DRect * xTextureClip, A2DDims * xTextureDims, A2DImageProperties * xImageProperties);
	void							RenderQuad(A2DQuadData * aQuadData);
	bool							setConstraints(A2DQuadData * aQuadData, A2DRect * xContraints);
	
public:

	//////////////////////////////////////////////////////////
	// A2DABSTRACT IMPLEMENTATION
	//////////////////////////////////////////////////////////

	virtual HRESULT                 Initialize();
	virtual void                    Deinitialize();
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(A2DAbstract * xAbstract); // Don't campare against quad but against any Object
};



#endif