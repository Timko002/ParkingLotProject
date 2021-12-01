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
			pSpaceD.push_back(new ParkingSpace(100, 100, LotName, i));
		}
	}
public:
	string getLotName();
	
	int getTotalNoOfSpots();
	
	bool checkIsLotFull();
	
	static LotD* getInstance();
	
	bool reserve(time_t startTime, time_t endTime);

	int getAvaialbleSlots(time_t startTime);

};

#endif