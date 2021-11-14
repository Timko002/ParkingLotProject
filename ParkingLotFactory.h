#pragma once
#ifndef ParkingLotFactory_H
#define ParkingLotFactory_H
#include <iostream>
#include <ctime>
#include "LotA.h"
#include "LotB.h"
#include "LotC.h"
#include "LotD.h"
using namespace std;

class ParkingLotFactory
{
	public:
		ParkingLot * chooseParkingLot(string LotName);
};

ParkingLot* ParkingLotFactory::chooseParkingLot(string LotName)
{
	ParkingLot* Lot;
	if (LotName == "A")
		Lot = LotA::getInstance();
	else
		if (LotName == "B")
			Lot = LotB::getInstance();
		else
			if (LotName == "C")
				Lot = LotC::getInstance();
			else
				if (LotName == "D")
					Lot = LotD::getInstance();
				else
					Lot = NULL;
	return Lot;
}
#endif