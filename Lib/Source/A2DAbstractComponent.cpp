
#include "../../include/A2DExtLibs.h"
#include "../../include/A2DAbstractComponent.h"
#include "../../include/A2DGraphics.h"

A2DAbstractComponent::A2DAbstractComponent() : 
aParentComp(NULL),
aGraphics(NULL) {}

A2DAbstractComponent::~A2DAbstractComponent(){}

void A2DAbstractComponent::invalidate()
{
	aValidatedContents = false;
}

void A2DAbstractComponent::validated()
{
	aValidatedContents = true;
}

void A2DAbstractComponent::revalidate()
{
	validate();
}

void A2DAbstractComponent::Update(A2DRenderData * xRenderData)
{
	if (!aValidatedContents)
	{
		validate();
	}

	// Calling the render algorithm
	// -> Render component
	// -> Render its children on top
	// -> Render the border that overlays
	//    both of the previous renders.
	Render(xRenderData);
}

A2DGraphics * A2DAbstractComponent::GetGraphics()
{
	return aGraphics;
}
A2DAbstractComponent * A2DAbstractComponent::GetParent()
{
	return aParentComp;
}

void A2DAbstractComponent::SetBounds(A2DRect * xRect)
{
	A2DGraphics * graphics = GetGraphics();
	
	aOptRegion.aWidth = xRect->aWidth;
	aOptRegion.aHeight = xRect->aHeight;
	aOptRegion.aX = xRect->aX;
	aOptRegion.aY = xRect->aY;

	aOptBackgroundRegion.aWidth = xRect->aWidth;
	aOptBackgroundRegion.aHeight = xRect->aHeight;

	invalidate();
}

void A2DAbstractComponent::validate()
{
	A2DAbstractComponent * parentComp = aParentComp;
	bool hasParent = parentComp != NULL;
	
	A2DRect& compRect = aOptRegion;
	A2DRect * parentRect = hasParent ? &parentComp->aOptRegion : NULL;
	A2DRect * parentGraphicsClip = hasParent ? &parentComp->aCalculatedRegion : NULL;

	aCalculatedRegion.aX = (hasParent ? parentGraphicsClip->aX : 0) + compRect.aX;
	aCalculatedRegion.aY = (hasParent ? parentGraphicsClip->aY : 0) + compRect.aY;
	aCalculatedRegion.aWidth = min(compRect.aWidth, (hasParent ? parentRect->aWidth : INT_MAX));
	aCalculatedRegion.aHeight = min(compRect.aHeight, (hasParent ? parentRect->aHeight : INT_MAX));

	aValidatedContents = true;
}

void A2DAbstractComponent::SetBounds(float xX, float xY, float xWidth, float xHeight)
{
	A2DGraphics * graphics = GetGraphics();

	aOptRegion.aWidth = xWidth;
	aOptRegion.aHeight = xHeight;
	aOptRegion.aX = xX;
	aOptRegion.aY = xY;

	aOptBackgroundRegion.aWidth = xWidth;
	aOptBackgroundRegion.aHeight = xHeight;

	invalidate();
}

void A2DAbstractComponent::Render(A2DRenderData * xRenderData)
{
	// Force region
	static_cast<A2DGraphics*>(xRenderData)->setClip(&aCalculatedRegion);

	// Render the current component
	RenderComponent(xRenderData);

	// This will call children updates
	// This is sort of saying: (Render <==> Update)
	RenderChildren(xRenderData);

	// Force region
	static_cast<A2DGraphics*>(xRenderData)->setClip(&aCalculatedRegion);

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
		aChildrenComps[i]->Update(xRenderData);
	}
}

void A2DAbstractComponent::AddComponent(A2DAbstractComponent * xAbstractComponent)
{
	A2DAbstractComponent **	newComponents;

	if (aChildrenCompsIndex >= aChildrenCompsLength)
	{
		newComponents = CreateAmmoritizedComponentArray();
		delete aChildrenComps;
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

HRESULT A2DAbstractComponent::Initialize()
{
	HRESULT hr = S_OK;

	aChildrenComps = new A2DAbstractComponent *[aChildrenCompsLength = 5];
	
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

A2DRect * A2DAbstractComponent::GetBounds()
{
	return &aOptRegion;
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
