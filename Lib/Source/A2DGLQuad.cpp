#include "../../include/A2DExtLibs.h"
#include "../../include/A2DGLQuad.h"

A2DGLQuad::A2DGLQuad(A2DBackBuffer * xBackBuffer, A2DRect * xRect) :
A2DAbstractShape(xBackBuffer, 6), aQuadWidth(xRect->aWidth), aQuadHeight(xRect->aHeight),
aTexture(0){}

A2DGLQuad::~A2DGLQuad(){}

HRESULT A2DGLQuad::Map()
{        
        HRESULT hr;
        
        // Calculate vertex and texture coordinates.
        CalculateCoords(aTexture->GetClip());

        // Map coordinates to vertex buffer.
        hr = glMapBuffer();
        
        return hr;
        
}

// NOTE: Cross platform - via skype message -Mathew K.
void A2DGLQuad::CalculateCoords(A2DRect * xTexRect)
{

        if (aConstraints->aX >= aRect->aWidth || aConstraints->aY >= aRect->aHeight)
        {
                // Render nothing.
                aLeft = aRight = aTop = aBottom = 0.0f;
                aLeftTex = aRightTex = aTopTex = aBottomTex = 0.0f;
        }
        else
        {
                float realX, realY;

                // Bitmap mapping calculations.
                realX = aConstraints->aX < 0 ? aRect->aX : aRect->aX + aConstraints->aX;
                realY = aConstraints->aY < 0 ? aRect->aY : aRect->aY + aConstraints->aY;

                // If the position we are rendering this bitmap to has not changed then don't update the vertex buffer since it
                // currently has the correct parameters.
                if ((realX == aPrevPosX) && (realY == aPrevPosY) && !aCONSTRAINT_CHANGED)
                {
                        return;
                }

                float realWidth, realHeight, calcWidth, calcHeight;
                float consOffsetX, consOffsetY;
                float realTWidth, realTHeight, calcTX, calcTY;
                float tWidthOffset, tHeightOffset;

                xTexRect->aX = xTexRect->aX;
                xTexRect->aY = xTexRect->aY;
                xTexRect->aHeight = xTexRect->aHeight;
                xTexRect->aWidth = xTexRect->aWidth;

                calcWidth = aConstraints->aWidth < 0 ? aConstraints->aWidth - abs(aConstraints->aX) : aConstraints->aWidth;
                calcHeight = aConstraints->aHeight < 0 ? aConstraints->aHeight - abs(aConstraints->aY) : aConstraints->aHeight;

                consOffsetX = aConstraints->aX < 0 ? 0 : aConstraints->aX;
                consOffsetY = aConstraints->aY < 0 ? 0 : aConstraints->aY;

                realWidth = aConstraints->aX + calcWidth > aRect->aWidth ? aRect->aWidth - consOffsetX : calcWidth;
                realHeight = aConstraints->aY + calcHeight > aRect->aHeight ? aRect->aHeight - consOffsetY : calcHeight;

                // Handle negative constraint dimensions.

                if (realWidth < 0)
                {
                        realWidth = realWidth + aConstraints->aX > 0 ? realWidth + aConstraints->aX : 0;
                }
                if (realHeight < 0)
                {
                        realHeight = realHeight + aConstraints->aY > 0 ? realHeight + aConstraints->aY : 0;
                }

                // Texture mapping calculations.
                calcTX = aConstraints->aX < 0 ? xTexRect->aX + (xTexRect->aWidth * abs(aConstraints->aX)) / aRect->aWidth : xTexRect->aX;
                calcTY = aConstraints->aY < 0 ? xTexRect->aY + (xTexRect->aHeight * abs(aConstraints->aY)) / aRect->aHeight : xTexRect->aY;

                // Calculate offset for x and y constraints.
                tWidthOffset = aConstraints->aX + calcWidth > aRect->aWidth || aConstraints->aX < 0 ? (xTexRect->aWidth * abs(aConstraints->aX)) / aRect->aWidth : 0;
                realTWidth = xTexRect->aWidth - tWidthOffset;

                tHeightOffset = aConstraints->aY + calcWidth > aRect->aHeight || aConstraints->aY < 0 ? (xTexRect->aHeight * abs(aConstraints->aY)) / aRect->aHeight : 0;
                realTHeight = xTexRect->aHeight - tHeightOffset;

                // Calculate offset for dimension constraints.
                realTWidth -= aConstraints->aWidth < aRect->aWidth ? (xTexRect->aWidth * (aRect->aWidth - aConstraints->aWidth)) / aRect->aWidth : 0;
                realTHeight -= aConstraints->aHeight < aRect->aHeight ? (xTexRect->aHeight * (aRect->aHeight - aConstraints->aHeight)) / aRect->aHeight : 0;

                // Reset constraint changed flag.
                aCONSTRAINT_CHANGED = false;

                // If it has changed then update the position it is being rendered to.
                aPrevPosX = aRect->aX;
                aPrevPosY = aRect->aY;

                // Calculate the screen coordinates of the left side of the bitmap.
                aLeft = ((aWindowDims->aWidth / 2) * -1) + realX;

                // Calculate the screen coordinates of the right side of the bitmap.
                aRight = aLeft + realWidth;

                // Calculate the screen coordinates of the top of the bitmap.
                aTop = (aWindowDims->aHeight / 2) - realY;

                // Calculate the screen coordinates of the bottom of the bitmap.
                aBottom = aTop - realHeight;

                // Calculate desired texture mapping.
                aLeftTex = calcTX / aTexture->GetSize()->aWidth;
                aRightTex = (calcTX + realTWidth) / aTexture->GetSize()->aWidth;
                aTopTex = calcTY / aTexture->GetSize()->aHeight;
                aBottomTex = (calcTY + realTHeight) / aTexture->GetSize()->aHeight;

        }
}

