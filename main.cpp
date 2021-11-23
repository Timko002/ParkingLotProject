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
EVT_BUTTON(3, OnReserveClick)
EVT_BUTTON(2, onClickX)
wxEND_EVENT_TABLE()

main::main() : wxFrame(nullptr, wxID_ANY, "Parking Lot Project - CSUSM")
{
	//
	// creating the Lots on startup
	ParkingLotFactory f;
	Lots.insert(make_pair("A", f.chooseParkingLot("A")));
	Lots.insert(make_pair("B", f.chooseParkingLot("B")));
	Lots.insert(make_pair("C", f.chooseParkingLot("C")));
	Lots.insert(make_pair("D", f.chooseParkingLot("D")));
	// draw the widgets on the login frame
	main::buildLoginPanel();
}

main::~main()
{
	main::Destroy();
	parkinglotIcon.clear();
}

void main::OnLotClick(wxCommandEvent& evt)
{
	main::buildParkingLotDisplay(getEventPointer(evt),getEventName(evt));
}

void main::OnLoginSubmit(wxCommandEvent& evt)
{

	// check login
	if (checkLogin(wxStringTostring(username->GetValue()), wxStringTostring(password->GetValue())))
	{
		// if successful then clear the screen
		main::clearLoginFrame();
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
	if (!checkAvailableSpots(Lots[wxStringTostring(getEventName(evt))]))
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