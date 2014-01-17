////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ABSTRACTSHADER_H__
#define __ABSTRACTSHADER_H__

//+-----------------------------------------------------------------------------
//
//  Class: 
//      TEXTURESHADER
//
//  Synopsis:
//      Texture quad.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////

#include "ExtLibs.h"
#include "GLShaderUtils.h"
#include "Texture.h"
#include "Common.h"

namespace A2D {

	////////////////////////////////////////////////////////////////////////////////
	// DECLARATION
	////////////////////////////////////////////////////////////////////////////////

	class AbstractShader
	{
	public:

        AbstractShader();
		virtual ~AbstractShader();

	protected:


	private:
        //variables
        char                    *       vshadername;
        char                    *       fshadername;

	public:
        //variables
        GLuint                          programID;
        GLuint                          TextureID;
        Texture                 *       aTexture;

        //methods
		void							renderShader();
        void                            setVShader(char * xshader);
        void                            setFShader(char * xshader);
        void                            associateTexture(Texture * xTexture);

		//////////////////////////////////////////////////////////
		// ABSTRACT IMPLEMENTATION
		//////////////////////////////////////////////////////////

		virtual HRESULT	                initialize();

	};
}

#endif
