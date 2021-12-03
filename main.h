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
	void setRating();
	void buildLoginPanel();
	void buildParkingMap();
	void OnLoginSubmit(wxCommandEvent& evt);
	void OnReserveClick(wxCommandEvent& evt);
	void OnLotClick(wxCommandEvent& evt);
	void notifyParked(int timer);
	void notifyLeft(int timer);
	void onClickX(wxCommandEvent& evt);
	void onClickNotifX(wxCommandEvent& evt);
	void onClickRating(wxCommandEvent& evt);
	wxPoint getEventPointer(wxCommandEvent& evt);
	wxString getEventName(wxCommandEvent& evt);
	void OnRegisterClick(wxCommandEvent& evt);
	void OnRegisterConfirm(wxCommandEvent& evt);
	void OnLogoutClick(wxCommandEvent& evt);
	void OnReturnClick(wxCommandEvent& evt);
	virtual bool canRegister(string name, string pass);
	virtual bool checkLogin(string name, string pass);
	wxDECLARE_EVENT_TABLE();
};
#endif // !MAIN_H