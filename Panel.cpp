#pragma once
#include "Panel.h"
void Panel::setContext(wxWindow* p)
{
	parent = p;
}
wxWindow* Panel::getContext()
{
	return parent;
}