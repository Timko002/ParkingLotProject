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
	m_frame1->Show();

	return true;
}