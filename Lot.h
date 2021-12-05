#ifndef Lot_H
#define Lot_H
#include <iostream>
#include <vector>
#include <ctime>
#include <wx/wx.h>
#include "ParkingLot.h"
#include "ParkingSpace.h"
using namespace std;
//class implementing the common functions for each lot
class Lot : public ParkingLot
{
protected:
	bool isLotFull;
	vector<ParkingSpace*> pSpace; //object composition
public:

	bool checkIsLotFull();

	int reserve(time_t startTime, time_t endTime);

	int getAvaialbleSlots(time_t startTime);

	int getNoOfTotallyBookedSpots();

	vector<wxString> getAvailableSlotsToStart(int currHour, int currMin);

};

#endif