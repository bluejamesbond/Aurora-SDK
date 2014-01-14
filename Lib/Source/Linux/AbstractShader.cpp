#include "../../../Include/Linux/ExtLibs.h"
#include "../../../Include/Linux/AbstractShader.h"

using namespace A2D;

AbstractShader::AbstractShader() {}

AbstractShader::~AbstractShader()
{

}

void AbstractShader::setVShader(char * xshader)
{
    vshadername = xshader;
}

void AbstractShader::setFShader(char * xshader)
{
    fshadername = xshader;
}

HRESULT AbstractShader::initialize()
{
    //set shader path?
        //temp
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

    //load all necessary textures with corresponding ID's, need to allow multiple(?)
    TextureID  = glGetUniformLocation(programID, "basic_texture");

}

void AbstractShader::renderShader()
{
    // Use our shader
    glUseProgram(programID);

    //might need texture::render to come here

    // Set our "myTextureSampler" sampler to user Texture Unit 0
    glUniform1i(TextureID, 0);

}
