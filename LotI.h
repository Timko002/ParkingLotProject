#pragma once
#ifndef LotI_H
#define LotI_H
#include <iostream>
#include <vector>
#include <ctime>
#include "Lot.h"

using namespace std;
//concrete singleton LotI
class LotI : public Lot
{
	const string LotName = "I";
	const int TotalNoOfSpots = 100;
	static LotI* i_instance;

	LotI()
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

	static LotI* getInstance();

};

#endif