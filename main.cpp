#include "main.h"
#include "PSpot.h"
#include "WidgetComposite.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <Windows.h>


using namespace std;

wxBEGIN_EVENT_TABLE(main, wxFrame)
EVT_BUTTON(1001, OnLoginSubmit)
EVT_BUTTON(4, OnReserveClick)
EVT_BUTTON(2, onClickX)
EVT_BUTTON(5, onClickX)
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

// async button example for us to try
void main::TestAsync(int timer)
{
	main::value = async(launch::async, [this,timer]
	{
		std::this_thread::sleep_for(std::chrono::seconds(timer));
		int answer = wxMessageBox(wxString::Format("This is your 5 minute notification"),wxT("Notification"), wxYES_DEFAULT | wxYES_NO | wxCANCEL | wxICON_EXCLAMATION);
		if (answer == wxYES)
			printToOutputStream("selected yes");
	});
	
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
	LotPanel->setContext(lot_frame);
	LotPanel->makePanel();
	ConcreteLotBuilder* builder = new ConcreteLotBuilder();
	Director* director = new Director();
	director->set_builder(builder,lot_frame,wxName);

	//	spotsTextField = new wxStaticText(lot_frame, wxID_ANY, buildAvailableSPots(wxName), wxPoint(30, 90), wxSize(300, 30));

	if (checkAvailableSpots(pLots[wxStringTostring(wxName)])) //(checkAvailableSpots(availableSpots))
	{
		getStartLotTime(timeStart);
		if (timeStart.size() != 0)
		{
			// building the full lot of cars
			director->BuildFullProduct();
			// get pointers to the combo boxes
			timeStartOptions = editor.generatePointerCombo(editor.getNode(lot_frame, "startTimeBox"));
			timeEndOptions = editor.generatePointerCombo(editor.getNode(lot_frame, "endTimeBox"));
			timeStartOptions->Set(timeStart);
			timeStartOptions->Bind(wxEVT_COMBOBOX, &main::buildEndTime, this);
		}
		else
		{
			// Too late to reserve 
			director->BuildPast6PM();	
		}
	}
	else
	{
		// Lot is full of cars
		director->BuildFullLot();
	}
	// cleanup pointers
	LotUI* p = builder->GetProduct();
	p->destroyParts();
	delete p;
	delete builder;
	delete director;
}

void main::OnReserveClick(wxCommandEvent& evt)
{
	// here is the reserve click

	if (checkAvailableSpots(pLots[wxStringTostring(getEventName(evt))]))
	{
		if ((timeStartOptions->GetValue() == "") || (timeEndOptions->GetValue() == ""))
		{
			//reserveReminder->SetLabel("You must make a selection to continue");
			editor.changeLabel(lot_frame, "setReserveTimeText", "You must make a selection to continue");
		}
		else
		{
			//testing reservation
			TestAsync(10);
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
				editor.changeLabel(lot_frame, "setReserveTimeText", "Successfully reserved the Spot " + timeStartOptions->GetValue() + "-" + timeEndOptions->GetValue());
				editor.deleteItem(lot_frame, getEventName(evt));
			}
			else
			{
				editor.changeLabel(lot_frame, "setReserveTimeText", "No spots available for the selected time and Lot.\nTry with a different time or check other Lots");
				editor.deleteItem(lot_frame, getEventName(evt));
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