#pragma once
#include "LoginPanel.h"
#include "WidgetEditor.h"

void LoginPanel::makePanel()
{
	wxPNGHandler* handler = new wxPNGHandler;
	wxImage::AddHandler(handler);
	loginWidget.add(new pngLogo(LoginPanel::getContext(), wxID_ANY, wxBitmap("images/csusm-logo.png", wxBITMAP_TYPE_PNG), wxPoint(100, 10), wxSize(300, 128), "PNG Logo"));
	loginWidget.add(new TextField(LoginPanel::getContext(), wxID_ANY, "Please log in to start reserving your parking spot.", wxPoint(100, 150), wxSize(300, 30), "LogMsg"));
	loginWidget.add(new TextField(LoginPanel::getContext(), wxID_ANY, "Username: ", wxPoint(10, 200), wxSize(70, 30),"userText"));
	loginWidget.add(new TextField(LoginPanel::getContext(), wxID_ANY, "Passowrd: ", wxPoint(10, 240), wxSize(70, 30),"passText"));
	loginWidget.add(new TextInput(LoginPanel::getContext(), wxID_ANY, "", wxPoint(100, 195), wxSize(300, 30),"username"));
	loginWidget.add(new TextInput(LoginPanel::getContext(), wxID_ANY, "", wxPoint(100, 235), wxSize(300, 30),"password", "pass"));
	loginWidget.add(new pngButton(LoginPanel::getContext(), 1100, wxBitmap("images/registerbutton.png", wxBITMAP_TYPE_PNG), wxPoint(10, 300), wxSize(90, 22), "registerButton"));
	loginWidget.add(new TextField(LoginPanel::getContext(), wxID_ANY, "", wxPoint(130, 305), wxSize(200, 30), "loginResponse"));
	loginWidget.add(new TextButton(LoginPanel::getContext(), 1001, "Submit", wxPoint(150, 350), wxSize(150, 50),"Submit"));
	loginWidget.add(new TextButton(LoginPanel::getContext(), 1101, "Complete Registration", wxPoint(150, 350), wxSize(150, 50), "completeRegistration", "hide"));
	loginWidget.add(new TextButton(LoginPanel::getContext(), 1102, "Return", wxPoint(375, 350), wxSize(75, 50), "loginReturn", "hide"));
}

void LoginPanel::destroyPanel()
{
	loginWidget.destroy();
	delete handler;
}

wxString LoginPanel::getWidgetValue(wxString widgetName)
{
	if (widgetName == "username")
	{
		return loginWidget.getValueByName("username");
	}
	else if (widgetName == "password")
	{
		return loginWidget.getValueByName("password");
	}
}