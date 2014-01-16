
#include "../../../Include/Linux/ExtLibs.h"
#include "../../../Include/Linux/QuadFactory.h"

using namespace A2D;

QuadFactory::QuadFactory(Dims * xWindowDims)
{
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
/*

HRESULT QuadFactory::updateVertexBuffer(QuadData<ColoredTextureVertex> * xQuadData, Rect * xRect, Texture * xTexture, Paint * xPaint, bool xRepeat)
{
	Rect& constraints = aConstraints;
	Rect * textureClip = xTexture->GetClip();
	
	int textureDimsChange = 0;
	int textureClipChange = 0;
	int rectChange = 0;
	int imagePropertiesChange = 0;

	float rectX = xRect->aX;
	float rectY = xRect->aY;
	float rectWidth = xRect->aWidth;
	float rectHeight = xRect->aHeight;

	if (rectX >= constraints.aWidth || rectY >= constraints.aHeight)	return S_OK;

	float calcLeft, calcTop, calcRight, calcBottom, calcHeight, calcWidth,
		left, right, top, bottom, texLeft, texTop, texRight, texBottom, texelLeft, texelTop,
		texelRight, texelBottom,
		textureWidth = textureClip->aWidth,
		textureHeight = textureClip->aHeight,
		depth = aDepth;

	ColoredTextureVertex * vertices = xQuadData->aVertices;
	void * mappedVertices = 0;

	calcLeft = max(rectX, 0);
	calcTop = max(rectY, 0);
	calcRight = min(constraints.aWidth, rectX > 0 ? rectWidth : rectX + rectWidth);
	calcBottom = min(constraints.aHeight, rectY > 0 ? rectHeight : rectY + rectHeight);

	calcHeight = calcBottom - calcTop;
	calcWidth = calcRight - calcLeft;

	left = -aWindowDims->aWidth / 2 + (constraints.aX + calcLeft);
	right = left + calcWidth;
	top = aWindowDims->aHeight / 2 - (constraints.aY + calcTop);
	bottom = top - calcHeight;

	texLeft = rectX > 0 ? 0.0f : abs(rectX);
	texTop = rectY > 0 ? 0.0f : abs(rectY);
	texRight = calcRight < constraints.aWidth ? rectWidth : calcWidth;
	texBottom = calcBottom < constraints.aHeight ? rectHeight : calcHeight;

	texelLeft = xRepeat ? texLeft / textureWidth : texLeft / rectWidth;
	texelTop = xRepeat ? texTop / textureHeight : texTop / rectHeight;
	texelRight = xRepeat ? (calcWidth + texLeft) / textureWidth : texRight / rectWidth;
	texelBottom = xRepeat ? (calcHeight + texTop) / textureHeight : texBottom / rectHeight;
	
	Color3D& topLeftColor = xPaint->aStart;
	Color3D& topRightColor = xPaint->aStart;
	Color3D& bottomLeftColor = xPaint->aEnd;
	Color3D& bottomRightColor = xPaint->aEnd;

	// Set up vertices
	vertices[0].position = D3DXVECTOR3(left, top, depth);  // Top left.
	vertices[0].texture = D3DXVECTOR2(texelLeft, texelTop);
	vertices[0].color = D3DXVECTOR4(topLeftColor.aRed, topLeftColor.aGreen, topLeftColor.aBlue, topLeftColor.aAlpha);

	vertices[1].position = D3DXVECTOR3(right, bottom, depth);  // Bottom right.
	vertices[1].texture = D3DXVECTOR2(texelRight, texelBottom);
	vertices[1].color = D3DXVECTOR4(bottomRightColor.aRed, bottomRightColor.aGreen, bottomRightColor.aBlue, bottomRightColor.aAlpha);

	vertices[2].position = D3DXVECTOR3(left, bottom, depth);  // Bottom left.
	vertices[2].texture = D3DXVECTOR2(texelLeft, texelBottom);
	vertices[2].color = D3DXVECTOR4(bottomLeftColor.aRed, bottomLeftColor.aGreen, bottomLeftColor.aBlue, bottomLeftColor.aAlpha);

	vertices[3].position = D3DXVECTOR3(left, top, depth);  // Top left.
	vertices[3].texture = D3DXVECTOR2(texelLeft, texelTop);
	vertices[3].color = D3DXVECTOR4(topLeftColor.aRed, topLeftColor.aGreen, topLeftColor.aBlue, topLeftColor.aAlpha);

	vertices[4].position = D3DXVECTOR3(right, top, depth);  // Top right.
	vertices[4].texture = D3DXVECTOR2(texelRight, texelTop);
	vertices[4].color = D3DXVECTOR4(topRightColor.aRed, topRightColor.aGreen, topRightColor.aBlue, topRightColor.aAlpha);

	vertices[5].position = D3DXVECTOR3(right, bottom, depth);  // Bottom right.
	vertices[5].texture = D3DXVECTOR2(texelRight, texelBottom);
	vertices[5].color = D3DXVECTOR4(bottomRightColor.aRed, bottomRightColor.aGreen, bottomRightColor.aBlue, bottomRightColor.aAlpha);

	// Lock the vertex buffer.
	SAFELY(xQuadData->aVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, static_cast<void**>(&mappedVertices)));

	// Copy data using SSE2 accelerated method
	QuadFactory::memcpySSE2QuadVertex(static_cast<ColoredTextureVertex*>(mappedVertices), vertices);

	// Unlock the vertex buffer.
	xQuadData->aVertexBuffer->Unmap();

	return S_OK;

}
*/
HRESULT QuadFactory::updateVertexBuffer(QuadData<float> * xQuadData, Rect * xRect, Texture * xTexture, bool xRepeat)
{
    //aCONSTRAINT VALUES ARE RELATIVE TO WINDOW, BUT ARE xRECT VALUES RELATIVE TO WINDOW OR CONSTRAINT?
    //LIKE IS aX = 15 AN OFFSET OF LEFT SIDE OF WINDOW OR CONSTRAINT???
    //##############~~~~!!!!!!!!!!!
    float XOffset = aConstraints.aX + xRect->aX;
    float YOffset = aConstraints.aY + xRect->aY;
    float RelativeXOffset = (XOffset/aWindowDims->aWidth) * 2;
    float RelativeYOffset = (YOffset/aWindowDims->aHeight) * 2;
    float RelativeWidth = (xRect->aWidth/aWindowDims->aWidth) * 2;
    float RelativeHeight = (xRect->aHeight/aWindowDims->aHeight) * 2;

    aTexture = xTexture;
	Rect& constraints = aConstraints;
    float relconstrX = (constraints.aX/aWindowDims->aWidth) * 2;
    float relconstrY = (constraints.aY/aWindowDims->aHeight) * 2;
    float relconstrWidth = (constraints.aWidth/aWindowDims->aWidth) * 2;
    float relconstrHeight = (constraints.aHeight/aWindowDims->aHeight) * 2;

    Rect * textureClip = aTexture->GetClip();

	float rectX = xRect->aX;
	float rectY = xRect->aY;
	float rectWidth = xRect->aWidth;
	float rectHeight = xRect->aHeight;

	if (rectX >= constraints.aWidth || rectY >= constraints.aHeight)	return S_OK;
    if (XOffset >= aWindowDims->aWidth || YOffset >= aWindowDims->aHeight)    return S_OK;
	// Compare using built in accelerated-function
    //rectChange = memcmp(&xQuadData->aPreviousRect, xRect, sizeof(Rect));
    //imagePropertiesChange = memcmp(&xQuadData->aPreviousImageProperties, xImageProperties, sizeof(ImageProperties));

    //if (!(rectChange | imagePropertiesChange) && !aContraintsChanged)	return hr;

	// Transfer all previous constraints over using accelerated functions
    //x_aligned_memcpy_sse2(&xQuadData->aPreviousRect, xRect, sizeof(Rect));
//	x_aligned_memcpy_sse2(&xQuadData->aPreviousImageProperties, xImageProperties, sizeof(Rect));

    //*************do later for optimization ^

#define min(a, b)                                             ((a > b ) ? b : a)
#define max(a, b)                                             ((a < b ) ? b : a)


    g_vertex_buffer_data = xQuadData->aVertices;

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

    GLfloat * vcoords = new GLfloat[18];
    vcoords[0] = ConstbottomleftX;
    vcoords[1] = ConstbottomleftY;
    vcoords[2] = (GLfloat)aDepth;
    vcoords[3] = ConsttopleftX;
    vcoords[4] = ConsttopleftY;
    vcoords[5] = (GLfloat)aDepth;
    vcoords[6] = ConstbottomrightX;
    vcoords[7] = ConstbottomrightY;
    vcoords[8] = (GLfloat)aDepth;
    vcoords[9] = ConsttoprightX;
    vcoords[10] = ConsttoprightY;
    vcoords[11] = (GLfloat)aDepth;
    vcoords[12] = ConsttopleftX;
    vcoords[13] = ConsttopleftY;
    vcoords[14] = (GLfloat)aDepth;
    vcoords[15] = ConstbottomrightX;
    vcoords[16] = ConstbottomrightY;
    vcoords[17] = (GLfloat)aDepth;

    g_vertex_buffer_data = vcoords;

    //Texture values-first check if repeat, then check if smaller than xRect, then check what portion is in constraints
    if(xRepeat)
    {
        aTexture->State = GL_REPEAT;
    }
        //calculate loss (0 - 1 scale) if quad is beyond constraint
    float textureWidth = textureClip->aWidth;
    float textureHeight = textureClip->aHeight;

    float leftloss=0, rightloss=0, toploss=0, bottomloss=0,topleftX,topleftY,toprightX, toprightY, bottomleftX,bottomleftY, bottomrightX, bottomrightY;

    if (rectX<0)
    {
        leftloss = (rectX * -1) / rectWidth;
    }

    if((rectX + rectWidth)>aConstraints.aWidth)
    {
        rightloss = ((rectX + rectWidth)-aConstraints.aWidth) / rectWidth;
    }

    if (rectY<0)
    {
        toploss = (rectY* -1)/ rectHeight;
    }

    if((rectY+ rectHeight)>aConstraints.aHeight)
    {
        bottomloss = ((rectY + rectHeight)-aConstraints.aHeight) / rectHeight;
    }
    //TEXELS

    //first if xRect completely in aConstraint
    //if((rectX> 0) && (rectY>0))

    //BASE: center-center case
        //if(((rectX+rectWidth)<=constraints.aWidth) && ((rectY+rectHeight)<=constraints.aHeight))
        //{
            bottomleftX = 0.0f;
            topleftY = 1.0f;
            topleftX = 0.0f;
            toprightY = 1.0f;
            bottomleftY = ((textureHeight>=rectHeight)?(1-(rectHeight/textureHeight)):((xRepeat)?(-(rectHeight/textureHeight) + 1):0.0f));
            bottomrightY = bottomrightY;
            toprightX = ((textureWidth>=rectWidth)?(rectWidth/textureWidth):((xRepeat)?(rectWidth/textureWidth):1.0f));
            bottomrightX = toprightX;
        //}
        //}
        //right case
        if((rectX+rectWidth)>constraints.aWidth)
        {
            toprightX = ((textureWidth>=(rectWidth-(rectWidth + rectX - constraints.aWidth)))?((-rectX+constraints.aWidth)/textureWidth):((xRepeat)?((-rectX+constraints.aWidth)/textureWidth):1.0f));
            bottomrightX = toprightX;
        }

        //bottom case
        if((rectY+rectHeight)>constraints.aHeight)
        {
            bottomrightY = ((textureHeight>=(rectHeight-(rectHeight + rectY - constraints.aHeight)))?1-((-rectY+constraints.aWidth)/textureHeight):((xRepeat)?-((-rectY + constraints.aHeight)/textureWidth)+1:1.0f));
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

        GLfloat * tcoords = new GLfloat[12];
        tcoords[0] = bottomleftX;
        tcoords[1] = bottomleftY;
        tcoords[2] = topleftX;
        tcoords[3] = topleftY;
        tcoords[4] = bottomrightX;
        tcoords[5] = bottomrightY;
        tcoords[6] = toprightX;
        tcoords[7] = toprightY;
        tcoords[8] = topleftX;
        tcoords[9] = topleftY;
        tcoords[10] = bottomrightX;
        tcoords[11] = bottomrightY;

    aTexture->texcoords = tcoords;

	// Lock the vertex buffer.
    glGenBuffers(1, &aVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, aVertexBuffer);

	// Unlock the vertex buffer.
//	xQuadData->aVertexBuffer->Unmap();

	return S_OK;

}
/*
HRESULT QuadFactory::updateVertexBuffer(QuadData<ColorVertex> * xQuadData, Rect * xRect, Paint * xPaint)
{
    //(x/realwidth)*2 = xoffset
    //-1 + xoffset = newstart
    //(width/realwidth)*2 = width
    //newstart + width = leftmost
    //do same for height, put in code for appropriate points

    Rect& constraints = aConstraints;

	float rectX = xRect->aX;
	float rectY = xRect->aY;
	float rectWidth = xRect->aWidth;
	float rectHeight = xRect->aHeight;

	if (rectX >= constraints.aWidth || rectY >= constraints.aHeight)	return S_OK;
	
	float calcLeft, calcTop, calcRight, calcBottom, calcHeight, calcWidth,
		left, right, top, bottom, depth = aDepth;

     = xQuadData->aVertices;

	calcLeft = max(rectX, 0);
	calcTop = max(rectY, 0);
	calcRight = min(constraints.aWidth, rectX > 0 ? rectWidth : rectX + rectWidth);
	calcBottom = min(constraints.aHeight, rectY > 0 ? rectHeight : rectY + rectHeight);

	calcHeight = calcBottom - calcTop;
	calcWidth = calcRight - calcLeft;

	left = -aWindowDims->aWidth / 2 + (constraints.aX + calcLeft);
	right = left + calcWidth;
	top = aWindowDims->aHeight / 2 - (constraints.aY + calcTop);
	bottom = top - calcHeight;

	// Set up vertices

	// Lock the vertex buffer.

	// Copy data using SSE2 accelerated method

	// Unlock the vertex buffer.

	return S_OK;

}
*/
void QuadFactory::renderQuad()
{
    // Set the vertex buffer to active in the input
	// assembler so it can be rendered.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, aVertexBuffer);

    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

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
