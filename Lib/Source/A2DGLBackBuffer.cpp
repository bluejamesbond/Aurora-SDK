#include "../../include/A2DExtLibs.h"
#include "../../include/A2DGLBackBuffer.h"

//replace MSWindow Handles with X11 Window Handles, etc

A2DGLBackBuffer::A2DGLBackBuffer(A2DWindow * xWindow, A2DGXSettings * xGXSettings) : A2DAbstractBackBUffer(xWindow, xWindowProps) 
{
	m_deviceContext = 0;
	m_renderingContext = 0;
	aWindowProps(xWindowProps),
	aWindow(xWindow),
}

A2DGLBackBuffer::~A2DGLBackBuffer(){}

void A2DGLBackBuffer::SetZBuffer(bool val)
{
	m_deviceContext->OMSetDepthStencilState(val ? aDXDepthStencilState : aDXDepthDisabledStencilState, 1);
    return;
}

void A2DGLBackBuffer::SetActive()
{
	m_deviceContext->OMSetRenderTargets(1, &aDXRenderTargetView, aDXDepthStencilView);
        return;
}

void A2DGLBackBuffer::Clear()
{
	glClearBufferData(GLenum target,
 	GLenum internalformat,
 	GLenum format,
 	GLenum type,
 	const void * data);
	glClearDepth(GLDoubleDepth);
	glClearBuffferiv(GLenum buffer,
 	GLint drawBuffer,
 	const GLint * value);
}

void A2DGLBackBuffer::Swap()
{
	
	// Present the back buffer to the screen since rendering is complete.
	SwapBuffers(m_deviceContext);

	return;
}

