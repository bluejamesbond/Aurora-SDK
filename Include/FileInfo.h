////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __FILEINFO_H__
#define __FILEINFO_H__

//+-----------------------------------------------------------------------------
//
//  Class:
//      FILEINFO
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "Common.h"
#include "Abstract.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// FORWARD DECLARATIONS
	////////////////////////////////////////////////////////////////////////////////

	class	Abstract;

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class FileInfo : public Abstract
	{

	public:

		FileInfo(LPCWSTR xFileName);
		~FileInfo();

	private:

		D3DXIMAGE_INFO		  * 	aFileInfo;
		LPCWSTR                     aFileName;
		
	public:

		float						getHeight();
		float						getWidth();
		int							getDepth();
		int							getMipLevels();
		D3DXIMAGE_INFO		*		getInfo();

	public:

		virtual HRESULT                 initialize();
		virtual LPCWSTR                 getClass();
		virtual LPCWSTR                 toString();

	};
}

#endif
