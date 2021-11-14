#include "main.h"
#include "PSpotComposite.h"
#include "PSpot.h"
#include "wx/string.h"
#include <Windows.h>

wxBEGIN_EVENT_TABLE(main, wxFrame)
	EVT_BUTTON(1001, OnLoginSubmit)
wxEND_EVENT_TABLE()

main::main() : wxFrame(nullptr, wxID_ANY, "Parking Lot Project - CSUSM")
{

	main::SetSize(500, 500);
	loginText = new wxStaticText(this, wxID_ANY, "Please log in to start reserving your parking spot.", wxPoint(50, 10), wxSize(300, 30));
	userNameText = new wxStaticText(this, wxID_ANY, "Username: ", wxPoint(10, 45), wxSize(70, 30));
	passwordText = new wxStaticText(this, wxID_ANY, "Passowrd: ", wxPoint(10, 85), wxSize(70, 30));
	username = new wxTextCtrl(this, wxID_ANY, "enter username...", wxPoint(100, 40), wxSize(300, 30));
	password = new wxTextCtrl(this, wxID_ANY, "enter password...", wxPoint(100, 80), wxSize(300, 30));
	loginConfirm = new wxButton(this, 1001, "Confirm", wxPoint(150, 150), wxSize(150, 50));
}

main::~main()
{

}

void main::OnLoginSubmit(wxCommandEvent& evt)
{
	// this is how to get the input values
	// 
	string userName = string(username->GetValue().mb_str(wxConvUTF8));
	string userPass = string(password->GetValue().mb_str(wxConvUTF8));

	// How to display output in output window(since we cant use cout
	std::wstring stemp = std::wstring(userName.begin(), userName.end());
	LPCWSTR sw = stemp.c_str();
	OutputDebugString(sw);
	
}