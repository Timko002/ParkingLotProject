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
wxEND_EVENT_TABLE()

main::main() : wxFrame(nullptr, wxID_ANY, "Parking Lot Project - CSUSM")
{
	// draw the widgets on the login frame
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

main::~main()
{

}

void main::OnLoginSubmit(wxCommandEvent& evt)
{
	// this is how to get the input values
	string userName = wxStringTostring(username->GetValue());
	string userPass = wxStringTostring(password->GetValue());

	// check login
	if (checkLogin(userName, userPass))
	{
		// clear the screen
		main::clearLoginFrame();
		//write code here to build the next window
		
	}
	else
	{
		// output failed login message
	}
}