#include "../../include/A2DExtLibs.h"
#include "../../include/A2DGLAbstractTexture.h"

A2DGLAbstractTexture::A2DGLAbstractTexture(A2DBackBuffer * xBackBuffer) :
aBackBuffer(xBackBuffer),
aResource(NULL) {}

A2DGLAbstractTexture::~A2DGLAbstractTexture(){}

ID3D10ShaderResourceView * A2DGLAbstractTexture::GetResource()
{
        return aResource;
}

bool A2DGLAbstractTexture::hasAlpha()
{
        // Force to be true
        return true;
}

A2DDims * A2DGLAbstractTexture::GetSize()
{
        return &aDims;
}

A2DRect * A2DGLAbstractTexture::GetClip(int xIndex)
{
        return &aClip;
}

void A2DGLAbstractTexture::DestroyResources()
{
        if (aResource)
        {
                aResource->Release();
                aResource = 0;
        }
}

void A2DGLAbstractTexture::SetClip(A2DRect * xClip, int xIndex)
{
        if (!xClip)
        {
                aClip.aX = 0.0f;
                aClip.aY = 0.0f;
                aClip.aWidth = aDims.aWidth;
                aClip.aHeight = aDims.aHeight;

                return;
        }

        // All values greater than zero but less than height/width
        aClip.aX = min(max(xClip->aX, 0.0f), aDims.aWidth);
        aClip.aY = min(max(xClip->aY, 0.0f), aDims.aHeight);
        aClip.aWidth = min(max(xClip->aWidth, 0.0f), aDims.aWidth);
        aClip.aHeight = min(max(xClip->aHeight, 0.0f), aDims.aHeight);
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY A2D_ABSTRACT
////////////////////////////////////////////////////////////////////////////

LPCWSTR A2DGLAbstractTexture::GetClass()
{
        return L"A2DGLAbstractTexture";
}

LPCWSTR A2DGLAbstractTexture::ToString()
{
        return L"A2DGLAbstractTexture";
}

bool A2DGLAbstractTexture::operator==(A2DAbstract * xAbstract)
{
        return false;
}

void A2DGLAbstractTexture::Deinitialize()
{
        delete &aDims;
        delete &aClip;
}

HRESULT A2DGLAbstractTexture::Initialize()
{
        SetClip(NULL);

        return S_OK;
}