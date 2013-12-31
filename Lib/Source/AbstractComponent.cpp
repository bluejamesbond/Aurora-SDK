
#include "../../include/ExtLibs.h"
#include "../../include/AbstractComponent.h"
#include "../../include/Graphics.h"

using namespace A2D;

AbstractComponent::AbstractComponent() : 
aParentComp(NULL),
aGraphics(NULL) {}

AbstractComponent::~AbstractComponent(){}

void AbstractComponent::invalidate()
{
	aValidatedContents = false;
}

void AbstractComponent::validated()
{
	aValidatedContents = true;
}

void AbstractComponent::revalidate()
{
	validate();
}

void AbstractComponent::Update(RenderData * xRenderData)
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

Graphics * AbstractComponent::GetGraphics()
{
	return aGraphics;
}
AbstractComponent * AbstractComponent::GetParent()
{
	return aParentComp;
}

void AbstractComponent::setBounds(Rect * xRect)
{
	Graphics * graphics = GetGraphics();
	
	aOptRegion.aWidth = xRect->aWidth;
	aOptRegion.aHeight = xRect->aHeight;
	aOptRegion.aX = xRect->aX;
	aOptRegion.aY = xRect->aY;

	aOptBackgroundRegion.aWidth = xRect->aWidth;
	aOptBackgroundRegion.aHeight = xRect->aHeight;

	invalidate();
}

void AbstractComponent::validate()
{
	AbstractComponent * parentComp = aParentComp;
	bool hasParent = parentComp != NULL;
	
	Rect& compRect = aOptRegion;
	Rect * parentRect = hasParent ? &parentComp->aOptRegion : NULL;
	Rect * parentGraphicsClip = hasParent ? &parentComp->aCalculatedRegion : NULL;

	aCalculatedRegion.aX = (hasParent ? parentGraphicsClip->aX : 0) + compRect.aX;
	aCalculatedRegion.aY = (hasParent ? parentGraphicsClip->aY : 0) + compRect.aY;
	aCalculatedRegion.aWidth = min(compRect.aWidth, (hasParent ? parentRect->aWidth : INT_MAX));
	aCalculatedRegion.aHeight = min(compRect.aHeight, (hasParent ? parentRect->aHeight : INT_MAX));

	aValidatedContents = true;
}

void AbstractComponent::setBounds(float xX, float xY, float xWidth, float xHeight)
{
	Graphics * graphics = GetGraphics();

	aOptRegion.aWidth = xWidth;
	aOptRegion.aHeight = xHeight;
	aOptRegion.aX = xX;
	aOptRegion.aY = xY;

	aOptBackgroundRegion.aWidth = xWidth;
	aOptBackgroundRegion.aHeight = xHeight;

	invalidate();
}

void AbstractComponent::Render(RenderData * xRenderData)
{
	// Force region
	static_cast<Graphics*>(xRenderData)->setClip(&aCalculatedRegion);

	// Render the current component
	paintComponent(xRenderData);

	// This will call children updates
	// This is sort of saying: (Render <==> Update)
	paintChildren(xRenderData);

	// Force region
	static_cast<Graphics*>(xRenderData)->setClip(&aCalculatedRegion);

	// Render the currect component border
	paintComponentBorder(xRenderData);
}

void AbstractComponent::paintChildren(RenderData * xRenderData)
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

void AbstractComponent::AddComponent(AbstractComponent * xAbstractComponent)
{
	AbstractComponent **	newComponents;

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

void AbstractComponent::SetParent(AbstractComponent * xComponent)
{
	aParentComp = xComponent;
}

AbstractComponent** AbstractComponent::CreateAmmoritizedComponentArray()
{
	AbstractComponent **	newComponents;

	newComponents = new AbstractComponent *[aChildrenCompsLength * 2];

	for (int i = 0; i < aChildrenCompsIndex; i++)
	{
		newComponents[i] = aChildrenComps[i];
	}

	aChildrenCompsLength *= 2;

	return newComponents;
}

HRESULT AbstractComponent::Initialize()
{
	HRESULT hr = S_OK;

	aChildrenComps = new AbstractComponent *[aChildrenCompsLength = 5];
	
	return hr;
}

void AbstractComponent::Deinitialize()
{
	DeinitializeChildren();

	delete [] aChildrenComps;
}

void AbstractComponent::DeinitializeChildren()
{
	for (int i = 0; i < aChildrenCompsIndex; i++)
	{
		aChildrenComps[i]->Deinitialize();
	}
}

Rect * AbstractComponent::GetBounds()
{
	return &aOptRegion;
}

void AbstractComponent::Add(AbstractComponent * xAbstractComponent)
{
	AddComponent(xAbstractComponent);
}

void AbstractComponent::RemoveComponent(AbstractComponent * xAbstractComponent)
{
	// Fix later
}

LRESULT AbstractComponent::WindowMsg(HWND * xHwnd, UINT * xMessage, WPARAM * xWParam, LPARAM * xLParam)
{
	// Fix later
	// Pass it all the children based on location!
	return NULL;
}

LPCWSTR AbstractComponent::GetClass()
{
	return L"AbstractComponent";
}

LPCWSTR AbstractComponent::ToString()
{
	return L"AbstractComponent";
}

bool AbstractComponent::operator==(Abstract * xAbstract)
{
	return false;
}
