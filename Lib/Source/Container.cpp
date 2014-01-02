
#include "../../include/ExtLibs.h"
#include "../../include/Container.h"
#include "../../include/Graphics.h"

using namespace A2D;

void Container::invalidate()
{
	aValidatedContents = false;
}

void Container::validated()
{
	aValidatedContents = true;
}

void Container::revalidate()
{
	validate();
}

LPCWSTR Container::getClass()
{
	return L"Container";
}

LPCWSTR Container::toString()
{
	return L"Container";
}

bool Container::operator==(Abstract * xAbstract)
{
	return false;
}
