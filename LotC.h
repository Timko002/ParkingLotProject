#ifndef LotC_H
#define LotC_H
#include <iostream>
#include <vector>
#include <ctime>
#include "Lot.h"

using namespace std;
//concrete singleton LotC
class LotC : public Lot
{
	const string LotName = "C";
	const int TotalNoOfSpots = 100;
	static LotC* c_instance;

	LotC()
	{
		for (int i = 0; i < TotalNoOfSpots; i++)
		{
			// Create parking space objects 
			pSpace.push_back(new ParkingSpace(100, 100, LotName, i + 1));
		}
	}

public:
	string getLotName();

	int getTotalNoOfSpots();

	static LotC* getInstance();

};

#endif