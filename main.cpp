#include "main.h"
#include "PSpotComposite.h"
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
}

main::~main()
{
	//this->Destroy();
	//this->GetParent()->Destroy();
	main::Close(true);
	main:Destroy();
}

void main::OnLotClick(wxCommandEvent& evt)
{
	main::buildParkingLotDisplay(getEventPointer(evt),getEventName(evt));
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
			bool result=true;
			//= Lots[wxStringTostring(getEventName(evt))]->reserve(startTime, endTime);
			if (result == true)
			{
				reserveReminder->SetLabel("Successfully reserved the Spot " + timeStartOptions->GetValue() + "-" + timeEndOptions->GetValue());
				reservationConfirm->Destroy();
			}
		}
	}
	
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