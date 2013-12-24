//IF ANY VIRTUAL METHODS (OTHER THAN PURE VIRTUAL), CALL PARENT FUNCTION FIRST INSIDE IT (IF APPLICABLE)
/*Also Available: int XMoveWindow(Display *display, Window w, int x, y);
int XResizeWindow(Display *display, Window w, unsigned width, unsigned height);
int XMoveResizeWindow(Display *display, Window w, int x, int y, unsigned width, unsigned height);
int XSetWindowBorderWidth(Display *display, Window w, unsigned width);
*/

A2DXWindow::A2DXWindow(HINSTANCE xHInstance) 
: aHInstance(xHInstance){}//default constructor with initiating parent constructor

A2DXWindow::~A2DXWindow(){}//default destructor

void A2DXWindow::render()
{
	XEvent e;
    pthread_t thread;

    d = XOpenDisplay(NULL);
    if (d == NULL)
        return 0;

    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), aRect.aX, aRect.aY, aOptBorderWidth, 800, 1,	//fill in header variables
                            (A2DColor)aOptBorderColor, (A2DColor)aOptBorderColor);
    XSelectInput(aDis, aWin, ExposureMask | KeyPressMask);
    XMapWindow(aDis, aWin);

    pthread_create(&thread, NULL, tp, NULL);
}

void A2DXWindow::validate()
{
	aValidatedContents = true;
}

void* A2DXWindow::getPlatformCompatibleWindowHandle()
{
	return &awin;
}

void A2DXWindow::setMinimumSize(A2DDims * xSize)
{
	aMinDims.aWidth = max(aOptBoxShadowRadius * A2D_WINDOW_BOX_SHADOW_SAFETY_RATIO, xSize.aWidth);
    aMinDims.aHeight = max(aOptBoxShadowRadius * A2D_WINDOW_BOX_SHADOW_SAFETY_RATIO, xSize.aHeight);

    aMinDims.aWidth = max(aMinDims.aWidth, (aOptBorderWidth * 2) + 1);
    aMinDims.aHeight = max(aMinDims.aHeight, (aOptBorderWidth * 2) + 1);
}

void A2DXWindow::setMaximumSize(A2DDims * xSize)
{
	aMaxDims.aWidth = max(aOptBoxShadowRadius * A2D_WINDOW_BOX_SHADOW_SAFETY_RATIO, xSize.aWidth);
    aMaxDims.aHeight = max(aOptBoxShadowRadius * A2D_WINDOW_BOX_SHADOW_SAFETY_RATIO, xSize.aHeight);

    aMaxDims.aWidth = max(aMaxDims.aWidth, (aOptBorderWidth * 2) + 1);
    aMaxDims.aHeight = max(aMaxDims.aHeight, (aOptBorderWidth * 2) + 1);
	invalidate();
	update();
}

void A2DXWindow::setSize(A2DDims * xSize)
{
	aCurrentSize.aWidth = xSize.aWidth;
	aCurrentSize.aHeight = xSize.aHeight;
	invalidate();
	update();
}

void A2DXWindow::setMinimumSize(float xWidth, float xHeight)
{
	aMinDims.aWidth = max(aOptBoxShadowRadius * A2D_WINDOW_BOX_SHADOW_SAFETY_RATIO, xWidth);
    aMinDims.aHeight = max(aOptBoxShadowRadius * A2D_WINDOW_BOX_SHADOW_SAFETY_RATIO, xHeight);

    aMinDims.aWidth = max(aMinDims.aWidth, (aOptBorderWidth * 2) + 1);
    aMinDims.aHeight = max(aMinDims.aHeight, (aOptBorderWidth * 2) + 1);
}

void A2DXWindow::setMaximumSize(float xWidth, float xHeight)
{
	aMaxDims.aWidth = max(aOptBoxShadowRadius * A2D_WINDOW_BOX_SHADOW_SAFETY_RATIO, xWidth);
    aMaxDims.aHeight = max(aOptBoxShadowRadius * A2D_WINDOW_BOX_SHADOW_SAFETY_RATIO, xHeight);

    aMaxDims.aWidth = max(aMaxDims.aWidth, (aOptBorderWidth * 2) + 1);
    aMaxDims.aHeight = max(aMaxDims.aHeight, (aOptBorderWidth * 2) + 1);
}

void A2DXWindow::setSize(float xWidth, float xHeight)
{
	aCurrentSize.aWidth = xWidth;
	aCurrentSize.aHeight = xHeight;
	invalidate();
	update();
}

void A2DXWindow::setName(LPCWSTR xName)
{
	Atom prop = XInternAtom(aDis,"WM_NAME",False), type;
    int form;
    unsigned long remain, len;
    unsigned char *list;


    if (XGetWindowProperty(aDis,aWin,prop,0,1024,False,XA_STRING,
                &type,&form,&len,&remain,&list) != Success) {

        return NULL;
    }
    invalidate();
    update();
}

