
#include "../../../Include/Linux/ExtLibs.h"
#include "../../../Include/Linux/QuadFactory.h"
#include "../../../Include/Linux/GLShaderUtils.h"
#include "../../../Include/Linux/Common.h"

using namespace A2D;

QuadFactory::QuadFactory(Dims * xWindowDims)
{
	SYSOUT_STR("[QuadFactory] Created QuadFactory");
    aWindowDims = xWindowDims;

}

QuadFactory::~QuadFactory()
{
    glDeleteBuffers(1, &aVertexBuffer);
}

void QuadFactory::setDepth(float xZ)
{
	aDepth = xZ;
}

HRESULT QuadFactory::updateVertexBuffer(QuadData<TextureVertex> * xQuadData, Rect * xRect, Texture * xTexture, bool xRepeat)
{
    TextureVertex * vertices = xQuadData->aVertices;

    float XOffset = aConstraints.aX + xRect->aX;
    float YOffset = aConstraints.aY + xRect->aY;
    float RelativeXOffset = (XOffset/aWindowDims->aWidth) * 2;
    float RelativeYOffset = (YOffset/aWindowDims->aHeight) * 2;
    float RelativeWidth = (xRect->aWidth/aWindowDims->aWidth) * 2;
    float RelativeHeight = (xRect->aHeight/aWindowDims->aHeight) * 2;

    aTexture = xTexture;

    Rect  constraints = aConstraints;
    float relconstrX = (constraints.aX/aWindowDims->aWidth) * 2;
    float relconstrY = (constraints.aY/aWindowDims->aHeight) * 2;
    float relconstrWidth = (constraints.aWidth/aWindowDims->aWidth) * 2;
    float relconstrHeight = (constraints.aHeight/aWindowDims->aHeight) * 2;

    Rect * textureClip = aTexture->GetClip();

    float rectX = xRect->aX;
    float rectY = xRect->aY;
    float rectWidth = xRect->aWidth;
    float rectHeight = xRect->aHeight;

    if (rectX >= constraints.aWidth || rectY >= constraints.aHeight){return S_OK;}
    if ((XOffset >= aWindowDims->aWidth) || (YOffset >= aWindowDims->aHeight)){return S_OK;}


    //vertex values.
    GLfloat ConstbottomleftX = -1.0 + RelativeXOffset;
    GLfloat ConstbottomleftY = max(max(1.0-relconstrY-relconstrHeight,1.0-RelativeHeight-RelativeYOffset), -1.0);
    GLfloat ConsttopleftX = -1.0 + RelativeXOffset;
    GLfloat ConsttopleftY = 1.0 - RelativeYOffset;
    GLfloat ConstbottomrightX = min(min(-1.0 + relconstrX + relconstrWidth, -1.0 + RelativeXOffset + RelativeWidth), 1.0);

    //but if it's beyond 1.0 we use this value ^ to crop texture
    GLfloat ConstbottomrightY =  max(max(1.0-relconstrY-relconstrHeight,1.0-RelativeHeight-RelativeYOffset), -1.0);
    GLfloat ConsttoprightX = min(min(-1.0 + relconstrX + relconstrWidth, -1.0 + RelativeXOffset + RelativeWidth), 1.0);
    GLfloat ConsttoprightY = 1.0 - RelativeYOffset;

    //safety conditionals
    if(xRect->aX<0){ConstbottomleftX = -1.0 + constraints.aX; ConsttopleftX = -1.0 + constraints.aX;}
    if(xRect->aY<0){ConsttopleftY = 1 - constraints.aY; ConsttoprightY= ConsttopleftY;}


    // Texture values-first check if repeat, then check if
    // smaller than xRect, then check what portion is in constraints
    if(xRepeat)
    {
        aTexture->State = GL_REPEAT;
    }

    // calculate loss (0 - 1 scale) if quad is beyond
    // constraint
    float textureWidth = textureClip->aWidth;
    float textureHeight = textureClip->aHeight;

    float leftloss=0, toploss=0, topleftX, topleftY,toprightX, toprightY, bottomleftX,bottomleftY, bottomrightX, bottomrightY;

    if (rectX<0)
    {
        leftloss = (rectX * -1) / rectWidth;
    }

    if (rectY<0)
    {
        toploss = 1-((rectY* -1)/ rectHeight);
    }

	bottomleftX = 0.0f;
	topleftY = 1.0f;
	topleftX = 0.0f;
	toprightY = 1.0f;
	bottomleftY = ((textureHeight>=rectHeight)?(1-(rectHeight/textureHeight)):((xRepeat)?(-(rectHeight/textureHeight) + 1):0.0f));
	bottomrightY = bottomleftY;
	toprightX = ((textureWidth>=rectWidth)?(rectWidth/textureWidth):((xRepeat)?(rectWidth/textureWidth):1.0f));
	bottomrightX = toprightX;

	//right case
	if((rectX+rectWidth)>constraints.aWidth)
	{
		toprightX = ((textureWidth>=(rectWidth-(rectWidth + rectX - constraints.aWidth)))?((-rectX+constraints.aWidth)/textureWidth):((xRepeat)?((-rectX+constraints.aWidth)/textureWidth):1.0f));
		bottomrightX = toprightX;
	}

	//bottom case
	if((rectY+rectHeight)>constraints.aHeight)
	{
		bottomrightY = ((textureHeight>=(rectHeight-(rectHeight + rectY - constraints.aHeight)))?1-((-rectY+constraints.aHeight)/textureHeight):((xRepeat)?-((-rectY + constraints.aHeight)/textureHeight)+1.0f:0.0f));
		bottomleftY = bottomrightY;
	}

	//left case
	if(rectX < 0)
	{
		topleftX = leftloss;
		bottomleftX = topleftX;
	}

	//top case
	if(rectY < 0)
	{
		topleftY = toploss;
		toprightY = topleftY;
	}

	//WINDOW SCOPE
	//right case
	if(XOffset + rectWidth > aWindowDims->aWidth && XOffset + constraints.aWidth >= aWindowDims->aWidth)   //Need to factor in if xRect > constraint
	{
		toprightX = ((textureWidth>=(rectWidth-(rectWidth + XOffset - aWindowDims->aWidth)))?((-XOffset + aWindowDims->aWidth)/textureWidth):((xRepeat)?((-XOffset + aWindowDims->aWidth)/textureWidth):1.0f));
		bottomrightX = toprightX;
	}

	//bottom case
	if((YOffset + rectHeight) > aWindowDims->aHeight && (YOffset + constraints.aHeight >= aWindowDims->aHeight))
	{
		bottomrightY = ((textureHeight>=(rectHeight-(rectHeight + YOffset - aWindowDims->aHeight)))?1-((-YOffset + aWindowDims->aHeight)/textureHeight):((xRepeat)?-((-YOffset + aWindowDims->aHeight)/textureHeight)+1.0f:0.0f));
		bottomleftY = bottomrightY;
	}

	//left case
	if(constraints.aX < 0 && rectX < -(constraints.aX))
	{
		leftloss = (YOffset * -1) / rectWidth;
		topleftX = leftloss;
		bottomleftX = topleftX;
	}

	//top case
	if(constraints.aY < 0 && (rectY < -(constraints.aY)))
	{
		toploss = 1-((YOffset * -1)/ rectHeight);
		topleftY = toploss;
		toprightY = topleftY;
	}

    // Set up vertices
    vertices[0].m_position = GL3DPOSITION(ConsttopleftX, ConsttopleftY, aDepth);  // Top left.
    vertices[0].m_textCoord = GL3DTEXCOORD(topleftX, topleftY);

    vertices[1].m_position = GL3DPOSITION(ConstbottomrightX, ConstbottomrightY, aDepth);  // Bottom right.
    vertices[1].m_textCoord = GL3DTEXCOORD(bottomrightX, bottomrightY);

    vertices[2].m_position = GL3DPOSITION(ConstbottomleftX, ConstbottomleftY, aDepth);  // Bottom left.
    vertices[2].m_textCoord = GL3DTEXCOORD(bottomleftX, bottomleftY);

    vertices[3].m_position = GL3DPOSITION(ConsttopleftX, ConsttopleftY, aDepth);  // Top left.
    vertices[3].m_textCoord = GL3DTEXCOORD(topleftX, topleftY);

    vertices[4].m_position = GL3DPOSITION(ConsttoprightX, ConsttoprightY, aDepth);  // Top right.
    vertices[4].m_textCoord = GL3DTEXCOORD(toprightX, toprightY);

    vertices[5].m_position = GL3DPOSITION(ConstbottomrightX, ConstbottomrightY, aDepth);  // Bottom right.
    vertices[5].m_textCoord = GL3DTEXCOORD(bottomrightX, bottomrightY);

	// Lock the vertex buffer.
    // Allocate an OpenGL vertex array object.
	glGenVertexArrays(1, &xQuadData->m_vertexArrayId);

#define GLUINT(x)	static_cast<GLuint>(x)

	// Bind the vertex array object to store all the buffers and vertex attributes we create here.
	glBindVertexArray(GLUINT(xQuadData->m_vertexArrayId));

	// Generate an ID for the vertex buffer.
	glGenBuffers(1, &xQuadData->m_vertexArrayId);

	// Bind the vertex buffer and load the vertex (position, texture, and normal) data into the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, xQuadData->m_vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(VertexType), vertices, GL_DYNAMIC_DRAW);

	// Enable the three vertex array attributes.
	glEnableVertexAttribArray(0);  // Vertex position.
	glEnableVertexAttribArray(1);  // Texture coordinates.

	// Specify the location and format of the position portion of the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, GLUINT(xQuadData->m_vertexBufferId));
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(TextureVertex), 0);

	// Specify the location and format of the texture coordinate portion of the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, GLUINT(xQuadData->m_vertexBufferId));
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(TextureVertex), (unsigned char*) NULL + (3 * sizeof(float)));

	return S_OK;
}

