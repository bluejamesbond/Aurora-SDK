#include "../../include/A2DExtLibs.h"
#include "../../include/A2DGLAbstractShape.h"
#include "../../include/A2DBackBuffer.h"


A2DGLAbstractShape::A2DGLAbstractShape(A2DBackBuffer * xBackBuffer, int xVertexCount) : 
aBackBuffer(xBackBuffer),
aVertexCount(xVertexCount), aIndexCount(xVertexCount) {}

A2DGLAbstractShape::~A2DGLAbstractShape(){}

//args
// 1: vertexcount
HRESULT A2DGLAbstractShape::CreateResources(void * xArgs[])
{
        HRESULT hr = S_OK;

        unsigned long * indices;
        GLuint vertexBufferDesc, indexBufferDesc;
        float* vertexData, indexData;
        int i;

        // Create the vertex array.
        vertices = new vertexData[aVertexCount];
        if (!vertices)
        {
                return E_FAIL;
        }

        // Create the index array.
        indices = new unsigned long[aIndexCount];
        if (!indices)
        {
                return E_FAIL;
        }

        // Initialize vertex array to zeros at first.
        memset(vertices, 0, (sizeof(vertexData)* aVertexCount));

        // Load the index array with data.
        for (i = 0; i < aIndexCount; i++)
        {
                indices[i] = i;
        }

        // Now finally create the vertex buffer.
        hr = aBackBuffer->CreateBuffer(&vertexBufferDesc, &vertexData, &aVertexBuffer);
        if (FAILED(hr))
        {
                return hr;
        }

       
        // Create the index buffer.
        hr = aBackBuffer->CreateBuffer(&indexBufferDesc, &indexData, &aIndexBuffer);
        if (FAILED(hr))
        {
                return hr;
        }

        // Release the arrays now that the vertex and index buffers have been created and loaded.
        delete[] vertices;
        vertices = 0;

        delete[] indices;
        indices = 0;

        return hr;
        
}

void A2DGLAbstractShape::Render()
{

        glDrawArrays(GL_TRIANGLES, 0, aVertexCount); // 3 indices starting at 0 -> 1 triangle
        glDisableVertexAttribArray(vertexPosition_modelspaceID);                        //pass this in i suppose
        glDisableVertexAttribArray(vertexColorID);                                      //pass in as well
        glfwSwapBuffers();

        return;
}

void A2DGLAbstractShape::DestroyResources()
{

       GLenum ErrorCheckValue = glGetError();
       glDisableVertexAttribArray(1);
       glDisableVertexAttribArray(0);
     
       glBindBuffer(GL_ARRAY_BUFFER, 0);
 
       glDeleteBuffers(1, &ColorBufferId);
       glDeleteBuffers(1, &VboId);
 
       glBindVertexArray(0);
       glDeleteVertexArrays(1, &VaoId);
       ErrorCheckValue = glGetError();
       if (ErrorCheckValue != GL_NO_ERROR)
       {
           fprintf(
               stderr,
               "ERROR: Could not destroy the VBO: %s \n",
                gluErrorString(ErrorCheckValue)
           );
 
           exit(-1);
       }
 
}


LPCWSTR A2DGLAbstractShape::GetClass()
{
        return L"A2DGLAbstractShape";
}

LPCWSTR A2DGLAbstractShape::ToString()
{
        return L"A2DGLAbstractShape";
}

bool A2DGLAbstractShape::operator==(A2DAbstract * A2DAbstract)
{
        return false;
}