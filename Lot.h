#ifndef Lot_H
#define Lot_H
#include <iostream>
#include <vector>
#include <ctime>
#include "ParkingLot.h"
#include "ParkingSpace.h"
using namespace std;
//class implementing the common functions for each lot
class Lot : public ParkingLot
{
protected:
	bool isLotFull;
	vector<ParkingSpace*> pSpace;
public:

	bool checkIsLotFull();

	int reserve(time_t startTime, time_t endTime);

	int getAvaialbleSlots(time_t startTime);

	int getNoOfTotallyBookedSpots();

	string getFirstAvailableSlot(int currHour, int currMin);

};

#endif