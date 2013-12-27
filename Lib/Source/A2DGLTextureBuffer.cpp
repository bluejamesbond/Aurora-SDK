#include "../../include/A2DExtLibs.h"
#include "../../include/A2DGLTextureBuffer.h"

A2DGLTextureBuffer::A2DGLTextureBuffer(A2DGLBackBuffer * xBackBuffer, A2DDims * xSize) :
A2DGLAbstractTexture(xBackBuffer)
{
        aDims.aWidth = xSize->aWidth;
        aDims.aHeight = xSize->aHeight;
}

bool A2DGLTextureBuffer::hasAlpha()
{
        // Force to be false
        return false;
}

HRESULT A2DGLTextureBuffer::CreateResources(void * xArgs[])
{
        unsigned int tex = 0;
        glGenTextures (1, &tex);
        glActiveTexture (GL_TEXTURE0);
        glBindTexture (GL_TEXTURE_2D, tex);
        glTexImage2D (
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        aDims.aWidth,
        aDims.aHeight,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        image_data
        );

        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

      /*  float texcoords[] = {
         0.0f, 1.0f,
         0.0f, 0.0f,
          1.0, 0.0,
         1.0, 0.0,
         1.0, 1.0,
         0.0, 1.0
        };*/            //sample texcoord of corners of image
        unsigned int vt_vbo;
        glGenBuffers (1, &vt_vbo);
        glBindBuffer (GL_ARRAY_BUFFER, vt_vbo);
        int dimensions = 2; // 2d data for texture coords
        int length = 6; // 6 vertices
        glBufferData (
        GL_ARRAY_BUFFER,
        dimensions * length * sizeof (float),
        texcoords,
        GL_STATIC_DRAW
        );
        // note: this is your existing VAO
        unsigned int vao;
        glGenVertexArrays (1, &vao);
        glBindVertexArray (vao);
        glBindBuffer (GL_ARRAY_BUFFER, vt_vbo);
        // note: I assume that vertex positions are location 0
        dimensions = 2; // 2d data for texture coords
        glVertexAttribPointer (1, dimensions, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray (1);
        /*D3D10_TEXTURE2D_DESC textureDesc;
        HRESULT hr;
        D3D10_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
        D3D10_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

        // Initialize the render target texture description.
        ZeroMemory(&textureDesc, sizeof(textureDesc));

        // Setup the render target texture description.
        textureDesc.Width = (int)aDims.aWidth;
        textureDesc.Height = (int)aDims.aHeight;
        textureDesc.MipLevels = 1;
        textureDesc.ArraySize = 1;
        textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        textureDesc.SampleDesc.Count = 1;
        textureDesc.Usage = D3D10_USAGE_DEFAULT;
        textureDesc.BindFlags = D3D10_BIND_RENDER_TARGET | D3D10_BIND_SHADER_RESOURCE;
        textureDesc.CPUAccessFlags = 0;
        textureDesc.MiscFlags = 0;

        // Create the render target texture.
        hr = aBackBuffer->aDXDevice->CreateTexture2D(&textureDesc, NULL, &aDXRenderTargetTexture);
        if (FAILED(hr))                return hr;

        // Setup the description of the render target view.
        renderTargetViewDesc.Format = textureDesc.Format;
        renderTargetViewDesc.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2D;
        renderTargetViewDesc.Texture2D.MipSlice = 0;

        // Create the render target view.
        hr = aBackBuffer->aDXDevice->CreateRenderTargetView(aDXRenderTargetTexture, &renderTargetViewDesc, &aDXRenderTargetView);
        if (FAILED(hr))                return hr;

        // Setup the description of the shader resource view.
        shaderResourceViewDesc.Format = textureDesc.Format;
        shaderResourceViewDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
        shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
        shaderResourceViewDesc.Texture2D.MipLevels = 1;
        
        // Create the shader resource view.
        hr = aBackBuffer->aDXDevice->CreateShaderResourceView(aDXRenderTargetTexture, &shaderResourceViewDesc, &aResource);
        if (FAILED(hr))                return hr;

        return hr;
        */
}

void A2DGLTextureBuffer::Update(void * xArgs[])
{
        // Change size and stuff here        
}

void A2DGLTextureBuffer::Render()
{
        // No real rendering for textures to do. They just act as containers in the pipeline.
}

void A2DGLTextureBuffer::SetActive()
{
        // Bind the render target view and depth stencil buffer to the output render pipeline.
     //   aBackBuffer->aDXDevice->OMSetRenderTargets(1, &aDXRenderTargetView, aBackBuffer->aDXDepthStencilView);
}

void A2DGLTextureBuffer::DestroyResources()
{
        A2DAbstractTexture::DestroyResources();
        
        // Delete all the other global variables created for a texture except for ones like A2DDim and A2DRect
}

void A2DGLTextureBuffer::Clear()
{
        float color[4];
        
        // Setup the color to clear the buffer to.
        color[0] = 1.0f;
        color[1] = 0.0f;
        color[2] = 0.0f;
        color[3] = 1.0f;

        // Clear the back buffer.
      //  aBackBuffer->aDXDevice->ClearRenderTargetView(aDXRenderTargetView, color);

        // Clear the depth buffer.
      //  aBackBuffer->aDXDevice->ClearDepthStencilView(aBackBuffer->aDXDepthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0);
        glClearBuffer(vao);
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY A2D_ABSTRACT
////////////////////////////////////////////////////////////////////////////

LPCWSTR A2DGLTextureBuffer::GetClass()
{
        return L"A2DGLTextureBuffer";
}

LPCWSTR A2DGLTextureBuffer::ToString()
{
        return L"A2DGLTextureBuffer";
}

bool A2DGLTextureBuffer::operator==(A2DAbstract * xAbstract)
{
        return false;
}