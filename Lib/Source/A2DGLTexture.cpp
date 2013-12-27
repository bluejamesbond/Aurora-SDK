#include "../../include/A2DExtLibs.h"
#include "../../include/A2DGLTexture.h"
#include "../../include/A2DGLImageLoader.h"

A2DGLTexture::A2DGLTexture(A2DBackBuffer * xBackBuffer, LPCWSTR * xSrc) :
A2DAbstractTexture(xBackBuffer)
{
        aResource = NULL;
        aSrc = xSrc;
}

A2DGLTexture::~A2DGLTexture(){}

bool A2DGLTexture::HasAlpha()
{
        // Force to be true
        return true;
}

HRESULT A2DGLTexture::CreateResources(void * xArgs[])
{
        HRESULT hr = S_OK;
        int x, y, n;
        int force_channels = 4;
        aResource = stbi_load(aSrc, &x, &y, &n, force_channels); //replaced file_name with aSrc, but i guess aSrc has to be a String
        
        if (!image_data)
        {
                fprintf (stderr, "ERROR: could not load %s\n", aSrc);
        }

        //check if not normal dims
        if (x & (x - 1) != 0 || y & (y - 1) != 0)
        {
                fprintf (stderr, "WARNING: texture %s is not power-of-2 dimensions\n", aSrc);
        }

        //invert to norm
        int width_in_bytes = x * 4;
        unsigned char *top = NULL;
        unsigned char *bottom = NULL;
        unsigned char temp = 0;
        int half_height = y / 2;

        for (int row = 0; row < half_height; row++) {
                top = image_data + row * width_in_bytes;
                bottom = image_data + (y - row - 1) * width_in_bytes;
                for (int col = 0; col < width_in_bytes; col++)
                {
                        temp = *top;
                        *top = *bottom;
                        *bottom = temp;
                        top++;
                        bottom++;
                }
        }

        /*
        HRESULT hr;
        D3DX10_IMAGE_LOAD_INFO loadInfo;
        D3DX10_IMAGE_INFO srcInfo;

        loadInfo.pSrcInfo = &srcInfo;

        // Load the texture in.
        hr = D3DX10CreateShaderResourceViewFromFile(aBackBuffer->aDXDevice, *aSrc, &loadInfo, NULL, &aResource, NULL);
        if (FAILED(hr))                return hr;
        */

        // Store the texture properties

        aDims.aWidth = (float)x;
        aDims.aHeight = (float)y;

        return hr;
}

void A2DGLTexture::Update(void * xArgs[])
{
        if (static_cast<LPCWSTR*>(xArgs[0]) == aSrc)
        {
                return;
        }

        // Can't catch error here!!!! NOTE: FIX
        // Remind @Mathew if you see this.
        CreateResources(xArgs);
}

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY A2D_ABSTRACT
////////////////////////////////////////////////////////////////////////////

LPCWSTR A2DGLTexture::GetClass()
{
        return L"A2DGLTexture";
}

LPCWSTR A2DGLTexture::ToString()
{
        return L"A2DGLTexture";
}

bool A2DGLTexture::operator==(A2DAbstract * xAbstract)
{
        return false;
}