void A2DXWindow::setUndecorated(bool xUndecoratedFlag)
{
	Hints hints;
	Atom property;
	hints.flags = 2;
	hints.decorations = 0;
	property = XInternAtom(display, "_MOTIF_WM_HINTS", true);
	XChangeProperty(aDis,aWin,property,property,32,PropModeReplace,(unsigned char *)&hints,5);
	XMapWindow(aDis, aWin);
	invalidate();
	update();
}

void A2DXWindow::setDefaultCloseOperation(int xCloseOperation)
{
	XSetCloseDownMode(aDis, xCloseOperation);
}

void A2DXWindow::setLocationRelativeTo(A2DXWindow * xWindow)
{
	if (aWin->monitor)
    {
        _glfwSetVideoMode(aWin->monitor, &aWin->videoMode);

        if (aWin->x11.overrideRedirect)
        {
            GLFWvidmode mode;
            _glfwPlatformGetVideoMode(aWin->monitor, &mode);
            XResizeWindow(_glfw.x11.display, aWin->x11.handle,
                          aRect.width, aRect.height);
        }
    }
    else
    {
        if (!aWin->resizable)
        {
            // Update window size restrictions to match new window size

            XSizeHints* hints = XAllocSizeHints();

            hints->flags |= (PMinSize | PMaxSize);
            hints->aMinDims.aWidth  = hints->aMaxDimx.aWidth  = xWidth;		//actually maybe aCurrentSize
            hints->aMindDims.aHeight = hints->aMaxDims.aHeight = xHeight;

            XSetWMNormalHints(_glfw.x11.display, aWin->x11.handle, hints);
            XFree(hints);
        }

        XResizeWindow(_glfw.x11.display, aWin->x11.handle, aCurrrentSize.aWidth, aCurrentSize.aHeight);
    }

    XFlush(_glfw.x11.display);
}

void A2DXWindow::setVisible(bool xVisible)
{
	if(xVisible)
	{
		XMapRaised(_glfw.x11.display, aWin->x11.handle);
   	    XFlush(_glfw.x11.display);
	}
	else
	{
		return;
	}
}

void A2DXWindow::setShadowed(bool xShadowFlag)
{
	//
}

void A2DXWindow::setBorderColor(Color xBorderColor)
{
	aOptBorderColor = xBorderColor;
	A2DColor Color = new A2DColor(aOptBorderColor);					//suggest transform of color to A2DColor, or maybe we'll just ditch color
	XSetWindowBorder(aDis, aWin, (unsigned long)Color.getValue());
	invalidate();
	update();
}

void A2DXWindow::setShadowRadius(float xShadowRadius)
{
	//
}

void A2DXWindow::setShadowColor(Color xShadowColor)
{
	//
}

void A2DXWindow::setBackgroundColor(Color xBackgroundColor)
{
	aOptBackgroundColor = xBackgroundColor;
	A2DColor Color = new A2DColor(aOptBackgroundColor);					//suggest transform of color to A2DColor, or maybe we'll just ditch color
	XSetWindowBackground(aDis, aWin, (unsigned long)Color.getValue());
	invalidate();
	update();
}

void A2DXWindow::setBorderWidth(float xBorderWidth)
{
	XSetWindowBorderWidth(aDis, aWin, (unsigned)aOptBorderWidth);
	invalidate();
	update();
}

void A2DXWindow::setBorder(Color xBorderColor, float xBorderWidth)
{
	setBorderColor(xBorderColor);
	setBorderWidth(xBorderWidth);
}

void A2DXWindow::setShadow(Color xShadowColor, float xShadowRadius)
{
	//
}

