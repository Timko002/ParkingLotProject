#pragma once
#ifndef ParkingSpace_H
#define ParkingSpace_H
#include <iostream>
#define AVAILABILITY_OF_TIME_SLOT 36
using namespace std;
class ParkingSpace
{

	int dim_x;
	int dim_y;
	bool isFull;
	bool timeSlot[AVAILABILITY_OF_TIME_SLOT+1];
	string LotName;
	int SpaceNo;
	public:
		ParkingSpace(int x, int y, string Lot, int Space)
		{
			dim_x = x;
			dim_y = y;
			LotName = Lot;
			SpaceNo = Space;
			//for (int i = 0; i <= AVAILABILITY_OF_TIME_SLOT; i++)
			//	timeSlot[i] = true;
			
		}

		bool checkIsFull();
		
		bool reserve(int start_hour, int start_min, int blocks);

		int getAvaialbleSlots(int start_hour, int start_min);
		
};
#endif