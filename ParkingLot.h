#pragma once
#ifndef ParkingLot_H
#define ParkingLot_H
#include <iostream>
using namespace std;

class ParkingLot
{
public:
	virtual int reserve(time_t startTime, time_t endTime) = 0;
	virtual string getLotName() = 0;
	virtual bool checkIsLotFull() = 0;
	virtual int getAvaialbleSlots(time_t startTime)=0;
	virtual int getNoOfTotallyBookedSpots() = 0;
	virtual string getFirstAvailableSlot(int currHour, int currMin) = 0;

};
#endif