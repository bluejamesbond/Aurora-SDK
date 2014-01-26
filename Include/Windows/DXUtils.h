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
		
		// Create border matrix
		static STATUS SYSFASTCALL		updateBorderMatrix(D3DXMATRIX * x_borderMatrix, const Dims * x_windowSize);

		// Create matrix for specific class
		template<class VertexClass>	
		inline static STATUS			CreateDefaultDynamicVertexBuffer(ID3D10Device * xDevice, ID3D10Buffer ** xVertexBuffer, int xVertices, D3D10_BIND_FLAG x_bindFlags);

		// Create index buffer
		static STATUS					CreateDefaultIndexBuffer(ID3D10Device * xDevice, ID3D10Buffer ** xIndexBuffer, int xIndices);
		
		enum ShaderType
		{
			VERTEX_SHADER,
			HULL_SHADER,
			GEOMETRY_SHADER,
			COMPUTE_SHADER,
			PIXEL_SHADER
		};

		enum ShaderVersion
		{
			VERSION_5,
			VERSION_4
		};

		static STATUS					createShaderFromFile(ID3D10Device * x_device, void ** x_shader, LPCWSTR x_fileName, LPCSTR x_methodName, ShaderType x_shaderType, ShaderVersion x_shaderVersion)
		{
			// Set std namespace
			using std::string;

			ID3D10Blob * errorData;
			ID3D10Blob * shaderBuffer;
			STATUS status;
			string shaderProfile;

			// Set pointers to null
			errorData = shaderBuffer = NULL;

			switch (x_shaderType)
			{
				case VERTEX_SHADER:
				{
					shaderProfile = "vs_";
					break;
				}
				case HULL_SHADER:
				{
					shaderProfile = "hs_";
					break;
				}
				case GEOMETRY_SHADER:
				{
					shaderProfile = "gs_";
					break;
				}
				case COMPUTE_SHADER:
				{
					shaderProfile = "cs_";
					break;
				}
				case PIXEL_SHADER:
				{
					 shaderProfile = "ps_";
					 break;
				}
			}

			switch (x_shaderVersion)
			{
				case VERSION_5:
				{
					shaderProfile += "5_0";
					break;
				}
				case VERSION_4:
				{
					shaderProfile += "4_0";
					break;
				}
			}
			
			status = D3DX10CompileFromFile(x_fileName, 
										  NULL, NULL, 
										  x_methodName, 
										  shaderProfile.c_str(), 
										  D3D10_SHADER_ENABLE_STRICTNESS, 
										  0, 
										  NULL,
										  &shaderBuffer, 
										  &errorData, 
										  NULL);

			if (FAILED(status))
			{
				// If the shader failed to compile it should 
				// have writen something to the error message.
				if (errorData)
				{
					// Check if the data is even inside the buffer.
					if (errorData->GetBufferPointer())
					{
						SYSOUT_F("[DXUtils] %s", static_cast<char*>(errorData->GetBufferPointer()));
					}
				}

				return STATUS_FAIL;
			}

			switch (x_shaderType)
			{
				case PIXEL_SHADER: SAFELY(x_device->CreatePixelShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), reinterpret_cast<ID3D10PixelShader**>(x_shader)));
				case VERTEX_SHADER: SAFELY(x_device->CreateVertexShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), reinterpret_cast<ID3D10VertexShader**>(x_shader)));
				case GEOMETRY_SHADER: SAFELY(x_device->CreateGeometryShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), reinterpret_cast<ID3D10GeometryShader**>(x_shader)));

				// Currently not supporting due to DX10
				// limitations
				case COMPUTE_SHADER: return STATUS_FAIL;
				case HULL_SHADER: return STATUS_FAIL;
				default: return STATUS_FAIL;
			}

			return STATUS_OK;
		}
	};

	template<class VertexClass>
	inline STATUS DXUtils::CreateDefaultDynamicVertexBuffer(ID3D10Device * xDevice, ID3D10Buffer ** xVertexBuffer, int xVertices, D3D10_BIND_FLAG x_bindFlags)
	{
		D3D10_BUFFER_DESC vertexBufferDesc;
		D3D10_SUBRESOURCE_DATA vertexData;
		VertexClass * vertices = new VertexClass[xVertices];

		// initialize vertex array to zeros at first.
		memset(vertices, 0, (sizeof(VertexClass)* xVertices));

		vertexBufferDesc.Usage = D3D10_USAGE_DYNAMIC;
		vertexBufferDesc.ByteWidth = sizeof(VertexClass) * xVertices;
		vertexBufferDesc.BindFlags = x_bindFlags;
		vertexBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		vertexBufferDesc.MiscFlags = 0;

		// Give the subresource structure a pointer to the vertex data.
		vertexData.pSysMem = vertices;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;

		SAFELY(xDevice->CreateBuffer(&vertexBufferDesc, &vertexData, xVertexBuffer));

		delete[] vertices;
		vertices = 0;

		return STATUS_OK;
	}
}


#endif