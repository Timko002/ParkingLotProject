#pragma once
#ifndef MAIN_H
#define MAIN_H
#include "WidgetComposite.h"
#include "wx/wx.h"
#include "wx/event.h"
#include "ParkingLotFactory.h"
#include "StaticPanelFactory.h"
#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <ctime>   
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
		for (int i = 0; i < lotReferences.size(); i++)
		{
			// this displays all the lot info on teh side and a search later on
		}
	}
	// building the popup lot frame based on the point of the button
	void buildParkingLotDisplay(wxPoint point,wxString wxName)
	{
		lot_frame = new wxFrame(this, wxID_ANY, "Lot Details", point, wxSize(300, 300), NULL, "Parking Lot");
		lot_frame->Show();
		lot_frame->SetWindowStyle(wxSTAY_ON_TOP);
		lotText = "Selected parking lot : " + wxName;
		// fix this later
		xButton = new wxButton(lot_frame, 2, "X", wxPoint(278, 0), wxSize(20, 20));
		HeaderHandlerPNG = new wxPNGHandler;
		wxImage::AddHandler(HeaderHandlerPNG);
		headerBG = new wxStaticBitmap(lot_frame, wxID_ANY, wxBitmap("images/headerBG.PNG", wxBITMAP_TYPE_PNG), wxPoint(00, 00), wxSize(278, 20));
		LotInfoText = new wxStaticText(lot_frame, wxID_ANY, lotText, wxPoint(100, 40), wxSize(300, 50));
	//	spotsTextField = new wxStaticText(lot_frame, wxID_ANY, buildAvailableSPots(wxName), wxPoint(30, 90), wxSize(300, 30));
		
		if (checkAvailableSpots(pLots[wxStringTostring(wxName)])) //(checkAvailableSpots(availableSpots))
		{
			hourText = new wxStaticText(lot_frame, wxID_ANY, "Time Start", wxPoint(80, 160), wxSize(70, 20));
			minuteText = new wxStaticText(lot_frame, wxID_ANY, "Time End", wxPoint(185, 160), wxSize(70, 20));
			timeStartOptions = new wxComboBox(lot_frame, wxID_ANY, "1", wxPoint(80, 180), wxSize(70, 30));
			setStartLotTime(timeStartOptions, wxStringTostring(wxName));
			timeStartOptions->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &main::buildEndTime, this);
			// Handle couldnt find any spaces 
			timeEndOptions = new wxComboBox(lot_frame, wxID_ANY, "0", wxPoint(180, 180), wxSize(70, 30));
			timeEndOptions->Hide();
			reserveReminder = new wxStaticText(lot_frame, wxID_ANY, "         Set a time to reserve a spot", wxPoint(40, 210), wxSize(200, 30));
			reservationConfirm = new wxButton(lot_frame, 3, "Reserve Spot", wxPoint(75, 250), wxSize(150, 40));
		}
		else
		{
			noReserveText = new wxStaticText(lot_frame, wxID_ANY, "No spots left for \n                        Lot " + wxName, wxPoint(50, 180), wxSize(300, 70));
		}
		

	}
// Login screen widgets
public:
	Panel* LoginPanel = StaticPanelFactory::makePanel("login");
// parking lot frame & widgets
public:
	wxFrame* lot_frame = nullptr;
	wxString lotText;
	wxString pspotText;
	wxString reservedSpots;
	wxString availableSpots;
	wxStaticBitmap* headerBG = nullptr;
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

	void buildEndTime(wxCommandEvent& evt) // this builds every available spot for the time
	{
		timeEnd.clear();
		wxString selection = timeStartOptions->GetValue();
		int endHour = wxAtoi(selection.substr(0, 2));
		int endMin = wxAtoi(selection.substr(3, 5)) + 15;
		timeEnd = buildComboOptions(timeEnd, endHour, endMin);
		timeEnd.push_back("18:00");
		timeEndOptions->Set(timeEnd);
		timeEndOptions->SetLabel(timeEnd[0]);
		timeEndOptions->Show();
	}
	// Search for a time to start
	void setStartLotTime(wxComboBox* combo,string lotNum)
	{
		timeStart.clear();
		time_t currentTime;
		struct tm* localTime;
		string stringToAdd;

		time(&currentTime);                   // Get the current time
		localTime = localtime(&currentTime);  // Convert the current time to the local time
		int Hour = localTime->tm_hour;
		if (Hour < 6)
		{
			Hour = 6;
		}

		int Min = localTime->tm_min;
		// Directing Min to next 15 min block
		if (Min == 0)
		{
			// do nothing
		}
		else if(Min <= 15)
		{
			Min = 15;
		}
		else if (Min <= 30)
		{
			Min = 30;
		}
		else if (Min <= 45)
		{
			Min = 45;
		}
		else
		{
			Min = 0;
			Hour += 1;
		}
		timeStart = buildComboOptions(timeStart, Hour, Min);
		combo->Set(timeStart);
	}
	vector<wxString> buildComboOptions(vector<wxString> vectorStringToadd, int Hours, int Minutes)
	{
		string stringToAdd;
		while (Hours < 18)
		{
			//fill the vecto
			for (Minutes; Minutes < 60; Minutes += 15)
			{
				stringToAdd = to_string(Hours);
				stringToAdd += ":";
				if (Minutes == 0)
				{
					stringToAdd += "00";
				}
				else
				{
					stringToAdd += to_string(Minutes);
				}
				vectorStringToadd.push_back(stringToAdd);
			}
			Minutes = 0;
			Hours++;
		}
		return vectorStringToadd;
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
		wxBitmapButton* button = wxDynamicCast(evt.GetEventObject(), wxBitmapButton);
		return button->GetName();
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