#pragma once
#ifndef MAIN_H
#define MAIN_H
#include "WidgetComposite.h"
#include "wx/wx.h"
#include "wx/event.h"
#include "wx/string.h"
#include "wx/thread.h"
#include <future>
#include "ParkingLotFactory.h"
#include "StaticPanelFactory.h"
#include "DBObject.h"
#include "User.h"
#include "WidgetEditor.h"
#include "WidgetBuilder.h"
#include "TimerFunctions.h"
#include "statusObserver.h"
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
	// build the side panel on the map
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
	Panel* ratingPanel = StaticPanelFactory::makePanel("rating");
// parking lot frame & widgets
public:
	leaveSpot lspotUpdate;
	registerUpdate regUpdate;
	parkedUpdate parkUpdate;
	wxFrame* lot_frame = nullptr;
	wxFrame* rating_frame = new wxFrame(this, wxID_ANY, "Rating Menu", wxDefaultPosition, wxSize(300, 200), NULL, "ratingMenu");
	future<void> notifParked;
	future<void> notifyleft;
	TimerFunctions timer;
	WidgetEditor editor;
	Panel* LotPanel = StaticPanelFactory::makePanel("lot");
	wxComboBox* timeStartOptions = nullptr;
	wxComboBox* timeEndOptions = nullptr;
	vector<wxString> timeStart;
	vector<wxString> timeEnd; 
	wxButton* xButton = nullptr;
	vector<wxString> lotReferences = { "A","B","C","D","E","F","G","H","I","J"};

//parking map widgets
public:
	Panel* MapPanel = StaticPanelFactory::makePanel("map");
	wxPNGHandler* HeaderHandlerPNG = nullptr;
	unordered_map<string, ParkingLot*> pLots;

	void buildEndTime(wxCommandEvent& evt);

	// Search for a time to start
	void getStartLotTime(vector<wxString> &timeStart)
	{
		timeStart.clear();
		timer.setCurrentTime();
		//sending the hour and min based on current time to look for the earliest slot available
		string startTimeFirstOption = pLots[wxStringTostring(lot_frame->GetName())]->getFirstAvailableSlot(timer.returnHour(), timer.returnMin());
		int startHour = wxAtoi(startTimeFirstOption.substr(0, 2));
		int startMin = wxAtoi(startTimeFirstOption.substr(3, 5));
		timeStart = timer.returnComboOptions(timeStart, startHour, startMin);
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
	void setRating();
	void buildLoginPanel();
	void buildParkingMap();
	void OnLoginSubmit(wxCommandEvent& evt);
	void OnReserveClick(wxCommandEvent& evt);
	void OnLotClick(wxCommandEvent& evt);
	void notifyParked(int timer);
	void notifyLeft(int timer);
	void onClickX(wxCommandEvent& evt)
	{
		lot_frame->Destroy();
	}
	void onClickNotifX(wxCommandEvent& evt)
	{
		rating_frame->Hide();
	}
	void onClickRating(wxCommandEvent& evt);
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
			return button->GetName();
		}
	}
	void OnRegisterClick(wxCommandEvent& evt)
	{
		editor.hideNode(this, "Submit");
		editor.hideNode(this, "registerButton");
		editor.showNode(this, "completeRegistration");
		editor.showNode(this, "loginReturn");
		editor.changeLabel(this, "LogMsg", "Please enter a username/password to create account");
	}
	void OnRegisterConfirm(wxCommandEvent& evt)
	{
		if (canRegister(wxStringTostring(LoginPanel->getWidgetValue("username")), wxStringTostring(LoginPanel->getWidgetValue("password"))))
		{
			DBObject::instance()->createUser(wxStringTostring(LoginPanel->getWidgetValue("username")), wxStringTostring(LoginPanel->getWidgetValue("password")));
			editor.showNode(this, "Submit");
			editor.showNode(this, "registerButton");
			editor.hideNode(this, "completeRegistration");
			editor.hideNode(this, "loginReturn");
			editor.changeLabel(this, "LogMsg", "Please log in to start reserving your parking spot.");
			editor.changeLabel(this, "loginResponse", "Registration completed");
		}
	}
	void OnLogoutClick(wxCommandEvent& evt)
	{
		main::SetMaxSize(wxSize(500, 500));
		main::SetMinSize(wxSize(500, 500));
		MapPanel->destroyPanel();
		buildLoginPanel();
	}
	void OnReturnClick(wxCommandEvent& evt)
	{
		editor.showNode(this, "Submit");
		editor.showNode(this, "registerButton");
		editor.hideNode(this, "completeRegistration");
		editor.hideNode(this, "loginReturn");
		editor.changeLabel(this, "LogMsg", "Please log in to start reserving your parking spot.");
		editor.changeLabel(this, "loginResponse", "");
	}
	virtual bool canRegister(string name, string pass)
	{
		if ((name.size() == 0) || (pass.size() == 0))
		{
			editor.changeLabel(this, "loginResponse", "Please fill out information before submitting");
			return false;
		}
		bool response = DBObject::instance()->checkUserExists(name);
		if (response)
		{
			editor.changeLabel(this, "loginResponse", "User account already exists");
			return false;
		}
		return true;
	}
	virtual bool checkLogin(string name, string pass)
	{
		string response = DBObject::instance()->checkLogin(name, pass);
		if (response == "success")
		{
			DBObject::instance()->isReserved(User::instance()->get_user());
			return true;
		}
		editor.changeLabel(this, "loginResponse", response);
		return false;
	}
	wxDECLARE_EVENT_TABLE();
};
#endif // !MAIN_H