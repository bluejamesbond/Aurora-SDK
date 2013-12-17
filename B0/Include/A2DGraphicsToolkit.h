////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __A2DGRAPHICSTOOLKIT_H__
#define __A2DGRAPHICSTOOLKIT_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      A2DGRAPHICSTOOLKIT
//
//  Synopsis:
//      Texture quad.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "A2DExtLibs.h"
#include "A2DWindowProperties.h"
#include "A2DTextureBuffer.h"

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

class A2D;
class A2DAbstract;

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DECLARATION
////////////////////////////////////////////////////////////////////////////////

class A2DGraphicsToolkit : public A2DAbstract
{
public:
	A2DGraphicsToolkit(A2DGraphics	* xGraphics);
	~A2DGraphicsToolkit();

	A2DImageProperties * aImageProps;
	A2DTexture * aTexture;
	A2DGraphics		*	 aGraphics;
	
	// Cache variables
	HWND		*	 aHWnd;
	int								aVertexCount;
	int								aIndexCount;
	
	ID3D10Buffer			*		aVertexBuffer;
	ID3D10Buffer			*		aIndexBuffer;
	ID3D10Device			*		aDXDevice;
	ID3D10ShaderResourceView	*	aTextureResource;

	ID3D10Effect				*	aEffect;
	ID3D10EffectTechnique		*	aTechnique;
	ID3D10InputLayout			*	aLayout;

	ID3D10EffectMatrixVariable	*	aWorldMatrixPtr;
	ID3D10EffectMatrixVariable	*	aViewMatrixPtr;
	ID3D10EffectMatrixVariable	*	aProjectionMatrixPtr;
	ID3D10EffectShaderResourceVariable	*	aTexturePtr;
	ID3D10EffectScalarVariable	*	aScreenHeightPtr;
	ID3D10EffectScalarVariable	*	aScreenWidthPtr;

	ID3D10BlendState* g_pBlendState = NULL;
	ID3D10BlendState* g_pBlendDisableState = NULL;

	//////////////////////////////////////////////////////////

	float aTextureWidth;
	float aTextureHeight;

	bool aRepeat;

	float aOrigWidth;
	float aOrigHeight;

	float aCalcLeft;
	float aCalcTop;
	float aCalcRight;
	float aCalcBottom;

	float aCalcHeight;
	float aCalcWidth;

	float aLeft;
	float aRight;
	float aTop;
	float aBottom;

	float aTexLeft;
	float aTexTop;
	float aTexRight;
	float aTexBottom;

	float aTexelLeft;
	float aTexelTop;
	float aTexelRight;
	float aTexelBottom;

	//////////////////////////////////////////////////////////

	HRESULT CreateQuadBuffers();
	HRESULT CreateShaderFromFile(WCHAR * xFilename, int xShader);
	HRESULT CreateTexture(LPCWSTR * xSrc);
	HRESULT CreateTexture(A2DTexture * xTexture);
	HRESULT CreateShader(int xShader);
	void	OutputShaderErrorMessage(ID3D10Blob * xErrorMessage, WCHAR* xShaderFilename);
	void	RenderQuadBuffers();
	void	UpdateQuadBuffers(float xImageLeft, float xImageTop, float xImageWidth, float xImageHeight, A2DImageProperties * xImageProps);
	void	RenderTextureShader();

	void SetShaderParameters(D3DXMATRIX xWorldMatrix, D3DXMATRIX xViewMatrix, D3DXMATRIX xProjectionMatrix,
		ID3D10ShaderResourceView* xTexture);

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