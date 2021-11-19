#pragma once
#ifndef MAIN_H
#define MAIN_H
#include "WidgetComposite.h"
#include "wx/wx.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class main : public wxFrame
{
public:
	main();
	~main();

private:
	void clearLoginFrame()
	{
		WidgetComposite widgetToDestory;
		widgetToDestory.add(new pngLogo(CSUSMLogo));
		widgetToDestory.add(new TextField(loginText));
		widgetToDestory.add(new TextField(userNameText));
		widgetToDestory.add(new TextField(passwordText));
		widgetToDestory.add(new TextInput(username));
		widgetToDestory.add(new TextInput(password));
		widgetToDestory.add(new TextButton(loginConfirm));
		widgetToDestory.destroy();
	}
	void buildLoginPanel()
	{
		main::SetSize(500, 500);
		handler = new wxPNGHandler;
		wxImage::AddHandler(handler);
		CSUSMLogo = new wxStaticBitmap(this, wxID_ANY, wxBitmap("images/csusm-logo.png", wxBITMAP_TYPE_PNG), wxPoint(100, 10), wxSize(300, 128));
		loginText = new wxStaticText(this, wxID_ANY, "Please log in to start reserving your parking spot.", wxPoint(100, 150), wxSize(300, 30));
		userNameText = new wxStaticText(this, wxID_ANY, "Username: ", wxPoint(10, 200), wxSize(70, 30));
		passwordText = new wxStaticText(this, wxID_ANY, "Passowrd: ", wxPoint(10, 240), wxSize(70, 30));
		username = new wxTextCtrl(this, wxID_ANY, "enter username...", wxPoint(100, 195), wxSize(300, 30));
		password = new wxTextCtrl(this, wxID_ANY, "enter password...", wxPoint(100, 235), wxSize(300, 30));
		loginConfirm = new wxButton(this, 1001, "Submit", wxPoint(150, 350), wxSize(150, 50));
	}
	void buildParkingSpot()
	{
		main::SetMaxSize(wxSize(1200, 830));
		main::SetMinSize(wxSize(1200, 830));
		main::SetSize(1200, 830);
		parkingPicHandler = new wxPNGHandler;
		wxImage::AddHandler(parkingPicHandler);
		ParkingPic = new wxStaticBitmap(this, wxID_ANY, wxBitmap("images/parking-map.PNG", wxBITMAP_TYPE_PNG), wxPoint(150, 00), wxSize(1050, 800));
		parkinglotIcon.push_back(new wxBitmapButton(this, 1002, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG),wxPoint(320,350), wxSize(41,50), wxBG_STYLE_TRANSPARENT));
		parkinglotIcon.push_back(new wxBitmapButton(this, 1003, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG), wxPoint(320, 450), wxSize(41, 50), wxBG_STYLE_TRANSPARENT));
		parkinglotIcon.push_back(new wxBitmapButton(this, 1004, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG), wxPoint(320, 550), wxSize(41, 50), wxBG_STYLE_TRANSPARENT));
		parkinglotIcon.push_back(new wxBitmapButton(this, 1005, wxBitmap("images/mapmarker.PNG", wxBITMAP_TYPE_PNG), wxPoint(380, 620), wxSize(41, 50), wxBG_STYLE_TRANSPARENT));
		for (int i = 0; i < parkinglotIcon.size(); i++)
		{
			parkinglotIcon[i]->Raise();
			parkinglotIcon[i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &main::OnLotClick, this);
		}

	}
	void buildParkingLotDisplay()
	{
		lot_frame = new wxFrame(NULL, wxID_ANY, "Lot Details", wxPoint(300, 300), wxSize(300, 300), NULL, "Parking Lot");
		lot_frame->Show();
		lot_frame->SetWindowStyle(wxSTAY_ON_TOP);
	}
// Login screen widgets
public:
	wxStaticText* loginText = nullptr;
	wxStaticText* userNameText = nullptr;
	wxStaticText* passwordText = nullptr;
	wxButton* loginConfirm = nullptr;
	wxTextCtrl* username = nullptr;
	wxTextCtrl* password = nullptr;
	wxPNGHandler* handler = nullptr;
	wxStaticBitmap* CSUSMLogo = nullptr;
	
// parking lot frame & widgets
public:
	wxFrame* lot_frame = nullptr;
//parking map widgets
public:
	wxPNGHandler* parkingPicHandler = nullptr;
	wxPNGHandler* parkingLotHandler = nullptr;
	vector<wxBitmapButton*>parkinglotIcon;
	wxStaticBitmap* ParkingPic = nullptr;

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
	void OnLoginSubmit(wxCommandEvent& evt);
	void OnLotClick(wxCommandEvent& evt);
	virtual bool checkLogin(string name, string pass)
	{
		// replace with real login check later
		if ((name == "name") && (pass == "pass"))
		{
			return true;
		}
		return false;
	}
	wxDECLARE_EVENT_TABLE();
};
#endif // !MAIN_H