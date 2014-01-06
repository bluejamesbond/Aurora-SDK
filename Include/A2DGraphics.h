////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DGRAPHICS_H__
#define __A2DGRAPHICS_H__

//+-----------------------------------------------------------------------------
//
//  Struct:
//      A2DGRAPHICS
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DCommon.h"
#include "A2DVertexData.h"
#include "A2DBackBuffer.h"
#include "A2DTextureShader.h"
#include "A2DTextureBuffer.h"
#include "A2DTexture.h"
#include "A2DQuad.h"
#include "A2DImageProperties.h"
#include "A2DAbstractComponent.h"
#include "A2DPipeline.h"

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
class A2DBackBuffer;
class A2DMatrixFactory;
class A2DRootPane;
class A2DWindow;
struct A2DVertexData;
class A2DTexture;
class A2DTextureBuffer;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////                               

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DGraphics : public A2DRenderData
{

public:

	A2DGraphics(A2DAbstractComponent * xComponent, A2DRenderData * xRenderData);

	// Deconstructor
	~A2DGraphics();

private:

	A2DImageProperties				aSecondaryBufferProps;					// background-size/background-repeat
	A2DRect							aClip;

	bool							aDoubleBuffer = false;
	A2DAbstractComponent	  *		aComponent;
	A2DPipelineable      *		aPipelineComponents[10];

public:

	// Additional
	void 							Recalculate();
	void							NextRender();
	void							RenderSecondaryBuffer();
	void							RenderBlurBuffer();
	void							SetActiveBuffer(int xBuffer);
	void							DrawImage(A2DPipeline ** xPipeline, LPCWSTR * xSrc, A2DRect * aRect, A2DImageProperties * xImageProps);
	void							DrawImage(A2DPipeline * xPipeline, A2DTexture * xTexture, float xImageLeft, float xImageTop, float xImageWidth, float xImageHeight, A2DImageProperties * xImageProps, int xBlur);

private:
	void							CalculateBounds();

public:

////////////////////////////////////////////////////////////////////////////////
// A2DABSTRACT
////////////////////////////////////////////////////////////////////////////////

	virtual HRESULT                 Initialize();
	virtual void                    Deinitialize();
	virtual LPCWSTR                 GetClass();
	virtual LPCWSTR                 ToString();
	virtual bool                    operator==(A2DAbstract * xAbstract);

};


#endif
