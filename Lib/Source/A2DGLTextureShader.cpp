#include "../../include/A2DExtLibs.h"
#include "../../include/A2DGLTextureShader.h"

A2DGLTextureShader::A2DGLTextureShader(A2DGLBackBuffer * xBackBuffer) :
A2DGLAbstractShader(xBackBuffer){}

A2DGLTextureShader::~A2DGLTextureShader(){}

HRESULT A2DGLTextureShader::CreateResources(void * xArgs[])
{
        HRESULT hr = S_OK;
        
        // No need to pass any arguments for this step
        hr = A2DGLAbstractShader::CreateResources(NULL);
        if (FAILED(hr))                return hr;
        glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
        glm::mat4 View       = glm::lookAt(
                                glm::vec3(0,0,3), // Camera is at (4,3,3), in World Space
                                glm::vec3(0,0,0), // and looks at the origin
                                glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                           );
    // Model matrix : an identity matrix (model will be at the origin)
        glm::mat4 Model      = glm::mat4(1.0f);\
        glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around
        /*
        // Get pointers to the three matrices inside the shader so we can update them from this class.
        aWorldMatrixPtr = aEffect->GetVariableByName("worldMatrix")->AsMatrix();
        aViewMatrixPtr = aEffect->GetVariableByName("viewMatrix")->AsMatrix();
        aProjectionMatrixPtr = aEffect->GetVariableByName("projectionMatrix")->AsMatrix();
        aTexturePtr = aEffect->GetVariableByName("shaderTexture")->AsShaderResource();
        
        // Set the world matrix variable inside the shader.
        aWorldMatrixPtr->SetMatrix(static_cast<float*>(xArgs[0]));

        // Set the view matrix variable inside the shader.
        aViewMatrixPtr->SetMatrix(static_cast<float*>(xArgs[1]));

        // Set the projection matrix variable inside the shader.
        aProjectionMatrixPtr->SetMatrix(static_cast<float*>(xArgs[2]));
*/
        // Bind the texture.
        aTexturePtr->SetResource(static_cast<A2DTexture*>(xArgs[3])->GetResource());

        return hr;
}

void A2DGLTextureShader::DestroyResources(){}

void A2DGLTextureShader::Update(void * xArgs[])
{
        // Bind the texture.
        aTexturePtr->SetResource(static_cast<A2DTexture*>(xArgs[0])->GetResource());

        A2DGLAbstractShader::Render();
}

LPCWSTR A2DGLTextureShader::GetClass()
{
        return L"A2DGLTextureShader";
}

LPCWSTR A2DGLTextureShader::ToString()
{
        return L"A2DGLTextureShader";
}

bool A2DGLTextureShader::operator==(A2DAbstract * xAbstract)
{
        return false;
}