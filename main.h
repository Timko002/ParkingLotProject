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
#include <regex>
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
// building the popup lot frame based on the point of the button
	void buildParkingLotDisplay(wxPoint point, wxString wxName);
// Login screen widgets
public:
	Panel* LoginPanel = StaticPanelFactory::makePanel("login");
// parking lot frame & widgets
public:
	Panel* ratingPanel = StaticPanelFactory::makePanel("rating");
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

//parking map widgets
public:
	Panel* MapPanel = StaticPanelFactory::makePanel("map");
	wxPNGHandler* HeaderHandlerPNG = nullptr;
	unordered_map<string, ParkingLot*> pLots;
	void buildEndTime(wxCommandEvent& evt);
	// Search for a time to start
	void getStartLotTime(vector<wxString>& timeStart);
	// turns a wxString to a regular string
	string wxStringTostring(wxString msg);
	//prints to output stream for debugging
	void printToOutputStream(string message);
	//checkAvailableSpots from a parking Lot
	bool checkAvailableSpots(ParkingLot* Lot); 
	//sets the user's rating in the left side panel
	void setRating();
	// builds the login panel display
	void buildLoginPanel();
	// builds the parking map
	void buildParkingMap();
	// event for when you submit your login details
	void OnLoginSubmit(wxCommandEvent& evt);
	// event for when you click to reserve a slot
	void OnReserveClick(wxCommandEvent& evt);
	// event for when you select a lot on the map
	void OnLotClick(wxCommandEvent& evt);
	// notification for when you should park
	void notifyParked(int timer);
	// notification for when you should leave the spot
	void notifyLeft(int timer);
	// event for when you click the x to close a lot window
	void onClickX(wxCommandEvent& evt);
	// event for when you click the x on a notification window
	void onClickNotifX(wxCommandEvent& evt);
	// event for when you click to select a rating
	void onClickRating(wxCommandEvent& evt);
	// returns the pointer for an event
	wxPoint getEventPointer(wxCommandEvent& evt);
	// returns the name of an event for event handling
	wxString getEventName(wxCommandEvent& evt);
	// event for when you click register on the login panel
	void OnRegisterClick(wxCommandEvent& evt);
	// event for when you click to confirm your registration
	void OnRegisterConfirm(wxCommandEvent& evt);
	// event for when you click to log out
	void OnLogoutClick(wxCommandEvent& evt);
	// event on the login panel to swap from registeration to login
	void OnReturnClick(wxCommandEvent& evt);
	// boolean check whether you can register
	virtual bool canRegister(string name, string pass);
	// checks your login credentials
	virtual bool checkLogin(string name, string pass);
	wxDECLARE_EVENT_TABLE();
};
#endif // !MAIN_H