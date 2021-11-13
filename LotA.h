#ifndef LotA_H
#define LotA_H
#include <iostream>
#include <vector>
#include <ctime>
#include "ParkingLot.h"
#include "ParkingSpace.h"
using namespace std;

class LotA : public ParkingLot
{
	bool isLotFull;
	const string LotName = "A";
	const int TotalNoOfSpots = 100;
	static LotA* a_instance;
	vector<ParkingSpace*> pSpaceA;

	LotA()
	{
		isLotFull = false;

		for (int i = 0; i < TotalNoOfSpots; i++)
		{
			// Create parking space objects 
			pSpaceA[i] = new ParkingSpace(100, 100);
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
			if (!pSpaceA[i]->checkIsFull()) //if even one space is free, it is not full
			{
				isLotFull = false;
				return isLotFull;
			}
		}
		isLotFull = true;
		return isLotFull;
	}
	static LotA* getInstance()
	{
		if (!a_instance)
			a_instance = new LotA();
		return a_instance;
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
			if (pSpaceA[i]->reserve(start_hour, start_min, blocks))
			{
				reserve_flag = true;
				break;
			}
		}
		return reserve_flag;
	}

};
LotA* LotA::a_instance = 0;
#endif