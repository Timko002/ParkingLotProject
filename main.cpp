#include "main.h"


main::main() : wxFrame(nullptr, wxID_ANY, "Parking Lot Project - CSUSM")
{
	main::SetSize(500, 300);
	loginText = new wxStaticText(this, wxID_ANY, "Please log in to start reserving your parking spot.", wxPoint(50, 10), wxSize(300, 30));
	userNameText = new wxStaticText(this, wxID_ANY, "Username: ", wxPoint(10, 45), wxSize(70, 30));
	passwordText = new wxStaticText(this, wxID_ANY, "Passowrd: ", wxPoint(10, 85), wxSize(70, 30));
	username = new wxTextCtrl(this, wxID_ANY, "enter username...", wxPoint(100, 40), wxSize(300, 30));
	password = new wxTextCtrl(this, wxID_ANY, "enter password...", wxPoint(100, 80), wxSize(300, 30));
	loginConfirm = new wxButton(this, wxID_ANY, "Confirm", wxPoint(150, 150), wxSize(150, 50));
}

main::~main()
{

}