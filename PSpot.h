#ifndef PSPOT_H
#define PSPOT_H
#include <iostream>
#include <ctime>
#include <chrono>
#include "PSpotComponent.h"

using namespace std;

class PSpot : public PSpotComponent
{
	bool isReserved = false;
	time_t timeStamp;
	int spotId;

	public:
		PSpot(int id)
		{
			spotId = id;
			timeStamp = time(0);
		}
		void reserveSpot(time_t reservedTimeStamp)
		{
			timeStamp = reservedTimeStamp;
			isReserved = true;
		}
		void spotDetails()
		{
			cout << "status: " << isReserved << " | Duration: " << timeStamp << endl;
		}
};

#endif // !PSPOT_H