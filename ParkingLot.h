#pragma once
#ifndef ParkingLot_H
#define ParkingLot_H
#include <iostream>
using namespace std;

class ParkingLot
{
public:
	virtual bool reserve(time_t startTime, time_t endTime) = 0;
	virtual string getLotName() = 0;
	virtual bool checkIsLotFull() = 0;

};
#endif