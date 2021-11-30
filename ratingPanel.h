#pragma once
#ifndef RATINGPANEL_H
#define RATINGPANEL_H
#include "Panel.h"

using namespace std;

class ratingPanel : public Panel
{
	public:
		ratingPanel()
		{
		}
		~ratingPanel();
		virtual void makePanel();
		virtual wxString getWidgetValue(wxString widgetName);
		virtual void destroyPanel();
	protected:
		WidgetComposite ratingWidget;
		wxPNGHandler* handler = nullptr;
};


#endif // !RATINGPANEL_H