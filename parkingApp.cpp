#include "parkingApp.h"

wxIMPLEMENT_APP(parkingApp);

parkingApp::parkingApp()
{

}

parkingApp::~parkingApp()
{

}

bool parkingApp::OnInit()
{

	m_frame1 = new main();
	m_frame1->SetMinSize(wxSize(500,500));
	m_frame1->SetMaxSize(wxSize(500, 500));
	m_frame1->Show(true);

	return true;
}