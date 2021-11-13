#ifndef LotD_H
#define LotD_H
#include <iostream>
#include <vector>
#include <ctime>
#include "ParkingLot.h"
#include "ParkingSpace.h"
using namespace std;

class LotD : public ParkingLot
{
	bool isLotFull;
	const string LotName = "D";
	const int TotalNoOfSpots = 150;
	static LotD* d_instance;
	vector<ParkingSpace*> pSpaceD;

	LotD()
	{
		isLotFull = false;

		for (int i = 0; i < TotalNoOfSpots; i++)
		{
			// Create parking space objects 
			pSpaceD[i] = new ParkingSpace(100, 100);
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
			if (!pSpaceD[i]->checkIsFull()) //if even one space is free, it is not full
			{
				isLotFull = false;
				return isLotFull;
			}
		}
		isLotFull = true;
		return isLotFull;
	}
	static LotD* getInstance()
	{
		if (!d_instance)
			d_instance = new LotD();
		return d_instance;
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
			if (pSpaceD[i]->reserve(start_hour, start_min, blocks))
			{
				reserve_flag = true;
				break;
			}
		}
		return reserve_flag;
	}

};
LotD* LotD::d_instance = 0;
#endif