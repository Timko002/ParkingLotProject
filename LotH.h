#pragma once
#ifndef LotH_H
#define LotH_H
#include <iostream>
#include <vector>
#include <ctime>
#include "ParkingLot.h"
#include "ParkingSpace.h"
using namespace std;

class LotH : public ParkingLot
{
	bool isLotFull;
	const string LotName = "H";
	const int TotalNoOfSpots = 200;
	static LotH* h_instance;
	vector<ParkingSpace*> pSpaceH;

	LotH()
	{
		isLotFull = false;

		for (int i = 0; i < TotalNoOfSpots; i++)
		{
			// Create parking space objects 
			pSpaceH.push_back(new ParkingSpace(100, 100));
		}
	}
public:
	string getLotName();

	int getTotalNoOfSpots();

	bool checkIsLotFull();

	static LotH* getInstance();

	bool reserve(time_t startTime, time_t endTime);

};

#endif

