
#include "../../../Include/Linux/ExtLibs.h"
#include "../../../Include/Linux/Texture.h"

using namespace A2D;

Texture::Texture(LPCWSTR xSrc, GLfloat* tcoords) : aSrc(xSrc)
{
    tBuffer = new TextureBuffer();
    texcoords = tcoords;
}

Texture::~Texture()
{
    glDeleteBuffers(1, &vt_vbo);

}

bool Texture::hasAlpha()
{
	// Force to be true
	return true;
}

void * Texture::getPlatformCompatibleResource()
{
//	return aResource;
}

HRESULT Texture::changeTexture(LPCWSTR  xSrc)
{
	aSrc = xSrc;

//    DESTROY(aResource);

	// Can't catch error here!!!! NOTE: FIX
	// Remind Mathew if you see this.
	return initialize();
}
 

/////////////////////////////////////////////////////////////////////////////
// REQUIRED BY _ABSTRACT
////////////////////////////////////////////////////////////////////////////

HRESULT Texture::initialize()
{
    int x, y, n;
    int force_channels = 4;

    image_data = stbi_load(aSrc, &x, &y, &n, force_channels); //replaced file_name with aSrc, but i guess aSrc has to be a String

    if (!image_data)
    {
           fprintf (stderr, "ERROR: could not load %s\n", aSrc);
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

    //generate and set active texture
    glGenTextures (1, &tex);
    glActiveTexture (GL_TEXTURE0);
    glBindTexture (GL_TEXTURE_2D, tex);

    //Uniform for Fragment (Texture) Shader
    //***Needs access to handle for shaders

    //Necessary Texture Settings
    glTexImage2D (
    GL_TEXTURE_2D,
    0,
    GL_RGBA,
    x,
    y,
    0,
    GL_RGBA,
    GL_UNSIGNED_BYTE,
    image_data
    );

    //necessary Texture settting (Tiling vs. Stretch)(how to crop?)
        //Default State is Stretch, Repeat is set by:GL_REPEAT

        //MIPMAP enabled by Default
    glGenerateMipmap (GL_TEXTURE_2D);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, State);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, State);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

    //set this according to amount of times necessary to repeat, need to set elsewhere

    //Set Texture Buffer
    int dimensions = 2; // 2d data for texture coords
    int length = 6; // 6 vertices

    tBuffer->genBuffer(vt_vbo, texcoords);

	// Load the texture in.
	// Store the texture properties
	aClip.aX = 0;
	aClip.aY = 0;
    aClip.aWidth = aDims.aWidth = (float)x;
    aClip.aHeight = aDims.aHeight = (float)y;

	
	return S_OK;
}

void Texture::checkSrcDims()
{
    int x = (int)aClip.aWidth;
    int y = (int)aClip.aHeight;

    if (x & (x - 1) != 0 || y & (y - 1) != 0)
        {
                fprintf (stderr, "WARNING: texture %s is not power-of-2 dimensions\n", aSrc);
        }
}

void Texture::renderTexture()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);

}
