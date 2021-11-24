#pragma
#include "LotPanel.h"

void LotPanel::makePanel()
{
	//LotPanel::getContext()->GetName();
	lotWidget.add(new TextButton(LotPanel::getContext(), 2, "X", wxPoint(278, 0), wxSize(20, 20), "Close"));
	wxPNGHandler* handler = new wxPNGHandler;
	wxImage::AddHandler(handler);
	lotWidget.add(new pngLogo(LotPanel::getContext(), wxID_ANY, wxBitmap("images/headerBG.PNG", wxBITMAP_TYPE_PNG), wxPoint(00, 00), wxSize(278, 20), "HeaderBG"));
	lotWidget.add(new TextField(LotPanel::getContext(), wxID_ANY, "Selected parking lot : "+LotPanel::getContext()->GetName(), wxPoint(100, 40), wxSize(300, 50), "Selected Message"));

}

void LotPanel::destroyPanel()
{
	lotWidget.destroy();
}

wxString LotPanel::getWidgetValue(wxString widgetName)
{
	if (widgetName == "username")
	{
		return lotWidget.getValueByName("username");
	}
	else if (widgetName == "password")
	{
		return lotWidget.getValueByName("password");
	}
}