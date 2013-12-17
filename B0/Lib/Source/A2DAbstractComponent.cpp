
#include "../../Include/A2DExtLibs.h"
#include "../../Include/A2DAbstractComponent.h"
#include "../../Include/A2DGraphics.h"

A2DAbstractComponent::A2DAbstractComponent() : 
aOptWidth(0),
aOptHeight(0),
aOptLeft(0),
aOptTop(0),
aParentComp(NULL),
aGraphics(NULL) {}

A2DAbstractComponent::~A2DAbstractComponent(){}

void A2DAbstractComponent::Update()
{
	A2DGraphics * graphics = this->GetGraphics();

	// Create resources must be called first!!!
	if (graphics == NULL)	return;

	graphics->SetMode(A2D_GRAPHICS_MODE_RENDER);

	// Calling the render algorithm
	// -> Render component
	// -> Render its children on top
	// -> Render the border that overlays
	//    both of the previous renders.
	Render(graphics);
}

A2DGraphics * A2DAbstractComponent::GetGraphics()
{
	return aGraphics;
}
A2DAbstractComponent * A2DAbstractComponent::GetParent()
{
	return aParentComp;
}
float	A2DAbstractComponent::GetOptWidth()
{
	return aOptWidth;
}
float	A2DAbstractComponent::GetOptHeight()
{
	return aOptHeight;
}
float	A2DAbstractComponent::GetOptTop()
{
	return aOptTop;
}
float	A2DAbstractComponent::GetOptLeft()
{
	return aOptLeft;
}
void A2DAbstractComponent::SetBounds(float xOptLeft, float xOptTop, float xOptWidth, float xOptHeight)
{
	A2DGraphics * graphics = GetGraphics();
	
	aOptWidth = xOptWidth;
	aOptHeight = xOptHeight;
	aOptLeft = xOptLeft;
	aOptTop = xOptTop;

	if (graphics)
		graphics->Recalculate();
}

void A2DAbstractComponent::Render(A2DRenderData * xRenderData)
{
	// Render the current component
	RenderComponent(xRenderData);

	// This will call children updates
	// This is sort of saying: (Render <==> Update)
	RenderChildren(xRenderData);

	// Render the currect component border
	RenderComponentBorder(xRenderData);
}

void A2DAbstractComponent::RenderChildren(A2DRenderData * xRenderData)
{
	for (int i = 0; i < aChildrenCompsIndex; i++)
	{
		// To render this. You have to call its children
		// update! This shows to update you have to call its
		// render and to render you are callings its update method.
		// A bit confusing but it's the best solution.
		aChildrenComps[i]->Update();
	}
}

void A2DAbstractComponent::AddComponent(A2DAbstractComponent * xAbstractComponent)
{
	A2DAbstractComponent **	newComponents;

	if (aChildrenCompsIndex >= aChildrenCompsIndex)
	{
		newComponents = CreateAmmoritizedComponentArray();
	//	delete[] aChildrenComps;
		aChildrenComps = newComponents;
	}

	aChildrenComps[aChildrenCompsIndex++] = xAbstractComponent;

	// Set the current component as the parent of the next
	xAbstractComponent->SetParent(this);
}

void A2DAbstractComponent::SetParent(A2DAbstractComponent * xComponent)
{
	aParentComp = xComponent;
}

A2DAbstractComponent** A2DAbstractComponent::CreateAmmoritizedComponentArray()
{
	A2DAbstractComponent **	newComponents;

	newComponents = new A2DAbstractComponent *[aChildrenCompsLength * 2];

	for (int i = 0; i < aChildrenCompsIndex; i++)
	{
		newComponents[i] = aChildrenComps[i];
	}

	aChildrenCompsLength *= 2;

	return newComponents;
}

LPCWSTR A2DAbstractComponent::GetClass()
{
	return L"A2DAbstractComponent";
}

LPCWSTR A2DAbstractComponent::ToString()
{
	return L"A2DAbstractComponent";
}

bool A2DAbstractComponent::operator==(A2DAbstract * xAbstract)
{
	return false;
}

