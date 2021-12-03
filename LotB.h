#ifndef LotB_H
#define LotB_H
#include <iostream>
#include <vector>
#include <ctime>
#include "Lot.h"

using namespace std;
//concrete singleton LotB
class LotB : public Lot
{
	const string LotName = "B";
	const int TotalNoOfSpots = 100;
	static LotB* b_instance;

	LotB()
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

	static LotB* getInstance();

};

#endif