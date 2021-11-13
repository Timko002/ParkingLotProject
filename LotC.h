#ifndef LotC_H
#define LotC_H
#include <iostream>
#include <vector>
#include <ctime>
#include "ParkingLot.h"
#include "ParkingSpace.h"
using namespace std;

class LotC : public ParkingLot
{
	bool isLotFull;
	const string LotName = "B";
	const int TotalNoOfSpots = 100;
	static LotC* c_instance;
	vector<ParkingSpace*> pSpaceC;

	LotC()
	{
		isLotFull = false;

		for (int i = 0; i < TotalNoOfSpots; i++)
		{
			// Create parking space objects 
			pSpaceC[i] = new ParkingSpace(100, 100);
		}
	}
public:
	string getLotName()
	{
		return LotName;
	}
	int getTotalNoOfSpots()
	{
		return TotalNoOfSpots;
	}
	bool checkIsLotFull()
	{
		for (int i = 0; i < pSpace.size(); i++)
		{
			if (!pSpaceC[i]->checkIsFull()) //if even one space is free, it is not full
			{
				isLotFull = false;
				return isLotFull;
			}
		}
		isLotFull = true;
		return isLotFull;
	}
	static LotC* getInstance()
	{
		if (!c_instance)
			c_instance = new LotC();
		return c_instance;
	}
	bool reserve(time_t startTime, time_t endTime)
	{
		tm* st = gmtime(&startTime);
		int start_hour = st->tm_hour;
		int start_min = st->tm_min;
		bool reserve_flag = false;
		double blocks = difftime(endTime, startTime) / 900;

		for (int i = 0; i < pSpace.size(); i++)
		{
			if (pSpaceC[i]->reserve(start_hour, start_min, blocks))
			{
				reserve_flag = true;
				break;
			}
		}
		return reserve_flag;
	}

};
LotC* LotC::c_instance = 0;
#endif