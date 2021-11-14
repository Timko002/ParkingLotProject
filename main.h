#pragma once
#ifndef MAIN_H
#define MAIN_H
#include "WidgetComposite.h"
#include "wx/wx.h"
#include <string>
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