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
EVT_BUTTON(1100, OnRegisterClick)
EVT_BUTTON(1101, OnRegisterConfirm)
EVT_BUTTON(1102, OnReturnClick)
EVT_BUTTON(4, OnReserveClick)
EVT_BUTTON(2, onClickX)
EVT_BUTTON(5, onClickX)
EVT_BUTTON(6, onClickNotifX)
EVT_BUTTON(7, onClickRating)
EVT_BUTTON(8, onClickRating)
EVT_BUTTON(9, onClickRating)
EVT_BUTTON(10, onClickRating)
EVT_BUTTON(11, onClickRating)
EVT_BUTTON(20, OnLogoutClick)
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

DBObject* DBObject::db = 0;
User* User::user = 0;
std::atomic<bool> threadcheck = false;

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
	threadcheck = true;
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
	threadcheck = false;
	main::SetMaxSize(wxSize(1200, 830));
	main::SetMinSize(wxSize(1200, 830));
	main::SetSize(1200, 830);
	MapPanel->setContext(this);
	MapPanel->makePanel();
	editor.changeLabel(this, "welcomeBack", "Welcome back, "+User::instance()->get_user());
	setRating();
	if (User::instance()->get_rating() < 1)
	{
		editor.changeLabel(this, "totalRating", " Unrated");
	}
	else
	{
		editor.changeLabel(this, "totalRating", to_string(User::instance()->get_rating()).substr(0, 4));
	}
	if (!(User::instance()->get_status() == "Unreserved"))
	{
		// restart timers if you close the app
		
		if ((timer.returnTimeLeft(User::instance()->get_startTime()) > 0) && (User::instance()->get_status() == "Reserved"))
		{
			//notifyParked(timer.returnTimeLeft(User::instance()->get_startTime()));
			//notifyLeft(timer.returnTimeLeft(User::instance()->get_endTime()));
			notifyParked(15);
			notifyLeft(30);
		}
		else if ((timer.returnTimeLeft(User::instance()->get_startTime()) <= 0) && (User::instance()->get_status() == "Reserved") && (timer.returnTimeLeft(User::instance()->get_endTime()) > 0))
		{
			//notifyParked(60);
			//notifyLeft(timer.returnTimeLeft(User::instance()->get_endTime()));
			notifyParked(15);
			notifyLeft(30);
		}

		if ((timer.returnTimeLeft(User::instance()->get_endTime()) > 0) && (User::instance()->get_status() == "Parked"))
		{
			//notifyLeft(timer.returnTimeLeft(User::instance()->get_endTime()));
			notifyLeft(15);
		}
		else if ((timer.returnTimeLeft(User::instance()->get_endTime()) <= 0) && (User::instance()->get_status() == "Parked"))
		{
			//notifyLeft(60);
			notifyLeft(15);
		}

		editor.changeLabel(this, "statusField", "Status: " + User::instance()->get_status() + " | ");
		editor.changeLabel(this, "spotLocation", "Location: Lot" + User::instance()->getReservedLot() + " | " + "Spot" + User::instance()->getReservedSpot());
		editor.changeLabel(this, "bookedTime", "Reserved Time : " + User::instance()->get_startTime() + "~" + User::instance()->get_endTime());
	}
	else
	{
		editor.changeLabel(this, "statusField", "Status: " + User::instance()->get_status());
	}
}

// notify that your status is parked
void main::notifyParked(int timer)
{
	ratingPanel->setContext(rating_frame);
	ratingPanel->makePanel();
	main::rating_frame->Center();
	main::notifParked = async(launch::async, [this, timer]
	{
		for (int i = 0; i < timer; i++)
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			if (threadcheck)
			{
				break;
			}
		}
		if (!threadcheck)
		{
			int answer = wxMessageBox(wxString::Format("Are you parked?"), wxT("Notification"), wxYES_DEFAULT | wxYES_NO | wxICON_QUESTION);
			if (answer == wxYES)
			{
				parkUpdate.setContext(this);
				parkUpdate.notify();
				if (DBObject::instance()->checkToRate(User::instance()->getReservedLot(), User::instance()->getReservedSpot(), User::instance()->get_startTime()))
				{
					main::rating_frame->Show();
				}
			}
		}
	});

}