HRESULT A2DGLBackBuffer::Initialize()
{
	HDC deviceContext;
	PIXELFORMATDESCRIPTOR pixelFormat;
	int error;
	HGLRC renderContext;
	bool result;


	int attributeListInt[19];
	int pixelFormat[1];
	unsigned int formatCount;
	int result;
    PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	int attributeList[5];
	float fieldOfView, screenAspect;
	char *vendorString, *rendererString;


	// Get the device context for this window.
	m_deviceContext = GetDC(hwnd);
	if(!m_deviceContext)
	{
		return false;
	}
	
	// Support for OpenGL rendering.
	attributeListInt[0] = glx_SUPPORT_OPENGL_ARB;
	attributeListInt[1] = TRUE;

	// Support for rendering to a window.
	attributeListInt[2] = glx_DRAW_TO_WINDOW_ARB;
	attributeListInt[3] = TRUE;

	// Support for hardware acceleration.
	attributeListInt[4] = glx_ACCELERATION_ARB;
	attributeListInt[5] = glx_FULL_ACCELERATION_ARB;

	// Support for 24bit color.
	attributeListInt[6] = glx_COLOR_BITS_ARB;
	attributeListInt[7] = 24;

	// Support for 24 bit depth buffer.
	attributeListInt[8] = glx_DEPTH_BITS_ARB;
	attributeListInt[9] = 24;

	// Support for double buffer.
	attributeListInt[10] = glx_DOUBLE_BUFFER_ARB;
	attributeListInt[11] = TRUE;

	// Support for swapping front and back buffer.
	attributeListInt[12] = glx_SWAP_METHOD_ARB;
	attributeListInt[13] = glx_SWAP_EXCHANGE_ARB;

	// Support for the RGBA pixel type.
	attributeListInt[14] = glx_PIXEL_TYPE_ARB;
	attributeListInt[15] = glx_TYPE_RGBA_ARB;

	// Support for a 8 bit stencil buffer.
	attributeListInt[16] = glx_STENCIL_BITS_ARB;
	attributeListInt[17] = 8;

	// Null terminate the attribute list.
	attributeListInt[18] = 0;
	
	// Query for a pixel format that fits the attributes we want.
	result = glxChoosePixelFormatARB(m_deviceContext, attributeListInt, NULL, 1, pixelFormat, &formatCount);
	if(result != 1)
	{
		return false;
	}

	// If the video card/display can handle our desired pixel format then we set it as the current one.
	result = SetPixelFormat(m_deviceContext, pixelFormat[0], &pixelFormatDescriptor);
	if(result != 1)
	{
		return false;
	}

	// Set the 4.0 version of OpenGL in the attribute list.
	attributeList[0] = glx_CONTEXT_MAJOR_VERSION_ARB;
	attributeList[1] = 4;
	attributeList[2] = glx_CONTEXT_MINOR_VERSION_ARB;
	attributeList[3] = 0;

	// Null terminate the attribute list.
	attributeList[4] = 0;

	// Create a OpenGL 4.0 rendering context.
	m_renderingContext = glxCreateContextAttribsARB(m_deviceContext, 0, attributeList);
	if(m_renderingContext == NULL)
	{
		return false;
	}

	// Set the rendering context to active.
	result = glxMakeCurrent(m_deviceContext, m_renderingContext);
	if(result != 1)
	{
		return false;
	}
	
	// Set the depth buffer to be entirely cleared to 1.0 values.
	glClearDepth(1.0f);

	// Enable depth testing.
	glEnable(GL_DEPTH_TEST);
	
	// Set the polygon winding to front facing for the left handed system.
	glFrontFace(GL_CW);

	// Enable back face culling.
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Initialize the world/model matrix to the identity matrix.
	BuildIdentityMatrix(m_worldMatrix);

	// Set the field of view and screen aspect ratio.
	fieldOfView = 3.14159265358979323846f / 4.0f;
	screenAspect = (float)screenWidth / (float)screenHeight;

	// Build the perspective projection matrix.
	BuildPerspectiveFovLHMatrix(m_projectionMatrix, fieldOfView, screenAspect, screenNear, screenDepth);

	// Get the name of the video card.
	vendorString = (char*)glGetString(GL_VENDOR);
	rendererString = (char*)glGetString(GL_RENDERER);

	// Store the video card name in a class member variable so it can be retrieved later.
	strcpy_s(m_videoCardDescription, vendorString);
	strcat_s(m_videoCardDescription, " - ");
	strcat_s(m_videoCardDescription, rendererString);

	// Turn on or off the vertical sync depending on the input bool value.
	if(vsync)
	{
		result = glxSwapIntervalEXT(1);
	}
	else
	{
		result = glxSwapIntervalEXT(0);
	}

	// Check if vsync was set correctly.
	if(result != 1)
	{
		return false;
	}


	// Get the device context for this window.
	deviceContext = GetDC(hwnd);
	if(!deviceContext)
	{
		return false;
	}

	// Set a temporary default pixel format.
	error = SetPixelFormat(deviceContext, 1, &pixelFormat);
	if(error != 1)
	{
		return false;
	}

	// Create a temporary rendering context.
	renderContext = glxCreateContext(deviceContext);
	if(!renderContext)
	{
		return false;
	}

	// Set the temporary rendering context as the current rendering context for this window.
	error = glxMakeCurrent(deviceContext, renderContext);
	if(error != 1)
	{
		return false;
	}

	// Initialize the OpenGL extensions needed for this application.  Note that a temporary rendering context was needed to do so.
	result = LoadExtensionList();
	if(!result)
	{
		return false;
	}

	// Release the temporary rendering context now that the extensions have been loaded.
	glxMakeCurrent(NULL, NULL);
	glxDeleteContext(renderContext);
	renderContext = NULL;

	// Release the device context for this window.
	ReleaseDC(hwnd, deviceContext);
	deviceContext = 0;

	//GetVideoCardInfo(aCardName);

	VertexType* vertices;
	unsigned int* indices;


	// Set the number of vertices in the vertex array.
	m_vertexCount = 3;

	// Set the number of indices in the index array.
	m_indexCount = 3;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned int[m_indexCount];
	if(!indices)
	{
		return false;
	}

	// Load the vertex array with data.

	// Bottom left.
	vertices[0].x = -1.0f;  // Position.
	vertices[0].y = -1.0f;
	vertices[0].z =  0.0f;

	vertices[0].r = 0.0f;  // Color.
	vertices[0].g = 1.0f;
	vertices[0].b = 0.0f;

	// Top middle.
	vertices[1].x = 0.0f;  // Position.
	vertices[1].y = 1.0f;
	vertices[1].z = 0.0f;

	vertices[1].r = 0.0f;  // Color.
	vertices[1].g = 1.0f;
	vertices[1].b = 0.0f;

	// Bottom right.
	vertices[2].x =  1.0f;  // Position.
	vertices[2].y = -1.0f;
	vertices[2].z =  0.0f;

	vertices[2].r = 0.0f;  // Color.
	vertices[2].g = 1.0f;
	vertices[2].b = 0.0f;

	// Load the index array with data.
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right.

	// Allocate an OpenGL vertex array object.
	glGenVertexArrays(1, &m_vertexArrayId);

	// Bind the vertex array object to store all the buffers and vertex attributes we create here.
	glBindVertexArray(m_vertexArrayId);

	// Generate an ID for the vertex buffer.
	glGenBuffers(1, &m_vertexBufferId);

	// Bind the vertex buffer and load the vertex (position and color) data into the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(VertexType), vertices, GL_STATIC_DRAW);

	// Enable the two vertex array attributes.
	glEnableVertexAttribArray(0);  // Vertex position.
	glEnableVertexAttribArray(1);  // Vertex color.

	// Specify the location and format of the position portion of the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexType), 0);

	// Specify the location and format of the color portion of the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(VertexType), (unsigned char*)NULL + (3 * sizeof(float)));

	// Generate an ID for the index buffer.
	glGenBuffers(1, &m_indexBufferId);

	// Bind the index buffer and load the index data into it.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount* sizeof(unsigned int), indices, GL_STATIC_DRAW);
	
	// Now that the buffers have been loaded we can release the array data.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}

void A2DGLBackBuffer::GetVideoCardInfo(char* xcardName)
	{
		strcpy_s(cardName, 128, m_videoCardDescription);
		return;
	}

bool A2DGLBackBuffer::LoadExtensionList()
{
	// Load the OpenGL extensions that this application will be using.
	glxChoosePixelFormatARB = (PFNglxCHOOSEPIXELFORMATARBPROC)glxGetProcAddress("glxChoosePixelFormatARB");
	if(!glxChoosePixelFormatARB)
	{
		return false;
	}

	glxCreateContextAttribsARB = (PFNglxCREATECONTEXTATTRIBSARBPROC)glxGetProcAddress("glxCreateContextAttribsARB");
	if(!glxCreateContextAttribsARB)
	{
		return false;
	}

	glxSwapIntervalEXT = (PFNglxSWAPINTERVALEXTPROC)glxGetProcAddress("glxSwapIntervalEXT");
	if(!glxSwapIntervalEXT)
	{
		return false;
	}

	glAttachShader = (PFNGLATTACHSHADERPROC)glxGetProcAddress("glAttachShader");
	if(!glAttachShader)
	{
		return false;
	}

	glBindBuffer = (PFNGLBINDBUFFERPROC)glxGetProcAddress("glBindBuffer");
	if(!glBindBuffer)
	{
		return false;
	}

	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)glxGetProcAddress("glBindVertexArray");
	if(!glBindVertexArray)
	{
		return false;
	}

	glBufferData = (PFNGLBUFFERDATAPROC)glxGetProcAddress("glBufferData");
	if(!glBufferData)
	{
		return false;
	}

	glCompileShader = (PFNGLCOMPILESHADERPROC)glxGetProcAddress("glCompileShader");
	if(!glCompileShader)
	{
		return false;
	}

	glCreateProgram = (PFNGLCREATEPROGRAMPROC)glxGetProcAddress("glCreateProgram");
	if(!glCreateProgram)
	{
		return false;
	}

	glCreateShader = (PFNGLCREATESHADERPROC)glxGetProcAddress("glCreateShader");
	if(!glCreateShader)
	{
		return false;
	}

	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)glxGetProcAddress("glDeleteBuffers");
	if(!glDeleteBuffers)
	{
		return false;
	}

	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)glxGetProcAddress("glDeleteProgram");
	if(!glDeleteProgram)
	{
		return false;
	}

	glDeleteShader = (PFNGLDELETESHADERPROC)glxGetProcAddress("glDeleteShader");
	if(!glDeleteShader)
	{
		return false;
	}

	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)glxGetProcAddress("glDeleteVertexArrays");
	if(!glDeleteVertexArrays)
	{
		return false;
	}

	glDetachShader = (PFNGLDETACHSHADERPROC)glxGetProcAddress("glDetachShader");
	if(!glDetachShader)
	{
		return false;
	}

	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)glxGetProcAddress("glEnableVertexAttribArray");
	if(!glEnableVertexAttribArray)
	{
		return false;
	}

	glGenBuffers = (PFNGLGENBUFFERSPROC)glxGetProcAddress("glGenBuffers");
	if(!glGenBuffers)
	{
		return false;
	}

	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)glxGetProcAddress("glGenVertexArrays");
	if(!glGenVertexArrays)
	{
		return false;
	}

	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)glxGetProcAddress("glGetAttribLocation");
	if(!glGetAttribLocation)
	{
		return false;
	}

	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)glxGetProcAddress("glGetProgramInfoLog");
	if(!glGetProgramInfoLog)
	{
		return false;
	}

	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)glxGetProcAddress("glGetProgramiv");
	if(!glGetProgramiv)
	{
		return false;
	}

	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)glxGetProcAddress("glGetShaderInfoLog");
	if(!glGetShaderInfoLog)
	{
		return false;
	}

	glGetShaderiv = (PFNGLGETSHADERIVPROC)glxGetProcAddress("glGetShaderiv");
	if(!glGetShaderiv)
	{
		return false;
	}

	glLinkProgram = (PFNGLLINKPROGRAMPROC)glxGetProcAddress("glLinkProgram");
	if(!glLinkProgram)
	{
		return false;
	}

	glShaderSource = (PFNGLSHADERSOURCEPROC)glxGetProcAddress("glShaderSource");
	if(!glShaderSource)
	{
		return false;
	}

	glUseProgram = (PFNGLUSEPROGRAMPROC)glxGetProcAddress("glUseProgram");
	if(!glUseProgram)
	{
		return false;
	}

	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)glxGetProcAddress("glVertexAttribPointer");
	if(!glVertexAttribPointer)
	{
		return false;
	}

	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)glxGetProcAddress("glBindAttribLocation");
	if(!glBindAttribLocation)
	{
		return false;
	}

	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)glxGetProcAddress("glGetUniformLocation");
	if(!glGetUniformLocation)
	{
		return false;
	}

	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)glxGetProcAddress("glUniformMatrix4fv");
	if(!glUniformMatrix4fv)
	{
		return false;
	}

	glActiveTexture = (PFNGLACTIVETEXTUREPROC)glxGetProcAddress("glActiveTexture");
	if(!glActiveTexture)
	{
		return false;
	}

	glUniform1i = (PFNGLUNIFORM1IPROC)glxGetProcAddress("glUniform1i");
	if(!glUniform1i)
	{
		return false;
	}

	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)glxGetProcAddress("glGenerateMipmap");
	if(!glGenerateMipmap)
	{
		return false;
	}

	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)glxGetProcAddress("glDisableVertexAttribArray");
	if(!glDisableVertexAttribArray)
	{
		return false;
	}

	glUniform3fv = (PFNGLUNIFORM3FVPROC)glxGetProcAddress("glUniform3fv");
	if(!glUniform3fv)
	{
		return false;
	}

	glUniform4fv = (PFNGLUNIFORM4FVPROC)glxGetProcAddress("glUniform4fv");
	if(!glUniform4fv)
	{
		return false;
	}


	return true;
}

void A2DGLBackBuffer::Deinitialize()
{
	// Disable the two vertex array attributes.
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	
	// Release the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &m_vertexBufferId);

	// Release the index buffer.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &m_indexBufferId);

	// Release the vertex array object.
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &m_vertexArrayId);

//do we really want to close the context though?		*********************

	if(m_renderingContext)
	{
		glxMakeCurrent(NULL, NULL);
		glxDeleteContext(m_renderingContext);
		m_renderingContext = 0;
	}

	// Release the device context.
	if(m_deviceContext)
	{
		ReleaseDC(hwnd, m_deviceContext);
		m_deviceContext = 0;
	}

	return;
}

LPCWSTR A2DGLBackBuffer::GetClass()
{
	return L"A2DGLBackBuffer";
}

LPCWSTR A2DGLBackBuffer::ToString()
{
	return L"A2LinDBackBuffer";
}

bool A2DGLBackBuffer::operator==(A2DAbstract * xAbstract)
{
	return false;
}