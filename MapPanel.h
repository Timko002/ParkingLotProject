#pragma once
#ifndef MAPPANEL_H
#define MAPPANEL_H
#include "Panel.h"

class MapPanel : public Panel
{
	public:
		MapPanel()
		{

		}
		~MapPanel();
		virtual void makePanel();
		virtual wxString getWidgetValue(wxString widgetName);
		virtual void destroyPanel();
	protected:
		WidgetComposite mapPanelWidget;
		wxPNGHandler* handler = nullptr;
};

#endif // !MAPPANEL_H
