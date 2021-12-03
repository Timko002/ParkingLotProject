#pragma once
#ifndef LotJ_H
#define LotJ_H
#include <iostream>
#include <vector>
#include <ctime>
#include "Lot.h"

using namespace std;
//concrete singleton LotJ
class LotJ : public Lot
{
	const string LotName = "J";
	const int TotalNoOfSpots = 100;
	static LotJ* j_instance;

	LotJ()
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

	static LotJ* getInstance();

};

#endif