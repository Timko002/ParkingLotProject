#pragma once
#ifndef MAIN_H
#define MAIN_H
#include "WidgetComposite.h"
#include "wx/wx.h"
#include "wx/event.h"
#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <ctime>   


using namespace std;

class main : public wxFrame
{
public:
	main();
	~main();

private:
	void clearLoginFrame()
	{
		WidgetComposite widgetToDestory;
		widgetToDestory.add(new pngLogo(CSUSMLogo));
		widgetToDestory.add(new TextField(loginText));
		widgetToDestory.add(new TextField(userNameText));
		widgetToDestory.add(new TextField(passwordText));
		widgetToDestory.add(new TextInput(username));
		widgetToDestory.add(new TextInput(password));
		widgetToDestory.add(new TextButton(loginConfirm));
		widgetToDestory.destroy();
	}
	void buildLoginPanel()
	{
		main::SetSize(500, 500);
		handler = new wxPNGHandler;
		wxImage::AddHandler(handler);
		CSUSMLogo = new wxStaticBitmap(this, wxID_ANY, wxBitmap("images/csusm-logo.png", wxBITMAP_TYPE_PNG), wxPoint(100, 10), wxSize(300, 128));
		loginText = new wxStaticText(this, wxID_ANY, "Please log in to start reserving your parking spot.", wxPoint(100, 150), wxSize(300, 30));
		userNameText = new wxStaticText(this, wxID_ANY, "Username: ", wxPoint(10, 200), wxSize(70, 30));
		passwordText = new wxStaticText(this, wxID_ANY, "Passowrd: ", wxPoint(10, 240), wxSize(70, 30));
		username = new wxTextCtrl(this, wxID_ANY, "enter username...", wxPoint(100, 195), wxSize(300, 30));
		password = new wxTextCtrl(this, wxID_ANY, "enter password...", wxPoint(100, 235), wxSize(300, 30));
		loginConfirm = new wxButton(this, 1001, "Submit", wxPoint(150, 350), wxSize(150, 50));
	}
	void buildParkingMap()
	{
		main::SetMaxSize(wxSize(1200, 830));
		main::SetMinSize(wxSize(1200, 830));
		main::SetSize(1200, 830);
		buildSidePanel();
		parkingPicHandler = new wxPNGHandler;
		wxImage::AddHandler(parkingPicHandler);
		ParkingPic = new wxStaticBitmap(this, wxID_ANY, wxBitmap("images/parking-map.PNG", wxBITMAP_TYPE_PNG), wxPoint(250, 00), wxSize(950, 800));
		parkinglotIcon.push_back(new wxBitmapButton(this, 1002, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG),wxPoint(330,355), wxSize(41,50), wxBG_STYLE_TRANSPARENT));
		parkinglotIcon.push_back(new wxBitmapButton(this, 1003, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG), wxPoint(320, 450), wxSize(41, 50), wxBG_STYLE_TRANSPARENT));
		parkinglotIcon.push_back(new wxBitmapButton(this, 1004, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG), wxPoint(320, 550), wxSize(41, 50), wxBG_STYLE_TRANSPARENT));
		parkinglotIcon.push_back(new wxBitmapButton(this, 1005, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG), wxPoint(395, 630), wxSize(41, 50), wxBG_STYLE_TRANSPARENT));
		parkinglotIcon.push_back(new wxBitmapButton(this, 1006, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG), wxPoint(520, 660), wxSize(41, 50), wxBG_STYLE_TRANSPARENT));
		parkinglotIcon.push_back(new wxBitmapButton(this, 1007, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG), wxPoint(660, 660), wxSize(41, 50), wxBG_STYLE_TRANSPARENT));
		parkinglotIcon.push_back(new wxBitmapButton(this, 1008, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG), wxPoint(770, 660), wxSize(41, 50), wxBG_STYLE_TRANSPARENT));
		parkinglotIcon.push_back(new wxBitmapButton(this, 1009, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG), wxPoint(770, 560), wxSize(41, 50), wxBG_STYLE_TRANSPARENT));
		parkinglotIcon.push_back(new wxBitmapButton(this, 1010, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG), wxPoint(760, 250), wxSize(41, 50), wxBG_STYLE_TRANSPARENT));
		parkinglotIcon.push_back(new wxBitmapButton(this, 1011, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG), wxPoint(700, 190), wxSize(41, 50), wxBG_STYLE_TRANSPARENT));
		for (int i = 0; i < parkinglotIcon.size(); i++)
		{
			parkinglotIcon[i]->Raise();
			parkinglotIcon[i]->SetName(lotReferences[i]);
			parkinglotIcon[i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &main::OnLotClick, this);
		}
	}
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
		spotsTextField = new wxStaticText(lot_frame, wxID_ANY, buildAvailableSPots(wxName), wxPoint(30, 90), wxSize(300, 30));
		if (checkAvailableSpots(availableSpots))
		{
			hourText = new wxStaticText(lot_frame, wxID_ANY, "Time Start", wxPoint(80, 160), wxSize(70, 20));
			minuteText = new wxStaticText(lot_frame, wxID_ANY, "Time End", wxPoint(185, 160), wxSize(70, 20));
			timeStartOptions = new wxComboBox(lot_frame, wxID_ANY, "1", wxPoint(80, 180), wxSize(70, 30));
			setStartLotTime(timeStartOptions, wxStringTostring(wxName));
			timeStartOptions->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &main::buildEndTime, this);
			timeEndOptions = new wxComboBox(lot_frame, wxID_ANY, "0", wxPoint(180, 180), wxSize(70, 30));
			timeEndOptions->Hide();
			reserveReminder = new wxStaticText(lot_frame, wxID_ANY, "         Set a time to reserve a spot", wxPoint(40, 210), wxSize(200, 30));
			reservationConfirm = new wxButton(lot_frame, 3, "Reserve Spot", wxPoint(75, 250), wxSize(150, 40));
		}
		else
		{
			noReserveText = new wxStaticText(lot_frame, wxID_ANY, "There are no reserved spots left for \n                        Lot " + wxName, wxPoint(50, 180), wxSize(300, 70));
		}

	}
// Login screen widgets
public:
	wxStaticText* loginText = nullptr;
	wxStaticText* userNameText = nullptr;
	wxStaticText* passwordText = nullptr;
	wxButton* loginConfirm = nullptr;
	wxTextCtrl* username = nullptr;
	wxTextCtrl* password = nullptr;
	wxPNGHandler* handler = nullptr;
	wxStaticBitmap* CSUSMLogo = nullptr;
	
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
	wxPNGHandler* parkingPicHandler = nullptr;
	wxPNGHandler* parkingLotHandler = nullptr;
	wxPNGHandler* HeaderHandlerPNG = nullptr;
	vector<wxBitmapButton*>parkinglotIcon;
	wxStaticBitmap* ParkingPic = nullptr;

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
	bool checkAvailableSpots(wxString availableSpots)
	{
		if (wxAtoi(availableSpots) > 0)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
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
		return button->GetName();;
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