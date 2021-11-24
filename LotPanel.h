#pragma once
#ifndef LOTPANEL_H
#define LOTPANEL_H
#include "Panel.h"

using namespace std;

class LotPanel : public Panel
{
public:
	LotPanel()
	{

	}
	~LotPanel();
	virtual void makePanel();
	virtual wxString getWidgetValue(wxString widgetName);
	virtual void destroyPanel();
protected:
	WidgetComposite lotWidget;
	wxPNGHandler* handler = nullptr;
};
#endif // !LOTPANEL_H