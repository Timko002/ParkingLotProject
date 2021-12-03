#pragma once
#ifndef LotF_H
#define LotF_H
#include <iostream>
#include <vector>
#include <ctime>
#include "Lot.h"

using namespace std;
//concrete singleton LotF
class LotF : public Lot
{
	const string LotName = "F";
	const int TotalNoOfSpots = 100;
	static LotF* f_instance;

	LotF()
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

	static LotF* getInstance();

};

#endif