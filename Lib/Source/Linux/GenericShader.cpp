#include "../../../Include/Linux/ExtLibs.h"
#include "../../../Include/Linux/GenericShader.h"

using namespace A2D;

GenericShader::GenericShader() {}

GenericShader::~GenericShader()
{
    glDeleteProgram(programID);
    glDeleteTextures(1, &TextureID);

}

void GenericShader::setVShader(char * xshader)
{
    vshadername = xshader;
}

void GenericShader::setFShader(char * xshader)
{
    fshadername = xshader;
}

void GenericShader::associateTexture(Texture * xTexture)
{
	SYSOUT_STR("[GenericShader] Called associateTexture");

    aTexture = xTexture;

    //load all necessary textures with corresponding ID's, need to allow multiple(?)
    TextureID  = glGetUniformLocation(programID, "basic_texture");
}


HRESULT GenericShader::initialize()
{
    //set shader path?
    //temp FOR TESTING
    if(vshadername == NULL)
    {
        vshadername = "/home/syk435/Testing Gl/GL-Test/SimpleVertexShader.vertexshader";
    }

    if(fshadername == NULL)
    {
        fshadername = "/home/syk435/Testing Gl/GL-Test/SimpleFragmentShader.fragmentshader";
    }

    // create shaders , tie to "programid". Maybe later make more shaders and tie to different IDs
    programID = GLShaderUtils::LoadEffectFromFile(vshadername, fshadername);
}

void GenericShader::renderShader()
{
    // Use our shader
    glUseProgram(programID);

    //might need texture::render to come here
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, aTexture->tex);

    // Set our "myTextureSampler" sampler to user Texture Unit 0
    glUniform1i(TextureID, 0);

}
