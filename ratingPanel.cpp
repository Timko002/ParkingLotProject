#include "ratingPanel.h"

void ratingPanel::makePanel()
{
	wxPNGHandler* handler = new wxPNGHandler;
	wxImage::AddHandler(handler);
	ratingWidget.add(new TextButton(ratingPanel::getContext(), 6, "X", wxPoint(278, 0), wxSize(20, 20), "Close"));
	ratingWidget.add(new pngLogo(ratingPanel::getContext(), wxID_ANY, wxBitmap("images/headerBG.PNG", wxBITMAP_TYPE_PNG), wxPoint(00, 00), wxSize(278, 20), "HeaderBG"));
	ratingWidget.add(new TextField(ratingPanel::getContext(), wxID_ANY, "Please review the previous user's parking.", wxPoint(50, 50), wxSize(240, 30), "LogMsg"));
	ratingWidget.add(new TextButton(ratingPanel::getContext(), 7, "1 Star", wxPoint(50, 100), wxSize(40, 30), "rate1"));
	ratingWidget.add(new TextButton(ratingPanel::getContext(), 8, "2 Star", wxPoint(95, 100), wxSize(40, 30), "rate2"));
	ratingWidget.add(new TextButton(ratingPanel::getContext(), 9, "3 Star", wxPoint(140, 100), wxSize(40, 30), "rate3"));
	ratingWidget.add(new TextButton(ratingPanel::getContext(), 10, "4 Star", wxPoint(185, 100), wxSize(40, 30), "rate4"));
	ratingWidget.add(new TextButton(ratingPanel::getContext(), 11, "5 Star", wxPoint(230, 100), wxSize(40, 30), "rate5"));

}

wxString ratingPanel::getWidgetValue(wxString widgetName)
{
    return wxString();
}

void ratingPanel::destroyPanel()
{
    ratingWidget.destroy();
    delete handler;
}
