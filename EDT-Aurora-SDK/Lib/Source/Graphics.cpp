
#include "../../Include/GLXExtLibs.h"
#include "../../Include/Graphics.h"

using namespace A2D;

Graphics::Graphics(BackBuffer * xBackBuffer)
{
    /*aBackBuffer = xBackBuffer;
	aDevice = xBackBuffer->getDevice();
	aBackBufferDims = xBackBuffer->getSize();
    aBackBufferSettings = xBackBuffer->getSettings();*/
    aBackBuffer = xBackBuffer;
}

Graphics::~Graphics()
{
    /*DESTROY(aQuadFactory);
	DESTROY(aColoredTextureShader);
	DESTROY(aViewMatrix);
	DESTROY(aWorldMatrix);
	DESTROY(aProjection2DMatrix);
	DESTROY(aProjection3DMatrix);
	DESTROY(aTextureBuffer);
    DESTROY(aBlurBuffer);*/
}

BackBuffer * Graphics::getBackBuffer()
{
	return aBackBuffer;
}

void Graphics::setBackBuffer(BackBuffer * xBackBuffer)
{
    aBackBuffer = xBackBuffer;
}

void Graphics::setWindow(AbstractWindow *xWindow)
{
    aWindow = xWindow;
}

/*
void Graphics::setClip(Rect * xClip, float xDepth)
{
	aQuadFactory->setConstraints(aClip = xClip, xDepth);
}


void Graphics::drawImage(Pipeline ** xPipeline, Rect& aRect, LPCWSTR& xSrc, bool xRepeat)
{
    Texture * texture;
	QuadData<TextureVertex> * quadData;

	// Pipeline not initalized
	if (*xPipeline == NULL)
	{
		*xPipeline = new Pipeline();

		texture = new Texture(aDevice, xSrc);
		quadData = new QuadData<TextureVertex>();

		DXShapeUtils::CreateDefaultDynamicVertexBuffer<TextureVertex>(*aDevice, &quadData->aVertexBuffer, 6);

		texture->initialize();

		(*xPipeline)->aPipelineComps[0] = texture;
		(*xPipeline)->aPipelineComps[1] = quadData;

		(*xPipeline)->aLength = 2;

		return;
	}

	texture = static_cast<Texture*>((*xPipeline)->aPipelineComps[0]);
	quadData = static_cast<QuadData<TextureVertex>*>((*xPipeline)->aPipelineComps[1]);

	// texture->Update(textureArgs); <<<<+++ ADD LATER
	aQuadFactory->updateVertexBuffer(quadData, &aRect, texture, xRepeat);
	aTextureShader->setTexture(texture);

	aQuadFactory->renderQuad(quadData->aVertexBuffer, sizeof(TextureVertex));
    aTextureShader->renderShader();
}
*/

void Graphics::drawImage()
{
    do{

            // Clear the screen
            glClearDepth(1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Use our shader
            glUseProgram(programID);
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, aBackBuffer->tex);

            // Set our "myTextureSampler" sampler to user Texture Unit 0
            glUniform1i(aBackBuffer->TextureID, 0);

            //bind vertext array before drawing
            glBindVertexArray (aBackBuffer->vao);

            // Draw the triangle !
            glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle

            // Swap buffers
         //   glfwSwapBuffers(window);
            glXSwapBuffers( aWindow->aDis, aWindow->aWin);

        } // Check if the ESC key was pressed or the window was closed
        while( true );

}

LPCWSTR Graphics::getClass()
{
    return "Graphics";
}

LPCWSTR Graphics::toString()
{
    return "Graphics";
}

HRESULT Graphics::initialize()
{
    programID = GLShaderUtils::LoadEffectFromFile( "/home/syk435/Testing Gl/GL-Test/SimpleVertexShader.vertexshader", "/home/syk435/Testing Gl/GL-Test/SimpleFragmentShader.fragmentshader" );

    MatrixID = glGetUniformLocation(programID, "MVP");

        // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    // Camera matrix
    glm::mat4 View       = glm::lookAt(
                                glm::vec3(0,0,2), // Camera is at (4,3,3), in World Space
                                glm::vec3(0,0,0), // and looks at the origin
                                glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                           );
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model      = glm::mat4(1.0f);
    // Our ModelViewProjection : multiplication of our 3 matrices
    MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

    file_name = "/home/syk435/Pictures/small_texture.png";
    int force_channels = 4;
    image_data = stbi_load(file_name, &x, &y, &n, force_channels); //replaced file_name with aSrc, but i guess aSrc has to be a String

    if (!image_data)
    {
           fprintf (stderr, "ERROR: could not load %s\n", file_name);
    }

    //check if not normal dims
    if (x & (x - 1) != 0 || y & (y - 1) != 0)
    {
            fprintf (stderr, "WARNING: texture %s is not power-of-2 dimensions\n", file_name);
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


    /*CameraProperties& cameraProperties = aCameraProperties;
	GXSettings* settings = aBackBufferSettings;
	Dims* size = aBackBufferDims;
	ID3D10Device ** device = aDevice;
		
	cameraProperties.aPositionX = 0.0f;
	cameraProperties.aPositionY = 0.0f;
	cameraProperties.aPositionZ = -800.0f;

	SAFELY(MatrixFactory::createDefaultWorldMatrix(reinterpret_cast<D3DXMATRIX**>(&aWorldMatrix)));
	SAFELY(MatrixFactory::createViewMatrix(reinterpret_cast<D3DXMATRIX**>(&aViewMatrix), cameraProperties));
	SAFELY(MatrixFactory::createDefaultProjectionMatrix(reinterpret_cast<D3DXMATRIX**>(&aProjection3DMatrix), size, settings));
	SAFELY(MatrixFactory::createDefaultOrthogonalMatrix(reinterpret_cast<D3DXMATRIX**>(&aProjection2DMatrix), size, settings));

	aQuadFactory = new QuadFactory(device, aBackBufferDims);
	SAFELY(aQuadFactory->initialize());

	aColoredTextureShader = new ColoredTextureShader(device);
	SAFELY(aColoredTextureShader->initialize());

	aTextureShader = new TextureShader(device);
	SAFELY(aTextureShader->initialize());

	aColorShader = new ColorShader(device);
	SAFELY(aColorShader->initialize());

	TextureShader::setViewMatrix(&aViewMatrix);
	ColorShader::setViewMatrix(&aViewMatrix);

	TextureShader::setProjectionMatrix(&aProjection2DMatrix);
	ColorShader::setProjectionMatrix(&aProjection2DMatrix);

	TextureShader::setWorldMatrix(&aWorldMatrix);
	ColorShader::setWorldMatrix(&aWorldMatrix);

	return S_OK;
    */
}
