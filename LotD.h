#ifndef LotD_H
#define LotD_H
#include <iostream>
#include <vector>
#include <ctime>
#include "Lot.h"

using namespace std;
//concrete singleton LotD
class LotD : public Lot
{
	const string LotName = "D";
	const int TotalNoOfSpots = 100;
	static LotD* d_instance;

	LotD()
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

	static LotD* getInstance();

};

#endif