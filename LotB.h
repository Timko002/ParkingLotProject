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
			pSpaceB.push_back(new ParkingSpace(100, 100));
		}
	}
	public:
		string getLotName();
		
		int getTotalNoOfSpots();
		
		bool checkIsLotFull();
		
		static LotB* getInstance();
		
		bool reserve(time_t startTime, time_t endTime);
		
};

#endif