#pragma once

#include "LotD.h"
LotD* LotD::d_instance = 0;
string LotD::getLotName()
{
	return LotName;
}
int LotD::getTotalNoOfSpots()
{
	return TotalNoOfSpots;
}

LotD* LotD::getInstance()
{
	if (!d_instance)
		d_instance = new LotD();
	return d_instance;
}

// !LotD