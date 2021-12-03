#ifndef LotA_H
#define LotA_H
#include <iostream>
#include <vector>
#include <ctime>
#include "Lot.h"

using namespace std;
//concrete singleton LotA
class LotA : public Lot
{
	const string LotName = "A";
	const int TotalNoOfSpots = 100;
	static LotA* a_instance;

	LotA()
	{
		for (int i = 0; i < TotalNoOfSpots; i++)
		{
			// Create parking space objects 
			pSpace.push_back(new ParkingSpace(100, 100, LotName,i+1));
		}
	}

public:	
	string getLotName();

	int getTotalNoOfSpots();

	static LotA* getInstance();

};

#endif