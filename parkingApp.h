#pragma once

#include "wx/wx.h"
#include "main.h"


class parkingApp : public wxApp
{
public:
	parkingApp();
	~parkingApp();

private:
	main* m_frame1 = nullptr;

public:
	virtual bool OnInit();
};

