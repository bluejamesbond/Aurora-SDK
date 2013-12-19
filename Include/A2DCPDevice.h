class A2DCPDevice
{
public:
	A2DCPDevice());

	~A2DCPDevice();
private:
#ifndef WIN32
	// code for X11
	HDC  			aDev;
#else
	//  code for Windows
	ID3D10Device	aDev;
#endif

public:
	//mutators and accessors

#ifndef WIN32
	HDC				getHandle();
	void			setHandle(HDC xDev);
#else
	ID3D10Device	getHandle();
	void			setHandle(ID3D10Device xDev);

#endif

};