HRESULT A2DXWindow::Initialize()
{
	// Load the OpenGL extensions that this application will be using.
	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	if(!wglChoosePixelFormatARB)
	{
		return false;
	}

	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	if(!wglCreateContextAttribsARB)
	{
		return false;
	}

	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	if(!wglSwapIntervalEXT)
	{
		return false;
	}

	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	if(!glAttachShader)
	{
		return false;
	}

	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	if(!glBindBuffer)
	{
		return false;
	}

	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
	if(!glBindVertexArray)
	{
		return false;
	}

	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	if(!glBufferData)
	{
		return false;
	}

	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	if(!glCompileShader)
	{
		return false;
	}

	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	if(!glCreateProgram)
	{
		return false;
	}

	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	if(!glCreateShader)
	{
		return false;
	}

	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
	if(!glDeleteBuffers)
	{
		return false;
	}

	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
	if(!glDeleteProgram)
	{
		return false;
	}

	glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	if(!glDeleteShader)
	{
		return false;
	}

	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
	if(!glDeleteVertexArrays)
	{
		return false;
	}

	glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
	if(!glDetachShader)
	{
		return false;
	}

	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	if(!glEnableVertexAttribArray)
	{
		return false;
	}

	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	if(!glGenBuffers)
	{
		return false;
	}

	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
	if(!glGenVertexArrays)
	{
		return false;
	}

	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
	if(!glGetAttribLocation)
	{
		return false;
	}

	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
	if(!glGetProgramInfoLog)
	{
		return false;
	}

	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	if(!glGetProgramiv)
	{
		return false;
	}

	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
	if(!glGetShaderInfoLog)
	{
		return false;
	}

	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	if(!glGetShaderiv)
	{
		return false;
	}

	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	if(!glLinkProgram)
	{
		return false;
	}

	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	if(!glShaderSource)
	{
		return false;
	}

	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	if(!glUseProgram)
	{
		return false;
	}

	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
	if(!glVertexAttribPointer)
	{
		return false;
	}

	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
	if(!glBindAttribLocation)
	{
		return false;
	}

	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
	if(!glGetUniformLocation)
	{
		return false;
	}

	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	if(!glUniformMatrix4fv)
	{
		return false;
	}

	glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
	if(!glActiveTexture)
	{
		return false;
	}

	glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
	if(!glUniform1i)
	{
		return false;
	}

	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
	if(!glGenerateMipmap)
	{
		return false;
	}

	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
	if(!glDisableVertexAttribArray)
	{
		return false;
	}

	glUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
	if(!glUniform3fv)
	{
		return false;
	}

	glUniform4fv = (PFNGLUNIFORM4FVPROC)wglGetProcAddress("glUniform4fv");
	if(!glUniform4fv)
	{
		return false;
	}

	return true;
	aDis = XOpenDisplay(NULL);
    aWin = XCreateSimpleWindow(aDis, RootWindow(aDis, 0), aRect.aX, aRect.ay, 10, 10,	//just random initial values
                                     0, BlackPixel (aDis, 0), BlackPixel(aDis, 0));	//last few: width, height, border with,long border, long background
    																				//BlackPixel (aDis, 0) sets them to black
    Atom wm_state = XInternAtom(aDis, "_NET_WM_STATE", False);
    Atom fullscreen = XInternAtom(aDis, "_NET_WM_STATE_FULLSCREEN", False);			//change later

    XEvent xev;
    memset(&xev, 0, sizeof(xev));
    xev.type = ClientMessage;
    xev.xclient.window = aWin;
    xev.xclient.message_type = wm_state;
    xev.xclient.format = 32;
    xev.xclient.data.l[0] = 1;
    xev.xclient.data.l[1] = fullscreen;
    xev.xclient.data.l[2] = 0;

    XMapWindow(aDis, aWin);

    XSendEvent (aDis, DefaultRootWindow(aDis), False,
                    SubstructureRedirectMask | SubstructureNotifyMask, &xev);		//prob comment out this line

    XFlush(aDis);

    //get out of fullscreen?

    _glfwRestoreVideoMode(aWin->monitor);

    _glfw.x11.saver.count--;

    if (_glfw.x11.saver.count == 0)
    {
        // Restore old screen saver settings
        XSetScreenSaver(_glfw.x11.display,
                        _glfw.x11.saver.timeout,
                        _glfw.x11.saver.interval,
                        _glfw.x11.saver.blanking,
                        _glfw.x11.saver.exposure);
    }

    if (_glfw.x11.hasEWMH &&
        _glfw.x11.NET_WM_STATE != None &&
        _glfw.x11.NET_WM_STATE_FULLSCREEN != None)
    {
        // Ask the window manager to make the GLFW window a normal window
        // Normal windows usually have frames and other decorations

        XEvent event;
        memset(&event, 0, sizeof(event));

        event.type = ClientMessage;
        event.xclient.window = aWin->x11.handle;
        event.xclient.format = 32; // Data is 32-bit longs
        event.xclient.message_type = _glfw.x11.NET_WM_STATE;
        event.xclient.data.l[0] = _NET_WM_STATE_REMOVE;
        event.xclient.data.l[1] = _glfw.x11.NET_WM_STATE_FULLSCREEN;
        event.xclient.data.l[2] = 0; // No secondary property
        event.xclient.data.l[3] = 1; // Sender is a normal application

        XSendEvent(_glfw.x11.display,
                   _glfw.x11.root,
                   False,
                   SubstructureNotifyMask | SubstructureRedirectMask,
                   &event);
    }
}

void A2DXWindow::Deinitialize()
{
	XDestroyWindow(aDis, aWin);
	glClearColor(0, 0, 0, 0); 

	// Clear the screen and depth buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(m_renderingContext)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_renderingContext);
		m_renderingContext = 0;
	}

	// Release the device context.
	if(aDis)
	{
		ReleaseDC(aWin, aDis);
		aDis = 0;
	}

	return;
}
	
	return;
}
    
LPCWSTR A2DXWindow::GetClass()
{
	return L"A2DXWindow";
}

LPCWSTR A2DXWindow::ToString()
{
	return L"A2DXWindow";
}

bool A2DXWindow::operator==(A2DAbstract * xAbstract)
{
	if(this ==xAbstract)
	{
		return true;
	}
	else
	{
		return false;
	}
}