/*
HRESULT A2DAbstractComponent::InitializeChildren()
{
	HRESULT hr = S_OK;

	for (int i = 0; i < aChildrenCompsIndex; i++)
	{
		if (aChildrenComps[i])
		{
			hr = aChildrenComps[i]->Initialize();
		}

		if (FAILED(hr)) return hr;
	}

	return hr;
}
*/

HRESULT A2DAbstractComponent::Initialize()
{
	HRESULT hr = S_OK;

	aChildrenComps = new A2DAbstractComponent *[aChildrenCompsLength = 5];

	// InitializeChildren();  // This will never do anything!!

	return hr;
}

void A2DAbstractComponent::Deinitialize()
{
	DeinitializeChildren();

	delete [] aChildrenComps;
}

void A2DAbstractComponent::DeinitializeChildren()
{
	for (int i = 0; i < aChildrenCompsIndex; i++)
	{
		aChildrenComps[i]->Deinitialize();
	}
}

// This will be a raw A2DRenderData. You can cast it to whatever you want!
HRESULT A2DAbstractComponent::CreateResources(A2DRenderData * xRenderData)
{
	HRESULT hr = S_OK;
	A2DGraphics * graphics;

	// Basic null check. If this pointer is null, then fail the
	// resources. The program must throw an exception and halt.
	if (xRenderData == NULL)	return E_FAIL;

	// This might be A2DRenderData or A2DGraphics. But we still have to make 
	// a new instance of it. But it will always be A2DGraphics from now on.
	graphics = (aGraphics = new A2DGraphics(this, xRenderData));

	// Initialize the unit
	hr = graphics->Initialize();

	if (FAILED(hr)) return hr;

	hr = CreateComponentResources(graphics); // These have to be type of A2DGraphics

	if (FAILED(hr)) return hr;

	hr = CreateChildrenResources(graphics); // These have to be type of A2DGraphics

	return hr;
}

void A2DAbstractComponent::DestroyResources()
{
	DestroyComponentResources();
	DestroyChildrenResources();
}

HRESULT A2DAbstractComponent::CreateComponentResources(A2DRenderData * xRenderData)
{
	HRESULT hr;
	A2DGraphics * graphics;

	// This is an example when of when I used A2DAbstract
	// Here, I have no need to do a dynamic typecast.
	// The method isClass is actually defined in the A2DAbstract
	// In fact, I just added this method recently, and I have it for
	// all objects instantly. No need to override it in any methods
	// in classes that extend A2DAbstract
	if (!xRenderData->isClass(L"A2DGraphics"))	return E_FAIL;

	// Cast to A2DGraphics.
	// Similar to java.awt.Graphics to java.awt.Graphics2D
	graphics = (A2DGraphics *) xRenderData;

	// Tell graphics to call the render method once in order to
	// set aside only those resources.
	graphics->SetMode(A2D_GRAPHICS_MODE_CREATE);

	// A2DGraphics will call the parent Render method once
	hr = graphics->CreateResources();

	return hr;
}

void A2DAbstractComponent::DestroyComponentResources(){}

void A2DAbstractComponent::DestroyChildrenResources()
{
	for (int i = 0; i < aChildrenCompsIndex; i++)
	{
		aChildrenComps[i]->DestroyResources();
	}
}

HRESULT A2DAbstractComponent::CreateChildrenResources(A2DRenderData * xRenderData)
{
	HRESULT hr = NULL;

	for (int i = 0; i < aChildrenCompsIndex; i++)
	{
		hr = aChildrenComps[i]->CreateResources(xRenderData);

		if (FAILED(hr)) return hr;
	}

	return hr;
}

void A2DAbstractComponent::Add(A2DAbstractComponent * xAbstractComponent)
{
	AddComponent(xAbstractComponent);
}

void A2DAbstractComponent::RemoveComponent(A2DAbstractComponent * xAbstractComponent)
{
	// Fix later
}

LRESULT A2DAbstractComponent::WindowMsg(HWND * xHwnd, UINT * xMessage, WPARAM * xWParam, LPARAM * xLParam)
{
	// Fix later
	// Pass it all the children based on location!
	return NULL;
}

