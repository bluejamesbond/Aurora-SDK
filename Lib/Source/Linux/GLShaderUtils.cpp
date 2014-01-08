
#include "../../../Include/Linux/ExtLibs.h"
#include "../../../Include/Linux/GLShaderUtils.h"

using namespace A2D;
using namespace std;

GLuint GLShaderUtils::LoadEffectFromFile(LPCWSTR xVertexShader,LPCWSTR xFragmentShader)
{
    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(xVertexShader, std::ios::in);
    if(VertexShaderStream.is_open()){
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    }else{
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", xVertexShader);
        getchar();
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(xFragmentShader, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::string Line = "";
        while(getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }



    GLint Result = GL_FALSE;
    int InfoLogLength;



    // Compile Vertex Shader
    printf("Compiling shader : %s\n", xVertexShader);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }



    // Compile Fragment Shader
    printf("Compiling shader : %s\n", xFragmentShader);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }



    // Link the program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

void GLShaderUtils::_check_gl_error(const char *file, int line)
{
        GLenum err (glGetError());

        while(err!=GL_NO_ERROR) {
                char* error;

                switch(err) {
                        case GL_INVALID_OPERATION:      error="INVALID_OPERATION";      break;
                        case GL_INVALID_ENUM:           error="INVALID_ENUM";           break;
                        case GL_INVALID_VALUE:          error="INVALID_VALUE";          break;
                        case GL_OUT_OF_MEMORY:          error="OUT_OF_MEMORY";          break;
                        case GL_INVALID_FRAMEBUFFER_OPERATION:  error="INVALID_FRAMEBUFFER_OPERATION";  break;
                }

                std::cerr << "GL_" << error <<" - "<<file<<":"<<line<<std::endl;
                err=glGetError();
        }
}

/*
void DXShaderUtils::SysOut(ID3D10Blob * xErrorMessage, LPCWSTR * xFilename){}

HRESULT DXShaderUtils::CreatePNGCompatibleBlendStates(ID3D10Device * aDevice, ID3D10BlendState ** xBlendState, ID3D10BlendState ** xBlendDisabledState)
{
	D3D10_BLEND_DESC blendDesc;

	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.BlendEnable[0] = TRUE;
	blendDesc.RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;
	blendDesc.SrcBlend = D3D10_BLEND_SRC_ALPHA;
	blendDesc.DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
	blendDesc.BlendOp = D3D10_BLEND_OP_ADD;
	blendDesc.SrcBlendAlpha = D3D10_BLEND_ONE;
	blendDesc.DestBlendAlpha = D3D10_BLEND_ZERO;
	blendDesc.BlendOpAlpha = D3D10_BLEND_OP_ADD;

	SAFELY(aDevice->CreateBlendState(&blendDesc, xBlendState));

	blendDesc.BlendEnable[0] = FALSE;

	SAFELY(aDevice->CreateBlendState(&blendDesc, xBlendDisabledState));

	return S_OK;
}

HRESULT DXShaderUtils::loadTechniqueFromEffect(ID3D10Device * xDevice, ID3D10Effect * xEffect, ID3D10InputLayout ** xLayout, ID3D10EffectTechnique ** xTechnqiue, D3D10_INPUT_ELEMENT_DESC * xPolygonLayout, LPCSTR xName, unsigned int xElements)
{
	D3D10_PASS_DESC passDesc;

	// Get a pointer to the technique inside the shader.
	NULLCHECK((*xTechnqiue = xEffect->GetTechniqueByName(xName)));
	
	// Get the description of the first pass 
	// described in the shader technique.
	(*xTechnqiue)->GetPassByIndex(0)->GetDesc(&passDesc);

	// Create the input layout.
	SAFELY(xDevice->CreateInputLayout(xPolygonLayout, xElements, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, xLayout));

	return S_OK;
}

*/
