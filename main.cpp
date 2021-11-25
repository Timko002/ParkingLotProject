#include "main.h"
#include "PSpot.h"
#include "WidgetComposite.h"
#include "wx/string.h"
#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

wxBEGIN_EVENT_TABLE(main, wxFrame)
EVT_BUTTON(1001, OnLoginSubmit)
EVT_BUTTON(4, OnReserveClick)
EVT_BUTTON(3, OnReserveClick)
EVT_BUTTON(2, onClickX)
EVT_BUTTON(1002, OnLotClick)
EVT_BUTTON(1003, OnLotClick)
EVT_BUTTON(1004, OnLotClick)
EVT_BUTTON(1005, OnLotClick)
EVT_BUTTON(1006, OnLotClick)
EVT_BUTTON(1007, OnLotClick)
EVT_BUTTON(1008, OnLotClick)
EVT_BUTTON(1009, OnLotClick)
EVT_BUTTON(1010, OnLotClick)
EVT_BUTTON(1011, OnLotClick)
wxEND_EVENT_TABLE()

main::main() : wxFrame(nullptr, wxID_ANY, "Parking Lot Project - CSUSM")
{
	//
	// creating the Lots on startup
	ParkingLotFactory f;
	
	pLots.insert(make_pair("A", f.chooseParkingLot("A")));
	pLots.insert(make_pair("B", f.chooseParkingLot("B")));
	pLots.insert(make_pair("C", f.chooseParkingLot("C")));
	pLots.insert(make_pair("D", f.chooseParkingLot("D")));
	pLots.insert(make_pair("E", f.chooseParkingLot("E")));
	pLots.insert(make_pair("F", f.chooseParkingLot("F")));
	pLots.insert(make_pair("G", f.chooseParkingLot("G")));
	pLots.insert(make_pair("H", f.chooseParkingLot("H")));
	pLots.insert(make_pair("I", f.chooseParkingLot("I")));
	pLots.insert(make_pair("J", f.chooseParkingLot("J")));
	// draw the widgets on the login frame
	main::buildLoginPanel();
	//editor.changeLabel(this, "userText", "new Text");
}

main::~main()
{
	//this->Destroy();
	//this->GetParent()->Destroy();
	main::Close(true);
	main::Destroy();
}

void main::OnLotClick(wxCommandEvent& evt)
{
	main::buildParkingLotDisplay(getEventPointer(evt),getEventName(evt));
	evt.Skip();
}

void main::buildLoginPanel()
{
	main::SetSize(500, 500);
	LoginPanel->setContext(this);
	LoginPanel->makePanel();
	
}

void main::buildParkingMap()
{
	main::SetMaxSize(wxSize(1200, 830));
	main::SetMinSize(wxSize(1200, 830));
	main::SetSize(1200, 830);
	buildSidePanel();
	MapPanel->setContext(this);
	MapPanel->makePanel();
}

void main::OnLoginSubmit(wxCommandEvent& evt)
{
	
	// its now done through a static factory, widgets are named and you can call their value like this
	if (checkLogin(wxStringTostring(LoginPanel->getWidgetValue("username")), wxStringTostring(LoginPanel->getWidgetValue("password"))))
	{
		// if successful then clear the screen
		LoginPanel->destroyPanel();
		//write code here to build the next window
		main::buildParkingMap();
	}
	else
	{
		// output failed login message
	}
	evt.Skip();
}


void main::buildEndTime(wxCommandEvent& evt) // this builds every available spot for the time
{
	timeEnd.clear();
	wxString selection = timeStartOptions->GetValue();
	int endHour = wxAtoi(selection.substr(0, 2));
	int endMin = wxAtoi(selection.substr(3, 5)) + 15;
	timeEnd = timer.returnComboOptions(timeEnd, endHour, endMin);
	timeEnd.push_back("18:00");
	timeEndOptions->Set(timeEnd);
	timeEndOptions->SetLabel(timeEnd[0]);
	timeEndOptions->Show();
	evt.Skip();
}

void main::buildParkingLotDisplay(wxPoint point, wxString wxName)
{
	lot_frame = new wxFrame(this, wxID_ANY, "Lot Details", point, wxSize(300, 300), NULL, "Parking Lot");
	lot_frame->SetName(wxName);
	lot_frame->Show();
	lot_frame->SetWindowStyle(wxSTAY_ON_TOP);
	LotPanel->setContext(lot_frame);
	LotPanel->makePanel();

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
		reservationConfirm = new wxButton(lot_frame, 4, "Reserve Spot", wxPoint(75, 250), wxSize(150, 40));
		reservationConfirm->SetName(wxName);
	}
	else
	{
		noReserveText = new wxStaticText(lot_frame, wxID_ANY, "No spots left for \n                        Lot " + wxName, wxPoint(50, 180), wxSize(300, 70));
	}

}

void main::OnReserveClick(wxCommandEvent& evt)
{
	// here is the reserve click

	if (checkAvailableSpots(pLots[wxStringTostring(getEventName(evt))]))
	{
		if ((timeStartOptions->GetValue() == "") || (timeEndOptions->GetValue() == ""))
		{
			reserveReminder->SetLabel("You must make a selection to continue");
		}
		else
		{
			// this is the hours value
			printToOutputStream(wxStringTostring(timeStartOptions->GetValue()));
			// this is the minutes value
			printToOutputStream(wxStringTostring(timeEndOptions->GetValue()));
			// fill this in to what to do with the time
			//debug
			//printToOutputStream("lot::::::::::" + pLots[wxStringTostring(getEventName(evt))]->getLotName());
			//printToOutputStream("start time : :::::" + wxStringTostring(timeStartOptions->GetValue()));
			//printToOutputStream("end time : :::::" + wxStringTostring(timeEndOptions->GetValue()));

			time_t startTime = timer.convertChoiceTime(wxStringTostring(timeStartOptions->GetValue()));
			time_t endTime = timer.convertChoiceTime(wxStringTostring(timeEndOptions->GetValue()));

			bool result= pLots[wxStringTostring(getEventName(evt))]->reserve(startTime, endTime);
			if (result == true)
			{
				reserveReminder->SetLabel("Successfully reserved the Spot " + timeStartOptions->GetValue() + "-" + timeEndOptions->GetValue());
				reservationConfirm->Destroy();
			}
			else
			{
				reserveReminder->SetLabel("No spots available for the selected time and Lot.\nTry with a different time or check other Lots");
				reservationConfirm->Destroy();
			}
		}
	}
	evt.Skip();
}
 /*Torsha - creating a placeholder for observer pattern related code
class subscriber 
 {
	 virtual void action() = 0;
 };
 class wxfeature : public subscriber
 {
	 action() {
		 display the lot is full
	 }
 };
 class user : public subscriber
 {
	 action() {
		 display "Parked" with timestamp in the user's session
	 }
 };
 class publisher
 {
	 reserve(){
	 bool result = Lots['A']->reserve(startTime, endTime); //the parking lot and time will come from another function TBD
	 if (result == true)
	 {
		 user.action();
		 bool chk = Lots['A']->checkIsLotFull();
		 if (chk == true)
			 wxfeature.action();
	 }
 };

*/