class A2DCPString
{
public:
	A2DCPString();

	~A2DCPString();
private:
#ifndef WIN32
	// code for X11
	string			aString;
#else
	//  code for Windows
	LPCWSTR			aString;
#endif

public:
	//mutators and accessors

#ifndef WIN32
	string			getString();
	void			setString(string xString);
#else
	LPCWSTR			getString();
	void			setString(LPCWSTR xString);

#endif

};