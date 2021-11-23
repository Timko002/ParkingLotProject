#pragma once
#ifndef PANEL_H
#define PANEL_H

#include "WidgetComposite.h"

using namespace std;

class Panel
{
public:
	Panel()
	{
	}
	virtual void setContext(wxWindow* p);
	virtual wxWindow* getContext();
	virtual wxString getWidgetValue(wxString widgetName) = 0;
	virtual void makePanel() = 0;
	virtual void destroyPanel() = 0;
protected:
	wxWindow* parent;
};

#endif // !PANEL_H
