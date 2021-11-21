#include "main.h"
#include "PSpotComposite.h"
#include "PSpot.h"
#include "WidgetComposite.h"
#include "wx/string.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include "ParkingLotFactory.h"
#include <unordered_map>
using namespace std;

wxBEGIN_EVENT_TABLE(main, wxFrame)
EVT_BUTTON(1001, OnLoginSubmit)
EVT_BUTTON(3, OnReserveClick)
EVT_BUTTON(2, onClickX)
wxEND_EVENT_TABLE()
unordered_map<char, ParkingLot*> Lots;
main::main() : wxFrame(nullptr, wxID_ANY, "Parking Lot Project - CSUSM")
{
	//
	// creating the Lots on startup
	ParkingLotFactory f;
	//unordered_map<char, ParkingLot*> Lots;
	for (char i = 'A'; i <= 'D'; i++)
		Lots.insert(make_pair(i, f.chooseParkingLot(i)));

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
	if (checkAvailableSpots(availableSpots))
	{
		// this is the hours value
		printToOutputStream(wxStringTostring(timeHourOptions->GetValue()));
		// this is teh minutes value
		printToOutputStream(wxStringTostring(timeMinuteOptions->GetValue()));
		// fill this in to what to do with the time
		reserveReminder->SetLabel("Successfully reserved a Spot for " + timeHourOptions->GetValue() + "h:" + timeMinuteOptions->GetValue()+"m");
		reservationConfirm->Destroy();
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