#pragma once
#ifndef LotF_H
#define LotF_H
#include <iostream>
#include <vector>
#include <ctime>
#include "ParkingLot.h"
#include "ParkingSpace.h"
using namespace std;

class LotF : public ParkingLot
{
	bool isLotFull;
	const string LotName = "F";
	const int TotalNoOfSpots = 200;
	static LotF* f_instance;
	vector<ParkingSpace*> pSpaceF;

	LotF()
	{
		isLotFull = false;

		for (int i = 0; i < TotalNoOfSpots; i++)
		{
			// Create parking space objects 
			pSpaceF.push_back(new ParkingSpace(100, 100));
		}
	}
public:
	string getLotName();

	int getTotalNoOfSpots();

	bool checkIsLotFull();

	static LotF* getInstance();

	bool reserve(time_t startTime, time_t endTime);

};

#endif