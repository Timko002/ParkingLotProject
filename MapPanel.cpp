#pragma once
#include "MapPanel.h"
#include "LotA.h"

void MapPanel::makePanel()
{
	wxPNGHandler* handler = new wxPNGHandler;
	wxImage::AddHandler(handler);
	//mapPanelWidget.add(new pngLogo(MapPanel::getContext(), wxID_ANY, wxBitmap("images/sidepanelbg.PNG", wxBITMAP_TYPE_PNG), wxPoint(0, 0), wxSize(250, 800), "sidePanelBG"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "Welcome back,", wxPoint(10, 50), wxSize(200, 30), "welcomeBack"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "Rating:", wxPoint(10, 85), wxSize(40, 30), "Rating"));
	mapPanelWidget.add(new pngLogo(MapPanel::getContext(), wxID_ANY, wxBitmap("images/star0.PNG", wxBITMAP_TYPE_PNG), wxPoint(50, 80), wxSize(20, 20), "1Star"));
	mapPanelWidget.add(new pngLogo(MapPanel::getContext(), wxID_ANY, wxBitmap("images/star0.PNG", wxBITMAP_TYPE_PNG), wxPoint(71, 80), wxSize(20, 20), "2Star"));
	mapPanelWidget.add(new pngLogo(MapPanel::getContext(), wxID_ANY, wxBitmap("images/star0.PNG", wxBITMAP_TYPE_PNG), wxPoint(92, 80), wxSize(20, 20), "3Star"));
	mapPanelWidget.add(new pngLogo(MapPanel::getContext(), wxID_ANY, wxBitmap("images/star0.PNG", wxBITMAP_TYPE_PNG), wxPoint(113, 80), wxSize(20, 20), "4Star"));
	mapPanelWidget.add(new pngLogo(MapPanel::getContext(), wxID_ANY, wxBitmap("images/star0.PNG", wxBITMAP_TYPE_PNG), wxPoint(134, 80), wxSize(20, 20), "5Star"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "", wxPoint(160, 85), wxSize(40, 30), "totalRating"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "Status: ", wxPoint(10, 117), wxSize(50, 30), "statusField"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "", wxPoint(110, 117), wxSize(50, 30), "spotLocation"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "LotA", wxPoint(15, 175), wxSize(40, 30), "LDetailsA"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "LotB", wxPoint(125, 175), wxSize(40, 30), "LDetailsB"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "LotC", wxPoint(15, 300), wxSize(40, 30), "LDetailsC"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "LotD", wxPoint(125, 300), wxSize(40, 30), "LDetailsD"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "LotE", wxPoint(15, 425), wxSize(40, 30), "LDetailsE"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "LotF", wxPoint(125, 425), wxSize(40, 30), "LDetailsF"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "LotG", wxPoint(15, 550), wxSize(40, 30), "LDetailsG"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "LotH", wxPoint(125, 550), wxSize(40, 30), "LDetailsH"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "LotI", wxPoint(15, 675), wxSize(40, 30), "LDetailsI"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "LotJ", wxPoint(125, 675), wxSize(40, 30), "LDetailsJ"));
	mapPanelWidget.add(new pngLogo(MapPanel::getContext(), wxID_ANY, wxBitmap("images/parking-map.PNG", wxBITMAP_TYPE_PNG), wxPoint(250, 00), wxSize(950, 800), "PNG Logo"));
	mapPanelWidget.add(new pngButton(MapPanel::getContext(), 1002, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG), wxPoint(330, 355), wxSize(41, 50), "LotA"));
	mapPanelWidget.add(new pngButton(MapPanel::getContext(), 1003, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG), wxPoint(320, 450), wxSize(41, 50), "LotB"));
	mapPanelWidget.add(new pngButton(MapPanel::getContext(), 1004, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG), wxPoint(320, 550), wxSize(41, 50), "LotC"));
	mapPanelWidget.add(new pngButton(MapPanel::getContext(), 1005, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG), wxPoint(395, 630), wxSize(41, 50), "LotD"));
	mapPanelWidget.add(new pngButton(MapPanel::getContext(), 1006, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG), wxPoint(520, 660), wxSize(41, 50), "LotE"));
	mapPanelWidget.add(new pngButton(MapPanel::getContext(), 1007, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG), wxPoint(660, 660), wxSize(41, 50), "LotF"));
	mapPanelWidget.add(new pngButton(MapPanel::getContext(), 1008, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG), wxPoint(770, 660), wxSize(41, 50), "LotG"));
	mapPanelWidget.add(new pngButton(MapPanel::getContext(), 1009, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG), wxPoint(770, 560), wxSize(41, 50), "LotH"));
	mapPanelWidget.add(new pngButton(MapPanel::getContext(), 1010, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG), wxPoint(760, 250), wxSize(41, 50), "LotI"));
	mapPanelWidget.add(new pngButton(MapPanel::getContext(), 1011, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG), wxPoint(700, 190), wxSize(41, 50), "LotJ"));
	
	//LotA::getInstance()->getTotalNoOfSpots();

	wxWindowList& children = MapPanel::getContext()->GetChildren();
	for (wxWindowList::Node* node = children.GetFirst(); node; node = node->GetNext())
	{
		wxWindow* current = (wxWindow*)node->GetData();
		if (current->GetName() == "PNG Logo")
		{
			// do nothing
		}
		else if (current->GetName().substr(0, 3) == "Lot")
		{
			current->Raise();
			current->SetName(current->GetName().substr(3,4));
		}
		else if (current->GetName().size() > 8)
		{

		}
	}
}

void MapPanel::destroyPanel()
{
	mapPanelWidget.destroy();
}

wxString MapPanel::getWidgetValue(wxString widgetName)
{
	if (widgetName == "username")
	{
		return mapPanelWidget.getValueByName("username");
	}
	else if (widgetName == "password")
	{
		return mapPanelWidget.getValueByName("password");
	}
}