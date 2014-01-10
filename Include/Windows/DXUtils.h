////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __DXSHADERUTILS_H__
#define __DXSHADERUTILS_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      DXSHADERUTILS
//
//  Synopsis:
//      Texture quad.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"

#include "../Core/../_A2DCommon.h"
#include "../Core/Rect.h"
#include "../Core/GXSettings.h"
#include "../Core/CameraProperties.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class Pipelineable;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class DXUtils
	{

	public:

		// Load a shader from file
		static HRESULT					LoadEffectFromFile(LPCWSTR xFilename, ID3D10Device * xDevice, ID3D10Effect ** xEffect);

		// Create Alpha transpareny supportable PNG
		static HRESULT					CreatePNGCompatibleBlendStates(ID3D10Device * xDevice, ID3D10BlendState ** xBlendState, ID3D10BlendState ** xBlendDisabledState);

		// Output Error - Use SYSOUT in the future
		static void						SysOut(ID3D10Blob * xErrorMessage, LPCWSTR * xFilename);

		// Load technieque from shader
		static HRESULT					loadTechniqueFromEffect(ID3D10Device * xDevice, ID3D10Effect * xEffect, ID3D10InputLayout ** xLayout, ID3D10EffectTechnique ** xTechnqiue, D3D10_INPUT_ELEMENT_DESC * xPolygonLayout, LPCSTR xName, unsigned int xElements);
		
		// Create default World Matrix
		static HRESULT				    createDefaultWorldMatrix(D3DXMATRIX ** xWorldMatrix);

		// Create Projection matrix
		static HRESULT					createDefaultProjectionMatrix(D3DXMATRIX ** xProjectionMatrix, Dims* xWindowSize, GXSettings*  xSettings);

		// Create orthogonal matrix
		static HRESULT				    createDefaultOrthogonalMatrix(D3DXMATRIX ** xProjectionMatrix, Dims* xWindowSize, GXSettings* xSettings);

		// Create view matrix
		static HRESULT					createViewMatrix(D3DXMATRIX ** xViewMatrix, CameraProperties& xCameraProperties);
		
		// Create matrix for specific class
		template<class VertexClass>	
		static HRESULT					CreateDefaultDynamicVertexBuffer(ID3D10Device * xDevice, ID3D10Buffer ** xVertexBuffer, int xVertices);

		// Create index buffer
		static HRESULT					CreateDefaultIndexBuffer(ID3D10Device * xDevice, ID3D10Buffer ** xIndexBuffer, int xIndices);
		
	};

	template<class VertexClass>
	HRESULT DXUtils::CreateDefaultDynamicVertexBuffer(ID3D10Device * xDevice, ID3D10Buffer ** xVertexBuffer, int xVertices)
	{
		D3D10_BUFFER_DESC vertexBufferDesc;
		D3D10_SUBRESOURCE_DATA vertexData;
		VertexClass * vertices = new VertexClass[xVertices];

		// initialize vertex array to zeros at first.
		memset(vertices, 0, (sizeof(VertexClass)* xVertices));

		vertexBufferDesc.Usage = D3D10_USAGE_DYNAMIC;
		vertexBufferDesc.ByteWidth = sizeof(VertexClass)* xVertices;
		vertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		vertexBufferDesc.MiscFlags = 0;

		// Give the subresource structure a pointer to the vertex data.
		vertexData.pSysMem = vertices;

		SAFELY(xDevice->CreateBuffer(&vertexBufferDesc, &vertexData, xVertexBuffer));

		delete[] vertices;
		vertices = 0;

		return S_OK;
	}
}


#endif