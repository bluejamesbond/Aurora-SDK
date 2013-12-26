#include "../../include/A2DExtLibs.h"
#include "../../include/A2DGLAbstractShader.h"

using namespace std;

A2DGLAbstractShader::A2DGLAbstractShader(A2DGLBackBuffer * xBackBuffer) : aBackBuffer(xBackBuffer){}

A2DGLAbstractShader::~A2DGLAbstractShader(){}

GLuint A2DGLAbstractShader::LoadShaders(const char * vertex_file_path,const char * fragment_file_path)
{

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
    	std::string Line = "";
    	while(getline(VertexShaderStream, Line))
        	VertexShaderCode += "\n" + Line;
    	VertexShaderStream.close();
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
	    std::string Line = "";
	    while(getline(FragmentShaderStream, Line))
	        FragmentShaderCode += "\n" + Line;
   		FragmentShaderStream.close();
}



	GLint Result = GL_FALSE;
	int InfoLogLength;



	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);




	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);




	// Link the program
	fprintf(stdout, "Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);


	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

HRESULT A2DGLAbstractShader::CreateResources(void * xArgs[])
{
	//
}

void A2DGLAbstractShader::Render() // Render should be defined seperately but called inside Update
{
	//
}

HRESULT A2DGLAbstractShader::LoadFromFile(LPCWSTR  xFilename)
{
	LoadShaders(...);
}

HRESULT A2DGLAbstractShader::CreateBlendStates()
{
	//
}

void A2DGLAbstractShader::SysOut(ID3D10Blob * xErrorMessage, LPCWSTR * xFilename)
{
	//
}

HRESULT A2DGLAbstractShader::Initialize()
{
	glClear( GL_COLOR_BUFFER_BIT );	//LATER NEED TO ALLOW ACCESS TO PROPER HANDLES/VARS
    // Use our shader
    glUseProgram(programID);
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(vertexPosition_modelspaceID);}

void A2DGLAbstractShader::Deinitialize()
{
	glDisableVertexAttribArray(vertexPosition_modelspaceID);
    glDisableVertexAttribArray(vertexColorID);
    glDeleteProgram(programID);
}

LPCWSTR A2DGLAbstractShader::GetClass()
{
	return L"A2DGLAbstractShader";
}

LPCWSTR A2DGLAbstractShader::ToString()
{
	return L"A2DGLAbstractShader";
}

bool A2DGLAbstractShader::operator==(A2DAbstract * xAbstract)
{
	return false;
}