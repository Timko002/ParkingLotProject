#pragma once
#ifndef LotE_H
#define LotE_H
#include <iostream>
#include <vector>
#include <ctime>
#include "ParkingLot.h"
#include "ParkingSpace.h"
using namespace std;

class LotE : public ParkingLot
{
	bool isLotFull;
	const string LotName = "E";
	const int TotalNoOfSpots = 100;
	static LotE* e_instance;
	vector<ParkingSpace*> pSpaceE;

	LotE()
	{
		isLotFull = false;

		for (int i = 0; i < TotalNoOfSpots; i++)
		{
			// Create parking space objects 
			pSpaceE.push_back(new ParkingSpace(100, 100, LotName, i+1));
		}
	}
public:
	string getLotName();

	int getTotalNoOfSpots();

	bool checkIsLotFull();

	static LotE* getInstance();

	int reserve(time_t startTime, time_t endTime);

	int getAvaialbleSlots(time_t startTime);

	int getNoOfTotallyBookedSpots();

};

#endif

