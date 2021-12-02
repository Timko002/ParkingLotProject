#pragma once
#ifndef LotG_H
#define LotG_H
#include <iostream>
#include <vector>
#include <ctime>
#include "ParkingLot.h"
#include "ParkingSpace.h"
using namespace std;

class LotG : public ParkingLot
{
	bool isLotFull;
	const string LotName = "G";
	const int TotalNoOfSpots = 100;
	static LotG* g_instance;
	vector<ParkingSpace*> pSpaceG;

	LotG()
	{
		isLotFull = false;

		for (int i = 0; i < TotalNoOfSpots; i++)
		{
			// Create parking space objects 
			pSpaceG.push_back(new ParkingSpace(100, 100, LotName, i+1));
		}
	}
public:
	string getLotName();

	int getTotalNoOfSpots();

	bool checkIsLotFull();

	static LotG* getInstance();

	int reserve(time_t startTime, time_t endTime);

	int getAvaialbleSlots(time_t startTime);

	int getNoOfTotallyBookedSpots();

	string getFirstAvailableSlot(int currHour, int currMin);

};

#endif