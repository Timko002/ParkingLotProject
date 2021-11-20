#include "main.h"
#include "PSpotComposite.h"
#include "PSpot.h"
#include "WidgetComposite.h"
#include "wx/string.h"
#include <iostream>
#include <vector>
#include <Windows.h>


wxBEGIN_EVENT_TABLE(main, wxFrame)
EVT_BUTTON(1001, OnLoginSubmit)
EVT_BUTTON(2, onClickX)
wxEND_EVENT_TABLE()

main::main() : wxFrame(nullptr, wxID_ANY, "Parking Lot Project - CSUSM")
{
	//
	// build factories here
	// draw the widgets on the login frame
	main::buildLoginPanel();
}

main::~main()
{

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