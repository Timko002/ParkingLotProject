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
	public:
		ParkingSpace(int x, int y)
		{
			dim_x = x;
			dim_y = y;

			isFull = false; // Read from DB 

			for (int i = 0; i <= AVAILABILITY_OF_TIME_SLOT; i++)
				timeSlot[i] = true; // Read from DB
		}

		bool checkIsFull();
		
		bool reserve(int start_hour, int start_min, int blocks);

		int getAvaialbleSlots(int start_hour, int start_min);
		
};
#endif