void QuadFactory::renderQuad(GLuint& x_id, unsigned int xStride)
{
	// Bind the vertex array object that stored
    // all the information about the vertex and
    // index buffers.
	glBindVertexArray(x_id);

	// Render the vertex buffer using the index buffer.
	// FIXME Forced to 6 for now
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


}

bool QuadFactory::setConstraints(Rect * xConstraints, float xZ)
{
	aDepth = xZ;

    aConstraints = *xConstraints;

	return true;
}

HRESULT QuadFactory::initialize()
{
//	SAFELY(DXShapeUtils::CreateDefaultDynamicVertexBuffer<ColoredTextureVertex>(*aDXDevice, &aVertexBuffer, 6));

    GLfloat temp_vertices[] = {
            0.0f, 0.0f, aDepth,
            0.0f, 0.0f, aDepth,
            0.0f, 0.0f, aDepth,
            0.0f, 0.0f, aDepth,
            0.0f, 0.0f, aDepth,
            0.0f, 0.0f, aDepth,
           };
    g_vertex_buffer_data = temp_vertices;

    SYSOUT_STR("[QuadFactory] Testing initialization.");

	return S_OK;
}

LPCWSTR QuadFactory::getClass()
{
    return "QuadFactory";
}

LPCWSTR QuadFactory::toString()
{
    return "QuadFactory";
}
