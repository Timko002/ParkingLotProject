#pragma once
#ifndef ParkingLot_H
#define ParkingLot_H
#include <iostream>
#include <wx/wx.h>
using namespace std;
//this is the interface for the parking lots
class ParkingLot
{
public:
	virtual int reserve(time_t startTime, time_t endTime) = 0;
	virtual string getLotName() = 0;
	virtual bool checkIsLotFull() = 0;
	virtual int getAvaialbleSlots(time_t startTime)=0;
	virtual int getNoOfTotallyBookedSpots() = 0;
	virtual vector<wxString> getAvailableSlotsToStart(int currHour, int currMin) = 0;

};
#endif