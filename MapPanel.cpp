#pragma once
#include "MapPanel.h"
#include "LotA.h"
#include "LotB.h"
#include "LotC.h"
#include "LotD.h"
#include "LotE.h"
#include "LotF.h"
#include "LotG.h"
#include "LotH.h"
#include "LotI.h"
#include "LotJ.h"

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
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "", wxPoint(10, 148), wxSize(150, 25), "bookedTime"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "LotA(Spots: " + to_string(LotA::getInstance()->getTotalNoOfSpots()) + ")", wxPoint(10, 200), wxSize(90, 25), "LDetailsA"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "Full Spots:" + to_string(LotA::getInstance()->getNoOfTotallyBookedSpots()), wxPoint(12, 250), wxSize(100, 30), "FullSpotsA"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "LotB(Spots: " + to_string(LotB::getInstance()->getTotalNoOfSpots()) + ")", wxPoint(125, 200), wxSize(90, 25), "LDetailsB"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "Full Spots:" + to_string(LotB::getInstance()->getNoOfTotallyBookedSpots()), wxPoint(127, 250), wxSize(100, 30), "FullSpotsB"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "LotC(Spots: " + to_string(LotC::getInstance()->getTotalNoOfSpots()) + ")", wxPoint(10, 300), wxSize(90, 25), "LDetailsC"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "Full Spots:" + to_string(LotC::getInstance()->getNoOfTotallyBookedSpots()), wxPoint(12, 350), wxSize(100, 30), "FullSpotsC"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "LotD(Spots: " + to_string(LotD::getInstance()->getTotalNoOfSpots()) + ")", wxPoint(125, 300), wxSize(90, 25), "LDetailsD"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "Full Spots:" + to_string(LotD::getInstance()->getNoOfTotallyBookedSpots()), wxPoint(127, 350), wxSize(100, 30), "FullSpotsD"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "LotE(Spots: " + to_string(LotE::getInstance()->getTotalNoOfSpots()) + ")", wxPoint(10, 400), wxSize(90, 25), "LDetailsE"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "Full Spots:" + to_string(LotE::getInstance()->getNoOfTotallyBookedSpots()), wxPoint(12, 450), wxSize(100, 30), "FullSpotsE"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "LotF(Spots:" + to_string(LotF::getInstance()->getTotalNoOfSpots()) + ")", wxPoint(125, 400), wxSize(90, 25), "LDetailsF"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "Full Spots:" + to_string(LotF::getInstance()->getNoOfTotallyBookedSpots()), wxPoint(127, 450), wxSize(100, 30), "FullSpotsF"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "LotG(Spots: " + to_string(LotG::getInstance()->getTotalNoOfSpots()) + ")", wxPoint(10, 500), wxSize(90, 25), "LDetailsG"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "Full Spots:" + to_string(LotG::getInstance()->getNoOfTotallyBookedSpots()), wxPoint(12, 550), wxSize(100, 30), "FullSpotsG"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "LotH(Spots: " + to_string(LotH::getInstance()->getTotalNoOfSpots()) + ")", wxPoint(125, 500), wxSize(90, 25), "LDetailsH"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "Full Spots:" + to_string(LotH::getInstance()->getNoOfTotallyBookedSpots()), wxPoint(127, 550), wxSize(100, 30), "FullSpotsH"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "LotI(Spots: " + to_string(LotI::getInstance()->getTotalNoOfSpots()) + ")", wxPoint(10, 600), wxSize(85, 25), "LDetailsI"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "Full Spots:" + to_string(LotI::getInstance()->getNoOfTotallyBookedSpots()), wxPoint(12, 650), wxSize(100, 30), "FullSpotsI"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "LotJ(Spots: " + to_string(LotJ::getInstance()->getTotalNoOfSpots()) + ")", wxPoint(125, 600), wxSize(85, 25), "LDetailsJ"));
	mapPanelWidget.add(new TextField(MapPanel::getContext(), wxID_ANY, "Full Spots: " + to_string(LotJ::getInstance()->getNoOfTotallyBookedSpots()), wxPoint(127, 650), wxSize(100, 30), "FullSpotsJ"));
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
	mapPanelWidget.add(new TextButton(MapPanel::getContext(), 20, "Log Out", wxPoint(75, 750), wxSize(75, 30), "Logout"));
	
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