#pragma once
#ifndef ParkingLotFactory_H
#define ParkingLotFactory_H
#include <iostream>
#include <ctime>
#include "LotA.h"
#include "LotB.h"
#include "LotC.h"
#include "LotD.h"
#include "LotE.h"
#include "LotF.h"
#include "LotG.h"
#include "LotH.h"
#include "LotI.h"
#include "LotJ.h"
#include <string>
using namespace std;

class ParkingLotFactory
{
	public:
		ParkingLot* chooseParkingLot(string LotName);
};
#endif