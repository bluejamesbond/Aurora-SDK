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

		// Constructor
		FileInfo(LPCWSTR * xFileName);

		// Deconstructor
		~FileInfo();

	private:

		// Variables
		D3DXIMAGE_INFO		  * 	aFileInfo;
		LPCWSTR               *     aFileName;


	public:
		// Accessors
		float						GetHeight();
		float						GetWidth();
		int							GetDepth();
		int							GetMipLevels();
		D3DXIMAGE_INFO		*		GetInfo();

	public:

		// Implementation
		// { ABSTRACT }
		virtual HRESULT                 initialize();
		virtual void                    Deinitialize();
		virtual LPCWSTR                 getClass();
		virtual LPCWSTR                 toString();
		virtual bool                    operator==(Abstract * xAbstract);

	};
}

#endif