// notify that your status is parked
void main::notifyLeft(int timer)
{
	main::notifyleft = async(launch::async, [this, timer]
	{
		for (int i = 0; i < timer; i++)
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			if (threadcheck)
			{
				break;
			}
		}
		if (!threadcheck)
		{
			int answer = wxMessageBox(wxString::Format("Have you left the spot?"), wxT("Notification"), wxYES_DEFAULT | wxYES_NO | wxICON_QUESTION);
			if (answer == wxYES)
			{
				lspotUpdate.setContext(this);
				lspotUpdate.notify();
			}
		}
	});

}

void main::onClickX(wxCommandEvent& evt)
{
	lot_frame->Destroy();
}

void main::getStartLotTime(vector<wxString>& timeStart)
{
	vector<wxString> startTimeCombo;
	timeStart.clear();
	timer.setCurrentTime();
	//sending the hour and min based on current time to look for the earliest slot available
	startTimeCombo = pLots[wxStringTostring(lot_frame->GetName())]->getAvailableSlotsToStart(timer.returnHour(), timer.returnMin());
	timeStart = startTimeCombo;
	//int startHour = wxAtoi(startTimeFirstOption.substr(0, 2));
	//nt startMin = wxAtoi(startTimeFirstOption.substr(startTimeFirstOption.length() - 2));
	//timeStart = timer.returnComboOptions(timeStart, timer.returnHour(), timer.returnMin());
}

string main::wxStringTostring(wxString msg)
{
	return string(msg.mb_str(wxConvUTF8));
}

void main::printToOutputStream(string message)
{
	std::wstring stemp = std::wstring(message.begin(), message.end());
	LPCWSTR sw = stemp.c_str();
	OutputDebugString(sw);
}

bool main::checkAvailableSpots(ParkingLot* Lot)
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

void main::setRating()
{
	string s = to_string(User::instance()->get_rating());
	int temp = User::instance()->get_rating();
	wxBitmap star = wxBitmap("images/star10.PNG", wxBITMAP_TYPE_PNG);
	
	for (int i = 1; i <= temp; i++)
	{
		editor.changeImg(this, to_string(i) + "Star", star);
	}
	// builds partial star rating
	if ((s.size() >= 3) & (temp < 5))
	{
		string imgmap = "images/star" + to_string(User::instance()->get_rating()).substr(2, 1) + ".PNG";
		wxBitmap star = wxBitmap(imgmap, wxBITMAP_TYPE_PNG);
		editor.changeImg(this, to_string(temp+1) + "Star", star);
	}
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
	int endMin = wxAtoi(selection.substr(selection.length() - 2)) + 15;
	//timeEnd.push_back(wxString(to_string(endHour) + ":" + to_string(endMin)));
	time_t startTime = timer.convertChoiceTime(wxStringTostring(selection));
	int count_blocks= pLots[wxStringTostring(lot_frame->GetName())]->getAvaialbleSlots(startTime);
	timeEnd = timer.returnComboOptionsForEndTime(timeEnd, endHour, endMin, count_blocks);
	timeEndOptions->Set(timeEnd);
	timeEndOptions->SetLabel(timeEnd[0]);
	timeEndOptions->Show();
	evt.Skip();
}

void main::onClickNotifX(wxCommandEvent& evt)
{
	rating_frame->Hide();
}

void main::onClickRating(wxCommandEvent& evt)
{
	switch (evt.GetId())
	{
	case 7:
		DBObject::instance()->updateRating(1);
		break;
	case 8:
		DBObject::instance()->updateRating(2);
		break;
	case 9:
		DBObject::instance()->updateRating(3);
		break;
	case 10:
		DBObject::instance()->updateRating(4);
		break;
	case 11:
		DBObject::instance()->updateRating(5);
		break;
	default:
		printToOutputStream("hit default");
	}

	rating_frame->Hide();
}