HRESULT A2DGLQuad::MapCoords()
{
         GLfloat g_vertex_buffer_data[] =       
         { 
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         };     //PUT IN VARS INSTEAD

        GLuint vertexbuffer;
        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        glEnableVertexAttribArray(vertexPosition_modelspaceID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            vertexPosition_modelspaceID, // The attribute we want to configure
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );
}

void A2DGLQuad::Update(void* xArgs[])
{

        // Set variables.
        aRect = static_cast<A2DRect*>(xArgs[0]);
        aTexture = static_cast<A2DTexture*>(xArgs[1]);
        aWindowDims = static_cast<A2DDims*>(xArgs[2]);

        HRESULT hr;

        // Map vertices.
        hr = Map();
        if (FAILED(hr))
        {
                // Mapping failed. 
                return;
        }

        // Render vertices to back buffer.
        Render();
        
        return;
}


void A2DGLQuad::SetConstraints(A2DRect * xRect)
{
        if (xRect->aX != aConstraints->aX ||
                xRect->aY != aConstraints->aY ||
                xRect->aWidth != aConstraints->aWidth ||
                xRect->aHeight != aConstraints->aHeight)
        {
                aConstraints->aX = xRect->aX;
                aConstraints->aY = xRect->aY;
                aConstraints->aWidth = xRect->aWidth;
                aConstraints->aHeight = xRect->aHeight;
                aCONSTRAINT_CHANGED = true;
        }
}

//////////////////////////////////////////////////////////
// A2DABSTRACT IMPLEMENTATION
//////////////////////////////////////////////////////////

HRESULT A2DGLQuad::Initialize()
{
        HRESULT hr = S_OK;
        
        aConstraints = new A2DRect();

        // Default point of constraint is NULL relative to location of quad.
        aConstraints->aX = 0;
        aConstraints->aY = 0;

        // Default dimensions of constraints is original width/height of quad.
        aConstraints->aWidth = aQuadWidth;
        aConstraints->aHeight = aQuadHeight;

        aCONSTRAINT_CHANGED = false; 

        // Initialize the previous rendering position to negative one.
        aPrevPosX = -1;
        aPrevPosY = -1;

        return hr;
}

void A2DGLQuad::DestroyResources()
{
        if (aRect)
        {
                delete aRect;
                aRect = 0;
        }

        if (aConstraints)
        {
                delete aConstraints;
                aConstraints = 0;
        }

        if (aVertices)
        {
                delete[] aVertices;
                aVertices = 0;
        }

        A2DAbstractShape::DestroyResources();
}

void A2DGLQuad::Deinitialize()
{
        // Delete the pointer but do not deallocate memory.
        aTexture = 0;
        aBackBuffer = 0;
        aWindowDims = 0;
}

LPCWSTR A2DGLQuad::GetClass()
{
        return L"A2DGLQuad";
}

LPCWSTR A2DGLQuad::ToString()
{
        return L"A2DGLQuad";
}

bool A2DGLQuad::operator==(A2DAbstract * A2DAbstract)
{
        return false;
}