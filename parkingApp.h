#pragma once
#ifndef PARKINGAPP_H
#define PARKINGAPP_H
#include "wx/wx.h"
#include "main.h"

// the application initiates here and creates the main frame
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
#endif // !PARKINGAPP_H