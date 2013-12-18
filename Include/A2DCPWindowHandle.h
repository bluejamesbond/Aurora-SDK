class A2DCPWindowHandle
{
public:
	A2DCPWindowHandle();

	~A2DCPWindowHandle();
private:
#ifndef WIN32
	// code for X11
	Window			aHandle;
#else
	//  code for Windows
	HWND			 aHandle;
#endif

public:
//mutators and accessors

#ifndef WIN32
	Window			getHandle();
	void			setHandle(Window xHandle);
#else
	HWND			getHandle();
	void			setHandle(HWND xHandle);

#endif

};