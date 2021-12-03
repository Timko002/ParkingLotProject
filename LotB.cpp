#pragma once

#include "LotB.h"
LotB* LotB::b_instance = 0;
string LotB::getLotName()
{
	return LotName;
}
int LotB::getTotalNoOfSpots()
{
	return TotalNoOfSpots;
}

LotB* LotB::getInstance()
{
	if (!b_instance)
		b_instance = new LotB();
	return b_instance;
}
