#include "../../../Include/Linux/ExtLibs.h"
#include "../../../Include/Linux/Graphics.h"

using namespace A2D;

Graphics::Graphics(AbstractBackBuffer * xBackBuffer)
{
    /*aBackBuffer = xBackBuffer;
	aBackBufferDims = xBackBuffer->getSize();
    aBackBufferSettings = xBackBuffer->getSettings();*/
    aBackBuffer = xBackBuffer;
    BackBuffer * xbuffer = dynamic_cast<BackBuffer * >(aBackBuffer);
    aWindow = xbuffer->getWindow();
}

Graphics::~Graphics()
{
    /*DESTROY(aQuadFactory);
    DESTROY(aTextureBuffer);*/
}

AbstractBackBuffer * Graphics::getBackBuffer()
{
    return aBackBuffer;
}

void Graphics::validate(){}

void Graphics::setBackBuffer(BackBuffer * xBackBuffer)
{
    aBackBuffer = xBackBuffer;
}

void Graphics::setWindow(AbstractWindow *xWindow)
{
    aWindow = xWindow;
}


void Graphics::setClip(Rect * xClip, float xDepth)
{
    aClip = xClip;
    aQuadFactory->setConstraints(aClip, xDepth);
}

/*
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
        BackBuffer * xBackBuffer = dynamic_cast<BackBuffer * >(aBackBuffer);
        XWindow * xwin = dynamic_cast<XWindow * >(aWindow);

    do{

            // Clear the screen
            glClearDepth(1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Use our shader
//            glUseProgram(programID);
            glActiveTexture(GL_TEXTURE0);
            //glBindTexture(GL_TEXTURE_2D, aBackBuffer->tex);

            // Set our "myTextureSampler" sampler to user Texture Unit 0
            //glUniform1i(aBackBuffer->TextureID, 0);

            //bind vertext array before drawing
            glBindVertexArray (xBackBuffer->vao);

            // Draw the triangle !
            glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle

            // Swap buffers
         //   glfwSwapBuffers(window);
            glXSwapBuffers( xwin->aDis, xwin->aWin);

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

void Graphics::swap()
{
    XWindow * xwin = dynamic_cast<XWindow * >(aWindow);
    glXSwapBuffers( xwin->aDis, xwin->aWin);
}

HRESULT Graphics::initialize()
{

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
