#include "../Core/Common.h"
#include "ExtLibs.h"
//+-----------------------------------------------------------------------------
//
//  Class:
//      COMMON
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// DEFINE
////////////////////////////////////////////////////////////////////////////////

// Debugging
#ifdef _WIN32

#define SYSOUT_FLT(x)										  _RPT1( 0, "[Aurora -SDK] %f\n", x )
#define SYSOUT_INT(x)										  _RPT1( 0, "[Aurora -SDK] %d\n", x )
#define SYSOUT_HEX(x)										  _RPT1( 0, "[Aurora -SDK] 0x%X\n", x )
#define SYSOUT_STR(x)										  _RPT1( 0, "[Aurora -SDK] %s\n", x )
#define SYSOUT_F(f, ...)									  _RPT1( 0, "[Aurora -SDK] " f "\n", __VA_ARGS__ )

#endif

/*
#ifndef GLERROR_H
#define GLERROR_H

#define check_gl_error() _check_gl_error(__FILE__,__LINE__)

#endif // GLERROR_H
void _check_gl_error(const char *file, int line) {
        GLenum err (glGetError());

        while(err!=GL_NO_ERROR) {
                std::string error;

                switch(err) {
                        case GL_INVALID_OPERATION:      error="INVALID_OPERATION";      break;
                        case GL_INVALID_ENUM:           error="INVALID_ENUM";           break;
                        case GL_INVALID_VALUE:          error="INVALID_VALUE";          break;
                        case GL_OUT_OF_MEMORY:          error="OUT_OF_MEMORY";          break;
                        case GL_INVALID_FRAMEBUFFER_OPERATION:  error="INVALID_FRAMEBUFFER_OPERATION";  break;
                }

                std::cerr << "GL_" << error.c_str() <<" - "<<file<<":"<<line<<std::endl;
                err=glGetError();
        }
}

#define SYSOUT_FLT(x)										  fprintf(stderr, "Failiure ");check_gl_error()
#define SYSOUT_INT(x)										  fprintf(stderr, "Failiure ");check_gl_error()
#define SYSOUT_HEX(x)										  fprintf(stderr, "Failiure ");check_gl_error()
#define SYSOUT_STR(x)										  fprintf(stderr, "Failiure ");check_gl_error()
#define SYSOUT_F(f, ...)									  fprintf(stderr, "Failiure ");check_gl_error()


#define FLT_255			255.0f

#define G_SAFELY(hr)    if(hr != 0) { SYSOUT_STR("Failure detected");	return; }
#define SAFELY(hr)		if(hr != 0){ SYSOUT_STR("Failure detected");return E_FAIL; }
#define NULLCHECK(hr)	if(!hr){ SYSOUT_STR("Failure detected"); return E_FAIL; }
#define	DESTROY(x)		if(x) { delete x; x = 0; }
#define D3DDESTROY(x)   if(x) { x->Release(); x = 0; }
#define THREAD_DESTROY(x)  if(x) { x->stop(); delete x; x = 0; }
#define FLOAT(x)		static_cast<float>(x)
#define INT(x)			static_cast<int>(x)
#define UINT(x)			static_cast<UINT>(x)

#define ifneg(x)		(x < 0 ? x : 0)
*/

