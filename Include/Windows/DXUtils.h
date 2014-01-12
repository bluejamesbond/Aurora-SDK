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

#include "../_A2DCommon.h"

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
		static STATUS					LoadEffectFromFile(LPCWSTR xFilename, ID3D10Device * xDevice, ID3D10Effect ** xEffect);

		// Create Alpha transpareny supportable PNG
		static STATUS					CreatePNGCompatibleBlendStates(ID3D10Device * xDevice, ID3D10BlendState ** xBlendState, ID3D10BlendState ** xBlendDisabledState);

		// Output Error - Use SYSOUT in the future
		static void						SysOut(ID3D10Blob * xErrorMessage, LPCWSTR * xFilename);

		// Load technieque from shader
		static STATUS					loadTechniqueFromEffect(ID3D10Device * xDevice, ID3D10Effect * xEffect, ID3D10InputLayout ** xLayout, ID3D10EffectTechnique ** xTechnqiue, D3D10_INPUT_ELEMENT_DESC * xPolygonLayout, LPCSTR xName, unsigned int xElements);
		
		// Create default World Matrix
		static STATUS				    createDefaultWorldMatrix(D3DXMATRIX ** xWorldMatrix);

		// Create Projection matrix
		static STATUS					createDefaultProjectionMatrix(D3DXMATRIX ** xProjectionMatrix, Dims* xWindowSize, GXSettings*  xSettings);

		// Create orthogonal matrix
		static STATUS				    createDefaultOrthogonalMatrix(D3DXMATRIX ** xProjectionMatrix, Dims* xWindowSize, GXSettings* xSettings);

		// Create view matrix
		static STATUS					createViewMatrix(D3DXMATRIX ** xViewMatrix, CameraProperties& xCameraProperties);
		
		// Create matrix for specific class
		template<class VertexClass>	
		inline static STATUS			CreateDefaultDynamicVertexBuffer(ID3D10Device * xDevice, ID3D10Buffer ** xVertexBuffer, int xVertices);

		// Create index buffer
		static STATUS					CreateDefaultIndexBuffer(ID3D10Device * xDevice, ID3D10Buffer ** xIndexBuffer, int xIndices);
		
	};

	template<class VertexClass>
	inline STATUS DXUtils::CreateDefaultDynamicVertexBuffer(ID3D10Device * xDevice, ID3D10Buffer ** xVertexBuffer, int xVertices)
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

		return STATUS_OK;
	}
}


#endif