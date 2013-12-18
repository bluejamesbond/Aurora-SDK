class A2DCPInstanceHandle
{
public:
	A2DCPInstanceHandle();

	~A2DCPInstanceHandle();
private:
#ifndef WIN32
	// code for X11
	XEvent			aHandle;
#else
	//  code for Windows
	HINSTANCE		 aHandle;
#endif

public:
	//mutators and accessors

#ifndef WIN32
	XEvent			getHandle();
	void			setHandle(XEvent xHandle);
#else
	HINSTANCE		getHandle();
	void			setHandle(HINSTANCE xHandle);

#endif

};