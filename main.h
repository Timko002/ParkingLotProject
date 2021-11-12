#pragma once
#include "wx/wx.h"

class main : public wxFrame
{
public:
	main();
	~main();

public:
	wxStaticText* loginText = nullptr;
	wxStaticText* userNameText = nullptr;
	wxStaticText* passwordText = nullptr;
	wxButton* loginConfirm = nullptr;
	wxTextCtrl* username = nullptr;
	wxTextCtrl* password = nullptr;
	wxListBox* m_list1 = nullptr;
};

