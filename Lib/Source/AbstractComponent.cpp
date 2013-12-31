
#include "../../include/ExtLibs.h"
#include "../../include/AbstractComponent.h"
#include "../../include/Graphics.h"

using namespace A2D;

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

void AbstractComponent::update(Graphics& xGraphics)
{
	if (!aValidatedContents)
	{
		validate();
	}

	// Calling the render algorithm
	// -> Render component
	// -> Render its children on top
	// -> Render the border that overlays
	//    both of the previous renders.	// Force region
	xGraphics.setClip(&aCalculatedRegion);

	// Render the current component
	paintComponent(xGraphics);

	// This will call children update
	// This is sort of saying: (Render <==> Update)
	updateChildren(xGraphics);

	// Force region
	xGraphics.setClip(&aCalculatedRegion);

	// Render the currect component border
	paintComponentBorder(xGraphics);
}

AbstractComponent& AbstractComponent::getParent()
{
	return *aParentComp;
}

void AbstractComponent::setBounds(Rect& xRect)
{	
	aOptRegion.aWidth = xRect.aWidth;
	aOptRegion.aHeight = xRect.aHeight;
	aOptRegion.aX = xRect.aX;
	aOptRegion.aY = xRect.aY;

	aOptBackgroundRegion.aWidth = xRect.aWidth;
	aOptBackgroundRegion.aHeight = xRect.aHeight;

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
	aOptRegion.aWidth = xWidth;
	aOptRegion.aHeight = xHeight;
	aOptRegion.aX = xX;
	aOptRegion.aY = xY;

	aOptBackgroundRegion.aWidth = xWidth;
	aOptBackgroundRegion.aHeight = xHeight;

	invalidate();
}

void AbstractComponent::updateChildren(Graphics& xGraphics)
{
	QuickList<AbstractComponent*>::Iterator<AbstractComponent*> iterator = aChildren.iterator();

	while (iterator.has_next())
	{
		iterator.next()->update(xGraphics);
	}
}

void AbstractComponent::setParent(AbstractComponent * xComponent)
{
	aParentComp = xComponent;
}

Rect AbstractComponent::getBounds()
{
	return aOptRegion;
}

Rect * AbstractComponent::_getBounds()
{
	return &aOptRegion;
}

void AbstractComponent::add(AbstractComponent& xAbstractComponent)
{
	aChildren.push_back(&xAbstractComponent);
}

void AbstractComponent::remove(AbstractComponent& xAbstractComponent)
{
	aChildren.remove(&xAbstractComponent);
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
