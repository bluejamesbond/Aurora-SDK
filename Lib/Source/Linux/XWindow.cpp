
#include "../../../Include/Linux/ExtLibs.h"
#include "../../../Include/Linux/XWindow.h"

using namespace A2D;

////////////////////////////////////////////////////////////////////////////////
// PLATFORM COMPATIBLE IMPLEMENTATION
////////////////////////////////////////////////////////////////////////////////

XWindow::XWindow(AbstractFrame * xFrame) : AbstractWindow(xFrame){}

HRESULT XWindow::isExtensionSupported(const char *extList, const char *extension)
{

  const char *start;
  const char *where, *terminator;

  /* Extension names should not have spaces. */
  where = strchr(extension, ' ');
  if ( where || *extension == '\0' )
    return 0;

  /* It takes a bit of care to be fool-proof about parsing the
     OpenGL extensions string. Don't be fooled by sub-strings,
     etc. */
  for ( start = extList; ; ) {
    where = strstr( start, extension );

    if ( !where )
      break;

    terminator = where + strlen( extension );

    if ( where == start || *(where - 1) == ' ' )
      if ( *terminator == ' ' || *terminator == '\0' )
        return 1;

    start = terminator;
  }
  return 0;
}


unsigned long int  XWindow::createCompatibleWindow(bool isParent)
{

	aParent = isParent;
	int doubleBufferVisual[] = { GLX_RGBA,GLX_DEPTH_SIZE, 24,GLX_DOUBLEBUFFER, None };
	XTextProperty tp;
	XSizeHints sh;

	aDis = XOpenDisplay( NULL );

	NULLCHECK(aDis);

	// make sure OpenGL's GLX extension supported
	int errorBase, eventBase;
	NULLCHECK(glXQueryExtension( aDis, &errorBase, &eventBase ))

	XVisualInfo *visualInfo = glXChooseVisual( aDis, DefaultScreen(aDis), doubleBufferVisual );
	NULLCHECK(visualInfo);

	GLXContext hRC = glXCreateContext( aDis, visualInfo, NULL, GL_TRUE );
	NULLCHECK(hRC);

	winAttr.colormap = XCreateColormap( aDis, RootWindow(aDis, visualInfo->screen), visualInfo->visual, AllocNone );
	winAttr.event_mask = KeyPressMask;
	winAttr.border_pixel = BlackPixel( aDis, visualInfo->screen );
	winAttr.background_pixel = BlackPixel( aDis, visualInfo->screen );
	int winattr_flags = CWColormap | CWEventMask | CWBorderPixel | CWBackPixel;

	aWin = XCreateWindow( aDis, RootWindow(aDis, visualInfo->screen),
			aRect.aX, aRect.aY, aRect.aWidth, aRect.aHeight, 0,
	visualInfo->depth, InputOutput, visualInfo->visual, winattr_flags, &winAttr );


	//Window hWnd = XCreateSimpleWindow( aDis, RootWindow(aDis, visualInfo->screen), 0, 0, XRES, YRES, 0, 0, 0 );

	NULLCHECK(aWin);

	 char * aName = "Yalo";

	XStringListToTextProperty(&aName, 1, &tp);
	sh.flags = USPosition | USSize;
	XSetWMProperties(aDis, aWin, &tp, &tp, 0, 0, &sh, 0, 0);

	XMapWindow( aDis, aWin );

    render_context = NULL;

    if( isExtensionSupported( glXQueryExtensionsString(aDis, DefaultScreen(aDis)), "GLX_ARB_create_context" ) ) {
        typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
        glXCreateContextAttribsARBProc glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );
        if( glXCreateContextAttribsARB ) {
            int context_attribs[] =
            {
                GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
                GLX_CONTEXT_MINOR_VERSION_ARB, 2,
                //GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
                None
            };
            XSync( aDis, False );
        } else {
            fputs("glXCreateContextAttribsARB could not be retrieved", stderr);
        }
    } else {
            fputs("glXCreateContextAttribsARB not supported", stderr);
    }

        glXMakeCurrent( aDis, aWin, hRC );

        return S_OK;

}

HRESULT XWindow::createGLXContext()
{
	glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return -1;
    }


    const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString (GL_VERSION); // version as a string
    SYSOUT_F("[XWindow] Renderer: %s", renderer);
    SYSOUT_F("[XWindow] OpenGL version supported %s", version);

    // tell GL to only draw onto a pixel if the shape is closer to the viewer
//    glEnable (GL_DEPTH_TEST); // enable depth-testing
    ///////////////glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
//    glDepthMask(GL_TRUE);
//    glDepthFunc(GL_LEQUAL);
//    glDepthRange(0.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return S_OK;
}

HRESULT XWindow::initialize()
{
	SAFELY(AbstractWindow::initialize());

	SYSOUT_STR("[XWindow] Create createCompatibleWindow");

    SAFELY(createCompatibleWindow(true));

	SYSOUT_STR("[XWindow] Create createGLXContext");

    SAFELY(createGLXContext());

    return S_OK;
}

void XWindow::initPlatformCompatibleEventDispatcher(AbstractEventQueue * xEventQueue)
{
	AbstractFrame& frame = *aFrame;
	int keep_running = 1;
	XEvent event;

	SYSOUT_STR("[XWindow] Started initPlatformCompatibleEventDispatcher");

	while (keep_running)
	{
		frame.update();

		// XNextEvent(aDis, &event);

		switch(event.type)
		{
			case ClientMessage:
				if (event.xclient.message_type == XInternAtom(aDis, "WM_PROTOCOLS", 1) &&
						(Atom)event.xclient.data.l[0] == XInternAtom(aDis, "WM_DELETE_WINDOW", 1))
					keep_running = 0;

				break;

			default:
				break;
		}
	}
}

void XWindow::render()
{
    int keep_running = 1;
        XEvent event;

        while (keep_running) {
            XNextEvent(aDis, &event);

            switch(event.type) {
                case ClientMessage:
                    if (event.xclient.message_type == XInternAtom(aDis, "WM_PROTOCOLS", 1) &&
                    		(Atom)event.xclient.data.l[0] == XInternAtom(aDis, "WM_DELETE_WINDOW", 1))
                        keep_running = 0;

                    break;

                default:
                    break;
            }

            glXSwapBuffers( aDis, aWin);

        }

    return;
}

void * XWindow::getPlatformCompatibleWindowHandle()
{
    return &aDis;
}

void XWindow::destroyBackgroundResources()
{
    /*
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &vt_vbo);
    glDeleteProgram(programID);
    glDeleteTextures(1, &TextureID);
    glDeleteVertexArrays(1, &vao);
    */
}

void XWindow::destroyResources()
{
    XDestroyWindow(aDis, aWin);
    XCloseDisplay(aDis);
    glClearColor(0, 0, 0, 0);

    // Clear the screen and depth buffer.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    return;
}
