#pragma once
#ifndef LotE_H
#define LotE_H
#include <iostream>
#include <vector>
#include <ctime>
#include "Lot.h"

using namespace std;
//concrete singleton LotE
class LotE : public Lot
{
	const string LotName = "E";
	const int TotalNoOfSpots = 100;
	static LotE* e_instance;

	LotE()
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

	static LotE* getInstance();

};

#endif