#pragma once
#ifndef LotJ_H
#define LotJ_H
#include <iostream>
#include <vector>
#include <ctime>
#include "ParkingLot.h"
#include "ParkingSpace.h"
using namespace std;

class LotJ : public ParkingLot
{
	bool isLotFull;
	const string LotName = "J";
	const int TotalNoOfSpots = 100;
	static LotJ* j_instance;
	vector<ParkingSpace*> pSpaceJ;

	LotJ()
	{
		isLotFull = false;

		for (int i = 0; i < TotalNoOfSpots; i++)
		{
			// Create parking space objects 
			pSpaceJ.push_back(new ParkingSpace(100, 100, LotName, i+1));
		}
	}
public:
	string getLotName();

	int getTotalNoOfSpots();

	bool checkIsLotFull();

	static LotJ* getInstance();

	int reserve(time_t startTime, time_t endTime);

	int getAvaialbleSlots(time_t startTime);

	int getNoOfTotallyBookedSpots();

};

#endif