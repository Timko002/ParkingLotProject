#pragma once
#ifndef ParkingLot_H
#define ParkingLot_H
#include <iostream>
using namespace std;

class ParkingLot
{
public:
	virtual void reserve() = 0;
	virtual string getLotName() = 0;
	virtual bool checkIsLotFull() = 0;

};
#endif