wxPoint main::getEventPointer(wxCommandEvent& evt)
{
	wxBitmapButton* button = wxDynamicCast(evt.GetEventObject(), wxBitmapButton);
	return button->GetPosition();;
}

wxString main::getEventName(wxCommandEvent& evt)
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

void main::OnRegisterClick(wxCommandEvent& evt)
{
	editor.hideNode(this, "Submit");
	editor.hideNode(this, "registerButton");
	editor.showNode(this, "completeRegistration");
	editor.showNode(this, "loginReturn");
	editor.changeLabel(this, "LogMsg", "Please enter a username/password to create account");
}

void main::OnRegisterConfirm(wxCommandEvent& evt)
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

void main::OnLogoutClick(wxCommandEvent& evt)
{
	main::SetMaxSize(wxSize(500, 500));
	main::SetMinSize(wxSize(500, 500));
	MapPanel->destroyPanel();
	buildLoginPanel();
	threadcheck = true;
}

void main::OnReturnClick(wxCommandEvent& evt)
{
	editor.showNode(this, "Submit");
	editor.showNode(this, "registerButton");
	editor.hideNode(this, "completeRegistration");
	editor.hideNode(this, "loginReturn");
	editor.changeLabel(this, "LogMsg", "Please log in to start reserving your parking spot.");
	editor.changeLabel(this, "loginResponse", "");
}

bool main::canRegister(string name, string pass)
{
	if ((name.size() == 0) || (pass.size() == 0))
	{
		editor.changeLabel(this, "loginResponse", "Please fill out information before submitting");
		return false;
	}
	//regex to check if the name is in the correct format
	if (!regex_search(name, regex("[A-Za-z]{1}[0-9]{3}$")))
	{
		editor.changeLabel(this, "loginResponse", "Your username must match your CSUSM ID");
		return false;
	}
	bool response = DBObject::instance()->checkUserExists(name);
	// check database for duplicates
	if (response)
	{
		editor.changeLabel(this, "loginResponse", "User account already exists");
		return false;
	}
	return true;
}

bool main::checkLogin(string name, string pass)
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
	if (User::instance()->get_status() == "Unreserved")
	{
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
	}
	else
	{
		director->BuildAlreadyReseved();
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
			// this is the hours value
			printToOutputStream(wxStringTostring(timeStartOptions->GetValue()));
			// this is the minutes value
			printToOutputStream(wxStringTostring(timeEndOptions->GetValue()));

			time_t startTime = timer.convertChoiceTime(wxStringTostring(timeStartOptions->GetValue()));
			time_t endTime = timer.convertChoiceTime(wxStringTostring(timeEndOptions->GetValue()));
			//spaceno                                 //lotname
			int reservedSpot = pLots[wxStringTostring(getEventName(evt))]->reserve(startTime, endTime);
			if (reservedSpot>=1)
			{
				editor.changeLabel(this, wxString("FullSpots")+getEventName(evt), "Full Spots:" + to_string(pLots[wxStringTostring(getEventName(evt))]->getNoOfTotallyBookedSpots()));
				printToOutputStream("\n"+to_string(reservedSpot) + "\n");
				regUpdate.setContext(this);
				regUpdate.setLocation(wxStringTostring(getEventName(evt)), to_string(reservedSpot));
				regUpdate.setTimes(wxStringTostring(timeStartOptions->GetValue()), wxStringTostring(timeEndOptions->GetValue()));
				regUpdate.notify();
				DBObject::instance()->bookUser(User::instance()->get_user(), wxStringTostring(getEventName(evt)), to_string(reservedSpot), wxStringTostring(timeStartOptions->GetValue()), wxStringTostring(timeEndOptions->GetValue()));
				editor.changeLabel(lot_frame, "setReserveTimeText", "Successfully reserved the Spot " + timeStartOptions->GetValue() + "-" + timeEndOptions->GetValue());
				editor.deleteItem(lot_frame, wxStringTostring(getEventName(evt)));
				//notifyParked(timer.returnTimeLeft(User::instance()->get_startTime()));
				notifyParked(15);
				//notifyLeft(timer.returnTimeLeft(User::instance()->get_endTime()));
				notifyLeft(30);
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