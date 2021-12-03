#pragma once
#ifndef LotG_H
#define LotG_H
#include <iostream>
#include <vector>
#include <ctime>
#include "Lot.h"

using namespace std;
//concrete singleton LotG
class LotG : public Lot
{
	const string LotName = "G";
	const int TotalNoOfSpots = 100;
	static LotG* g_instance;

	LotG()
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

	static LotG* getInstance();

};

#endif