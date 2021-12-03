#pragma once
#ifndef LotH_H
#define LotH_H
#include <iostream>
#include <vector>
#include <ctime>
#include "Lot.h"

using namespace std;
//concrete singleton LotH
class LotH : public Lot
{
	const string LotName = "H";
	const int TotalNoOfSpots = 100;
	static LotH* h_instance;

	LotH()
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

	static LotH* getInstance();

};

#endif