#pragma once
#ifndef LOGINPANEL_H
#define LOGINPANEL_H
#include "Panel.h"

using namespace std;

class LoginPanel : public Panel
{
	public:
		LoginPanel()
		{
		}
		~LoginPanel();
		virtual void makePanel();
		virtual wxString getWidgetValue(wxString widgetName);
		virtual void destroyPanel();
	protected:
		WidgetComposite loginWidget;
		wxPNGHandler* handler = nullptr;
};
#endif // !LOGINPANEL_H
