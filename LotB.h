#ifndef LotB_H
#define LotB_H
#include <iostream>
#include <vector>
#include <ctime>
#include "ParkingLot.h"
#include "ParkingSpace.h"
using namespace std;

class LotB : public ParkingLot
{
	bool isLotFull;
	const string LotName="B";
	const int TotalNoOfSpots=100;
	static LotB* b_instance;
	vector<ParkingSpace *> pSpaceB;

	LotB()
	{	
		isLotFull = false;

		for (int i = 0; i < TotalNoOfSpots; i++)
		{
			// Create parking space objects 
			pSpaceB[i] = new ParkingSpace(100, 100);
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
				if (!pSpaceB[i]->checkIsFull()) //if even one space is free, it is not full
				{
					isLotFull = false;
					return isLotFull;
				}
			}
			isLotFull = true;
			return isLotFull;
		}
		static LotB* getInstance()
		{
			if (!b_instance)
				b_instance = new LotB();
			return b_instance;
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
				if (pSpaceB[i]->reserve(start_hour, start_min, blocks))
				{
					reserve_flag = true;
					break;
				}
			}
			return reserve_flag;
		}

};
LotB* LotB::b_instance = 0;
#endif