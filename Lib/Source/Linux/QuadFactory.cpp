
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

    //vertex values. put in safety conditionals later***********************

    float ConstbottomleftX = -1.0 + RelativeXOffset;
        if(xRect->aX<0){ConstbottomleftX = -1;}
    float ConstbottomleftY = max(max(1.0-aConstraints.aY-aConstraints.aHeight,1.0-RelativeHeight-RelativeYOffset), -1.0);
    float ConsttopleftX = -1.0 + RelativeXOffset;
    float ConsttopleftY = 1.0 - RelativeYOffset;
    float ConstbottomrightX = min(min(-1.0 + aConstraints.aX + aConstraints.aWidth, -1.0 + RelativeXOffset + RelativeWidth), 1.0);
    //but if it's beyond 1.0 we use this value ^ to crop texture
    float ConstbottomrightY =  max(max(1.0-aConstraints.aY-aConstraints.aHeight,1.0-RelativeHeight-RelativeYOffset), -1.0);
    float ConsttoprightX = min(min(-1.0 + aConstraints.aX + aConstraints.aWidth, -1.0 + RelativeXOffset + RelativeWidth), 1.0);
    float ConsttoprightY = 1.0 - RelativeYOffset;

    //Texture values-first check if repeat, then check if smaller than xRect, then check what portion is in constraints
    if(xRepeat)
    {
        aTexture->State = GL_REPEAT;
    }
        //calculate loss (0 - 1 scale) if quad is beyond constraint
    float textureWidth = textureClip->aWidth;
    float textureHeight = textureClip->aHeight;

    float leftloss=0, rightloss=0, toploss=0, bottomloss=0,topleftX,topleftY,toprightX, toprightY, bottomleftX
          ,bottomleftY, bottomrightX, bottomrightY;

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
    if(xRepeat){aTexture->State = GL_REPEAT;}

    //first if xRect completely in aConstraint
    //if((rectX> 0) && (rectY>0))

    //BASE: center-center case
        //if(((rectX+rectWidth)<=constraints.aWidth) && ((rectY+rectHeight)<=constraints.aHeight))
        //{
            bottomleftX = 0.0f;
            topleftY = 1.0f;
            topleftX = 0.0f;
            toprightY = 1.0f;
            bottomleftY = ((textureHeight>=rectHeight)?(1-(rectHeight/textureHeight)):(-(rectHeight/textureHeight) + 1));
            bottomrightY = bottomrightY;
            toprightX = ((textureWidth>=rectWidth)?(rectWidth/textureWidth):(rectWidth/textureWidth));
            bottomrightX = toprightX;
        //}
        //}
        //right case
        if((rectX+rectWidth)>constraints.aWidth)
        {
            toprightX = ((textureWidth>=(rectWidth-(rectWidth + rectX - constraints.aWidth)))?(rectWidth/textureWidth):(rectWidth/textureWidth));;
            bottomrightX = ;
        }


    //if smaller than xRect
    if((textureWidth < rectWidth))
    {
        if(xRepeat)
        {
            aTexture->State = GL_REPEAT;

            if(xRect->aX < 0)
            {
                topleftX =leftloss;
                toprightX = (1/(textureWidth/rectWidth));
                bottomleftX = leftloss;
                bottomrightX = (1/(textureWidth/rectWidth));
            }
            else if(textureWidth > (rectWidth-rectX))
            {
                topleftX = 0.0f;
                toprightX = (rectWidth-rectX)/(textureWidth);
                bottomleftX = 0.0f;
                bottomrightX = (rectWidth-rectX)/(textureWidth);
            }
            else
            {
                topleftX = 0.0f;
                toprightX =
            }

        }
        else
        {

        }
        //topright

    }

    //if larger than xRect/samesize





    /*
    float calcLeft, calcTop, calcRight, calcBottom, calcHeight, calcWidth,
        left, right, top, bottom, texLeft, texTop, texRight, texBottom, texelLeft, texelTop,
        texelRight, texelBottom,
        textureWidth = textureClip->aWidth,
        textureHeight = textureClip->aHeight,
        depth = aDepth;

    calcLeft = max(rectX, 0); //left relative to rect
    calcTop = max(rectY, 0);  //right relative to rect
    calcRight = min(constraints.aWidth, rectX > 0 ? rectWidth : rectX + rectWidth); //
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
*/
	// Set up vertices

//	vertices[0].position = D3DXVECTOR3(left, top, depth);  // Top left.
//	vertices[0].texture = D3DXVECTOR2(texelLeft, texelTop);

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
	unsigned int offset = 0;

    // Set the vertex buffer to active in the input
	// assembler so it can be rendered.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

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
