#pragma once

#include "wx/wx.h"

class parkingApp : public wxApp
{
public:
	parkingApp();
	~parkingApp();
public:
	virtual bool OnInit();
};

