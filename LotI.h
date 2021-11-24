#pragma once
#ifndef LotI_H
#define LotI_H
#include <iostream>
#include <vector>
#include <ctime>
#include "ParkingLot.h"
#include "ParkingSpace.h"
using namespace std;

class LotI : public ParkingLot
{
	bool isLotFull;
	const string LotName = "I";
	const int TotalNoOfSpots = 200;
	static LotI* i_instance;
	vector<ParkingSpace*> pSpaceI;

	LotI()
	{
		isLotFull = false;

		for (int i = 0; i < TotalNoOfSpots; i++)
		{
			// Create parking space objects 
			pSpaceI.push_back(new ParkingSpace(100, 100));
		}
	}
public:
	string getLotName();

	int getTotalNoOfSpots();

	bool checkIsLotFull();

	static LotI* getInstance();

	bool reserve(time_t startTime, time_t endTime);

};

#endif