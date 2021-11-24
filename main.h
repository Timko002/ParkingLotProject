#pragma once
#ifndef MAIN_H
#define MAIN_H
#include "WidgetComposite.h"
#include "wx/wx.h"
#include "wx/event.h"
#include "ParkingLotFactory.h"
#include "StaticPanelFactory.h"
#include "TimerFunctions.h"
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

class main : public wxFrame
{
public:
	main();
	~main();

private:
	void buildSidePanel()
	{
		for (size_t i = 0; i < lotReferences.size(); i++)
		{
			// this displays all the lot info on teh side and a search later on
		}
	}

	// building the popup lot frame based on the point of the button
	void buildParkingLotDisplay(wxPoint point, wxString wxName);
// Login screen widgets
public:
	Panel* LoginPanel = StaticPanelFactory::makePanel("login");
	
// parking lot frame & widgets
public:
	TimerFunctions timer;
	Panel* LotPanel = StaticPanelFactory::makePanel("lot");
	wxFrame* lot_frame = nullptr;
	wxString pspotText;
	wxString reservedSpots;
	wxString availableSpots;
	wxStaticText* noReserveText = nullptr;
	wxStaticText* reserveReminder = nullptr;
	wxStaticText* hourText = nullptr;
	wxStaticText* minuteText = nullptr;
	wxStaticText* LotInfoText = nullptr;
	wxStaticText* numOpenSpots = nullptr;
	wxStaticText* spotsTextField = nullptr;
	wxStaticText* reservedTime = nullptr;
	wxComboBox* timeStartOptions = nullptr;
	wxComboBox* timeEndOptions = nullptr;
	vector<wxString> timeStart; //= {"1","2","3","4","5","6","7","8","9","10","11","12"};
	vector<wxString> timeEnd; //= {"0","15","30","45"};
	wxButton* reservationConfirm = nullptr;
	wxButton* xButton = nullptr;
	vector<wxString> lotReferences = { "A","B","C","D","E","F","G","H","I","J"};

//parking map widgets
public:
	Panel* MapPanel = StaticPanelFactory::makePanel("map");
	wxPNGHandler* HeaderHandlerPNG = nullptr;
	unordered_map<string, ParkingLot*> pLots;

	void buildEndTime(wxCommandEvent& evt);
	// Search for a time to start
	void setStartLotTime(wxComboBox* combo,string lotNum)
	{
		timeStart.clear();
		timer.setCurrentTime();
		timeStart = timer.returnComboOptions(timeStart, timer.returnHour(), timer.returnMin());
		combo->Set(timeStart);
	}
	
	string wxStringTostring(wxString msg)
	{
		// turns a wxString to a regular string
		return string(msg.mb_str(wxConvUTF8));
	}
	void printToOutputStream(string message) 
	{	
		//saving this for later to print to output
		std::wstring stemp = std::wstring(message.begin(), message.end());
		LPCWSTR sw = stemp.c_str();
		OutputDebugString(sw);
	}
	
	bool checkAvailableSpots(ParkingLot* Lot) //checkAvailableSpots(wxString availableSpots)
	{
		if (!Lot->checkIsLotFull())// (wxAtoi(availableSpots) > 0)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	void buildLoginPanel();
	void buildParkingMap();
	wxString buildAvailableSPots(wxString wxLotName)
	{
		//replace function here to get lot information
		reservedSpots = "30";
		availableSpots = "10";
		pspotText = "The detailed information for this available spot is: \n   Available spots: " + reservedSpots + wxString(" Reserved spots: ") + availableSpots;
		return pspotText;
	}

	void OnLoginSubmit(wxCommandEvent& evt);
	void OnReserveClick(wxCommandEvent& evt);
	void OnLotClick(wxCommandEvent& evt);
	void onClickX(wxCommandEvent& evt)
	{
		
		lot_frame->Destroy();
	}

	wxPoint getEventPointer(wxCommandEvent& evt)
	{
		wxBitmapButton* button = wxDynamicCast(evt.GetEventObject(), wxBitmapButton);
		return button->GetPosition();;
	}
	wxString getEventName(wxCommandEvent& evt)
	{
		if (evt.GetId() == 3)
		{
			wxBitmapButton* button = wxDynamicCast(evt.GetEventObject(), wxBitmapButton);
			return button->GetName();
		}
		else
		{
			wxButton* button = wxDynamicCast(evt.GetEventObject(), wxButton);
			printToOutputStream(wxStringTostring(button->GetName()));
			return button->GetName();
		}
	}
	virtual bool checkLogin(string name, string pass)
	{
		// replace with real login check later
		if ((name == "name") && (pass == "pass"))
		{
			return true;
		}
		return false;
	}
	wxDECLARE_EVENT_TABLE();
};
#endif // !MAIN_H