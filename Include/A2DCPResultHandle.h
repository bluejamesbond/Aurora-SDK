class A2DCPResultHandle
{
public:
	A2DCPResultHandle();

	~A2DCPResultHandle();
private:
#ifndef WIN32
	// code for X11
	bool			aHandle;
#else
	//  code for Windows
	HRESULT			aHandle;
#endif

public:
	//mutators and accessors

#ifndef WIN32
	bool			getHandle();
	void			setHandle(bool xHandle);
#else
	HRESULT			getHandle();
	void			setHandle(HRESULT xHandle);

#endif

};